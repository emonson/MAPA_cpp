// This file is part of libigl, a simple c++ geometry processing library.
// 
// Copyright (C) 2013 Alec Jacobson <alecjacobson@gmail.com>
// 
// This Source Code Form is subject to the terms of the Mozilla Public License 
// v. 2.0. If a copy of the MPL was not distributed with this file, You can 
// obtain one at http://mozilla.org/MPL/2.0/.
#include "tetgenio_to_tetmesh.h"

// IGL includes
#include <igl/list_to_matrix.h>

// STL includes
#include <iostream>

IGL_INLINE bool igl::tetgenio_to_tetmesh(
  const tetgenio & out,
  std::vector<std::vector<REAL > > & V, 
  std::vector<std::vector<int> > & T)
{
  using namespace std;
  // process points
  if(out.pointlist == NULL)
  {
    cerr<<"^tetgenio_to_tetmesh Error: point list is NULL\n"<<endl;
    return false;
  }
  V.resize(out.numberofpoints,vector<REAL>(3));
  // loop over points
  for(int i = 0;i < out.numberofpoints; i++)
  {
    V[i][0] = out.pointlist[i*3+0];
    V[i][1] = out.pointlist[i*3+1];
    V[i][2] = out.pointlist[i*3+2];
  }


  // process tets
  if(out.tetrahedronlist == NULL)
  {
    cerr<<"^tetgenio_to_tetmesh Error: tet list is NULL\n"<<endl;
    return false;
  }

  // When would this not be 4?
  assert(out.numberofcorners == 4);
  T.resize(out.numberoftetrahedra,vector<int>(out.numberofcorners));
  int min_index = 1e7;
  int max_index = -1e7;
  // loop over tetrahedra
  for(int i = 0; i < out.numberoftetrahedra; i++)
  {
    for(int j = 0; j<out.numberofcorners; j++)
    {
      int index = out.tetrahedronlist[i * out.numberofcorners + j];
      T[i][j] = index;
      min_index = (min_index > index ? index : min_index);
      max_index = (max_index < index ? index : max_index);
    }
  }
  assert(min_index >= 0);
  assert(max_index >= 0);
  assert(max_index < (int)V.size());

  return true;
}

template <typename DerivedV, typename DerivedT>
IGL_INLINE bool igl::tetgenio_to_tetmesh(
  const tetgenio & out,
  Eigen::PlainObjectBase<DerivedV>& V,
  Eigen::PlainObjectBase<DerivedT>& T)
{
  using namespace igl;
  using namespace std;
  vector<vector<REAL> > vV;
  vector<vector<int> > vT;
  bool success = tetgenio_to_tetmesh(out,vV,vT);
  if(!success)
  {
    return false;
  }
  bool V_rect = list_to_matrix(vV,V);
  if(!V_rect)
  {
    // igl::list_to_matrix(vV,V) already printed error message to std err
    return false;
  }
  bool T_rect = list_to_matrix(vT,T);
  if(!T_rect)
  {
    // igl::list_to_matrix(vT,T) already printed error message to std err
    return false;
  }
  return true;
}

#ifndef IGL_HEADER_ONLY
// Explicit template specialization
template bool igl::tetgenio_to_tetmesh<Eigen::Matrix<double, -1, -1, 0, -1, -1>, Eigen::Matrix<int, -1, -1, 0, -1, -1> >(tetgenio const&, Eigen::PlainObjectBase<Eigen::Matrix<double, -1, -1, 0, -1, -1> >&, Eigen::PlainObjectBase<Eigen::Matrix<int, -1, -1, 0, -1, -1> >&);
#endif
