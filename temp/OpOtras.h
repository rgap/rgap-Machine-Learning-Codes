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

	static double squared_distance(Array1D_double &u, Array1D_double &v, int dim){
	   double d = 0.0, x;

	   while (dim-- > 0) {
	      x = u[dim] -  v[dim];
	      d += x * x;
	   }
	   return d;
	}

	static double euclidean_distance(Array1D_double &u, Array1D_double &v, int dim){
	   return sqrt(squared_distance(u, v, dim));
	}

	static double squared_distance2D(double x1, double y1, double x2, double y2){
	   return (x2-x1)*(x2-x1) + (y2-y1)*(y2-x1);
	}

	static double euclidean_distance2D(double x1, double y1, double x2, double y2){
	   return sqrt(squared_distance2D(x1, y1, x2, y2));
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


	//labels = data labels

	static int knnLabel(Array2D_double& data, unsigned int dim, Array1D_int& labels, Array1D_double& x, unsigned int k, double distanciaMin = -1){

		if (distanciaMin > 0) distanciaMin *= distanciaMin;

		list<pair<int, double> > nabors; // a list of {index => distance} pairs
		list<pair<int, double> >::iterator i;

		double distance;

		unsigned int h,j;

		for (h = 0; h < data.size(); h++) {

			distance = 0;

			for (j = dim; j-- > 0; distance += (data[h][j] - x[j])*(data[h][j] - x[j]));

			if (distance <= distanciaMin) return labels[h]; // vecino dentro del distanciaMin

			// check if data[h] is closer to the target than any recorded neighbours
			// and if true then sort its index/distance profile into the list.

			// searching the list for the first one with a longer distance
			for (i = nabors.begin(); i != nabors.end() && distance >= i->second; i++);

			if (i != nabors.end() || nabors.size() < k) { // data[h] qualified
				nabors.insert(i, 1, pair<int, double>(h, distance));
				if (nabors.size() > k) { // list overfilled (has k+1 profiles)
					nabors.pop_back(); // bumping out the farthest neighbour
				}
			}
		}

		// each of the k nearest neighbours cast a vote, and the majority wins
		// use class average distance to the target to break any possible ties

		// a {category => {count => distance}} map
		map<int, pair<int, double> > votes;
		int winner = labels[0]; // randomly assign an initial category

		for (i = nabors.begin(); i != nabors.end(); i++) {

			int count = ++(votes[labels[i->first]].first);
			double distance = (votes[labels[i->first]].second += i->second);

			if (count > votes[winner].first || // check for a possible tie
				(count == votes[winner].first && distance < votes[winner].second)) {

				winner = labels[i->first];
			}
		}

		return winner; //most likely category of point x
	}


	//////////////////////////////////////////////////////////////////

	template <typename Type>
	static Type* c_1D(Type* v, int size) {
		v = new Type[size];
		return v;
	}

	template <typename Type>
	static Type** c_2D(Type** v, int rows, int cols) {
		v = new Type*[rows];
		for(int i = 0; i < rows; ++i) v[i] = new Type[cols];
		return v;
	}

	template <typename Type>
	static void d_1D(Type* v) {
		delete [] v;
	}

	template <typename Type>
	static void d_2D(Type** v, int rows) {
		for ( int i = 0; i < rows; ++i ) delete [] v[i];
		delete [] v;
	}

};

#endif // OPOTRAS_H
