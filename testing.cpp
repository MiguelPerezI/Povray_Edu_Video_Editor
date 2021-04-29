#include <iostream>
#include <cstdlib>
#include "VectorND.hpp"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "simplex.hpp"

using namespace std;

int main() {
	printf("\n\nTesting Simplex Program\n\n");

	VectorInt v, v0, v1, w, w0, w1, w2;
	v.initVectorInt(0, 0);

	MatrixInt path;
	MatrixVectorInt image;

	path.initMatrixInt(1, 3);

	path.updateA(0, 0, 0);
	path.updateA(0, 1, 0);
	path.updateA(0, 2, 0);
	

	TreeNode * ground;
	ground = new TreeNode();
	ground->plantSeed(v);

	TreeNode * ground0;
	ground0 = new TreeNode();
	ground0->plantSeed(v);
	

	ground->grow(5, ground);
	ground0->grow(4, ground0);

	//TreeNode * subTree;
	//subTree = auxFunctions(ground);
	ground = ground->localMapChoice(0);
	image = ground->initPath(path);

	ground->escTreeNode();
	

	printf("\n\nPath:\n");
	image.A[0][0].escVectorInt(); printf("-");
	image.A[0][1].escVectorInt(); printf("-");
	image.A[0][2].escVectorInt(); printf("-");
	image.A[0][3].escVectorInt();

	SimplexND genSimplex;
	genSimplex.initSimplexNDM(image);
	genSimplex.escSimplexND();
	printf("\n\n\n");

	SimplexRND realSimplex;
	VectorND a0, a1, a2, a3;
	a0.initVectorND(3, 0.0, 0.0, 0.0);
	a1.initVectorND(3, 1.0, 0.0, 0.0);
	a2.initVectorND(3, 0.0, 1.0, 0.0);
	a3.initVectorND(3, 0.0, 0.0, 1.0);
	realSimplex.initSimplex3D(0, a0, a1, a2, a3);

	MatrixVectorND AA, arrayImage;
	AA.zeroMatrixVector3D();
	AA.A[0][2].escVectorND();

	arrayImage.vectorArray3D(4); printf("\n");
	arrayImage.updateVectorArray3D(1, a3);
	arrayImage.escVectorArray3D();

	VectorND b0, b1, b2, b3;
	double ss = 1.0/sqrt(2);
	b0.initVectorND(3, 1.0, 0.0, -ss);
	b1.initVectorND(3,-1.0, 0.0, -ss);
	b2.initVectorND(3, 0.0, 1.0,  ss);
	b3.initVectorND(3, 0.0,-1.0,  ss);

	SimplexRND simplex3D;
	simplex3D.initSimplex3D(0, b0, b1, b2, b3);

	cout << "\n\n\n";
	return 0;
}