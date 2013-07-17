#include <iostream>
#include <boost/lexical_cast.hpp>

using namespace std;

#include "OpOtras.h"

int main( int argc, char** argv ){

	int k = 2;

	Array2D_double data(boost::extents[5][2]);

	data[0][0] = 1.5;
	data[0][1] = 2.5;
	data[1][0] = 9.0;
	data[1][1] = 2.0;
	data[2][0] = 1.5;
	data[2][1] = 0.0;
	data[3][0] = 1.0;
	data[3][1] = 4.0;
	data[4][0] = 9.0;
	data[4][1] = 6.0;

	Array2D_double centroids(boost::extents[2][2]);

	OpOtras::estimar_centroides(data,centroids,2,k);
	OpOtras::printArray2D<Array2D_double>(centroids,0,0,1,1);

/*
	centroids[0][0] = 1.5;
	centroids[0][1] = 2.5;
	centroids[1][0] = 9.0;
	centroids[1][1] = 2.0;
*/

	Array1D_int labels = OpOtras::k_means(data,2,2,0.1,centroids);
	OpOtras::printArray1D<Array1D_int>(labels,0,4);


	cout<<"Fin proceso"<<endl;

	return 1;
}
