#include <iostream>
#include <fstream>

#include "redNeuronal.h"



using namespace std;

RedNeuronal::RedNeuronal(){};

void RedNeuronal::setAtributos(int numCapas, int *numNeuronasCapa, double factorAprendizaje = 0.25, double momentum = 0.9){

    this->numCapas = numCapas;
	this->factorAprendizaje = factorAprendizaje;
	this->momentum = momentum;

	//Asignar memoria
	capa = new Capa[numCapas];

	//capa entrada
    capa[0].setAtributos(0, TIPO_CAPA_INPUT, numNeuronasCapa[0], 0, &capa[1],factorAprendizaje,momentum);

	//capas ocultas
    for (int i=1; i<numCapas-1; ++i)
		capa[i].setAtributos(i, TIPO_CAPA_HIDDEN, numNeuronasCapa[i], &capa[i-1], &capa[i+1],factorAprendizaje,momentum);

	//Capa salida
	capa[numCapas-1].setAtributos(numCapas-1, TIPO_CAPA_OUTPUT, numNeuronasCapa[numCapas-1], &capa[numCapas-2],0,factorAprendizaje,momentum);


    //Asignar memoria arrays de valores de entrada, Ii, Oi, Di
	entradaRed = new double[capa[0].numNeuronas];
    salidaRed = new double[capa[numCapas-1].numNeuronas];
    salidaEsperada = new double[capa[numCapas-1].numNeuronas];


    //Inicializar con pesos aleatorios
    pesosAleatoriosRed();
}

void RedNeuronal::pesosAleatoriosRed(){

    for (int i=1; i < numCapas; ++i)
		capa[i].pesosAleatorios();
}


double RedNeuronal::entrenarRed_MSecuencial(double errorMin){

	if(DEBUG_RN) mostrarRedN();

	this->errorMin = errorMin;

	double testError = 100;

    epocaActual = 0;

	while (testError >= errorMin) {

		feedForward();
		testError = calcularError();
		backPropagate();

		epocaActual++;
	}

	return testError;

}

void RedNeuronal::feedForward(){

	
    for (int i=1; i < numCapas; ++i)
		capa[i].propagate(salidaRed);

	if(DEBUG_RN) mostrarRedN();
}

double RedNeuronal::calcularError(){
	double suma = 0;

	for(int i=0; i < capa[numCapas-1].numNeuronas; ++i)
		suma += (salidaEsperada[i] - salidaRed[i]) * (salidaEsperada[i] - salidaRed[i]);

	suma /= 2;

	return suma;
}

void RedNeuronal::backPropagate(){

	int i;
    for (i = numCapas-1; i >= 1 ; --i)	
		capa[i].backPropagate(salidaEsperada);

	if(DEBUG_RN) mostrarRedN();
}


void RedNeuronal::setEntrada(double* entradaRed){

	this->entradaRed = entradaRed;

	//Inicializar valores de salida de neuronas capa entrada
	int i;
	for (i=0; i < capa[0].numNeuronas; ++i)
		capa[0].neurona[i].salida = entradaRed[i];
	capa[0].neurona[i].salida = 1; //BIAS
}

void RedNeuronal::setSalidaEsperada(double* salidaEsperada){
	this->salidaEsperada = salidaEsperada;
}


void RedNeuronal::printSalidas(){
    /*
	for(int i=0; i < capa[numCapas-1].numNeuronas; ++i)
		cout<<salidaRed[i]<<" ";
	cout<<endl;
    */
    cout<<salidaRed[0];
}

void RedNeuronal::cargarDatosRed(const char *archivoRed){

    ifstream ficheroRed(archivoRed);

	ficheroRed>>factorAprendizaje>>momentum;

	ficheroRed>>numCapas;

	int* layerSizes = new int[numCapas];

	int i;
	for(i= 0; i<numCapas; ++i)
		ficheroRed>>layerSizes[i];

	setAtributos(numCapas,layerSizes,factorAprendizaje,momentum);

	for(i= 1; i<numCapas; ++i)
		capa[i].cargarDatosCapa(&ficheroRed);

    ficheroRed.close();
}

void RedNeuronal::guardarDatosRed(const char *archivoRed){



    ofstream ficheroRed(archivoRed);

	ficheroRed<<factorAprendizaje<<" "<<momentum<<endl;

	ficheroRed<<numCapas<<endl;

	int i;
	for(i= 0; i<numCapas; ++i)
		ficheroRed<<capa[i].numNeuronas<<" ";
	
	ficheroRed<<endl;

	for(i= 1; i<numCapas; ++i)
		capa[i].guardarDatosCapa(&ficheroRed);

    ficheroRed.close();
}

void RedNeuronal::mostrarRedN(){

	ofstream ficheroRed("RedMostrar.txt");

	ficheroRed<<"numCapas = "<<numCapas<<endl;
	ficheroRed<<"factorAprendizaje = "<<factorAprendizaje<<endl;
	ficheroRed<<"momentum = "<<momentum<<endl<<endl;

	for (int i=0; i < numCapas; ++i)
		capa[i].mostrarCapa();

	//cout<<"TERMINO\n";

	ficheroRed.close();
}


RedNeuronal::~RedNeuronal(){
}
