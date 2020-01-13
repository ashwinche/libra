#include "pipeline.h"
#include <chrono> 
#include <iostream>
#include <glm/glm.hpp>
#include <stdio.h>
#include <string.h>
#include <set>
#include <queue>
#include <limits>
#include <queue>
#include <SFML/Graphics.hpp>

#include "blobmath.h"


using namespace std::chrono; 
using namespace std;

static void tick(std::string text){
  static auto clock = high_resolution_clock::now();
  auto next = high_resolution_clock::now();
  long d = duration_cast<milliseconds>(next-clock).count();
  printf("%s",text.c_str());
  printf(">> elapsed %lums\n\n",d);
  clock = next;
}
ReprMode::ReprMode(const char *name){
  this->name = name;
  this->geom = "none";
  blob.scale = 0;
  timestep   = 0;
  highlight.blobs = std::vector<ScaleBlob*>();
  highlight.lines = std::vector<vec3>();
  highlight.paths = std::vector<std::vector<ScaleBlob*>>();
  highlight.timestep = -1;
  highlight.locus    = vec3(0,0,0);
  highlight.path_smooth_alpha = 0.7f;
}
bool ReprMode::operator==(ReprMode &r){
  return (name == r.name) && (timestep == r.timestep)
    && ((blob.scale == r.blob.scale));
}
ArPipeline::ArPipeline(ArExperiment *exp){
  this->exp = exp;
  for(int i=0;i<exp->high-exp->low+1;i++){
    ArFrameData data;
    data.blob     = 0;
    data.complete = false;
    frames.push_back(data);
  }
  store.nbuf = 3;
  store.buf  = new Nrrd*[store.nbuf];
  for(int i=0;i<store.nbuf;++i){
    store.buf[i] = exp->copy(0);
  }
  store.init = true;

  filter.init(store.buf[0]);
}
ArFrameData &ArPipeline::get(int frame){
  return frames[frame - exp->low];
}
int ArPipeline::low(){
  return exp->low;
}
int ArPipeline::high(){
  return exp->high;
}

static std::vector<float> collect_scales(ScaleBlob *blob){
  std::set<float> scales;
  std::queue<ScaleBlob*> queue;
  queue.push(blob);
  while(!queue.empty()){
    blob = queue.front();
    queue.pop();
    scales.insert(blob->scale);
    for(ScaleBlob *child : blob->children){
      queue.push(child);
    }
  }
  scales.erase(0);
  return std::vector<float>(scales.begin(), scales.end());
}
static float compute_epsilon(std::vector<float> &v){
  if(v.size() < 2)return 0;
  float eps = fabs(v[1] - v[0]);
  for(int i=1;i<v.size();++i){
    eps = fmin(eps, fabs(v[i]-v[i-1]));
  }
  return eps/2.f;
}

void ArPipeline::repr_highlight(ReprMode *rm, vec3 p, vec3 ray, bool diagnose, bool add){
  if(get(rm->timestep).complete){
    // printf("highlight along (%.2f %.2f %.2f) + (%.2f %.2f %.2f)\n",p.x,p.y,p.z, ray.x,ray.y,ray.z);
    ray = normalize(ray)*3.f;
    std::vector<ScaleBlob*> found;
    ArFrameData frame = get(rm->timestep);
    BSPTree<ScaleBlob> *bsptree = &(frame.bspblobs);

    // shoot ray out until it hits a blob.
    for(int i=0;i<100 && found.size()==0;++i){
      p+=ray;
      bsptree->find_within_distance(found, p, i+1);
      if(found.size()>0 && !diagnose){
        if(diagnose){
          printf("highlight blob %p:\n", found[0]);
          found[0]->print();
        }
        if(!add){
          rm->highlight.highlight_loci.clear();
        }
        rm->highlight.highlight_loci.push_back(found[0]);

        found = std::vector<ScaleBlob*>();
        bsptree->find_within_distance(found, p, 625);
      }
    }

    if(diagnose){
      // lots of various diagnostic information...
    }

    if(!add)rm->highlight.blobs.clear();
    for(int i=0;i<found.size();i++)rm->highlight.blobs.push_back(found[i]);

    rm->highlight.paths.clear();
    for(std::vector<ScaleBlob*> path : paths){
      for(ScaleBlob *blob : path){
        if(glm::distance(vec3(blob->position), p) < 25){
          rm->highlight.paths.push_back(path);
          break;
        }
      }
    }
    rm->highlight.locus = p;
    rm->highlight.timestep = rm->timestep;
    // rm->highlight.paths = longest_paths(rm->highlight.blobs);
    // printf("highlight %d\n",found.size());
  }
  // rm->highlight.lines.push_back(p+ray*1.f);
  // rm->highlight.lines.push_back(p+ray*100.f);
}

