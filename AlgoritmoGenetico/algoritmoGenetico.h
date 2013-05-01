#ifndef ALGORITMOGENETICO_H
#define ALGORITMOGENETICO_H

#pragma once

#include "cromosoma.h"
#include <vector>
#include <algorithm>
#include "libOperaciones.h"

class Poblacion{

public:

	unsigned int tamPoblacion;
	unsigned int longitudCromosoma;

	vector<Cromosoma*> individuo;

	Cromosoma* mejorCromosoma;

    Poblacion(){}

	Poblacion(int tamPoblacion, int longitudCromosoma){

		for(int i = 0; i < tamPoblacion; ++i)
			individuo.push_back(new Cromosoma(longitudCromosoma));
    }

	static bool comparadorFitness (Cromosoma* c1, Cromosoma* c2) { 
		return (c1->fitness < c2->fitness); 
	}

	double peorFitness;
	double promedioFitness;
	double mejorFitness;
	double totalFitness;

    ~Poblacion(){
    	/*
        for(unsigned int i=0;i<individuo.size();++i)
            delete []individuo[i];

        individuo.clear();

        delete[]mejorCromosoma;
        */
    }

};


class AlgoritmoGenetico{

private:

	Poblacion poblacion;

	//PARAMETROS SELECCION
	int numElite;
	int numCopiasElite;

	//PARAMETROS CRUZAMIENTO
	double probCrossOver;

	//PARAMETROS MUTACION
	double probMutacion;
	double maxMutacion;

public:

	AlgoritmoGenetico();

	AlgoritmoGenetico(int tamPoblacion, int longitudCromosomas, double probCrossOver, double probMutacion, 
					double maxMutacion, int numElite, int numCopiasElite);

	void generarSiguienteGeneracion();

	//SELECCION
	void agregarElite();
	Cromosoma *escogerCromosoma();

	//CRUZAMIENTO
	vector<Cromosoma*> crossOver(Cromosoma* madre, Cromosoma* padre);

	//Calcular fitness maximo, minimo, promedio y total en la poblacion
	void actualizarIndicadoresFitness();

	void mostrarAG(const char* archivoAG);

    ~AlgoritmoGenetico();

};

#endif // ALGORITMOGENETICO_H
