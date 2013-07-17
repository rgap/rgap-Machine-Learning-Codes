#ifndef OPOTRAS_H
#define OPOTRAS_H

#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/core/core.hpp"

#include <iostream>
#include <fstream>

#include <math.h>
#include<stdint.h>

#include <dirent.h>
#include <errno.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "boost/multi_array.hpp"

using namespace std;

typedef boost::multi_array<double, 2> Array2D_double;
typedef boost::multi_array<int, 1> Array1D_int;
typedef boost::multi_array<double, 1> Array1D_double;

class OpOtras
{
public:

	template <typename Type>
	static void printArray1D(Type& v, int pI, int pF){
		ofstream fichero1DA("1D_A.txt");
		for(int i=pI;i<=pF;++i)
			fichero1DA<<i<<" : "<<v[i]<<endl;
		fichero1DA.close();
	}

	template <typename Type>
	static void printArray2D(Type& v, int ini_row, int ini_col, int fin_row, int fin_col){
		ofstream fichero2DA("2D_A.txt");
		int i,j;
		for(i=ini_row;i<=fin_row;++i){
			fichero2DA<<"r: "<<i<<" - ";
			for(j=ini_col;j<=fin_col;++j){
				fichero2DA<<v[i][j]<<", ";
			}
			fichero2DA<<endl;
		}
		fichero2DA.close();
	}

	static void estimar_centroides(Array2D_double& data, Array2D_double& centroids, int dim, int k){
		int h = 0,i,j;
		for (i = 0; i < k; h += data.size() / k, i++) {
			// pick k points as initial centroids
			for (j = dim; j-- > 0;) centroids[i][j] = data[h][j];
		}
	}

	//centroide del tam k
	static Array1D_int k_means(Array2D_double& data, unsigned int dim, unsigned int k, double error_min, Array2D_double& centroids) {

		Array1D_int labels(boost::extents[data.size()]); //label de cada punto en resultado
		Array1D_int counts(boost::extents[k]); //tamanio de cada cluster
		Array2D_double centroids_temp(boost::extents[k][dim]);

		double old_error, error = DBL_MAX; // sum of squared euclidean distance
		double min_distance, distance; //distancia entre puntos

		unsigned int h,i,j;

		//hasta error min permitido
		do {
			old_error = error, error = 0;
			fill( centroids_temp.data(), centroids_temp.data() + centroids_temp.num_elements(), 0 );
			fill( counts.data(), counts.data() + counts.num_elements(), 0 );

			for (h = 0; h < data.size(); h++) {
				min_distance = DBL_MAX;

				// identify the closest cluster
				for (i = 0; i < k; i++) {
					distance = 0;
					for (j = dim; j-- > 0; distance += (data[h][j] - centroids[i][j])*(data[h][j] - centroids[i][j]));

					if (distance < min_distance) {
					   labels[h] = i;
					   min_distance = distance;
					}
				}

				// update size and temp centroid of the destination cluster
				for (j = dim; j-- > 0; centroids_temp[labels[h]][j] += data[h][j]);

				counts[labels[h]]++;

				error += min_distance; // update standard error
			}

			for (i = 0; i < k; i++) { // update all centroids
				for (j = 0; j < dim; j++)
					centroids[i][j] = counts[i] ? centroids_temp[i][j] / counts[i] : centroids_temp[i][j];
			}

			cout<<"error calculado : "<<(error - old_error)<<endl;

		} while (fabs(error - old_error) > error_min);

		return labels; //grupo al q pertenece de cada punto
	}

};

#endif // OPOTRAS_H
