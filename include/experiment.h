#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <teem/nrrd.h>
#include <string>
#include <map>
#include "filter.h"

struct NrrdFrame{
  int n;
  long accessed;
  std::string path;
  Nrrd* nrrd;
};

// Exposes methods for interacting with
// the raw data of the experiment.
class ArExperiment{
public:
  ArExperiment(std::string path, std::string tgmmpath, int low, int high, int mem_cap);
  NrrdFrame* frames;
  Nrrd* get(int n);
  Nrrd* copy(int n);
  std::string getfilepath(int n);
  std::string gettgmmpath(int n);
  int low;
  int high;
private:
  ArFilter filter;
  std::string *paths;
  std::string *tgmmpaths;
  int nframes;
  int npaths;
  long time;
};

#endif