ReprMode ArPipeline::repr_coarser(ReprMode rm){
  std::vector<float> scales = get(rm.timestep).scales;
  ++rm.blob.scale;
  if(rm.blob.scale < 0)rm.blob.scale = 0;
  if(rm.blob.scale >= scales.size()) rm.blob.scale = scales.size()-1;
  return rm;
}
ReprMode ArPipeline::repr_finer(ReprMode rm){
  std::vector<float> scales = get(rm.timestep).scales;
  --rm.blob.scale;
  if(rm.blob.scale < 0)rm.blob.scale = 0;
  if(rm.blob.scale >= scales.size()) rm.blob.scale = scales.size()-1;
  return rm;
}

static std::vector<ScaleBlob*> collect_blobs(ScaleBlob *blob, float scalemin, float scalemax){
  // scalemin = -1000;
  // scalemax = 10000;
  // printf("(");
  std::vector<ScaleBlob*> blobs;
  if(blob->scale >= scalemin || blob->scale == 0){
    if(blob->scale <= scalemax || blob->scale == 0){
      // printf(".");
      blobs.push_back(blob);      
    }
    for(ScaleBlob *child : blob->children){
      std::vector<ScaleBlob*> childblobs = collect_blobs(child, scalemin, scalemax);
      blobs.insert(blobs.end(), childblobs.begin(), childblobs.end());
    }
  }
  // printf(")");
  return blobs;
}

/* find all paths in the part of the dataset that has been
 * processed so far, so long as the path is greater than
 * minlen in length.
 *
 */
void ArPipeline::find_paths(int minlen){
  std::vector<ScaleBlob*> allblobs;
  for(int i=0;i<frames.size();i++){   // for each frame
    if(frames[i].complete){           // if it is processed
                                      // collect blobs
      std::vector<ScaleBlob*> blobsi = collect_blobs(frames[i].blob, 0, std::numeric_limits<float>::infinity());
      allblobs.insert(allblobs.end(), blobsi.begin(), blobsi.end());
      // minlen = int(i*0.75);
    }
  }
  printf("find paths > %d.\n", minlen);
  printf("find paths in %d blobs.\n", allblobs.size());
  std::vector<std::vector<ScaleBlob*>> allpaths = longest_paths(allblobs, minlen);
  paths.clear();
  for(int i=0;i<allpaths.size();++i){
    if(allpaths[i].size() > minlen){
      paths.push_back(allpaths[i]);
    }
  }
  printf("found %d paths.\n", paths.size());
}

/* store.buf[0] contains the output of the filter chain.
 * store.buf[1] contains the output of repr().
 */
