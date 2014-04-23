#include <Eigen/Core>
#include <igl/readDMAT.h>
#include <cstdio>
#include "kMeansRex.h"


#include <stdexcept>
#undef eigen_assert
#define eigen_assert(x) \
  if (!x) { throw (std::runtime_error("TEST FAILED: Some wrong values were generated")); }

#include <cmath>
#define close_enough(a,b) (std::abs(a-b) < 0.0001)
	

int main(int argc, char * argv[])
{
  // Read in test data
  Eigen::ArrayXXd X;
  std::cout << "Reading in Artifical 3D test data (rev1)" << std::endl;
  igl::readDMAT( "artificial_data_rev1.dmat", X );
  
  // Actual KMeansRex object
  KMeans::KMeansRex km(X, 3);
  std::cout << "KMeansRex with mapa seeding – 3 clusters" << std::endl;
  
	std::cout << "Seed points" << std::endl;
  std::cout << km.Seeds << std::endl;
	
	// Test Mu (kmeans seed points) values
	Eigen::MatrixXd Seeds_correct(3,3);
	Seeds_correct << -0.433417, -0.64096, 0.666714, \
	               0.623972, 0.364006, -0.716225, \
                -0.762395, 0.527501, 0.385417;
	for (int ii = 0; ii < Seeds_correct.size(); ii++)
	{
		eigen_assert( close_enough( km.Seeds(ii), Seeds_correct(ii) ) );
	}
	
  std::cout << "Cluster assignments" << std::endl;
  std::cout << km.Z.transpose() << std::endl;
	
	// Test Z (first 10 cluster labels) values
	Eigen::VectorXd Cluster_assigns_first10(10);
	Cluster_assigns_first10 << 2, 2, 1, 1, 2, 1, 1, 2, 2, 1;
	for (int ii = 0; ii < Cluster_assigns_first10.size(); ii++)
	{
		eigen_assert( close_enough( km.Z(ii), Cluster_assigns_first10(ii) ) );
	}
	
	// Test Z (last 10 cluster labels) values
	Eigen::VectorXd Cluster_assigns_last10(10);
	Cluster_assigns_last10 << 2, 2, 2, 1, 2, 2, 2, 1, 2, 1;
	int jj = km.Z.size()-Cluster_assigns_last10.size();
	for (int ii = 0; ii < Cluster_assigns_last10.size(); ii++)
	{
		eigen_assert( close_enough( km.Z(jj+ii), Cluster_assigns_last10(ii) ) );
	}

	std::cout << "Cluster centers" << std::endl;
  std::cout << km.Centers << std::endl;

	// Test Mu (cluster centroids) values
	Eigen::MatrixXd Centers_correct(3,3);
	Centers_correct << 0.0355854, -0.580986, 0.248681, \
	               0.329016, -0.129425, -0.207384, \
                -0.270798, 0.252273, 0.153366;
	for (int ii = 0; ii < Centers_correct.size(); ii++)
	{
		eigen_assert( close_enough( km.Centers(ii), Centers_correct(ii) ) );
	}
	
	std::cout << "TEST PASSED" << std::endl;

	return 0;
}