#ifndef CLASIFICADOR_H
#define CLASIFICADOR_H

#pragma once

#include "redNeuronal.h"
#include "patrones.h"

#define DEBUG_CLASIF 1

class Clasificador
{

private:

	Patrones* patrones;

    RedNeuronal redN;

public:

    Clasificador();

    Clasificador(int numCapas, int *numNeuronasCapa, double factorAprendizaje, double factorMomento);

    double* clasificarEntradas(double* vectorCaracteristico);

	void setPatrones(Patrones* patrones);


	void entrenar(double errorTotalMin, double minErrorRed);

    void guardarDatosClasif(const char* archivoClasificador);

    void cargarDatosClasif(const char* archivoClasificador);

	void printSalidas();

    void mostrarClasif();
	
    ~Clasificador();

};

#endif // CLASIFICADOR_H
