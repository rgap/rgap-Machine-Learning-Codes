#include <iostream>
#include <boost/lexical_cast.hpp>
#include "boost/multi_array.hpp"

//#include "procesamientoImagen.h"
//#include "OpOtras.h"

using namespace std;

#include <stdlib.h>
#include <assert.h>
#include <float.h>
#include <math.h>

#include <list>
#include <map>
#include <cassert>

#include "OpOtras.h"





int main( int argc, char** argv ){

	int k = 5;

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

	Array1D_int labels(boost::extents[5]);

	labels[0] = 0;
	labels[1] = 1;
	labels[2] = 2;
	labels[3] = 3;
	labels[4] = 4;


	Array1D_double x(boost::extents[2]);

	x[0] = 6.8;
	x[1] = 3.0;

	int label = OpOtras::knnLabel(data,2,labels,x,k,-1);
	cout<<label<<endl;

	cout<<"Fin proceso"<<endl;

	return 1;
}