void ArPipeline::process(int low, int high){
  if(high > exp->high){
    high = exp->high;
    printf("pipeline.process, low=%d, high=%d\n", low, high);
  }
  for(int frame=low;frame<=high;frame++){
    printf("pipeline.process %d\n",frame);
    tick("");

    // THIS CAN BE PARALLALIZED {
        // ARFilter filter;
        filter.capture(exp->get(frame));
        // printf("process %d\n", frame)
        ScaleBlob *blob             = filter.compute_blob_tree();


        std::vector<float> scales   = collect_scales(blob);
        frames[frame - exp->low].blob      = blob;
        frames[frame - exp->low].scales    = scales;
        frames[frame - exp->low].scale_eps = compute_epsilon(scales);
        frames[frame - exp->low].complete  = true;
        frames[frame - exp->low].bspblobs  = filter.get_bsp(10);

        BSPTree<ScaleBlob> *bsptree = &frames[frame - exp->low].bspblobs;
        std::vector<ScaleBlob*> allblobs = collect_blobs(blob, 0, std::numeric_limits<float>::infinity());
        
        for(ScaleBlob *sb : allblobs){
          bsptree->insert(sb, sb->position);
        }

    // } THIS CAN BE PARALLELIZED

    // link with previous frame.
    printf("linking.\n");
    if(frame-1 >= this->low() && get(frame-1).complete){
      BSPTree<ScaleBlob> *t0 = &frames[ frame - exp->low -1 ].bspblobs;
      BSPTree<ScaleBlob> *t1 = &frames[ frame - exp->low    ].bspblobs;

      std::vector<ScaleBlob*> v0 = t0->as_vector();
      int itr = 0;
      for(ScaleBlob *sb : v0){
        std::vector<ScaleBlob*> potential;
        t1->find_within_distance(potential, sb->position, 1000.f);
        for(int i=0;i<potential.size();i++){

          //  *** NOTE ***
          // 1.0 means touching. I don't know what 2.0 means. This is somewhat
          // arbitrary, but we notice that in the data, sometimes successor
          // blobs aren't touching predecessor blobs, so we need a small margin.
          // In any case, we next want to choose the potential successor with
          // the smallest distance and closest scale.
          //  *** **** ***

          if(sb->n>1 && potential[i]->n>1 && sb->distance(potential[i]) <= 2.f){
            // if(sb->detCov/potential[i]->detCov < 2.f && potential[i]->detCov/sb->detCov < 2.f){
              // volume cannot more than double or half.
              sb->succ.push_back(potential[i]);
              potential[i]->pred.push_back(sb);
            // }
          }
          // printf("%d.", i);
        }
        // printf("o");
        ++itr;
        // for(ScaleBlob *sb0 : sb->succ){
        //   sb0->pred.push_back(sb);
        // }
      }
    }
    tick("done.\n");
  }
  filter.commit(store.buf[2]);
}

