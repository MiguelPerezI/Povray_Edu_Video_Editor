#include <iostream>
#include <cstdlib>
#include "VectorND.hpp"
#include "geometry.hpp"
#include "dodecahedron.hpp"
#include <math.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

void Dodecahedron::initDodecahedron(double radius, VectorND center) {

	printf("\n\nBegin Dodecahedron --->\n\n");
	this->radius = radius;
	this->center.initVectorNDType2(3);
	this->gold = 1.618;
	this->g1 = 1/1.618;
	this->g2 = (1/1.618) * (1/1.618);
	this->n = 20;
	this->inversion.initInversion(2.0, center);

	this->center.updateVector3D(center.access(0), center.access(1), center.access(2));
	this->vertex[0].initVectorND(3,	 this->g2*radius + center.access(0),      0.0*radius + center.access(1),      1.0*radius + center.access(2));
	this->vertex[1].initVectorND(3,	-this->g2*radius + center.access(0),      0.0*radius + center.access(1),      1.0*radius + center.access(2));
	this->vertex[2].initVectorND(3,	-this->g1*radius + center.access(0), this->g1*radius + center.access(1), this->g1*radius + center.access(2));
	this->vertex[3].initVectorND(3,	      0.0*radius + center.access(0),      1.0*radius + center.access(1), this->g2*radius + center.access(2));
	this->vertex[4].initVectorND(3,	 this->g1*radius + center.access(0), this->g1*radius + center.access(1), this->g1*radius + center.access(2));
	this->vertex[5].initVectorND(3,	   	  0.0*radius + center.access(0),     -1.0*radius + center.access(1), this->g2*radius + center.access(2));
	this->vertex[6].initVectorND(3,	 this->g1*radius + center.access(0),-this->g1*radius + center.access(1), this->g1*radius + center.access(2));
	this->vertex[7].initVectorND(3,	-this->g1*radius + center.access(0),-this->g1*radius + center.access(1), this->g1*radius + center.access(2));
	this->vertex[8].initVectorND(3,	 this->g2*radius + center.access(0),      0.0*radius + center.access(1),     -1.0*radius + center.access(2));
	this->vertex[9].initVectorND(3,	-this->g2*radius + center.access(0),      0.0*radius + center.access(1),     -1.0*radius + center.access(2));
	this->vertex[10].initVectorND(3,-this->g1*radius + center.access(0),-this->g1*radius + center.access(1),-this->g1*radius + center.access(2));
	this->vertex[11].initVectorND(3,   	  0.0*radius + center.access(0),     -1.0*radius + center.access(1),-this->g2*radius + center.access(2));
	this->vertex[12].initVectorND(3, this->g1*radius + center.access(0),-this->g1*radius + center.access(1),-this->g1*radius + center.access(2));
	this->vertex[13].initVectorND(3, this->g1*radius + center.access(0), this->g1*radius + center.access(1),-this->g1*radius + center.access(2));
	this->vertex[14].initVectorND(3,      0.0*radius + center.access(0),      1.0*radius + center.access(1),-this->g2*radius + center.access(2));
	this->vertex[15].initVectorND(3,-this->g1*radius + center.access(0), this->g1*radius + center.access(1),-this->g1*radius + center.access(2));
	this->vertex[16].initVectorND(3,      1.0*radius + center.access(0),-this->g2*radius + center.access(1),      0.0*radius + center.access(2));
	this->vertex[17].initVectorND(3,     -1.0*radius + center.access(0), this->g2*radius + center.access(1),      0.0*radius + center.access(2));
	this->vertex[18].initVectorND(3,     -1.0*radius + center.access(0),-this->g2*radius + center.access(1),      0.0*radius + center.access(2));
	this->vertex[19].initVectorND(3,      1.0*radius + center.access(0), this->g2*radius + center.access(1),      0.0*radius + center.access(2));

	this->mesh.initMatrixFacet(12, 3);
	this->mesh.inputFacet(0, 0, this->vertex[9], this->vertex[15], this->vertex[14]);
    this->mesh.inputFacet(0, 1, this->vertex[8], this->vertex[9], this->vertex[14]);
    this->mesh.inputFacet(0, 2, this->vertex[13], this->vertex[8], this->vertex[14]);
	
    this->mesh.inputFacet(1, 0, this->vertex[1], this->vertex[7], this->vertex[5]);
    this->mesh.inputFacet(1, 1, this->vertex[0], this->vertex[1], this->vertex[5]);
    this->mesh.inputFacet(1, 2, this->vertex[6], this->vertex[0], this->vertex[5]);
     
    this->mesh.inputFacet(2, 0, this->vertex[12], this->vertex[8], this->vertex[13]);
    this->mesh.inputFacet(2, 1, this->vertex[16], this->vertex[12], this->vertex[13]);
    this->mesh.inputFacet(2, 2, this->vertex[19], this->vertex[16], this->vertex[13]);
     
    this->mesh.inputFacet(3, 0, this->vertex[17], this->vertex[18], this->vertex[7]);
    this->mesh.inputFacet(3, 1, this->vertex[2], this->vertex[17], this->vertex[7]);
    this->mesh.inputFacet(3, 2, this->vertex[1], this->vertex[2], this->vertex[7]);
     
	this->mesh.inputFacet(4, 0, this->vertex[18], this->vertex[17], this->vertex[15]);
    this->mesh.inputFacet(4, 1, this->vertex[10], this->vertex[18], this->vertex[15]);
    this->mesh.inputFacet(4, 2, this->vertex[9], this->vertex[10], this->vertex[15]);
     
	this->mesh.inputFacet(5, 0, this->vertex[4], this->vertex[0], this->vertex[6]);
    this->mesh.inputFacet(5, 1, this->vertex[19], this->vertex[4], this->vertex[6]);
    this->mesh.inputFacet(5, 2, this->vertex[16], this->vertex[19], this->vertex[6]);
     
    this->mesh.inputFacet(6, 0, this->vertex[11], this->vertex[10], this->vertex[9]);
    this->mesh.inputFacet(6, 1, this->vertex[12], this->vertex[11], this->vertex[9]);
    this->mesh.inputFacet(6, 2, this->vertex[8], this->vertex[12], this->vertex[9]);
     
	this->mesh.inputFacet(7, 0, this->vertex[2], this->vertex[1], this->vertex[0]);
    this->mesh.inputFacet(7, 1, this->vertex[3], this->vertex[2], this->vertex[0]);
    this->mesh.inputFacet(7, 2, this->vertex[4], this->vertex[3], this->vertex[0]);
     
    this->mesh.inputFacet(8, 0, this->vertex[11], this->vertex[12], this->vertex[16]);
    this->mesh.inputFacet(8, 1, this->vertex[5], this->vertex[11], this->vertex[16]);
    this->mesh.inputFacet(8, 2, this->vertex[6], this->vertex[5], this->vertex[16]);
     
    this->mesh.inputFacet(9, 0, this->vertex[14], this->vertex[15], this->vertex[17]);
    this->mesh.inputFacet(9, 1, this->vertex[3], this->vertex[14], this->vertex[17]);
    this->mesh.inputFacet(9, 2, this->vertex[2], this->vertex[3], this->vertex[17]);
     
	this->mesh.inputFacet(10, 0, this->vertex[7], this->vertex[18], this->vertex[10]);
    this->mesh.inputFacet(10, 1, this->vertex[5], this->vertex[7], this->vertex[10]);
    this->mesh.inputFacet(10, 2, this->vertex[11], this->vertex[5], this->vertex[10]);
     
    this->mesh.inputFacet(11, 0, this->vertex[14], this->vertex[3], this->vertex[4]);
    this->mesh.inputFacet(11, 1, this->vertex[13], this->vertex[14], this->vertex[4]);
    this->mesh.inputFacet(11, 2, this->vertex[19], this->vertex[13], this->vertex[4]);

    this->arista.initMatrixArista(1, 30);
    this->arista.inputArista(0,  0, this->vertex[ 0], this->vertex[ 4]);
    this->arista.inputArista(0,  1, this->vertex[ 4], this->vertex[ 3]);
    this->arista.inputArista(0,  2, this->vertex[ 3], this->vertex[ 2]);
    this->arista.inputArista(0,  3, this->vertex[ 2], this->vertex[ 1]);
    this->arista.inputArista(0,  4, this->vertex[ 1], this->vertex[ 0]);
    this->arista.inputArista(0,  5, this->vertex[ 0], this->vertex[ 6]);
    this->arista.inputArista(0,  6, this->vertex[ 6], this->vertex[16]);
    this->arista.inputArista(0,  7, this->vertex[16], this->vertex[19]);
    this->arista.inputArista(0,  8, this->vertex[19], this->vertex[ 4]);
    this->arista.inputArista(0,  9, this->vertex[ 1], this->vertex[ 7]);
    this->arista.inputArista(0, 10, this->vertex[ 7], this->vertex[ 5]);
    this->arista.inputArista(0, 11, this->vertex[ 5], this->vertex[ 6]);
    this->arista.inputArista(0, 12, this->vertex[ 2], this->vertex[17]);
    this->arista.inputArista(0, 13, this->vertex[17], this->vertex[18]);
    this->arista.inputArista(0, 14, this->vertex[18], this->vertex[ 7]);
    this->arista.inputArista(0, 15, this->vertex[ 3], this->vertex[14]);
    this->arista.inputArista(0, 16, this->vertex[14], this->vertex[15]);
    this->arista.inputArista(0, 17, this->vertex[15], this->vertex[17]);
    this->arista.inputArista(0, 18, this->vertex[19], this->vertex[13]);
    this->arista.inputArista(0, 19, this->vertex[13], this->vertex[14]);
    this->arista.inputArista(0, 20, this->vertex[15], this->vertex[ 9]);
    this->arista.inputArista(0, 21, this->vertex[ 9], this->vertex[ 8]);
    this->arista.inputArista(0, 22, this->vertex[ 8], this->vertex[13]);
    this->arista.inputArista(0, 23, this->vertex[ 8], this->vertex[12]);
    this->arista.inputArista(0, 24, this->vertex[12], this->vertex[16]);
    this->arista.inputArista(0, 25, this->vertex[12], this->vertex[11]);
    this->arista.inputArista(0, 26, this->vertex[ 5], this->vertex[11]);
    this->arista.inputArista(0, 27, this->vertex[11], this->vertex[10]);
    this->arista.inputArista(0, 28, this->vertex[10], this->vertex[ 9]);
    this->arista.inputArista(0, 29, this->vertex[10], this->vertex[18]);
}

