
#include <iostream>
#include <fstream>
#include <math.h>

#include "clasificador.h"

using namespace std;

Clasificador::Clasificador(){}

Clasificador::Clasificador(int numCapas, int *numNeuronasCapa, double factorAprendizaje, double factorMomento){

	redN = RedNeuronal();
	redN.setAtributos(numCapas, numNeuronasCapa, factorAprendizaje, factorMomento);

}

void Clasificador::setPatrones(Patrones* patrones){
	this->patrones = patrones;
}

void Clasificador::entrenar(double errorTotalMin, double minErrorRed){

	cout<<"Entrenando la red - Modo secuencial"<<endl;

	double errorTotal = 100;   //Variable de error para detener el entrenamiento cuando baja de un minimo de error
	double sumaErrores = 0;

	double errorRed = 0;

	int cEpoca, cPatron;

    //Iniciar entrenamiento de la red neuronal
    for (cEpoca=0; errorTotal > errorTotalMin; ++cEpoca){

        if (cEpoca == 60000){
            cout<<"ERROR: Superado limite de 60000 epocas en el entrenamiento"<<endl;
            break;
        }

        //Entrenar la red con los patrones 
		for (cPatron=0; cPatron<patrones->nPatrones; ++cPatron){

			redN.setEntrada(patrones->patronEntrada[cPatron]);
            redN.setSalidaEsperada(patrones->salidaEsperada[cPatron]);

            errorRed = redN.entrenarRed_MSecuencial(minErrorRed);
            sumaErrores += errorRed;
        }

		errorTotal = sqrt ( ( sumaErrores ) * ( sumaErrores ) );

        //errorTotal = sumaErrores/patrones->nPatrones;

        if(DEBUG_CLASIF) cout<<"errorTotal de Iteracion = "<<errorTotal<<endl;

		sumaErrores = 0;
		
    }


    cout<<"errorTotal-RN = "<<errorTotal<<endl;
    cout<<"FIN DE ENTRENAMIENTO en la epoca: "<<cEpoca<<endl;

}

void Clasificador::guardarDatosClasif(const char* archivoClasificador){
    redN.guardarDatosRed(archivoClasificador);
}

void Clasificador::cargarDatosClasif(const char* archivoClasificador){
    redN.cargarDatosRed(archivoClasificador);
}

double* Clasificador::clasificarEntradas(double* vectorCaracteristico){

	redN.setEntrada(vectorCaracteristico);

    redN.feedForward();

	return redN.salidaRed;
}

void Clasificador::printSalidas(){
	redN.printSalidas();
}

void Clasificador::mostrarClasif(){
	redN.mostrarRedN();
}

Clasificador::~Clasificador(){
	redN.~RedNeuronal();
}
