#ifndef PATRONES_H
#define PATRONES_H
#pragma once


//#include "procesamientoImagen.h"

class Patrones {

private:

    int nEntradas;  //Numero de entradas de la red
    int nSalidas;   //Numero de salidas de la red

    const char *archivoPatrones; //Nombre del archivo de patrones

public:

    int nPatrones;  //Numero de patrones

	double **patronEntrada;  //Valores de entrada
    double **salidaEsperada;   //Valores de salida

	Patrones();
    Patrones(const char *archivoPatrones);

    ~Patrones();

    void almacenarPatrones();

};


#endif // PATRONES_H
