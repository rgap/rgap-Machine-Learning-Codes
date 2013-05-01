#include <iostream>
#include <fstream>

#include "algoritmoGenetico.h"


using namespace std;

#define MAX_VALUE 100

AlgoritmoGenetico::AlgoritmoGenetico(){};

AlgoritmoGenetico::AlgoritmoGenetico(int tamPoblacion, int longitudCromosoma, double probCrossOver, double probMutacion, 
					double maxMutacion, int numElite, int numCopiasElite){

	this->probCrossOver = probCrossOver; //probabilidad de que ocurra crossover
	this->probMutacion = probMutacion;
	this->maxMutacion = maxMutacion; //valor maximo (+\-) en que puede cambiar un nucleotido

	this->numElite = numElite; //numero de cromosomas mas aptos
	this->numCopiasElite = numCopiasElite; //numero de copias de cada cromosoma 'elite' que pasara a la siguiente generacion


	//inicializar poblacion
	poblacion = Poblacion(tamPoblacion, longitudCromosoma);

}

void AlgoritmoGenetico::generarSiguienteGeneracion(){

	//Agrega los cromosomas Elite a la poblacion actual
	agregarElite();

	vector<Cromosoma*> hijos;

	poblacion.individuo.clear();

	while(poblacion.individuo.size() < poblacion.tamPoblacion){

		hijos = crossOver(escogerCromosoma(), escogerCromosoma());

		hijos[0]->mutar(probMutacion, maxMutacion);
		hijos[1]->mutar(probMutacion, maxMutacion);

		poblacion.individuo.push_back(hijos[0]);
		poblacion.individuo.push_back(hijos[1]);
	}

}

Cromosoma* AlgoritmoGenetico::escogerCromosoma(){

	Cromosoma* cromosomaActual;

	double temp = 0.0;
	double rand = randomVal(0,1) * poblacion.totalFitness;

	for(unsigned int i = 0; i < poblacion.tamPoblacion; ++i){

		cromosomaActual = poblacion.individuo[i];

		temp += cromosomaActual->fitness;

		if(temp >= rand) //Ruleta
			return poblacion.individuo[i];
	}

	return poblacion.individuo[(int)(poblacion.tamPoblacion * randomVal(0,1))] ;
}

vector<Cromosoma*> AlgoritmoGenetico::crossOver(Cromosoma* madre, Cromosoma* padre){

	vector<Cromosoma*> hijos;

	if(randomVal(0,1) > probCrossOver || madre == padre){ 

		hijos[0] = madre;
		hijos[1] = padre;

		return hijos;
	}

	//punto de cruzamiento aleatorio entre 1 y la longitud del cromosoma

	unsigned int puntoCruce = (int)(randomVal(0,1) * (poblacion.longitudCromosoma - 2)) + 1;

	hijos[0] = new Cromosoma(poblacion.longitudCromosoma);
	hijos[1] = new Cromosoma(poblacion.longitudCromosoma);

	unsigned int i;
	//secuencias de los hijos
	for (i = 0; i < puntoCruce; ++i){
		hijos[0]->secuencia[i] = madre->secuencia[i];
		hijos[1]->secuencia[i] = padre->secuencia[i];
	}

	for (i = puntoCruce; i < poblacion.longitudCromosoma; ++i){
		hijos[0]->secuencia[i] = padre->secuencia[i];
		hijos[1]->secuencia[i] = madre->secuencia[i];
	}

	return hijos;
}


void AlgoritmoGenetico::agregarElite(){

	//Cromosomas de mayor a menor de acuerdo a su fitness
	sort(poblacion.individuo.begin(), poblacion.individuo.end(),poblacion.comparadorFitness); 

	vector<Cromosoma*> individuoElite;

	int i,j;
	for(i = 0; i < numElite; ++i)
		individuoElite.push_back(poblacion.individuo[i]);

	for(i = 0; i < numElite; ++i){
		for(j = 0; j < numCopiasElite; ++j){
			poblacion.individuo.insert(poblacion.individuo.begin(),individuoElite[i]); // agregar los Elite en la primera posicion 

			// agrega los Elite en una posicion aleatoria
			//poblacion.add((int)(Aleatorio.getRandom(false) * poblacion.size()), tempCromos[i].clone());
		}
	}

}


//Calcular fitness maximo, minimo, promedio y total en la poblacion
void AlgoritmoGenetico::actualizarIndicadoresFitness(){

	double max = 0.0;
	double min = MAX_VALUE;
	double total = 0.0;

	double tempPromedioTotal = 0.0;
	double temp = 0.0;

	poblacion.peorFitness = MAX_VALUE;
	poblacion.mejorFitness = poblacion.promedioFitness = poblacion.totalFitness = 0.0;

	for(unsigned int i = 0; i < poblacion.tamPoblacion; ++i){

		temp = poblacion.individuo[i]->fitness;

		total += temp;
		tempPromedioTotal += temp;

		if(temp > max){ 
			max = temp;
			poblacion.mejorCromosoma = poblacion.individuo[i];
		}

		if(temp < min)
			min = temp;
	}

	poblacion.totalFitness = total;
	poblacion.mejorFitness = max;
	poblacion.peorFitness = min;
	poblacion.promedioFitness = tempPromedioTotal / poblacion.tamPoblacion;
}

void AlgoritmoGenetico::mostrarAG(const char* archivoAG){

	ofstream ficheroAG(archivoAG);


	ficheroAG<<"Atributos AG"<<endl<<endl;

	ficheroAG<<"numElite = "<<numElite<<endl;
	ficheroAG<<"numCopiasElite = "<<numCopiasElite<<endl;
	ficheroAG<<"probCrossOver = "<<probCrossOver<<endl;
	ficheroAG<<"probMutacion = "<<probMutacion<<endl;
	ficheroAG<<"maxMutacion = "<<maxMutacion<<endl<<endl;

	ficheroAG<<"Atributos Poblacion"<<endl<<endl;

	ficheroAG<<"tamPoblacion = "<<poblacion.tamPoblacion<<endl;
	ficheroAG<<"longitudCromosoma = "<<poblacion.longitudCromosoma<<endl<<endl;

	ficheroAG<<"Indicadores"<<endl<<endl;

	ficheroAG<<"peorFitness = "<<poblacion.peorFitness<<endl;
	ficheroAG<<"promedioFitness = "<<poblacion.promedioFitness<<endl;
	ficheroAG<<"mejorFitness = "<<poblacion.mejorFitness<<endl;
	ficheroAG<<"totalFitness = "<<poblacion.totalFitness<<endl;

	ficheroAG<<"mejorCromosoma = "<<endl;

	unsigned int i,j;
	for(i=0; i < poblacion.longitudCromosoma; ++i)
		ficheroAG<<poblacion.mejorCromosoma->secuencia[i]<<"	";

	for(i=0; i < poblacion.tamPoblacion; ++i){
		ficheroAG<<i<<" : ";

		for(j=0; j < poblacion.longitudCromosoma; ++j){
			ficheroAG<<poblacion.individuo[i]->fitness<<endl;
			ficheroAG<<poblacion.individuo[i]->secuencia[j]<<"	";
		}
	}

	cout<<"TERMINO\n";

	ficheroAG.close();

}

AlgoritmoGenetico::~AlgoritmoGenetico(){
}
