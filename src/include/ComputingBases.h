#ifndef COMPUTINGBASES_H
#define COMPUTINGBASES_H

/* ComputingBases.h

Based on the Matlab code of
Guangliang Chen & Mauro Maggioni

Eric E Monson – 2014
Duke University

*/

#include "Options.h"
#include "SvdlibcSVD.h"
#include "UtilityCalcs.h"
#include <vector>
#include "Eigen/Dense"

using namespace Eigen;


namespace MAPA {

class ComputingBases {

public:

    ComputingBases(const ArrayXXd &data, const ArrayXi &labels, const ArrayXi &dims)
    {
    // function [centers,bases] = computing_bases(data,labels,dims)

        // K = max(labels);
        int K = labels.maxCoeff();
        
        // DEBUG
        // std::cout << "dims size " << dims.size() << " K " << K << std::endl;

        // for k = 1:K
        // NOTE: labels that should be ignored need to be set negative
        for (int k = 0; k <= K; k++)
        {
            // cls_k = data((labels==k),:);
            // n_k = size(cls_k,1);
            
            ArrayXi cls_k_idxs = MAPA::UtilityCalcs::IdxsFromComparison(labels, "eq", k);
            ArrayXXd cls_k;
            int n_k;
            if (cls_k_idxs.size() > 0)
            {
                igl::slice(data, cls_k_idxs, 1, cls_k);
                n_k = cls_k.rows();
            }
            else
            {
                n_k = 0;
            }

            // if n_k >= dims(k)+1
            if (n_k >= (dims(k) + 1))
            {
                // centers{k} = mean(cls_k,1);
                centers.push_back( cls_k.colwise().mean() );
                
                // cls_k = cls_k - repmat(centers{k},n_k,1);
                cls_k.rowwise() -= centers[k].transpose();
                
                // [~,~,vk] = svds(cls_k,dims(k));
                // JacobiSVD<MatrixXd> svd(cls_k, Eigen::ComputeThinU | Eigen::ComputeThinV);
                SvdlibcSVD svd(cls_k, dims(k));
                ArrayXXd vk = svd.matrixV();
                
                // DEBUG
                // std::cout << "vk cols " << vk.cols() << " dims(k) " << dims(k) << std::endl;
                
                // bases{k} = vk';
                bases.push_back(vk.leftCols(dims(k)).transpose());
                
            // end
            }
            else
            {
                ArrayXd empty1d;
                ArrayXXd empty2d;
                centers.push_back( empty1d );
                bases.push_back( empty2d );
            }
            
        // end
        }
    };

    std::vector<ArrayXd> GetCenters()
    {
        return centers;
    };
    
    std::vector<ArrayXXd> GetBases()
    {
        return bases;
    };
    
private:

    std::vector<ArrayXd> centers;
    std::vector<ArrayXXd> bases;

}; // class def

} // namespace MAPA

#endif