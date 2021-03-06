// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#ifndef IGL_MATRIX_TO_LIST_H
#define IGL_MATRIX_TO_LIST_H
#include "igl_inline.h"
#include <vector>
#include <Eigen/Dense>

namespace igl
{
  // Convert a matrix to a list (std::vector) of row vectors of the same size
  // Template: 
  //   Mat  Matrix type, must implement:
  //     .resize(m,n)
  //     .row(i) = Row
  //   T  type that can be safely cast to type in Mat via '='
  // Inputs:
  //   V  a m-long list of vectors of size n
  // Outputs:
  //   M  an m by n matrix
  //
  // See also: list_to_matrix
  template <typename DerivedM>
  IGL_INLINE void matrix_to_list(
    const Eigen::MatrixBase<DerivedM> & M, 
    std::vector<std::vector<typename DerivedM::Scalar > > & V);
  // For vector input
  template <typename DerivedM>
  IGL_INLINE void matrix_to_list(
    const Eigen::MatrixBase<DerivedM> & M, 
    std::vector<typename DerivedM::Scalar > & V);
  // Return wrapper
  template <typename DerivedM>
  IGL_INLINE std::vector<typename DerivedM::Scalar > matrix_to_list(
      const Eigen::MatrixBase<DerivedM> & M);
}

#ifdef IGL_HEADER_ONLY
#  include "matrix_to_list.cpp"
#endif

#endif

