// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#ifndef IGL_COMPONENTS_H
#define IGL_COMPONENTS_H
#include <igl/igl_inline.h>
#include <Eigen/Core>
#include <Eigen/Sparse>
namespace igl
{
  // Compute connected components of a graph represented by an adjacency matrix
  //
  // Inputs:
  //   A  n by n adjacency matrix
  // Outputs:
  //   C  n list of component ids
  //
  template <typename AScalar, typename DerivedC>
  IGL_INLINE void components(
    const Eigen::SparseMatrix<AScalar> & A,
    Eigen::PlainObjectBase<DerivedC> & C);
  // Ditto but for mesh faces as input
  //
  // Inputs:
  //   F  n by 3 list of triangle indices
  // Outputs:
  //   C  max(F) list of component ids
  template <typename DerivedF, typename DerivedC>
  IGL_INLINE void components(
    const Eigen::PlainObjectBase<DerivedF> & F,
    Eigen::PlainObjectBase<DerivedC> & C);

}

#ifdef IGL_HEADER_ONLY
#  include "components.cpp"
#endif

#endif
