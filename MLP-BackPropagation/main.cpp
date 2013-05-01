
#include <iostream>

#include "clasificador.h"

using namespace std;

int main()
{

	string archivoRed_s = "redNeuronal.dat";
	const char* archivoRed = archivoRed_s.c_str ();

	Clasificador clasificador;
	clasificador.cargarDatosClasif(archivoRed);

	double vectorCaracteristico[5] = {90, 140, 20, 12, 10};

    clasificador.clasificarEntradas(vectorCaracteristico);

    clasificador.printSalidas();

    return 0;
}

/*
#include <iostream>

#include "entrenamiento.h"

using namespace std;


int main(){

	Entrenamiento entrenamiento;


	//CREAR ARCHIVO PATRONES

	//int numMuestras = 18;
	//int numEntradas = 22;
	//int numSalidas = 1;
	//int* salida = new int[numSalidas];
	//salida[0] = 1;

	//entrenamiento.crearArchivoPatrones("patrones.dat","C:\\Users\\rgap\\Desktop\\PT-SKIN\\APLICACION\\CVHerpesCutaneo\\ImagenesPrueba\\HERPES_CUTANEO_INICIAL",numMuestras,numEntradas,salida,numSalidas);


    //RED NEURONAL

    double errorTotalMin = 0.001;

    int numCapas = 3;
    int layerSizes[] = { 5, 6, 1};

    //Min error Backpropagation
    double minErrorRed = 0.001;

    double factorAprendizaje = 0.5;
    double momentum = 0.3;


    Clasificador clasificador(numCapas, layerSizes, factorAprendizaje, momentum);

    entrenamiento = Entrenamiento(&clasificador);


    string archivoRed_s = "redNeuronal.dat";
    string archivoPatrones_s = "patrones.dat";

    const char* archivoRed = archivoRed_s.c_str ();
    const char* archivoPatrones = archivoPatrones_s.c_str ();

    entrenamiento.entrenarConPatrones(archivoRed, archivoPatrones, errorTotalMin, minErrorRed);


    entrenamiento.mostrarRN();


    return 0;

}
*/
