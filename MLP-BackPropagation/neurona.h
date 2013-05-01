#ifndef NEURONA_H
#define NEURONA_H

#pragma once

#include "neurona.h"
#include <iostream>
#include <fstream>

class Neurona
{

private:

	struct Conexion{

		Neurona* neuronaOrigen;

		double valorPeso; //wij
		double  dPeso; // dj 
	};

public:

	int numConexiones;

	bool bias;

	int numNeurona;
	int numCapa;

	double resPropag; // netj
	double activacion; //aj
	double salida; // oj

	Conexion *conexion;

	double delta;


	Neurona();
	
	~Neurona();

	
	void setAtributos(int numNeurona,int &numCapa, int numConexionesEntrantes, bool bias);

	void setConexion(Neurona* neuronaOrigen);

	void setResPropagacion(double resPropag);

	/////////// Calculo de salida /////////////////

	double calcularSalida(); // oj

	double funcionActivacion(double &x); //aj

	double funcionTransferencia(double &x); //Funcion de salida

	void setDelta(double error);

	void cargarDatosNeurona(std::ifstream* ficheroRed);

	void guardarDatosNeurona(std::ofstream *ficheroRed);

	void mostrarNeurona();

};

#endif // NEURONA_H