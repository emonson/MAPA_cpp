EMonson C++ MAPA Code based on Mauro Maggioni & Guangiang Chen's Matlab code
using Eigen as a base, plus IGL, boost tokenize, tinyxml2, SVDLIBC, ANN, dirent,
and TCLAP. All dependencies besides CMake itself and compilers, etc, are 
included in the lib/ directory.

CMake is used for the build system. Build out of source from the root
directory. The main MAPA clustering application and custom code is in 
the src/ directory.

Tested on OS X 10.9, Ubuntu 14 64-bit, and Windows 7 64-bit with MS Visual
Studio Professional 2013.

Output is an XML file describing clusters of documents which can be
imported into Jigsaw http://www.cc.gatech.edu/gvu/ii/jigsaw/
