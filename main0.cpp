#include <iostream>
#include <cstdlib>
#include "VectorND.hpp"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main() {
	printf("\n\nVectorND Class Testing Program\n\n");

	/*Primero necesitamos un espacio en la memoria que almacene un vector de dimensión-N.*/
	VectorND vecGo;
	VectorND vecGo0;

	/*Aquí nombramos la etiqueta para un vector de dim-3*/
	VectorND vecGo3D;

	/*Declaramos el tamaño y el contenido.*/
	vecGo.initVectorND(5, 1.0, 1.0, 1.0, 1.0, 1.0);
	vecGo0.zeroVectorND(5);

	/*Rellenamos la etiqueta*/
	vecGo3D.zeroVectorND(3);

	printf("\nVectorND object info:\n--> dim := %d\n--> Vec := ", vecGo.dim());
	vecGo.escVectorND();
	printf("\n\n");
	printf("\nVectorND object info:\n--> dim := %d\n--> Vec := ", vecGo0.dim());
	vecGo0.escVectorND();
	printf("\n\n");
	printf("\nVectorND object info:\n--> dim := %d\n--> Vec := ", vecGo3D.dim());
	vecGo3D.escVectorND();
	printf("\n--> Norm := %lg\n", vecGo3D.norm());

	printf("\n\n\n-->Udating VectorND\n");
	vecGo3D.updateVector3D(1.618, 0.000, 1.618 * 1.618);
	printf("--> Udated := ");
	vecGo3D.escVectorND();
	printf("\n\n-->Udating VectorND again...\n");
	vecGo3D.updateVector3D(1.0, 1.0, 1.0);
	printf("--> Udated := ");
	vecGo3D.escVectorND();
	printf("\n--> UdatedNorm := %lg\n", vecGo3D.norm());


	cout << "\n\n\n";
	return 0;
}