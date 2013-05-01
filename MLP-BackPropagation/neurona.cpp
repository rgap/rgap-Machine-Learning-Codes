
#include "neurona.h"
#include <math.h>

using namespace std;

Neurona::Neurona(){
	resPropag = 0;
	activacion = 0;
	salida = 0;
	numConexiones = 0;
	delta = 0;
}

void Neurona::setAtributos(int numNeurona,int &numCapa, int numConexionesEntrantes, bool bias){
	this->numNeurona = numNeurona;
	this->numCapa = numCapa;
	this->bias = bias;

	if(bias)
		conexion = 0;
	else
		conexion = new Conexion[numConexionesEntrantes];
}

void Neurona::setResPropagacion(double resPropag){
	this->resPropag = resPropag;
}

double Neurona::calcularSalida(){ // oj

	if(bias) {salida = 1; return salida;}

	activacion = funcionActivacion(resPropag);

	salida = funcionTransferencia(activacion);

	return salida;
}

double Neurona::funcionActivacion(double &x){ //aj
	return (1.0/(1+exp(-x)));
}

double Neurona::funcionTransferencia(double &x){ //Funcion de salida
	return x;

}

void Neurona::setDelta(double error){
	delta = activacion * (1 - activacion) * error;
}

void Neurona::setConexion(Neurona* neuronaOrigen){
	conexion[numConexiones].neuronaOrigen = neuronaOrigen;

	numConexiones++;
}

void Neurona::cargarDatosNeurona(ifstream* ficheroRed){

	*ficheroRed>>delta;
	
	*ficheroRed>>numConexiones;
	for (int i=0; i < numConexiones; ++i)
		*ficheroRed>>conexion[i].valorPeso>>conexion[i].dPeso;

}

void Neurona::guardarDatosNeurona(ofstream *ficheroRed){

	*ficheroRed<<delta<<endl;

	*ficheroRed<<numConexiones<<endl;
	for (int i=0; i < numConexiones; ++i)
		*ficheroRed<<conexion[i].valorPeso<<" "<<conexion[i].dPeso<<endl;

}

void Neurona::mostrarNeurona(){

	ofstream ficheroRed("RedMostrar.txt",ofstream::app);

	ficheroRed<<"-------------------------------------------- \n";

	ficheroRed<<"numNeurona = "<<numNeurona<<endl;
	ficheroRed<<"numCapa = "<<numCapa<<endl;
	ficheroRed<<"es bias = "<<bias<<endl; 
	ficheroRed<<"delta = "<<delta<<endl;
	ficheroRed<<"--------------- "<<endl; 
	ficheroRed<<"resPropag = "<<resPropag<<endl;
	ficheroRed<<"activacion = "<<activacion<<endl;
	ficheroRed<<"salida = "<<salida<<endl<<endl;

	
	
	for (int i=0; i < numConexiones; ++i){
		ficheroRed<<"Conexion #"<< i<<" : ";
		ficheroRed<<"W("<<conexion[i].neuronaOrigen->numNeurona<<","<<numNeurona<<") = "<<conexion[i].valorPeso<<endl;
	}

	ficheroRed<<"-------------------------------------------- \n";

	ficheroRed.close();
}

Neurona::~Neurona(){
}
