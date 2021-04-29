#include <iostream>
#include <cstdlib>
#include "matrix.hpp"
#include <math.h>

using namespace std;

int main() {
	cout << "Matrix Class\n\n\n";

	/*Primero necesitamos un espacio en la memoria que almacene una matriz.*/
	Matrix matGo;

	/*Ya que el espacio "matGo" en la memoria es tan solo una etiqueta se necesita definir que tan grande y que tipo de objetos contiene.*/
	/**/matGo.diagonalIgualAUno(3, 3);
	/**//**/


	/*Ponemos unos numeros al azar en nuestra matriz.*/
	/**/matGo.accessMat(0, 0, 0.1);
	/**/matGo.accessMat(1, 0, 1);
	/**/matGo.accessMat(2, 0, 3);

	/**/matGo.accessMat(0, 1, 1);
	/**/matGo.accessMat(1, 1, 0);
	/**/matGo.accessMat(2, 1, 3.01);

	/**/matGo.accessMat(0, 2, 1);
	/**/matGo.accessMat(1, 2, 111);
	/**/matGo.accessMat(2, 2, 23.2222);
	/**//**/

	matGo.escMat();
	/*El metodo determinant() regresa un double, entonces inicializamos DET para que reciba el double que arroja el metodo.*/
	/**/double DET = matGo.determinant();
	/**//**/
	
	/*Imprimimos el resultado.*/
	/**/cout << "Det(M) = " << DET;	
	/**//**/
	cout << "\n\n\n";
	return 0;
}