ArGeometry3D* ArPipeline::reprgeometry(ReprMode &mode){
  geometry.lines = std::vector<vec3>();
  geometry.lines_c = std::vector<sf::Color>();
  // printf("mode %s\n", mode.geom);
  if(!strcmp(mode.geom, "graph") || !strcmp(mode.geom, "paths") || !strcmp(mode.geom, "succs")){
    if(get(mode.timestep).complete){
      ArFrameData frame = get(mode.timestep);
      float scalemin = frame.scales[mode.blob.scale] - frame.scale_eps;
      float scalemax = frame.scales[mode.blob.scale] + frame.scale_eps;
      std::vector<ScaleBlob*> blobs;

      // if(!strcmp(mode.name, "plain")){
      //   blobs = collect_blobs(frame.blob, 0, std::numeric_limits<float>::infinity());
      // }else{
      //   blobs = collect_blobs(frame.blob, scalemin, scalemax);
      // }


      if(!strcmp(mode.geom, "graph")){
        // draw scale hierarchy:
        blobs = collect_blobs(frame.blob, 0, std::numeric_limits<float>::infinity());
        for(ScaleBlob *sb : mode.highlight.blobs){
        // for(ScaleBlob *sb : blobs){
          // for(ScaleBlob *succ : sb->succ){
          //   geometry.lines.push_back(sb->position);
          //   geometry.lines.push_back(succ->position);
          //   geometry.lines_c.push_back(sf::Color(255,255,255,120));
          //   geometry.lines_c.push_back(sf::Color(255,255,255,120));
          // }
          // for(ScaleBlob *pred : sb->pred){
          //   geometry.lines.push_back(sb->position);
          //   geometry.lines.push_back(pred->position);
          //   geometry.lines_c.push_back(sf::Color(80,80,80,80));
          //   geometry.lines_c.push_back(sf::Color(80,80,80,80));
          // }
          if(sb->parent){
            geometry.lines.push_back(sb->position);
            geometry.lines.push_back(sb->parent->position);
            geometry.lines_c.push_back(sf::Color(0,0,255,150));
            geometry.lines_c.push_back(sf::Color(0,0,255,150));
          }
        }
      }


      // draw trajectory of highlighted blobs
      if(!mode.highlight.blobs.empty()){
        // std::queue<ScaleBlob*> traverse;
        // for(int i=0;i<mode.highlight.blobs.size();++i){
        //   traverse.push(mode.highlight.blobs[i]);
        // }
        // while(!traverse.empty()){
        //   ScaleBlob* curr = traverse.front();
        //   traverse.pop();
        //   for(ScaleBlob *succ : curr->succ){
        //     traverse.push(succ);
        //     geometry.lines.push_back(curr->position);
        //     geometry.lines.push_back(succ->position);
        //     geometry.lines_c.push_back(sf::Color(255,255,255,120));
        //     geometry.lines_c.push_back(sf::Color(255,255,255,120));
        //   }
        // }

        // // draw all branches in white.
        // for(std::vector<ScaleBlob*> path : paths){
        //   for(int j=0;j<path.size()-1;j++){
        //     for(int k=0;k<path[j]->succ.size();k++){
        //       geometry.lines.push_back(path[j]->position);
        //       geometry.lines.push_back(path[j]->succ[k]->position);
        //       geometry.lines_c.push_back(sf::Color::White);
        //       geometry.lines_c.push_back(sf::Color::White);
        //     }
        //   }
        // }

        // draw the longest trajectories.
        double path_smooth_beta = 1.f - mode.highlight.path_smooth_alpha;
        for(std::vector<ScaleBlob*> path : mode.highlight.paths){
          float len  = float(path.size());
          float step = 1.f/len;
          glm::dvec3 weightedp = path[0]->position;
          for(int j=0;j<path.size()-1;j++){
            // geometry.lines.push_back(path[j]->position);
            // geometry.lines.push_back(path[j+1]->position);
            geometry.lines.push_back(weightedp);
            glm::dvec3 weightedq = path[j+1]->position;
            
            weightedp = (weightedp * mode.highlight.path_smooth_alpha) + (weightedq * path_smooth_beta);

            geometry.lines.push_back(weightedp);
            int r0 = 0   + int(200.f * step * j    );
            int g0 = 155 + int(100.f * step * j    );
            int b0 = 255 - int(250.f * step * j    );
            int r1 = 0   + int(200.f * step * (j+1));
            int g1 = 155 + int(100.f * step * (j+1));
            int b1 = 255 - int(250.f * step * j    );
            geometry.lines_c.push_back(sf::Color(r0,g0,b0,255));
            geometry.lines_c.push_back(sf::Color(r1,g1,b1,255));
          }
        }
      }
      // draw successors and predecessors:
      if(!strcmp(mode.geom, "succs")){
        float scalemin = frame.scales[mode.blob.scale] - frame.scale_eps;
        float scalemax = frame.scales[mode.blob.scale] + frame.scale_eps;
        // blobs = collect_blobs(frame.blob, 0, std::numeric_limits<float>::infinity());
        // blobs = collect_blobs(frame.blob, scalemin, scalemax);
        for(ScaleBlob *sb : mode.highlight.blobs){
        // for(ScaleBlob *sb : blobs){
          // if(sb->scale < scalemin || sb->scale > scalemax)continue;
          for(ScaleBlob *succ : sb->succ){
            geometry.lines.push_back(sb->position);
            geometry.lines.push_back(succ->position);
            geometry.lines_c.push_back(sf::Color(255,255,255,200));
            geometry.lines_c.push_back(sf::Color(255,255,255,200));
          }
          for(ScaleBlob *pred : sb->pred){
            geometry.lines.push_back(sb->position);
            geometry.lines.push_back(pred->position);
            geometry.lines_c.push_back(sf::Color(0,40,0,200));
            geometry.lines_c.push_back(sf::Color(0,40,0,200));
          }
        }
      }
    }
  }

  for(vec3 v : mode.highlight.lines){
    geometry.lines.push_back(v);
    geometry.lines_c.push_back(sf::Color::Yellow);
  }

  return &geometry;
}
/**
 * Chooses how to represent the volume-rendered data.
 * Eg. we may represent the data as:
 *   - "plain"     : raw data
 *   - "blobs"     : depicting the blobs recovered from the data
 *   - "gaussian"  : rendering a blurred version of the data at some sigma
 *   - "laplacian" : laplacian of gaussian filter at some sigma
*/
Nrrd *ArPipeline::repr(ReprMode &mode, bool force){
  if(mode.timestep < exp->low)mode.timestep = exp->low;
  if(mode.timestep > exp->high)mode.timestep = exp->high;
  if(!strcmp(mode.name, "plain")){
    // plain representation is simple and is always allowed.
    // default to plain if there the frame has not been processed yet.
    // printf("repr plain\n");
    return exp->get(mode.timestep);
  }
  if(!strcmp(mode.name, "filter residue")){
    printf("repr %s\n", mode.name);
    return store.buf[2];
  }
  if(!strcmp(mode.name, "filter internal")){
    printf("repr %s\n", mode.name);
    return store.buf[0];
  }
  if(!strcmp(mode.name, "flow")){
    printf("repr %s\n", mode.name);
    Flow flow;
    return store.buf[0];
  }
  if(!strcmp(mode.name, "sandbox")){
    filter.capture(exp->get(mode.timestep));
    // filter.clear();
    // std::vector<ScaleBlob*> blobs;
    // ScaleBlob *a = new ScaleBlob();
    // a->pass(vec3(10,10,10), 10);
    // a->pass(vec3(15,15,15), 30);
    // a->pass(vec3(10,20,20), 10);
    // a->commit();
    // blobs.push_back(a);
    // filter.draw_blobs(blobs, false);
    filter.max1();
    filter.normalize(3.f);
    filter.commit(store.buf[1]);
    return store.buf[1];
  }
  if(!get(mode.timestep).complete){
    return exp->get(mode.timestep);
  }

  static ReprMode last_repr("");
  static Nrrd *last_nrrd;
  if(mode == last_repr && !force){
    // printf("repr %s unchanged.\n",mode.name);
    return last_nrrd;
  }
  last_repr  = mode;
  // printf("repr %s\n",mode.name);
  if(!strcmp(mode.name, "blobs") || !strcmp(mode.name, "blobs_succs")){
    ArFrameData frame = get(mode.timestep);
    float scalemin = frame.scales[mode.blob.scale] - frame.scale_eps;
    float scalemax = frame.scales[mode.blob.scale] + frame.scale_eps;
    // printf("mode %s. view scale %d with %.2f %.2f\n", mode.name, scalemin, scalemax);
    std::vector<ScaleBlob*> blobs = collect_blobs(frame.blob, scalemin, scalemax);
    
    // draw the blobs in paths at the current timestep.
    // if(!strcmp(mode.geom, "paths")){
    //   for(std::vector<ScaleBlob*> path : mode.highlight.paths){
    //     if(mode.timestep < path.size()){
    //       blobs.push_back(path[mode.timestep]);
    //     }
    //   }
    // }

    // printf("\n");
    filter.clear();
    for(int i=0;i<mode.highlight.highlight_loci.size();i++){
      blobs.push_back(mode.highlight.highlight_loci[i]);
    }
    // blobs.push_back(mode.highlight.highlight_loci);
    // blobs.insert(blobs.end(), mode.highlight.highlight_loci.begin(), mode.highlight.highlight_loci.end());
    filter.draw_blobs(blobs, true);

    // for(ScaleBlob *sb : mode.highlight.blobs){
    if(mode.highlight.highlight_loci.size() > 0){
      printf("highlight %d; scale = %.2f \n", mode.highlight.highlight_loci.size(), mode.highlight.highlight_loci[0]->scale);
      filter.color_blobs(mode.highlight.highlight_loci, 2.f);
    }
    if(mode.highlight.highlight_loci.size() > 1){
      int i=0;
      int j=0;
      for(int i=0;i<mode.highlight.highlight_loci.size();++i){
        for(int j=0;j<mode.highlight.highlight_loci.size();++j){
          printf("  distance %d %d -- %.4f\n", i, j, 
            mode.highlight.highlight_loci[i]
              ->distance(
            mode.highlight.highlight_loci[j])
            );
        }
      }
    }
    // }

    // show all successors of  blob.
    if(!strcmp(mode.name, "blobs_succs")){
      BSPTree<ScaleBlob> *t1 = &frames[ mode.highlight.timestep - exp->low    ].bspblobs;
      std::vector<ScaleBlob*> succs;
      for(ScaleBlob *sb : mode.highlight.blobs){
        std::vector<ScaleBlob*> potential;
        t1->find_within_distance(potential, sb->position, 1000.f);
        for(int i=0;i<potential.size();i++){
          if(sb->n>1 && potential[i]->n>1 && sb->distance(potential[i]) <= 1.f){
            // if(sb->detCov/potential[i]->detCov < 2.f && potential[i]->detCov/sb->detCov < 2.f){
              // volume cannot more than double or half.
              succs.push_back(potential[i]);
              potential[i]->pred.push_back(sb);
            // }
          }
          // printf("%d.", i);
        }
      }
      filter.color_blobs(succs, 4.f);
    }
    filter.commit(store.buf[1]);
    return (last_nrrd = store.buf[1]);
  }
  if(!strcmp(mode.name, "gaussian")){
    // printf("mode %s.\n", mode.name);
    ArFrameData frame = get(mode.timestep);
    float scale = frame.scales[mode.blob.scale];
    filter.capture(exp->get(mode.timestep));
    DiscreteKernel kernel = filter.gaussian(scale, int(scale*4));
    filter.set_kernel(kernel);
    filter.max1();
    filter.filter();
    filter.commit(store.buf[1]);
    kernel.destroy();
    return (last_nrrd = store.buf[1]);
  }
  if(!strcmp(mode.name, "laplacian")){
    // printf("mode %s.\n", mode.name);
    ArFrameData frame = get(mode.timestep);
    float scale = frame.scales[mode.blob.scale];
    filter.capture(exp->get(mode.timestep));
    DiscreteKernel kernel = filter.gaussian(scale, int(scale*4));
    filter.set_kernel(kernel);
    filter.max1();
    filter.filter();
    filter.laplacian3d();
    filter.normalize();
    filter.commit(store.buf[1]);
    kernel.destroy();
    return (last_nrrd = store.buf[1]);
  }
}


  /* Save/Load processed pipeline. format:
   * filename as [filepath_0].pipeline
   * [int] number of frames processed sequentially from 0.
   * <list of blobs:
   *    [int] address of blob
   *    ... data ...
   * 
   * >
   */

