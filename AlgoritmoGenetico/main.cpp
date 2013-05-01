
#include <iostream>

#include "algoritmoGenetico.h"

using namespace std;

int main()
{

	string archivoAG_s = "AGMostrar.txt";
	const char* archivoAG = archivoAG_s.c_str ();

	int tamPoblacion = 20;
	int longitudCromosomas = 10;
	double probCrossOver = 0.5;
	double probMutacion = 0.1;
	double maxMutacion = 0.01;
	int numElite = 3;
	int numCopiasElite = 1;



	AlgoritmoGenetico AG(tamPoblacion, longitudCromosomas, probCrossOver, probMutacion, maxMutacion, numElite, numCopiasElite);

	AG.generarSiguienteGeneracion();


    return 0;
}
