#ifndef LMSVD_H
#define LMSVD_H

/* lmsvd.h

Based on the Matlab code of
Guangliang Chen & Mauro Maggioni

Eric E Monson – 2014

*/

#include "Options.h"
#include <vector>
#include "Eigen/Dense"

using namespace Eigen;


namespace MAPA {

class LMsvd {

public:

    LMsvd(const ArrayXXd &Xin, unsigned int Kin)
    {

    };

private:

    std::vector<ArrayXi> goodLocalRegions;
    ArrayXi goodSeedPoints;
    ArrayXi estDims;

}; // class def

} // namespace MAPA

#endif