void Dodecahedron::updateDodecahedron(double newR, VectorND center) {
	
	this->center.updateVector3D(center.access(0), center.access(1), center.access(2));
	this->vertex[0].updateVector3D(  this->g2*newR + this->center.access(0),      0.0*newR + this->center.access(1),   	  1.0*newR + this->center.access(2));
	this->vertex[1].updateVector3D( -this->g2*newR + this->center.access(0),      0.0*newR + this->center.access(1),   	  1.0*newR + this->center.access(2));
	this->vertex[2].updateVector3D( -this->g1*newR + this->center.access(0), this->g1*newR + this->center.access(1), this->g1*newR + this->center.access(2));
	this->vertex[3].updateVector3D(       0.0*newR + this->center.access(0),      1.0*newR + this->center.access(1), this->g2*newR + this->center.access(2));
	this->vertex[4].updateVector3D(  this->g1*newR + this->center.access(0), this->g1*newR + this->center.access(1), this->g1*newR + this->center.access(2));
	this->vertex[5].updateVector3D(       0.0*newR + this->center.access(0),     -1.0*newR + this->center.access(1), this->g2*newR + this->center.access(2));
	this->vertex[6].updateVector3D(  this->g1*newR + this->center.access(0),-this->g1*newR + this->center.access(1), this->g1*newR + this->center.access(2));
	this->vertex[7].updateVector3D( -this->g1*newR + this->center.access(0),-this->g1*newR + this->center.access(1), this->g1*newR + this->center.access(2));
	this->vertex[8].updateVector3D(  this->g2*newR + this->center.access(0),      0.0*newR + this->center.access(1),     -1.0*newR + this->center.access(2));
	this->vertex[9].updateVector3D( -this->g2*newR + this->center.access(0),      0.0*newR + this->center.access(1),     -1.0*newR + this->center.access(2));
	this->vertex[10].updateVector3D(-this->g1*newR + this->center.access(0),-this->g1*newR + this->center.access(1),-this->g1*newR + this->center.access(2));
	this->vertex[11].updateVector3D(      0.0*newR + this->center.access(0),     -1.0*newR + this->center.access(1),-this->g2*newR + this->center.access(2));
	this->vertex[12].updateVector3D( this->g1*newR + this->center.access(0),-this->g1*newR + this->center.access(1),-this->g1*newR + this->center.access(2));
	this->vertex[13].updateVector3D( this->g1*newR + this->center.access(0), this->g1*newR + this->center.access(1),-this->g1*newR + this->center.access(2));
	this->vertex[14].updateVector3D(      0.0*newR + this->center.access(0),      1.0*newR + this->center.access(1),-this->g2*newR + this->center.access(2));
	this->vertex[15].updateVector3D(-this->g1*newR + this->center.access(0), this->g1*newR + this->center.access(1),-this->g1*newR + this->center.access(2));
	this->vertex[16].updateVector3D(      1.0*newR + this->center.access(0),-this->g2*newR + this->center.access(1),      0.0*newR + this->center.access(2));
	this->vertex[17].updateVector3D(     -1.0*newR + this->center.access(0), this->g2*newR + this->center.access(1),      0.0*newR + this->center.access(2));
	this->vertex[18].updateVector3D(     -1.0*newR + this->center.access(0),-this->g2*newR + this->center.access(1),      0.0*newR + this->center.access(2));
	this->vertex[19].updateVector3D(      1.0*newR + this->center.access(0), this->g2*newR + this->center.access(1),      0.0*newR + this->center.access(2));

	this->updateMesh();
}

