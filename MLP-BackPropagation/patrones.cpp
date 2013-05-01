#include "patrones.h"

#include <iostream>
#include <fstream>

using namespace std;

Patrones::Patrones(){}

Patrones::Patrones(const char *archivoPatrones) {

    this->archivoPatrones = archivoPatrones;
}

Patrones::~Patrones() { //Liberar memoria

}

void Patrones::almacenarPatrones() {

    ifstream fAchivoPatrones(archivoPatrones);

    if (!fAchivoPatrones) {
        cerr<<"ERROR: No se pudo abrir el archivo de patrones"; return;
    }

    fAchivoPatrones>>nPatrones;
	fAchivoPatrones>>nEntradas;
	fAchivoPatrones>>nSalidas;

	int i,j;

	//Asignar memoria
	patronEntrada = new double*[nPatrones];
    for ( i = 0; i < nPatrones; ++i )
       patronEntrada[i] = new double[nEntradas];

	salidaEsperada = new double*[nPatrones];
    for ( i = 0; i < nPatrones; ++i )
       salidaEsperada[i] = new double[nSalidas];


    //Guardar patrones
	for ( i=0; i<nPatrones; ++i ) {     
        for ( j = 0; j < nEntradas; ++j )
            fAchivoPatrones>>patronEntrada[i][j];
        for ( j = 0; j < nSalidas; ++j )
            fAchivoPatrones>>salidaEsperada[i][j];
    }

    fAchivoPatrones.close();
}




