## MAPA document clustering for Jigsaw

### Multiscale Analysis of Plane Arrangements (MAPA)

This is a C++ implementation of MAPA Code based on Mauro Maggioni & Guangiang Chen's 
Matlab code, specifically targeted to perform text-based document clustering to be
imported into the Jigsaw Visual Analytics plaform from John Stasko's lab at Georgia
Tech (see more details below). A PDF of the original paper describing the algorithm can be obtained 
from http://www.math.duke.edu/~mauro/Papers/mapa_for_cvpr2011.pdf

A modified version of the Matlab code is included in this repository in
the `matlab/` directory. The original code can be obtained from
Guangliang Chen's old Duke page at http://www.math.duke.edu/~glchen/mapa.html

### System Requirements

Tested on OS X 10.9, Ubuntu 14 64-bit, and Windows 7 64-bit with MS Visual
Studio Professional 2013.

**Git**

**[CMake][]** is used for the build system. Build out of source from the root
directory. The main MAPA clustering application and custom code is in 
the src/ directory.

### Dependencies (all included)

The libraries used are: the [Eigen][] C++ templated matrix library, 
the [libigl][] extension of Eigen, 
[boost tokenizer][] (1.55.0), [TinyXML-2][] for XML parsing, 
[SVDLIBC][] for sparse SVD, [ANN][] for approximate nearest-neighbor calculation, 
[dirent][] (1.20.1) for filesystem navigation in Windows, 
and [TCLAP][] for command line argument parsing. 
All dependencies besides [CMake][] itself and compilers, etc, are 
included in the `lib/` directory.

[Eigen]: http://eigen.tuxfamily.org/ "Eigen"
[libigl]: http://igl.ethz.ch/projects/libigl/ "libigl"
[boost tokenizer]: http://www.boost.org/doc/libs/1_55_0/libs/tokenizer/ "boost tokenizer"
[dirent]: http://softagalleria.net/dirent.php "dirent"
[TCLAP]: http://tclap.sourceforge.net/ "TCLAP"
[TinyXML-2]: http://www.grinninglizard.com/tinyxml2/ "TinyXML-2"
[CMake]: http://www.cmake.org/ "CMake"
[SVDLIBC]: http://tedlab.mit.edu/~dr/SVDLIBC/ "SVDLIBC"
[ANN]: http://www.cs.umd.edu/~mount/ANN/ "ANN"


### Jigsaw Visual Analytics Platform

Output is an XML file describing clusters of documents which can be
imported into Jigsaw 

[Jigsaw: Visual Analytics for Exploring and Understanding Document Collections](http://www.cc.gatech.edu/gvu/ii/jigsaw/)

[John Stasko](http://www.cc.gatech.edu/home/stasko/)

### Usage


### Building

#### Mac OS X

#### Ubuntu

#### Windows 7

### Support

This work was developed with support from the NSF FODAVA (Mathematical Foundations
of Visual Analytics) program grant, "Mathematical Foundations of Multiscale Graph Representations 
and Interactive Learning", NSF-CCF-11-32184. 

### More complete code

Finally, this repository is a subset of a larger one called em_cpp_mapa that
I used during development, which is also available on Github at
https://github.com/emonson/em_cpp_mapa

