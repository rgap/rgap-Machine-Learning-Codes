#ifndef CROMOSOMA_H
#define CROMOSOMA_H

#pragma once

#include <iostream>
#include <fstream>
#include "libOperaciones.h"

using namespace std;


class Cromosoma
{

public:

	double *secuencia; //secuencia de nucleotidos
	int longitudCromosoma;

	double fitness;

	Cromosoma();

	Cromosoma(int longitudCromosoma);

	Cromosoma(double fitness, double* secuencia, int longitudCromosoma);

	void mutar(double probMutacion, double maxMutacion);

	Cromosoma* clone();

    ~Cromosoma();

};

#endif // CROMOSOMA_H
