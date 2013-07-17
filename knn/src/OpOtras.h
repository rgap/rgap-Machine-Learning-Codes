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

};

#endif // OPOTRAS_H
