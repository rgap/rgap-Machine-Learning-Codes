#ifndef REDNEURONAL_H
#define REDNEURONAL_H

#pragma once

#include "capa.h"
#include "patrones.h"
#include <vector>

#define DEBUG_RN 0

class RedNeuronal
{

private:

	int numCapas; //Numero de capas

	Capa* capa;  

	double factorAprendizaje; //Learning rate     
	double momentum;


	double* entradaRed;
	double* salidaEsperada;
	
	double errorRed;

	double errorMin;

	int epocaActual;

public:

	double* salidaRed;

    vector<double> vectorPesosRed;

	RedNeuronal();

	~RedNeuronal();

	void setAtributos(int numCapas, int *numNeuronasCapa, double factorAprendizaje, double momentum);

	void pesosAleatoriosRed();

	double entrenarRed_MSecuencial(double errorMin);

	double entrenarRed();

	void feedForward();

	double calcularError();

	void backPropagate();


	void setEntrada(double* entradaRed);
	void setSalidaEsperada(double* salidaEsperada);

    void cargarDatosRed(const char *archivoRed);

    void guardarDatosRed(const char *archivoRed);



	void printSalidas();

	void mostrarRedN();

};

#endif // REDNEURONAL_H