void Dodecahedron::updateMesh() {

    this->mesh.updateFacet(0, 0, this->vertex[9], this->vertex[15], this->vertex[14]);
    this->mesh.updateFacet(0, 1, this->vertex[8], this->vertex[9], this->vertex[14]);
    this->mesh.updateFacet(0, 2, this->vertex[13], this->vertex[8], this->vertex[14]);
    
    this->mesh.updateFacet(1, 0, this->vertex[1], this->vertex[7], this->vertex[5]);
    this->mesh.updateFacet(1, 1, this->vertex[0], this->vertex[1], this->vertex[5]);
    this->mesh.updateFacet(1, 2, this->vertex[6], this->vertex[0], this->vertex[5]);
     
    this->mesh.updateFacet(2, 0, this->vertex[12], this->vertex[8], this->vertex[13]);
    this->mesh.updateFacet(2, 1, this->vertex[16], this->vertex[12], this->vertex[13]);
    this->mesh.updateFacet(2, 2, this->vertex[19], this->vertex[16], this->vertex[13]);
     
    this->mesh.updateFacet(3, 0, this->vertex[17], this->vertex[18], this->vertex[7]);
    this->mesh.updateFacet(3, 1, this->vertex[2], this->vertex[17], this->vertex[7]);
    this->mesh.updateFacet(3, 2, this->vertex[1], this->vertex[2], this->vertex[7]);
     
    this->mesh.updateFacet(4, 0, this->vertex[18], this->vertex[17], this->vertex[15]);
    this->mesh.updateFacet(4, 1, this->vertex[10], this->vertex[18], this->vertex[15]);
    this->mesh.updateFacet(4, 2, this->vertex[9], this->vertex[10], this->vertex[15]);
     
    this->mesh.updateFacet(5, 0, this->vertex[4], this->vertex[0], this->vertex[6]);
    this->mesh.updateFacet(5, 1, this->vertex[19], this->vertex[4], this->vertex[6]);
    this->mesh.updateFacet(5, 2, this->vertex[16], this->vertex[19], this->vertex[6]);
     
    this->mesh.updateFacet(6, 0, this->vertex[11], this->vertex[10], this->vertex[9]);
    this->mesh.updateFacet(6, 1, this->vertex[12], this->vertex[11], this->vertex[9]);
    this->mesh.updateFacet(6, 2, this->vertex[8], this->vertex[12], this->vertex[9]);
     
    this->mesh.updateFacet(7, 0, this->vertex[2], this->vertex[1], this->vertex[0]);
    this->mesh.updateFacet(7, 1, this->vertex[3], this->vertex[2], this->vertex[0]);
    this->mesh.updateFacet(7, 2, this->vertex[4], this->vertex[3], this->vertex[0]);
     
    this->mesh.updateFacet(8, 0, this->vertex[11], this->vertex[12], this->vertex[16]);
    this->mesh.updateFacet(8, 1, this->vertex[5], this->vertex[11], this->vertex[16]);
    this->mesh.updateFacet(8, 2, this->vertex[6], this->vertex[5], this->vertex[16]);
     
    this->mesh.updateFacet(9, 0, this->vertex[14], this->vertex[15], this->vertex[17]);
    this->mesh.updateFacet(9, 1, this->vertex[3], this->vertex[14], this->vertex[17]);
    this->mesh.updateFacet(9, 2, this->vertex[2], this->vertex[3], this->vertex[17]);
     
    this->mesh.updateFacet(10, 0, this->vertex[7], this->vertex[18], this->vertex[10]);
    this->mesh.updateFacet(10, 1, this->vertex[5], this->vertex[7], this->vertex[10]);
    this->mesh.updateFacet(10, 2, this->vertex[11], this->vertex[5], this->vertex[10]);
     
    this->mesh.updateFacet(11, 0, this->vertex[14], this->vertex[3], this->vertex[4]);
    this->mesh.updateFacet(11, 1, this->vertex[13], this->vertex[14], this->vertex[4]);
    this->mesh.updateFacet(11, 2, this->vertex[19], this->vertex[13], this->vertex[4]);

    this->arista.updateArista(0,  0, this->vertex[ 0], this->vertex[ 4]);
    this->arista.updateArista(0,  1, this->vertex[ 4], this->vertex[ 3]);
    this->arista.updateArista(0,  2, this->vertex[ 3], this->vertex[ 2]);
    this->arista.updateArista(0,  3, this->vertex[ 2], this->vertex[ 1]);
    this->arista.updateArista(0,  4, this->vertex[ 1], this->vertex[ 0]);
    this->arista.updateArista(0,  5, this->vertex[ 0], this->vertex[ 6]);
    this->arista.updateArista(0,  6, this->vertex[ 6], this->vertex[16]);
    this->arista.updateArista(0,  7, this->vertex[16], this->vertex[19]);
    this->arista.updateArista(0,  8, this->vertex[19], this->vertex[ 4]);
    this->arista.updateArista(0,  9, this->vertex[ 1], this->vertex[ 7]);
    this->arista.updateArista(0, 10, this->vertex[ 7], this->vertex[ 5]);
    this->arista.updateArista(0, 11, this->vertex[ 5], this->vertex[ 6]);
    this->arista.updateArista(0, 12, this->vertex[ 2], this->vertex[17]);
    this->arista.updateArista(0, 13, this->vertex[17], this->vertex[18]);
    this->arista.updateArista(0, 14, this->vertex[18], this->vertex[ 7]);
    this->arista.updateArista(0, 15, this->vertex[ 3], this->vertex[14]);
    this->arista.updateArista(0, 16, this->vertex[14], this->vertex[15]);
    this->arista.updateArista(0, 17, this->vertex[15], this->vertex[17]);
    this->arista.updateArista(0, 18, this->vertex[19], this->vertex[13]);
    this->arista.updateArista(0, 19, this->vertex[13], this->vertex[14]);
    this->arista.updateArista(0, 20, this->vertex[15], this->vertex[ 9]);
    this->arista.updateArista(0, 21, this->vertex[ 9], this->vertex[ 8]);
    this->arista.updateArista(0, 22, this->vertex[ 8], this->vertex[13]);
    this->arista.updateArista(0, 23, this->vertex[ 8], this->vertex[12]);
    this->arista.updateArista(0, 24, this->vertex[12], this->vertex[16]);
    this->arista.updateArista(0, 25, this->vertex[12], this->vertex[11]);
    this->arista.updateArista(0, 26, this->vertex[ 5], this->vertex[11]);
    this->arista.updateArista(0, 27, this->vertex[11], this->vertex[10]);
    this->arista.updateArista(0, 28, this->vertex[10], this->vertex[ 9]);
    this->arista.updateArista(0, 29, this->vertex[10], this->vertex[18]);
}

