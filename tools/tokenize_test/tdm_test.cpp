#include <iostream>
#include <string>

#include <Eigen/Core>
#include <Eigen/SparseCore>

#include "JIGtokenizer.h"

int main( int argc, const char** argv )
{
    #if defined( _MSC_VER ) && defined( DEBUG )
        _CrtMemCheckpoint( &startMemState );
    #endif
    
    std::string filename = "/Users/emonson/Programming/em_cpp_mapa/tools/tokenize_test/InfovisVAST-papers.jig";

    int min_term_length = 3;
    int min_term_count = 5;
	MAPA::JIGtokenizer jig_tok(filename, min_term_length, min_term_count);
    
    Eigen::SparseMatrix<double,0,long> tdm = jig_tok.getTDM();
    
    std::cout << "TDM: " << tdm.rows() << " x " << tdm.cols() << ", " << tdm.nonZeros() << std::endl << std::endl;

    return EXIT_SUCCESS;
}
