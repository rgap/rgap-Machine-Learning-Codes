
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>

#include "capa.h"
#include "redNeuronal.h"

using namespace std;


// Valor aleatorio [Low, High]
static double randomVal(double Low, double High){
	//srand ( time(NULL) );
    return ((double) rand() / RAND_MAX) * (High-Low) + Low;
}      

Capa::Capa(){
}

void Capa::setAtributos(int numCapa, int tipoCapa, int numNeuronas, Capa* capaAnterior, Capa* capaSiguiente,double factorAprendizaje, double momentum) 
{
	this->numCapa = numCapa;
	this->tipoCapa = tipoCapa;
	this->numNeuronas = numNeuronas;
	this->capaAnterior = capaAnterior;
	this->capaSiguiente = capaSiguiente;

	this->factorAprendizaje = factorAprendizaje;
	this->momentum = momentum;

	///////////////// Asignar memoria //////////////

	if(tipoCapa != TIPO_CAPA_OUTPUT){
		this->numNeuronasTotal = numNeuronas + 1;
		neurona = new Neurona[numNeuronasTotal]; //neuronas de la capa
		
		neurona[numNeuronas].setAtributos(numNeuronas,numCapa,0,1); // BIAS
	}
	else{
		this->numNeuronasTotal = numNeuronas; //considerando BIAS
		neurona = new Neurona[numNeuronasTotal]; //neuronas de la capa
	}

	
	///////////////// Inicializar neuronas //////////////

	//Si no es la capa entrada => tiene pesos de entrada
    if (tipoCapa != TIPO_CAPA_INPUT){

		int i,j;
		for(i=0; i < numNeuronas; ++i){ // neuronas no BIAS
			neurona[i].setAtributos(i, numCapa, capaAnterior->numNeuronasTotal, 0);

			for(j=0; j< capaAnterior->numNeuronasTotal; ++j) //neuronas de capa anterior
				neurona[i].setConexion(& capaAnterior->neurona[j]);
		}

    }
    else{

		this->capaAnterior = 0;

		for(int i=0; i < numNeuronas; ++i) // neuronas no BIAS
			neurona[i].setAtributos(i, numCapa, 0, 0);
	}

}

// Pesos hacia esta capa aleatorios
void Capa::pesosAleatorios(){

	int i,j;
    for (i=0; i < numNeuronas; ++i){
		for (j=0; j < neurona[i].numConexiones; ++j){
			neurona[i].conexion[j].valorPeso = randomVal(-0.5, 0.5);
			neurona[i].conexion[j].dPeso = 0;
		}
    }
}


void Capa::propagate(double* salidaCapa){

    for (int i=0; i < numNeuronasTotal; ++i){
		if(!neurona[i].bias)
			neurona[i].setResPropagacion( funcionPropagacion(&neurona[i]) );

		salidaCapa[i] = neurona[i].calcularSalida();
	}

}

double Capa::funcionPropagacion(Neurona *neurona){

	double sumaPonderada = 0;
	for (int i=0; i < neurona->numConexiones; ++i) //Sumatoria
		sumaPonderada += neurona->conexion[i].valorPeso * neurona->conexion[i].neuronaOrigen->salida;

	return sumaPonderada;
}

void Capa::backPropagate(double* salidaEsperada){

	if(tipoCapa != TIPO_CAPA_OUTPUT){

		double suma;

		int i,k;
		for(i=0; i < numNeuronasTotal; ++i){

			//suma = delta_k * w_kj   de j a k
			suma = 0; //delta = fact(neti) * suma

			//Capa siguiente 
			for(k=0; k < capaSiguiente->numNeuronas; ++k)
				suma += capaSiguiente->neurona[k].conexion[i].valorPeso * capaSiguiente->neurona[k].delta;

			neurona[i].setDelta(suma); 

			actualizarPesos(&neurona[i]); //Asignar nuevos pesos a las conexiones entrantes

		}

	} else{

		double error;

		for (int i=0; i < numNeuronasTotal; ++i){

			error = salidaEsperada[i] - neurona[i].salida;

			neurona[i].setDelta(error); 
			
			//Asignar nuevos pesos a las conexiones entrantes
			actualizarPesos(&neurona[i]);
		}
	}
}


void Capa::actualizarPesos(Neurona* neurona){

	for (int i=0; i < neurona->numConexiones; ++i){ //Sumatoria
		neurona->conexion[i].dPeso = factorAprendizaje * neurona->conexion[i].neuronaOrigen->salida * neurona->delta
									+ momentum * neurona->conexion[i].dPeso;
		//actualizar peso
		neurona->conexion[i].valorPeso += neurona->conexion[i].dPeso;
	}
}

void Capa::cargarDatosCapa(ifstream *ficheroRed){

	for (int i=0; i < numNeuronasTotal; ++i)
		neurona[i].cargarDatosNeurona(ficheroRed);

}

void Capa::guardarDatosCapa(ofstream *ficheroRed){

	for (int i=0; i < numNeuronasTotal; ++i)
		neurona[i].guardarDatosNeurona(ficheroRed);

}

void Capa::mostrarCapa(){
	ofstream ficheroRed("RedMostrar.txt",ofstream::app);

	ficheroRed<<"#######################  numCapa = "<<numCapa<<" ####################### "<<endl<<endl;

	if(numCapa){
		ficheroRed<<"Conexiones entre Capas \n";
		ficheroRed<<"Capa origen: "<<capaAnterior->numCapa<<" ->  Capa destino: "<<numCapa<<endl<<endl;
	}

	ficheroRed<<"tipoCapa = "<<tipoCapa<<endl;
	ficheroRed<<"numNeuronas = "<<numNeuronas<<endl;
	ficheroRed<<"numNeuronasTotal = "<<numNeuronasTotal<<endl;

	for (int i=0; i < numNeuronasTotal; ++i)
		neurona[i].mostrarNeurona();

	ficheroRed<<endl<<endl;

	ficheroRed.close();
}

Capa::~Capa(){

}