Dodecahedron Dodecahedron::dilateDodecahedron(VectorND resp, double lambda) {

    Dodecahedron ret;
    ret.initDodecahedron(this->radius, this->center);

    for (int i = 0; i < 20; i++)
        ret.vertex[i].dilate(ret.vertex[i], resp, lambda);
    
    ret.updateMesh();
    return ret;
}

void Dodecahedron::updateDodecahedronInversion() {
	
	for (int i = 0; i < 20; i++)
		this->inversion.applyInversion(this->vertex[i]);

	this->updateMesh();
}

void Dodecahedron::renderDodecahedron(int color, RotationMats U) {

	for (int i = 0; i < 12; i++)
		for (int j = 0; j < 3; j++) {
			this->mesh.getFacet(i, j).renderFacetOpenGL(color, U);
		}
}

MatrixFacet Dodecahedron::getMesh(int i) {
	return this->complex.getMatrixFacet(i);
}

Arista Dodecahedron::getArista(int i, int j) {
	return this->arista.getArista(i, j);
}

void Dodecahedron::initSmooth(int m) {

	printf("\n--->init dodecahedron smooth surface\n");
	this->complex.initMatrixFacetList(m + 1);
	this->complex.inputMatrixFacet(0, this->mesh);
	this->aux.initCrackFacet(this->mesh.getFacet(0, 0));
    this->complex.inversion.initInversion(2.0, this->center);

	int pow = 3;
	int cycle = 1;
	if (m > 0) {
		while (cycle < m + 1) {
			pow *= 6;
			this->complex.inputMatrixFacet2(cycle, 12, pow);
			//printf("-->Built mesh list of 12 of %d\n", pow);
			int mod = 0;

			//Accedemos a la matriz anterior.
			for (int i = 0; i < 12; i++)
			for (int j = 0; j < this->complex.getMatrixFacet(cycle - 1).getN(); j++) {
				this->aux.updateCrackFacet(this->complex.getMatrixFacet(cycle - 1).getFacet(i, j));
				this->complex.updateMatrixFacet(cycle, i, (6*j)  , this->aux.getFacet(0).pointA(), this->aux.getFacet(0).pointB(), this->aux.getFacet(0).pointC());
				this->complex.updateMatrixFacet(cycle, i, (6*j)+1, this->aux.getFacet(1).pointA(), this->aux.getFacet(1).pointB(), this->aux.getFacet(1).pointC());
				this->complex.updateMatrixFacet(cycle, i, (6*j)+2, this->aux.getFacet(2).pointA(), this->aux.getFacet(2).pointB(), this->aux.getFacet(2).pointC());
				this->complex.updateMatrixFacet(cycle, i, (6*j)+3, this->aux.getFacet(3).pointA(), this->aux.getFacet(3).pointB(), this->aux.getFacet(3).pointC());
				this->complex.updateMatrixFacet(cycle, i, (6*j)+4, this->aux.getFacet(4).pointA(), this->aux.getFacet(4).pointB(), this->aux.getFacet(4).pointC());
				this->complex.updateMatrixFacet(cycle, i, (6*j)+5, this->aux.getFacet(5).pointA(), this->aux.getFacet(5).pointB(), this->aux.getFacet(5).pointC());
				mod += 1;
			}

			cycle += 1;
		}
	}
}

