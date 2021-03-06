// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#ifndef IGL_TETGENIO_TO_TETMESH_H
#define IGL_TETGENIO_TO_TETMESH_H
#include "../igl_inline.h"

#define TETLIBRARY 
#include "tetgen.h" // Defined tetgenio, REAL
#include <vector>
#include <Eigen/Core>
namespace igl
{
  // Extract a tetrahedral mesh from a tetgenio object
  // Inputs:
  //   out tetgenio output object
  // Outputs:
  //   V  #V by 3 vertex position list
  //   T  #T by 4 list of tetrahedra indices into V
  // Returns true on success, false on error
  IGL_INLINE bool tetgenio_to_tetmesh(
    const tetgenio & out,
    std::vector<std::vector<REAL > > & V, 
    std::vector<std::vector<int> > & T);
  
  // Wrapper with Eigen types
  // Templates:
  //   DerivedV  real-value: i.e. from MatrixXd
  //   DerivedT  integer-value: i.e. from MatrixXi
  template <typename DerivedV, typename DerivedT>
  IGL_INLINE bool tetgenio_to_tetmesh(
    const tetgenio & out,
    Eigen::PlainObjectBase<DerivedV>& V,
    Eigen::PlainObjectBase<DerivedT>& T);
}


#ifdef IGL_HEADER_ONLY
#  include "tetgenio_to_tetmesh.cpp"
#endif

#endif
