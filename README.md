## MAPA document clustering for Jigsaw

### Multiscale Analysis of Plane Arrangements (MAPA)

This is a C++ implementation of MAPA Code based on Mauro Maggioni & Guangiang Chen's 
Matlab code. A PDF of the original paper describing the algorithm can be obtained 
from http://www.math.duke.edu/~mauro/Papers/mapa_for_cvpr2011.pdf

A modified version of the Matlab code is included in this repository in
the `matlab/` directory. The original code can be obtained from
Guangliang Chen's old Duke page at http://www.math.duke.edu/~glchen/mapa.html

### System Requirements

Tested on OS X 10.9, Ubuntu 14 64-bit, and Windows 7 64-bit with MS Visual
Studio Professional 2013.

**Git**

**CMake** is used for the build system. Build out of source from the root
directory. The main MAPA clustering application and custom code is in 
the src/ directory.

### Dependencies (all included)

using Eigen as a base, plus IGL, boost tokenize, tinyxml2, SVDLIBC, ANN, dirent,
and TCLAP. All dependencies besides CMake itself and compilers, etc, are 
included in the lib/ directory.

### Jigsaw Visual Analytics Platform

Output is an XML file describing clusters of documents which can be
imported into Jigsaw http://www.cc.gatech.edu/gvu/ii/jigsaw/

### Usage


### Support


### More complete code

Finally, this repository is a subset of a larger one called em_cpp_mapa that
I used during development, which is also available on Github at
https://github.com/emonson/em_cpp_mapa