void Dodecahedron::updateSmooth() {

	printf("\n--->update dodecahedron smooth surface\n");
	this->complex.updateMatrixFacet(0, this->mesh);
	int pow = 3;
	int cycle = 1;
	if (this->complex.getLength()-1 > 0) {
		while (cycle < this->complex.getLength()) {
			pow *= 6;
			for (int i = 0; i < 12; i++)
			for (int j = 0; j < this->complex.getMatrixFacet(cycle - 1).getN(); j++) {
				this->aux.updateCrackFacet(this->complex.getMatrixFacet(cycle - 1).getFacet(i, j));
				this->complex.updateMatrixFacet(cycle, i, (6*j)  , this->aux.getFacet(0).pointA(), this->aux.getFacet(0).pointB(), this->aux.getFacet(0).pointC());
				this->complex.updateMatrixFacet(cycle, i, (6*j)+1, this->aux.getFacet(1).pointA(), this->aux.getFacet(1).pointB(), this->aux.getFacet(1).pointC());
				this->complex.updateMatrixFacet(cycle, i, (6*j)+2, this->aux.getFacet(2).pointA(), this->aux.getFacet(2).pointB(), this->aux.getFacet(2).pointC());
				this->complex.updateMatrixFacet(cycle, i, (6*j)+3, this->aux.getFacet(3).pointA(), this->aux.getFacet(3).pointB(), this->aux.getFacet(3).pointC());
				this->complex.updateMatrixFacet(cycle, i, (6*j)+4, this->aux.getFacet(4).pointA(), this->aux.getFacet(4).pointB(), this->aux.getFacet(4).pointC());
				this->complex.updateMatrixFacet(cycle, i, (6*j)+5, this->aux.getFacet(5).pointA(), this->aux.getFacet(5).pointB(), this->aux.getFacet(5).pointC());
			}
			cycle += 1;
		}
	}
}

