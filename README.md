# conda-ci-test
Testing CI pipeline using github actions for Python/C++ projects


## Requirements

* C++ libraries
* Python modules 
* Multiple python versions
* Automatic versioning using git
* DRY!


## Overview 

### .github/workflows

Contains the github workflows that runs the build using github runners

### conda-recepie

Config files for the conda pkg build 

### python

The python packages. Should, if possible support independent builds regardless of conda support. 

### libnoop

Generic C++ code that can be used without python