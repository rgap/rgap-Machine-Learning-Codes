
#include <iostream>
#include <dirent.h>
#include <errno.h>

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "entrenamiento.h"

using namespace std;


Entrenamiento::Entrenamiento(){}

Entrenamiento::Entrenamiento(Clasificador *clasificador){
	this->clasificador = clasificador;
}


void Entrenamiento::entrenarConPatrones(const char*archivoClasif, const char*archivoPatrones, double errorTotalMin, double minErrorRed){

	this->archivoPatrones = archivoPatrones;

	patrones = Patrones(archivoPatrones);

	patrones.almacenarPatrones();

	clasificador->setPatrones(&patrones);

	clasificador->entrenar(errorTotalMin, minErrorRed);

	clasificador->guardarDatosClasif(archivoClasif);
}

void Entrenamiento::crearArchivoPatrones(const char*archivoPatrones, const char*directorioBD, int numMuestras, int numDescrs, int* salida, int numSalidas){

    DIR *directorio;
    //struct dirent *dirp;
    //struct stat filestat;

    string rutaArchivo;

    if((directorio = opendir(directorioBD)) == NULL) {
        cout << "ERROR (" << errno << ") al abrir " << directorioBD << endl;
        return;
    }

    this->directorioBD = directorioBD;


    ofstream ficheroPatrones(archivoPatrones);

    /*

    ficheroPatrones<<numMuestras<<" "<<numDescrs<<" "<<numSalidas<<endl;

	procesamientoImagen.definirDescriptores(numDescrs);

    //Leer directorio

    while ((dirp = readdir(directorio)) != NULL){

        cout<<"Imagen: "<<dirp->d_name<<endl;

        rutaArchivo = (string)directorioBD + "\\" + dirp->d_name;

        if (stat( rutaArchivo.c_str(), &filestat )) continue;
        if (S_ISDIR( filestat.st_mode )) continue;


        imagenActual = Image(rutaArchivo.c_str(),1);


        procesamientoImagen.setImagen(&imagenActual);

        //PREPROCESAMIENTO
        procesamientoImagen.supresionRuido();

        procesamientoImagen.convertirGrises();


        //EXTRACCION CARACTERISTICAS
        procesamientoImagen.definirDescriptores(22);

        caracteristicasActual = procesamientoImagen.extraerDescriptores();

        procesamientoImagen.mostrarDescriptoresImagen();

        int i;
        for(i=0; i<procesamientoImagen.numDescriptores; ++i)
            ficheroPatrones<<caracteristicasActual[i]<<" ";

        for(i=0; i<numSalidas; ++i)
            ficheroPatrones<<salida[i]<<" ";

        ficheroPatrones<<endl;
    }

    closedir(directorio);

    */
	

	ficheroPatrones.close();
}

void Entrenamiento::mostrarDescripsActual(){
/*
	for(int i=0; i<procesamientoImagen.numDescriptores; ++i)
		cout<<caracteristicasActual<<" ";
*/
}

void Entrenamiento::mostrarRN(){
	clasificador->mostrarClasif();
}

Entrenamiento::~Entrenamiento(){

}