void Dodecahedron::updateSmoothInversion() {

	this->complex.updateMatrixFacet(0, this->mesh);
	int pow = 3;
	int cycle = 1;
    int len = this->complex.getLength();
	if (len - 1 > 0) {
		while (cycle < len) {
			pow *= 6;
			for (int i = 0; i < 12; i++)
				for (int j = 0; j < this->complex.getMatrixFacet(cycle - 1).getN(); j++) {
					this->aux.updateCrackFacet(this->complex.getMatrixFacet(cycle - 1).getFacet(i, j));
					this->complex.updateMatrixFacetInversion(cycle, i, (6*j)  , this->aux.getFacet(0).pointA(), this->aux.getFacet(0).pointB(), this->aux.getFacet(0).pointC());
					this->complex.updateMatrixFacetInversion(cycle, i, (6*j)+1, this->aux.getFacet(1).pointA(), this->aux.getFacet(1).pointB(), this->aux.getFacet(1).pointC());
					this->complex.updateMatrixFacetInversion(cycle, i, (6*j)+2, this->aux.getFacet(2).pointA(), this->aux.getFacet(2).pointB(), this->aux.getFacet(2).pointC());
					this->complex.updateMatrixFacetInversion(cycle, i, (6*j)+3, this->aux.getFacet(3).pointA(), this->aux.getFacet(3).pointB(), this->aux.getFacet(3).pointC());
					this->complex.updateMatrixFacetInversion(cycle, i, (6*j)+4, this->aux.getFacet(4).pointA(), this->aux.getFacet(4).pointB(), this->aux.getFacet(4).pointC());
					this->complex.updateMatrixFacetInversion(cycle, i, (6*j)+5, this->aux.getFacet(5).pointA(), this->aux.getFacet(5).pointB(), this->aux.getFacet(5).pointC());
				}
			cycle += 1;
		}
	}
}

