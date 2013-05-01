#ifndef ENTRENAMIENTO_H
#define ENTRENAMIENTO_H

#pragma once

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "patrones.h"
#include "clasificador.h"


class Entrenamiento {

private:

    Clasificador* clasificador;
	Patrones patrones;

    const char*directorioBD;
    const char*archivoPatrones;

	double* caracteristicasActual;

public:

	Entrenamiento();

    Entrenamiento(Clasificador *clasificador);

    void entrenarConPatrones(const char*clasificador,const char*archivoPatrones, double errorTotalMin, double minErrorRed);

    void crearArchivoPatrones(const char*archivoPatrones, const char*directorioBD, int numMuestras, int numDescrs, int* salida, int numSalidas);

	void mostrarDescripsActual();

	void mostrarRN();

	~Entrenamiento();

};



#endif // ENTRENAMIENTO_H