void ArPipeline::save(){

#define WRITET(T, x) {T xx = (T)x; fwrite(&(xx), sizeof(T), 1, file);}
#define WRITE(x)    {fwrite(&(x), sizeof(x), 1, file);}

  std::string path0 = exp->getfilepath(exp->low);
  std::replace(path0.begin(), path0.end(), '/', '-');
  path0 = "../rsc/store/s" + path0;

  printf("writing to : %s\n", path0.c_str());

  FILE *file = fopen((path0 + ".pipeline").c_str(),"wb");

  // fwrite("hello!",sizeof(char),6,file);

  // count number of frames that are processed.
  int nframes = 0;
  for(int i=0;i<frames.size();i++){
    if(!frames[i].complete){
      break;
    }else{
      nframes = i+1;
    }
  }

  WRITET(int, nframes);

  for(int i=0;i<nframes;++i){
    // fwrite("ff", sizeof(char), 2, file);
    // write address of root scaleblob.
    WRITET(ScaleBlob*, frames[i].blob);
    // fwrite(&frames[i].blob, sizeof(ScaleBlob*), 1, file);
    std::vector<ScaleBlob*> allblobs = frames[i].bspblobs.as_vector();
    
    // write total number of blobs in this frame.
    WRITET(int, allblobs.size());
    // fwrite(&nblobs, sizeof(int), 1, file);

    for(ScaleBlob *sb : allblobs){
      // write each blob
      WRITET(ScaleBlob*, sb);

      WRITET(int, sb->children.size());
      for(ScaleBlob *s : sb->children){
        WRITE(s);
      }

      WRITET(int, sb->pred.size());
      for(ScaleBlob *s : sb->pred){
        WRITE(s);
      }

      WRITET(int, sb->succ.size());
      for(ScaleBlob *s : sb->succ){
        WRITE(s);
      }
      WRITE(sb->parent);
      WRITE(sb->mode);
      WRITE(sb->position);
      WRITE(sb->shape);
      WRITE(sb->fshape);
      WRITE(sb->timestep);
      WRITE(sb->covariance);
      WRITE(sb->invCov);
      WRITE(sb->detCov);
      WRITE(sb->pdfCoef);
      WRITE(sb->min);
      WRITE(sb->max);
      WRITE(sb->scale);
      WRITE(sb->n);
      WRITE(sb->npass);
    }
  }

  fclose(file);

  file = fopen((path0 + ".paths").c_str(),"wb");
  printf("write %d\n", paths.size());
  WRITET(int, paths.size());
  for(std::vector<ScaleBlob*> path : paths){
    WRITET(int, path.size());
    for(ScaleBlob* s : path){
      WRITE(s);
    }
  }

  fclose(file);

  file = fopen((path0 + ".paths.txt").c_str(), "w");
  for(std::vector<ScaleBlob*> path : paths){
    for(ScaleBlob* blob : path){
      fprintf(file, "%.2f %.2f %.2f; ", blob->position.x, blob->position.y, blob->position.z);
    }
    fprintf(file, "\n");
  }

}
#undef WRITE
#undef WRITET
void ArPipeline::load(){
//   printf("loading...\n");
  std::string path0 = exp->getfilepath(exp->low);
  std::replace(path0.begin(), path0.end(), '/', '-');
  path0 = "../rsc/store/s" + path0;

  std::string path0pipeline = path0 + ".pipeline";
  std::string path0paths    = path0 + ".paths";

  if(access(path0pipeline.c_str(), F_OK) == -1)return;
  FILE *file = fopen(path0pipeline.c_str(),"rb");

  char buf[2];
  int good=1;
#define READ(x) (good&=!!(fread(&(x), sizeof(x), 1, file)));
  int nframes;
  READ(nframes);
  printf("nframes = %d\n", nframes);
  std::vector<ScaleBlob*> frameroots;
  std::unordered_map<ScaleBlob*, ScaleBlob*> allblobs;
  std::vector<std::vector<ScaleBlob*>> frameblobs;
  for(int i=0;i<nframes;++i){
    ScaleBlob *rootaddr;
    int   nblobs;
    READ(rootaddr);
    READ(nblobs);
    frameroots.push_back(rootaddr);
    // printf("root %p has %d blobs.\n", rootaddr, nblobs);
    std::vector<ScaleBlob*> blobs;
    for(int i=0;i<nblobs;++i){
      ScaleBlob* p0;
      ScaleBlob* label;
      int nchildren, npred, nsucc;
      READ(label);
      if(!label)continue;
      ScaleBlob *blob = new ScaleBlob();
      READ(nchildren);
      for(int i=0;i<nchildren;++i){
        READ(p0);
        blob->children.push_back((ScaleBlob*)p0);
      }
      READ(npred);
      for(int i=0;i<npred;++i){
        READ(p0);
        blob->pred.push_back((ScaleBlob*)p0);
      }
      READ(nsucc);
      for(int i=0;i<nsucc;++i){
        READ(p0);
        blob->succ.push_back((ScaleBlob*)p0);
      }
      READ(blob->parent);
      READ(blob->mode);
      READ(blob->position);
      READ(blob->shape);
      READ(blob->fshape);
      READ(blob->timestep);
      READ(blob->covariance);
      READ(blob->invCov);
      READ(blob->detCov);
      READ(blob->pdfCoef);
      READ(blob->min);
      READ(blob->max);
      READ(blob->scale);
      READ(blob->n);
      READ(blob->npass);

      allblobs[label] = blob;
      blobs.push_back(blob);
    }
    frameblobs.push_back(blobs);
  }
  if(!good){
    fprintf(stderr, "read error.\n");
    exit(0);
  }
  // printf("fixing...\n");
  for(std::pair<ScaleBlob*, ScaleBlob*> elt : allblobs){
    if(!elt.second)continue;
    // printf("parents...");
    // printf("%p; ", elt.second->parent);
    elt.second->parent = allblobs[elt.second->parent];
    // printf("children...");
    for(int i=0;i<elt.second->children.size(); ++i){
      // printf("%d/%d; ", i, elt.second->children.size());
      elt.second->children[i] = allblobs[elt.second->children[i]];
    }
    // printf("preds...");
    for(int i=0;i<elt.second->pred.size(); ++i){
      // printf("%d/%d; ", i, elt.second->pred.size());
      elt.second->pred[i] = allblobs[elt.second->pred[i]];
    }
    // printf("succs...");
    for(int i=0;i<elt.second->succ.size(); ++i){
      // printf("%d/%d; ", i, elt.second->succ.size());
      elt.second->succ[i] = allblobs[elt.second->succ[i]];
    }
  }
  // printf("\nread......\n");
  // printf("all blobs:");
  int i=0;
  for(std::pair<ScaleBlob*, ScaleBlob*> elt : allblobs){
    // printf("%d: %p\n", i, elt.second);
    ++i;
  }
  // printf("pushing\n");
  // printf("frames %d %d\n", nframes, frames.size());
  for(int i=0;i<nframes;i++){
    ArFrameData fd;
    fd.blob      = allblobs[frameroots[i]];
    fd.scales    = collect_scales(fd.blob);
    fd.scale_eps = compute_epsilon(fd.scales);
    fd.complete  = true;
    fd.bspblobs = filter.get_bsp(10);
    
    BSPTree<ScaleBlob> *bsptree = &fd.bspblobs;
    for(ScaleBlob *sb : frameblobs[i]){
      bsptree->insert(sb, sb->position);
    }

    // DEBUG

    // for(float f : fd.scales){
    //   printf("scale %.2f;\n", f);
    // }
    // /////
    frames[i] = fd;
  }

  // load paths...

  if(access(path0paths.c_str(), F_OK) == -1)return;
  file = fopen(path0paths.c_str(),"rb");

  int n;
  READ(n);
  printf("read %d paths.\n", n);
  for(int i=0;i<n;++i){
    std::vector<ScaleBlob*> path;
    int pathlen;
    ScaleBlob *blob;
    READ(pathlen);
    for(int i=0;i<pathlen;++i){
      READ(blob);
      path.push_back(allblobs[blob]);
    }
    paths.push_back(path);
  }

  // done.
#undef READ
}