void MatrixDodecahedron::initMatrixDodecahedron(int m, int n) {

    this->m = m;
    this->n = n;

    this->A = (Dodecahedron * *) malloc (m * sizeof(Dodecahedron*));
    for (int i = 0; i < m; i++)
        this->A[i] = (Dodecahedron *) malloc (n * sizeof(Dodecahedron));
}

void MatrixDodecahedron::initMatrixDodecahedronRotation(VectorND head, VectorND tail, double lambda) {

    this->U.initAxeRotation(head, tail, lambda);
}

void MatrixDodecahedron::rotateA(int i, int j) {

    for (int k = 0; k < 20; k++)
        this->U.rot3DAxe(this->A[i][j].vertex[k]);
    this->A[i][j].updateMesh();
}

void MatrixDodecahedron::updateMatrixDodecahedronRotation(VectorND head, VectorND tail, double lambda) {

    this->U.updateAxeRotation(head, tail, lambda);
}

void MatrixDodecahedron::initA(int i, int j, double radius, VectorND center) {

    this->A[i][j].initDodecahedron(radius, center);
}

void MatrixDodecahedron::renderMatrixDodecahedron(int mod, RotationMats U) {

    for (int i = 0; i < this->m; i++)
        for (int j = 0; j < this->n; j++)
            this->A[i][j].renderDodecahedron(mod, U);
}