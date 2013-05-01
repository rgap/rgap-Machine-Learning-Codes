#ifndef CAPA_H
#define CAPA_H

#pragma once

#include <iostream>

#include "neurona.h"

#define TIPO_CAPA_INPUT 0
#define TIPO_CAPA_HIDDEN 1
#define TIPO_CAPA_OUTPUT 2

using namespace std;

class Capa
{

private:

	int numCapa; //numero de capa

public:

	double factorAprendizaje; //Learning rate     
	double momentum;

	Neurona* neurona; //neuronas de la capa

    Capa* capaAnterior; //puntero a la capa anterior
	Capa* capaSiguiente; //puntero a la capa anterior

	int tipoCapa;

	int numNeuronasTotal; //num considerando bias

	int numNeuronas; //num neuronas capa actual

	Capa();

	~Capa();

	void setAtributos(int numCapa, int tipoCapa, int numNeuronas, Capa* capaAnterior, Capa* capaSiguiente,
					  double factorAprendizaje,double momentum) ;

	////////////// Propagacion ////////////
	void pesosAleatorios();

	void propagate(double* salidaCapa);

	double funcionPropagacion(Neurona *neurona);

	void backPropagate(double* salidaEsperada);

	void actualizarPesos(Neurona *neurona);

	void cargarDatosCapa(std::ifstream *ficheroRed);

	void guardarDatosCapa(std::ofstream *ficheroRed);

	void mostrarCapa();

};


#endif // CAPA_H
