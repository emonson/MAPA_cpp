## MAPA document clustering for Jigsaw

### Multiscale Analysis of Plane Arrangements (MAPA)

This is a C++ implementation of MAPA Code based on [Mauro Maggioni][Mauro] & [Guangiang Chen's][GChen]
Matlab code, specifically targeted to perform text-based document clustering to be
imported into the [Jigsaw Visual Analytics plaform for Exploring and Understanding 
Document Collections][Jigsaw] from [John Stasko's lab at Georgia Institute of Technology][Stasko].
A PDF of the original paper describing the algorithm can be obtained 
from http://www.math.duke.edu/~mauro/Papers/mapa_for_cvpr2011.pdf

This is a command line application with many adjustable options (see Usage below) which
can read in a document corpus which is either stored in a Jigsaw .jig data file, or as a 
collection of text documents in a directory. The output is an XML file describing the 
document clusters, which can be imported into Jigsaw.

A modified version of the Matlab code is included in this repository in
the `matlab/` directory. The original code can be obtained from
Guangliang Chen's old Duke page at http://www.math.duke.edu/~glchen/mapa.html

[Jigsaw]: http://www.cc.gatech.edu/gvu/ii/jigsaw/ "Jigsaw: Visual Analytics for Exploring and Understanding Document Collections"
[Stasko]: http://www.cc.gatech.edu/home/stasko/ "John Stasko's lab at Georgia Tech"
[Mauro]: http://www.math.duke.edu/~mauro/ "Mauro Maggioni's home page"
[GChen]: http://www.cmc.edu/pages/faculty/GChen/ "Guangliang Chen's home page"


### System Requirements

The code will build, and has been tested on OS X 10.9, Ubuntu 14 64-bit, 
and Windows 7 64-bit with MS Visual Studio Professional 2013. 

[CMake][] is used for the build system, and in principle 
is the only external requirement that isn't included with the repository 
besides compilers.


### Building

The point of using [CMake][], if you haven't used it before, is that you can use the
same set of configuration files to generate the proper build instructions for all
platforms. So, on OS X it can gerate a Makefile (or XCode project – not demonstrated here)
while on Windows you can generate a MS Visual Studio project file. 

CMake encourages "out of source" builds, which means you should create a new directory for the build
products, not build right in the repository source directory. Often I will just create
a `build/` directory right in the original source directory. This keeps the project together
but sequesters the build files in a separate place.

- #### Mac OS X (tested on 10.9, "Mavericks"). 
At a minimum you'll need [CMake][] and the XCode command-line tools. 
The former I tend to install these days using the [homebrew][]
package manager, but you can also download it directly from the development repository.
If you don't have the latter (which includes things like the `gcc` compiler), you can
type `xcode-select --install` in a terminal and the system should start a GUI for downloading.
If you want to pull directly from the GitHub repository you'll also need git, which
can be installed easily with [homebrew][] also, or from [this git site][git].

    After you download the source repository, either as a `.zip` file from this GitHub page
    or by cloning the repository, create a build directory, then run `cmake`
    (or the ccmake curses GUI, or a more traditional GUI), pointing to the root of the
    source repository, then build. The executable will end up in the build/bin directory.

    ```
    git clone git@github.com:emonson/MAPA_cpp.git
    cd MAPA_cpp
    mkdir build
    cd build
    cmake ..
    make 
    ```

- #### Ubuntu (tested on v 14, 64-bit)
Building on Ubuntu is almost identical to building on OS X, as above. The only difference
is in installing the necessary dependencies ahead of time.

    ```
    sudo apt-get install git
    sudo apt-get install cmake
    sudo apt-get install cmake-curses-gui
    sudo apt-get install build-essential
    ```

- #### Windows 7 (tested on 64-bit)
As on other platforms you have the choice of downloading a `.zip` file of the repository
or cloning it using Git. Even if you choose to do the latter, I would advise [downloading
the Git client][git] and installing it because it also comes with a very nice UNIX-like 
"Git bash shell", which will be useful for running the MAPA clustering application just
like in the instructions for OS X and Ubuntu.

    For CMake on Windows I always use the GUI, which you get when you [download CMake for
    Windows from the software listing page][CMakeDownload]. The CMake GUI will ask you to
    find the path to the root of the repository that you downloaded or cloned, "Where
    is the source code". In the next
    line it asks for a build directory, "Where to build the binaries". 
    I always just copy the project path and add `/build`
    on the end.
    First, hit the `Configure` button in the lower left. It will ask you if you want
    it to create the build directory. Hit "yes", and then it will ask you to
    "Specify the generator for this project". I chose "Visual Studio 12 Win64", and 
    the default radio button below, "Use default native compilers". When you hit "Finish",
    CMake will run and show you options. The defaults should be fine, so you can hit
    "Generate" to create the MS Visual Studio project files. Navigate to the build
    directory with Windows Explorer (filesystem browser), and double-click on the
    `ALL_BUILD.vcxproj` file to load. Once you have built the ALL_BUILD project
    in MSVS, you need to run the `mapa_clustering.exe` program with options specified
    below, either in the `Run` program which you can search for from the Start menu,
    or through the `Git bash` shell application.

[homebrew]: http://brew.sh/ "homebrew"
[git]: http://git-scm.com/ "git"
[CMakeDownload]: http://www.cmake.org/cmake/resources/software.html "CMake download"


### Usage

```
mapa_clustering  {-K <integer>|--kmax <integer>} [-o <path string>]
                 [--n0 <integer>] [-D <integer>] [--dmax <integer>]
                 [--dhard <integer>] [--min_term_length <integer>]
                 [--min_term_count <integer>] [--add_stopwords <string>] 
                 [--n_cluster_labels <integer>]
                 [--n_stop_labels <integer>] [-V] [--] [--version]
                 [-h] <path string>
```

The minimum required for running is to set the number (or max number) of clusters
to be formed, plus the name of either the `.jig` Jigsaw text corpus data file, or the
name (path) of a directory containing just the text files, one per document in the corpus,
that you want clustered.

```
   -K <integer>,  --K <integer>
     (OR required)  Number of clusters
         -- OR --
   --kmax <integer>
     (OR required)  Maximum number of clusters
```

In principle the MAPA algorithm will find the "number of clusters" automatically, without
having to specify a number, but in practice that works better with image data than with
text documents as in this implementation. (The algorithm would set a very large number
of clusters in many cases if you let it.) So, in most cases you might as well set the number
of clusters you want with the `-K` option.

```
   -o <path string>,  --outfile <path string>
     Path (name) of output .xml file (default <data_file_name>.xml)
```

If no output name is set, the data input path will have any extension stripped off and 
`.xml` appended. There will not be any warning for overwriting an existing file.

```
   --n0 <integer>
     Number of seed points (default = 20 * K)
```

This algorithm isn't like k-means, where there is one seed point per cluster. MAPA needs
many seed points per cluster, so the default value of `n0` is `20 * K`. You do want to minimize
this value, though, since the algorithm scales with n0.

```
   -D <integer>,  --dim_reduced <integer>
     Dimensionality to reduce original data to with SVD 
     (default = K * dmax)
```

Since MAPA also scales with the original dimensionality of the data, it is not practical
to analyze document data sets, which can easily have term vectors in the thousands of
dimensions, directly in the original space. So, data dimensionality is reduced with SVD
before analysis. In principle, this should be set at just greater than the sum of the 
MAPA-derived dimensionalities of all of the clusters.

```
   --dmax <integer>
     Suggested limit on dimensionality of each cluster (default = 6)

   --dhard <integer>
     Forced hard limit on max dimensionality of each cluster (default = 10)
```

The original MAPA algorithm had a parameter, `dmax`, which wasn't a hard cutoff on the 
allowed dimensionality of the clusters, but instead was an estimate of the dimensionalities
of the clusters, which helped set some other parameter values. Later in the algorithm
there was a step where seed points were disregarded if they were found to have the ambient
dimensionality of the system. I have found, though, that with document data sets I get
much better clustering results (as well as execution times) if I set a hard limit of around
10-d at that stage (otherwise, I get a few clusters with very high-D, which suck up most
of the points, and it isn't very informative).

```
   --min_term_length <integer>
     Minimum number of characters for a term (default = 3)

   --min_term_count <integer>
     Minimum term count per document (default = 2)

   --add_stopwords <string>
     Space-delimited string in quotes of extra stopwords to add
```

These options are used during the generation of the term-document matrix (TDM). Terms
will be excluded that are under the minimum term length, or which occur less than the 
minumum count per document, or which show up in the stopwords list. There is a built-in
list of "stopwords" for english, but depending on your corpus you may want to add extra
terms on the command line, separated by spaces within a single set of double-quotes.

```
   --n_cluster_labels <integer>
     Number of cluster keyword labels in XML (default = 3)

   --n_stop_labels <integer>
     Number of clusters center labels to ignore when generating cluster
     labels (default = 10)
```

Each cluster in the output `.xml` file includes a set number of terms which are 
characteristic of the cluster (based on its center location), but we exclude a certain
number of terms which are characteristic of the average cluster center. These latter
terms are listed in the `.xml` file under a `<commonterms>` tag, but are not imported
into Jigsaw. It will probably take some experimentation to decide whether with your
particular data set it would be better to add these terms to the "stopwords" above,
or just exclude them from the cluster terms here.

```
   -V,  --verbose
     Verbose output
```

Verbose output just prints more information in the terminal window during program
execution.

```
   -h,  --help
     Displays usage information and exits.

   <path string>
     (required)  Path to .jig file or directory of text files


EXAMPLES:

./mapa_clustering -K 6 ../../data/InfovisVAST-papers.jig

./mapa_clustering -K 12 -n_cluster_labels 5 -V -o sci_news_12 -n_stop_labels 0 
    -add_stopwords "science news year years work university researchers new people scientists"
    
```


### Loading into Jigsaw (v0.53)

After launching Jigsaw (version later than v0.53), import your document collection by 
going to `File->Import`, and 
choosing a `.jig` file or a directory of text documents. Import the clusters generated
by MAPA by going to `Tools->Import Cluster`, and locating the cluster definitions `.xml` file.
When you go to the Document Cluster view under `Views->Document Cluster`, your MAPA cluster
should show up in the combo-box / drop-down in the "Clusters" pane in the lower left.


### Support

This code was developed for and supported by the NSF FODAVA (Mathematical Foundations
of Visual Analytics) program grant, "Mathematical Foundations of Multiscale Graph Representations 
and Interactive Learning", NSF-CCF-11-32184. 


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


### More complete code

Finally, this repository is a subset of a larger one called em_cpp_mapa that
I used during development, which is also available on Github at
https://github.com/emonson/em_cpp_mapa

