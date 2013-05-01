
#include <iostream>
#include <fstream>

#include "cromosoma.h"

using namespace std;


Cromosoma::Cromosoma(){}

Cromosoma::Cromosoma(int longitudCromosoma){

	this->longitudCromosoma = longitudCromosoma;

	fitness = 0;
	secuencia = new double[longitudCromosoma];
	
	//inicializar secuencia
	for(int i = 0; i < longitudCromosoma; ++i)
		secuencia[i] = randomVal(-1,1); //nucleotido con valor entre [-1, 1]
}


Cromosoma::Cromosoma(double fitness, double* secuencia, int longitudCromosoma){

	this->fitness = fitness;
	this->longitudCromosoma = longitudCromosoma;

	secuencia = new double[longitudCromosoma];

	for(int i = 0; i < longitudCromosoma; ++i)
		this->secuencia[i] = secuencia[i];
}

void Cromosoma::mutar(double probMutacion, double maxMutacion){

	for(int i = 0; i < longitudCromosoma; ++i){
		if(randomVal(0,1) < probMutacion)
			secuencia[i] += randomVal(-1,1) * maxMutacion; //mutar nucleotido con el rango de mutacion maxima
	}
}

//Clona el cromosoma actual
Cromosoma* Cromosoma::clone(){	
	return (new Cromosoma(this->fitness, this->secuencia, this->longitudCromosoma));	
}

Cromosoma::~Cromosoma(){
}
