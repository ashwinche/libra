# Install script for directory: /home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/Eigen/src/Eigenvalues

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xDevelx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/eigen3/Eigen/src/Eigenvalues" TYPE FILE FILES
    "/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/Eigen/src/Eigenvalues/ComplexEigenSolver.h"
    "/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/Eigen/src/Eigenvalues/ComplexSchur.h"
    "/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/Eigen/src/Eigenvalues/ComplexSchur_MKL.h"
    "/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/Eigen/src/Eigenvalues/EigenSolver.h"
    "/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/Eigen/src/Eigenvalues/GeneralizedEigenSolver.h"
    "/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/Eigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h"
    "/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/Eigen/src/Eigenvalues/HessenbergDecomposition.h"
    "/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/Eigen/src/Eigenvalues/MatrixBaseEigenvalues.h"
    "/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/Eigen/src/Eigenvalues/RealQZ.h"
    "/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/Eigen/src/Eigenvalues/RealSchur.h"
    "/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/Eigen/src/Eigenvalues/RealSchur_MKL.h"
    "/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h"
    "/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/Eigen/src/Eigenvalues/SelfAdjointEigenSolver_MKL.h"
    "/home/ashwin/repo/libra/lib/eigen/eigen-eigen-b9cd8366d4e8/Eigen/src/Eigenvalues/Tridiagonalization.h"
    )
endif()

