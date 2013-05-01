#ifndef IMGOPERACIONES_H
#define IMGOPERACIONES_H

#pragma once


#include <time.h>
#include <stdlib.h>


// Valor aleatorio [Low, High]
static double randomVal(double Low, double High){
	//srand ( time(NULL) );
    return ((double) rand() / RAND_MAX) * (High-Low) + Low;
}


#endif // IMGOPERACIONES_H
