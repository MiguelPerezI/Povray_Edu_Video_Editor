#include <iostream>
#include <cstdlib>
#include "VectorND.hpp"
#include "geometry.hpp"
#include <math.h>
#include "matrix.hpp"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>


//////////////////////////////
//							//
//			FACETS			//
//							//
//////////////////////////////

void Facet::updateNormal() {

	this->aux1.subVectorND(this->b, this->a);
	this->aux2.subVectorND(this->c, this->a);
	this->normal.Cross3D(this->aux1, this->aux2);
}

void Facet::updateBarycenter() {

	this->barycenter.updateVector3D(
									0.33 * (this->a.access(0) + this->b.access(0) + this->c.access(0)),
									0.33 * (this->a.access(1) + this->b.access(1) + this->c.access(1)),
									0.33 * (this->a.access(2) + this->b.access(2) + this->c.access(2))
									);
}

void Facet::updatePrime() {
	this->aPrime.dilate(b, a, 0.5);
	this->bPrime.dilate(c, a, 0.5);
	this->cPrime.dilate(b, c, 0.5);
}

void Facet::initFacet(VectorND a, VectorND b, VectorND c) {

	if (a.dim() == 3 && b.dim() == 3 && c.dim() == 3) {

		this->a.initVectorNDType2(3);
		this->b.initVectorNDType2(3);
		this->c.initVectorNDType2(3);
		this->aPrime.initVectorNDType2(3);
		this->bPrime.initVectorNDType2(3);
		this->cPrime.initVectorNDType2(3);
		this->a.updateVector3DP(a);
		this->b.updateVector3DP(b);
		this->c.updateVector3DP(c);
		this->aux1.zeroVectorND(3);
		this->aux2.zeroVectorND(3);
		this->normal.zeroVectorND(3);
		this->barycenter.initVectorNDType2(3);
		this->updateNormal();
		this->updateBarycenter();
		this->updatePrime();
	}
}

void Facet::updatePoints(VectorND a, VectorND b, VectorND c) {

	this->a.updateVector3DP(a);
	this->b.updateVector3DP(b);
	this->c.updateVector3DP(c);
}

VectorND Facet::pointA() {
	return this->a;
}

VectorND Facet::pointB() {
	return this->b;
}

VectorND Facet::pointC() {
	return this->c;
}

VectorND Facet::normalK() {
	return this->normal;
}

void Facet::updateFacet(VectorND a, VectorND b, VectorND c) {

	this->updatePoints(a, b, c);
	this->updateNormal();
	this->updateBarycenter();
	this->updatePrime();
}

void Facet::renderFacetOpenGL(int mod, RotationMats U) {

	if (mod%8 == 0) glColor3ub(255, 255, 255);
	if (mod%8 == 1) glColor3ub(  0, 255, 255);
	if (mod%8 == 2) glColor3ub(  0,   0, 255);
	if (mod%8 == 3) glColor3ub(255,   0, 255);
	if (mod%8 == 4) glColor3ub(255, 255, 	 0);
	if (mod%8 == 5) glColor3ub(  0, 255, 	 0);
	if (mod%8 == 6) glColor3ub(255, 150, 	 0);
	if (mod%8 == 7) glColor3ub(255,   0, 	 0);

	U.rot3D(this->normal);
	glBegin(GL_TRIANGLES);
	glNormal3f( U.getAux().access(0), U.getAux().access(1), U.getAux().access(2));
	U.rot3D(this->a);
	glVertex3f( U.getAux().access(0), U.getAux().access(1), U.getAux().access(2));
	U.rot3D(this->b);
	glVertex3f( U.getAux().access(0), U.getAux().access(1), U.getAux().access(2));
	U.rot3D(this->c);
	glVertex3f( U.getAux().access(0), U.getAux().access(1), U.getAux().access(2));
	glEnd();
}

VectorND Facet::getBarycenter() {
	return this->barycenter;
}

VectorND Facet::getPrimeA() {
	return this->aPrime;
}

VectorND Facet::getPrimeB() {
	return this->bPrime;
}

VectorND Facet::getPrimeC() {
	return this->cPrime;
}

void MatrixFacet::initMatrixFacet(int m, int n) {

	this->m = m;
	this->n = n;
	this->A = (Facet**) malloc (m * sizeof(Facet*));
	if (this->A != NULL){
	    for(int i = 0; i < m; i++) {
	      this->A[i] = (Facet *) malloc (n * sizeof(Facet));
	      	if (this->A[i] == NULL){
	        	while(i > 0){
	          		free(this->A[--i]);
	          		this->A[i] = NULL;
	       		}
	        	break;
	      	}
	    }
  	}
}

void MatrixFacet::inputFacet(int i, int j, VectorND a, VectorND b, VectorND c) {

	this->A[i][j].initFacet(a, b, c);
}

void MatrixFacet::updateFacet(int i, int j, VectorND a, VectorND b, VectorND c) {

	this->A[i][j].updateFacet(a, b, c);
}

Facet MatrixFacet::getFacet(int i, int j) {

	return this->A[i][j];
}

int MatrixFacet::getM() {
	return this->m;
}

int MatrixFacet::getN() {
	return this->n;
}

void MatrixFacet::renderMatrixFacet(int mod, RotationMats U) {

	int count = 0;
	for (int i = 0; i < this->getM(); i++)
		for (int j = 0; j < this->getN(); j++) {
			this->getFacet(i, j).renderFacetOpenGL(i%8, U);

			count += 1;
		}
}

void MatrixFacetList::initMatrixFacetList(int n) {

	this->n = n;
	this->A = (MatrixFacet *) malloc (n * sizeof(MatrixFacet));
	
}

void MatrixFacetList::inputMatrixFacet(int m, MatrixFacet matrixFacet) {
	
	this->A[m].initMatrixFacet(matrixFacet.getM(), matrixFacet.getN());
	for (int i = 0; i < matrixFacet.getM(); i++)
		for (int j = 0; j < matrixFacet.getN(); j++) {
			this->A[m].inputFacet(i, j,
										matrixFacet.getFacet(i, j).pointA(),
										matrixFacet.getFacet(i, j).pointB(),
										matrixFacet.getFacet(i, j).pointC()
				);
		}
}

void MatrixFacetList::updateMatrixFacet(int m, MatrixFacet matrixFacet) {
	
	for (int i = 0; i < matrixFacet.getM(); i++)
		for (int j = 0; j < matrixFacet.getN(); j++) {
			this->A[m].updateFacet(i, j,
										matrixFacet.getFacet(i, j).pointA(),
										matrixFacet.getFacet(i, j).pointB(),
										matrixFacet.getFacet(i, j).pointC()
				);
		}
}

void MatrixFacetList::renderMatrixFacetList(int m, int mod, RotationMats U) {

	this->A[m].renderMatrixFacet(mod, U);
}

void MatrixFacetList::inputMatrixFacet2(int i, int m, int n) {
	
	this->A[i].initMatrixFacet(m, n);
	VectorND a, b, c;
	a.initVectorND(3, 0.0, 0.0, 0.0);
	b.initVectorND(3, 1.0, 0.0, 0.0);
	c.initVectorND(3, 0.0, 1.0, 0.0);
	for (int k = 0; k < m; k++)
		for (int j = 0; j < n; j++)
			this->A[i].inputFacet(k, j, a, b, c);
}

MatrixFacet MatrixFacetList::getMatrixFacet(int i) {
	return this->A[i];
}

int MatrixFacetList::getLength() {
	return this->n;
}

void MatrixFacetList::updateMatrixFacet(int i, int m, int n, VectorND a, VectorND b, VectorND c) {

	this->A[i].updateFacet(m, n, a, b, c);
}

void MatrixFacetList::updateMatrixFacetInversion(int i, int m, int n, VectorND a, VectorND b, VectorND c) {

	this->inversion.applyInversion(a);
	this->inversion.applyInversion(b);
	this->inversion.applyInversion(c);
	this->A[i].updateFacet(m, n, a, b, c);
}

void CrackFacet::initCrackFacet(Facet facet) {

	this->mainFacet.initFacet(facet.pointA(), facet.pointB(), facet.pointC());
	this->mesh.initMatrixFacet(1, 6);
	this->mesh.inputFacet(0, 0, facet.getPrimeB(),    facet.pointA(), facet.getBarycenter());
	this->mesh.inputFacet(0, 1,    facet.pointA(), facet.getPrimeA(), facet.getBarycenter());
	this->mesh.inputFacet(0, 2, facet.getPrimeA(),    facet.pointB(), facet.getBarycenter());
	this->mesh.inputFacet(0, 3,    facet.pointB(), facet.getPrimeC(), facet.getBarycenter());
	this->mesh.inputFacet(0, 4, facet.getPrimeC(),    facet.pointC(), facet.getBarycenter());
	this->mesh.inputFacet(0, 5,    facet.pointC(), facet.getPrimeB(), facet.getBarycenter());
}

void CrackFacet::updateCrackFacet(Facet facet) {

	this->mainFacet.updateFacet(facet.pointA(), facet.pointB(), facet.pointC());
	this->mesh.updateFacet(0, 0, facet.getPrimeB(),    facet.pointA(), facet.getBarycenter());
	this->mesh.updateFacet(0, 1,    facet.pointA(), facet.getPrimeA(), facet.getBarycenter());
	this->mesh.updateFacet(0, 2, facet.getPrimeA(),    facet.pointB(), facet.getBarycenter());
	this->mesh.updateFacet(0, 3,    facet.pointB(), facet.getPrimeC(), facet.getBarycenter());
	this->mesh.updateFacet(0, 4, facet.getPrimeC(),    facet.pointC(), facet.getBarycenter());
	this->mesh.updateFacet(0, 5,    facet.pointC(), facet.getPrimeB(), facet.getBarycenter());
}

Facet CrackFacet::getFacet(int i) {
	return this->mesh.getFacet(0, i);
}

void CrackFacet::updateSubFacet(int i, VectorND a, VectorND b, VectorND c) {
	return this->mesh.updateFacet(0, i, a, b, c);
}
//////////////////////////////
//							//
//			CUBES			//
//							//
//////////////////////////////




void CubeNeighborhood::initCubeNeighborhood(VectorND center, double radius, int color) {

	this->center = center;
	this->radius = radius;

	this->mesh.initMatrixFacet(1, 12);
	int i0 = center.access(0);
	int j0 = center.access(1);

	if ((i0 * j0 + 1)%8 == 0) this->color = 0;
	if ((i0 * j0 + 1)%8 == 1) this->color = 1;
	if ((i0 * j0 + 1)%8 == 2) this->color = 2;
	if ((i0 * j0 + 1)%8 == 3) this->color = 3;
	if ((i0 * j0 + 1)%8 == 4) this->color = 4;
	if ((i0 * j0 + 1)%8 == 5) this->color = 5;
	if ((i0 * j0 + 1)%8 == 6) this->color = 6;
	if ((i0 * j0 + 1)%8 == 7) this->color = 7;

	this->vertex[0].initVectorND(3, radius + center.access(0), radius + center.access(1), radius + center.access(2));
	this->vertex[1].initVectorND(3,-radius + center.access(0), radius + center.access(1), radius + center.access(2));
	this->vertex[2].initVectorND(3,-radius + center.access(0),-radius + center.access(1), radius + center.access(2));
	this->vertex[3].initVectorND(3, radius + center.access(0),-radius + center.access(1), radius + center.access(2));
	this->vertex[4].initVectorND(3, radius + center.access(0), radius + center.access(1),-radius + center.access(2));
	this->vertex[5].initVectorND(3,-radius + center.access(0), radius + center.access(1),-radius + center.access(2));
	this->vertex[6].initVectorND(3,-radius + center.access(0),-radius + center.access(1),-radius + center.access(2));
	this->vertex[7].initVectorND(3, radius + center.access(0),-radius + center.access(1),-radius + center.access(2));


	this->mesh.inputFacet(0, 0, this->vertex[0], this->vertex[1], this->vertex[2]);
	this->mesh.inputFacet(0, 1, this->vertex[2], this->vertex[3], this->vertex[0]);

	this->mesh.inputFacet(0, 2, this->vertex[4], this->vertex[7], this->vertex[6]);
	this->mesh.inputFacet(0, 3, this->vertex[6], this->vertex[5], this->vertex[4]);

	this->mesh.inputFacet(0, 4, this->vertex[0], this->vertex[3], this->vertex[7]);
	this->mesh.inputFacet(0, 5, this->vertex[7], this->vertex[4], this->vertex[0]);

//	this->mesh.inputFacet(0, 4, this->vertex[1], this->vertex[5], this->vertex[6]);
//	this->mesh.inputFacet(0, 5, this->vertex[6], this->vertex[2], this->vertex[1]);
//
//	this->mesh.inputFacet(0, 4, this->vertex[3], this->vertex[2], this->vertex[6]);
//	this->mesh.inputFacet(0, 5, this->vertex[6], this->vertex[7], this->vertex[3]);
}

void CubeNeighborhood::renderCubeNeighborhood(RotationMats U) {

	this->mesh.getFacet(0, 0).renderFacetOpenGL(0, U);
	this->mesh.getFacet(0, 1).renderFacetOpenGL(0, U);
	this->mesh.getFacet(0, 2).renderFacetOpenGL(0, U);
	this->mesh.getFacet(0, 3).renderFacetOpenGL(0, U);
	this->mesh.getFacet(0, 4).renderFacetOpenGL(0, U);
	this->mesh.getFacet(0, 5).renderFacetOpenGL(0, U);
}

VectorND CubeNeighborhood::getVertex(int i) {
		return this->vertex[i];
}

VectorND CubeNeighborhood::getCenter() {
		return this->center;
}

double CubeNeighborhood::getRadius() {
		return this->radius;
}

Facet CubeNeighborhood::getFacet(int i) {
		return this->mesh.getFacet(0, i);
}

void CubeNeighborhood::updateRadius(double newR) {

	this->radius = newR;

	this->vertex[0].updateVector3D( newR + center.access(0), newR + center.access(1), newR + center.access(2));
	this->vertex[1].updateVector3D(-newR + center.access(0), newR + center.access(1), newR + center.access(2));
	this->vertex[2].updateVector3D(-newR + center.access(0),-newR + center.access(1), newR + center.access(2));
	this->vertex[3].updateVector3D( newR + center.access(0),-newR + center.access(1), newR + center.access(2));
	this->vertex[4].updateVector3D( newR + center.access(0), newR + center.access(1),-newR + center.access(2));
	this->vertex[5].updateVector3D(-newR + center.access(0), newR + center.access(1),-newR + center.access(2));
	this->vertex[6].updateVector3D(-newR + center.access(0),-newR + center.access(1),-newR + center.access(2));
	this->vertex[7].updateVector3D( newR + center.access(0),-newR + center.access(1),-newR + center.access(2));


	this->mesh.updateFacet(0, 0, this->vertex[0], this->vertex[1], this->vertex[2]);
	this->mesh.updateFacet(0, 1, this->vertex[2], this->vertex[3], this->vertex[0]);

	this->mesh.updateFacet(0, 2, this->vertex[4], this->vertex[7], this->vertex[6]);
	this->mesh.updateFacet(0, 3, this->vertex[6], this->vertex[5], this->vertex[4]);

	this->mesh.updateFacet(0, 4, this->vertex[0], this->vertex[3], this->vertex[7]);
	this->mesh.updateFacet(0, 5, this->vertex[7], this->vertex[4], this->vertex[0]);
}

void CubeNeighborhood::updateCenter(VectorND newCenter) {

	this->center = newCenter;
	
	int i0 = newCenter.access(0);
	int j0 = newCenter.access(1);

	if ((i0 * j0 + 1)%8 == 0) this->color = 0;
	if ((i0 * j0 + 1)%8 == 1) this->color = 1;
	if ((i0 * j0 + 1)%8 == 2) this->color = 2;
	if ((i0 * j0 + 1)%8 == 3) this->color = 3;
	if ((i0 * j0 + 1)%8 == 4) this->color = 4;
	if ((i0 * j0 + 1)%8 == 5) this->color = 5;
	if ((i0 * j0 + 1)%8 == 6) this->color = 6;
	if ((i0 * j0 + 1)%8 == 7) this->color = 7;

	this->vertex[0].updateVector3D( radius + newCenter.access(0), radius + newCenter.access(1), radius + newCenter.access(2));
	this->vertex[1].updateVector3D(-radius + newCenter.access(0), radius + newCenter.access(1), radius + newCenter.access(2));
	this->vertex[2].updateVector3D(-radius + newCenter.access(0),-radius + newCenter.access(1), radius + newCenter.access(2));
	this->vertex[3].updateVector3D( radius + newCenter.access(0),-radius + newCenter.access(1), radius + newCenter.access(2));
	this->vertex[4].updateVector3D( radius + newCenter.access(0), radius + newCenter.access(1),-radius + newCenter.access(2));
	this->vertex[5].updateVector3D(-radius + newCenter.access(0), radius + newCenter.access(1),-radius + newCenter.access(2));
	this->vertex[6].updateVector3D(-radius + newCenter.access(0),-radius + newCenter.access(1),-radius + newCenter.access(2));
	this->vertex[7].updateVector3D( radius + newCenter.access(0),-radius + newCenter.access(1),-radius + newCenter.access(2));


	this->mesh.updateFacet(0, 0, this->vertex[0], this->vertex[1], this->vertex[2]);
	this->mesh.updateFacet(0, 1, this->vertex[2], this->vertex[3], this->vertex[0]);

	this->mesh.updateFacet(0, 2, this->vertex[4], this->vertex[7], this->vertex[6]);
	this->mesh.updateFacet(0, 3, this->vertex[6], this->vertex[5], this->vertex[4]);

	this->mesh.updateFacet(0, 4, this->vertex[0], this->vertex[3], this->vertex[7]);
	this->mesh.updateFacet(0, 5, this->vertex[7], this->vertex[4], this->vertex[0]);
}

void CubeNeighborhood::applyInversionF(double radius, VectorND gamma) {

	this->systemInversion.initInversion(radius, gamma);

	for (int i = 0; i < 8; i++)
		this->systemInversion.applyInversion(this->vertex[i]);

	this->mesh.updateFacet(0, 0, this->vertex[0], this->vertex[1], this->vertex[2]);
	this->mesh.updateFacet(0, 1, this->vertex[2], this->vertex[3], this->vertex[0]);

	this->mesh.updateFacet(0, 2, this->vertex[4], this->vertex[7], this->vertex[6]);
	this->mesh.updateFacet(0, 3, this->vertex[6], this->vertex[5], this->vertex[4]);

	this->mesh.updateFacet(0, 4, this->vertex[0], this->vertex[3], this->vertex[7]);
	this->mesh.updateFacet(0, 5, this->vertex[7], this->vertex[4], this->vertex[0]);
}

void MatrixCubeNeighborhood::initMatrixCubeNeighborhood(int m, int n) {

	this->m = m;
	this->n = n;
	this->A = (CubeNeighborhood**) malloc (m * sizeof(CubeNeighborhood*));
	if (this->A != NULL){
	    for(int i = 0; i < m; i++) {
	      this->A[i] = (CubeNeighborhood *) malloc (n * sizeof(CubeNeighborhood));
	      	if (this->A[i] == NULL){
	        	while(i > 0){
	          		free(this->A[--i]);
	          		this->A[i] = NULL;
	       		}
	        	break;
	      	}
	    }
  	}
}

void MatrixCubeNeighborhood::inputCubeNeighborhood(int i, int j, VectorND center, double radius, int color) {

	this->A[i][j].initCubeNeighborhood(center, radius, color);
}

CubeNeighborhood MatrixCubeNeighborhood::getCube(int i, int j) {

	return this->A[i][j];
}

void MatrixCubeNeighborhood::updateRadiusMatrix(int i, int j, double newR) {
	this->A[i][j].updateRadius(newR);
}

void MatrixCubeNeighborhood::updateInversionMatrix(int i, int j, double newR, VectorND gamma) {
	this->A[i][j].applyInversionF(newR, gamma);
}

void Lattice2D::initLattice2D(int m, int n, VectorND center, double radius) {

	this->m = m;
	this->n = n;
	this->center = center;
	this->radius = radius;
	this->A.initMatrixCubeNeighborhood(this->m, this->n);
	this->A0.initMatrixCubeNeighborhood(this->m, this->n);
	this->A1.initMatrixCubeNeighborhood(this->m, this->n);
	this->A2.initMatrixCubeNeighborhood(this->m, this->n);
	this->pivote.initVectorNDType2(3);

	double RR = 4.0;
	VectorND gamma;
	gamma.initVectorND(3, 0.0, 0.0, 0.0);

	for (int i = 0; i < this->m; i++)
		for (int j = 0; j < this->n; j++) {
			
			this->pivote.updateVector3D(	
										center.access(0) + (2.0 * (double)i * this->radius), 
										center.access(1), 
										center.access(2) + (2.0 * (double)j * this->radius));

			this->A.inputCubeNeighborhood(i, j, this->pivote, this->radius, 0);
			this->A.updateInversionMatrix(i, j,RR, gamma);

			this->pivote.updateVector3D(	
										center.access(0) - (2.0 * (double)i * this->radius), 
										center.access(1), 
										center.access(2) + (2.0 * (double)j * this->radius));

			this->A0.inputCubeNeighborhood(i, j, this->pivote, this->radius, 0);
			this->A0.updateInversionMatrix(i, j,RR, gamma);

			this->pivote.updateVector3D(	
										center.access(0) - (2.0 * (double)i * this->radius), 
										center.access(1), 
										center.access(2) - (2.0 * (double)j * this->radius));

			this->A1.inputCubeNeighborhood(i, j, this->pivote, this->radius, 0);
			this->A1.updateInversionMatrix(i, j,RR, gamma);

			this->pivote.updateVector3D(	
										center.access(0) + (2.0 * (double)i * this->radius), 
										center.access(1), 
										center.access(2) - (2.0 * (double)j * this->radius));

			this->A2.inputCubeNeighborhood(i, j, this->pivote, this->radius, 0);
			this->A2.updateInversionMatrix(i, j,RR, gamma);
		}
}

CubeNeighborhood Lattice2D::getCell(int i, int j) {
	return this->A.getCube(i, j);
}

CubeNeighborhood Lattice2D::getCell0(int i, int j) {
	return this->A0.getCube(i, j);
}

CubeNeighborhood Lattice2D::getCell1(int i, int j) {
	return this->A1.getCube(i, j);
}

CubeNeighborhood Lattice2D::getCell2(int i, int j) {
	return this->A2.getCube(i, j);
}

int Lattice2D::getM() {
	return this->m;
}

int Lattice2D::getN() {
	return this->n;
}

void Arista::initArista(VectorND head, VectorND tail) {

	this->head.initVectorNDType2(3);
	this->tail.initVectorNDType2(3);
	this->diff.initVectorNDType2(3);

	this->head.updateVector3D(head.access(0), head.access(1), head.access(2));
	this->tail.updateVector3D(tail.access(0), tail.access(1), tail.access(2));

	this->diff.subVectorND(this->head, this->tail);
	this->length = this->diff.norm();
}

void Arista::initMesh(double width) {

	this->points[0].initVectorND(3, width, width, this->length);
	this->points[1].initVectorND(3,-width, width, this->length);
	this->points[2].initVectorND(3,-width,-width, this->length);
	this->points[3].initVectorND(3, width,-width, this->length);
	this->points[4].initVectorND(3, width, width, 0.0);
	this->points[5].initVectorND(3,-width, width, 0.0);
	this->points[6].initVectorND(3,-width,-width, 0.0);
	this->points[7].initVectorND(3, width,-width, 0.0);
	this->points[8].initVectorND(3,   0.0, 	 0.0, this->length);
	this->points[9].initVectorND(3,   0.0, 	 0.0, 0.0);
	this->points[10].initVectorNDType2(3);

	for (int i = 0; i < 10; i++)
		this->points[i].SumVectorND(this->points[i], this->tail);

	this->points[10].subVectorND(this->points[8], this->points[9]);

	this->orientationPlane.initFacet(this->points[8], this->points[9], this->head);

	double dot = this->points[10].dotProd(this->diff);
	double norm = this->points[10].norm() * this->diff.norm();
	double angle = acos(dot/norm);

	this->U.initAxeRotation(this->orientationPlane.normalK(), this->points[9], angle);

	printf("\n-->angle := %lg", angle);
	for (int i = 0; i < 10; i++)
		this->U.rot3D(this->points[i]);

	this->mesh.initMatrixFacet(1, 12);
	this->mesh.inputFacet(0, 0, this->points[0], this->points[1], this->points[2]);
	this->mesh.inputFacet(0, 1, this->points[2], this->points[3], this->points[0]);

	this->mesh.inputFacet(0, 2, this->points[4], this->points[7], this->points[6]);
	this->mesh.inputFacet(0, 3, this->points[6], this->points[5], this->points[4]);

	this->mesh.inputFacet(0, 4, this->points[0], this->points[3], this->points[7]);
	this->mesh.inputFacet(0, 5, this->points[7], this->points[4], this->points[0]);

	this->mesh.inputFacet(0, 6, this->points[1], this->points[5], this->points[6]);
	this->mesh.inputFacet(0, 7, this->points[6], this->points[2], this->points[1]);

	this->mesh.inputFacet(0, 8, this->points[0], this->points[4], this->points[5]);
	this->mesh.inputFacet(0, 9, this->points[5], this->points[1], this->points[0]);

	this->mesh.inputFacet(0, 10, this->points[3], this->points[2], this->points[6]);
	this->mesh.inputFacet(0, 11, this->points[6], this->points[7], this->points[3]);
}

Facet Arista::getOrientationPlane() {
	return this->orientationPlane;
}

void Arista::renderMesh(int mod, RotationMats U) {

	for (int i = 0; i < 12; i++)
		this->mesh.getFacet(0, i).renderFacetOpenGL(0, U);
}

VectorND Arista::getHead() {

	return this->head;
}

VectorND Arista::getTail() {

	return this->tail;
}

double Arista::getLength() {
	return this->length;
}

void Arista::escArista() {

	printf("\nArista := \n");
	printf("Head - ");this->head.escVectorND();
	printf("\n-\n");
	printf("-\n");
	printf("Tail - ");this->tail.escVectorND();
	printf("\n");

}

void Arista::updateArista(VectorND head, VectorND tail) {

	this->head.updateVector3D(head.access(0), head.access(1), head.access(2));
	this->tail.updateVector3D(tail.access(0), tail.access(1), tail.access(2));

	this->diff.subVectorND(this->head, this->tail);
	this->length = this->diff.norm();
}

void MatrixArista::initMatrixArista(int m, int n) {

	this->m = m;
	this->n = n;
	this->A = (Arista**) malloc (m * sizeof(Arista*));
	if (this->A != NULL){
	    for(int i = 0; i < m; i++) {
	      this->A[i] = (Arista *) malloc (n * sizeof(Arista));
	      	if (this->A[i] == NULL){
	        	while(i > 0){
	          		free(this->A[--i]);
	          		this->A[i] = NULL;
	       		}
	        	break;
	      	}
	    }
  	}
}

void MatrixArista::inputArista(int i, int j, VectorND head, VectorND tail) {

	if ((0 <= i && i < this->m) && (0 <= j && j < this->n))
		this->A[i][j].initArista(head, tail);
	else printf("\n\nMatrixArista::inputArista :: Unable to Input Arista Data\n\n");
}

void MatrixArista::updateArista(int i, int j, VectorND head, VectorND tail) {

	if ((0 <= i && i < this->m) && (0 <= j && j < this->n))
		this->A[i][j].updateArista(head, tail);
	else printf("\n\nMatrixArista::updateArista :: Unable to Input Arista Data\n\n");
}

Arista MatrixArista::getArista(int i, int j) {
	return this->A[i][j];
}

void Inversion::initInversion(double radius, VectorND gamma) {

	this->radius = radius;
	this->gamma = gamma;
	this->rest.initVectorNDType2(gamma.dim());
	this->rest0.initVectorNDType2(gamma.dim());
	this->rest1.initVectorNDType2(gamma.dim());

	this->aux.initVectorNDType2(gamma.dim());

	this->a.initVectorND(3, 1.0, 0.0, 0.0);
	this->b.initVectorND(3, 0.0, 1.0, 0.0);
	this->c.initVectorND(3, 0.0, 0.0, 1.0);
	this->facet.initFacet(this->a, this->b, this->c);
}

void Inversion::updateInversion(double radius, VectorND gamma) {

	this->radius = radius;
	this->gamma.updateVector3D(gamma.access(0), gamma.access(1), gamma.access(2));
}

void Inversion::applyInversion(VectorND p) {

	this->d = p.distance(this->gamma);
	this->check = sqrt((this->d - this->radius) * (this->d - this->radius));
	if (this->check < 1e-20) return;
	else {
		this->dd = (this->radius * this->radius)/this->d;
		this->rest.updateVector3D(
			p.access(0) - this->gamma.access(0),
			p.access(1) - this->gamma.access(1),
			p.access(2) - this->gamma.access(2));
		this->rest.unit();
		this->rest0.scaleVectorND(dd, this->rest);
		p.SumVectorND(this->rest0, gamma);
		return;
	}
}

VectorND Inversion::returnInversion(VectorND p) {
	this->aux.updateVector3D(p.access(0), p.access(1), p.access(2));
	this->applyInversion(aux);
	return this->aux;
}

void Square::initSquare(VectorND a, VectorND b, VectorND c, VectorND d) {

	this->a.initVectorNDType2(3);
	this->b.initVectorNDType2(3);
	this->c.initVectorNDType2(3);
	this->d.initVectorNDType2(3);

	this->a.updateVector3DP(a);
	this->b.updateVector3DP(b);
	this->c.updateVector3DP(c);
	this->d.updateVector3DP(d);

	this->mesh.initMatrixFacet(1, 2);
	this->mesh.inputFacet(0, 0, a, b, c);
	this->mesh.inputFacet(0, 1, c, d, a);
}

void Square::renderSquare(int mod, RotationMats U) {

	this->mesh.getFacet(0, 0).renderFacetOpenGL(mod, U);
	this->mesh.getFacet(0, 1).renderFacetOpenGL(mod, U);
}

void MatrixSquare::initMatrixSquare(int m, int n) {

	this->m = m;
	this->n = n;
	this->A = (Square**) malloc (m * sizeof(Square*));
	if (this->A != NULL){
	    for(int i = 0; i < m; i++) {
	      this->A[i] = (Square *) malloc (n * sizeof(Square));
	      	if (this->A[i] == NULL){
	        	while(i > 0){
	          		free(this->A[--i]);
	          		this->A[i] = NULL;
	       		}
	        	break;
	      	}
	    }
  	}
}

void Sphere::initSphere(int n, double R, VectorND center) {

	this->n = n;
	this->R = R;
	this->center.initVectorNDType2(3);
	this->center.updateVector3DP(center);

	for (int i = 0; i < 4; i++)
		aux[i].initVectorNDType2(3);

	this->mesh.initMatrixSquare(n, n);

	double stepU = (3.14159265358979) /(double)n;
	double stepV = (2.0 * 3.14159265358979) /(double)n;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			double u1 = (double)i * stepU;
			double v1 = (double)j * stepV;

			double u2 = ((double)i * stepU) + stepU;
			double v2 = (double)j * stepV;

			double u3 = (double)i * stepU + stepU;
			double v3 = (double)j * stepV + stepV;

			double u4 = (double)i * stepU;
			double v4 = (double)j * stepV + stepV;

			this->aux[0].updateVector3D(R * sin(u1) * cos(v1) + center.access(0), R * sin(u1) * sin(v1) + center.access(1), R * cos(u1) + center.access(2));
			this->aux[1].updateVector3D(R * sin(u2) * cos(v2) + center.access(0), R * sin(u2) * sin(v2) + center.access(1), R * cos(u2) + center.access(2));
			this->aux[2].updateVector3D(R * sin(u3) * cos(v3) + center.access(0), R * sin(u3) * sin(v3) + center.access(1), R * cos(u3) + center.access(2));
			this->aux[3].updateVector3D(R * sin(u4) * cos(v4) + center.access(0), R * sin(u4) * sin(v4) + center.access(1), R * cos(u4) + center.access(2));

			this->mesh.A[i][j].initSquare(this->aux[0], this->aux[1], this->aux[2], this->aux[3]);
		}
}

void Sphere::renderSphere(int mod, RotationMats U) {

	for (int i = 0; i < this->mesh.m; i++)
		for (int j = 0; j < this->mesh.n; j++)
			this->mesh.A[i][j].renderSquare(mod, U);
}

void MatrixSphere::initMatrixSphere(int m, int n) {

	this->m = m;
	this->n = n;
	this->A = (Sphere**) malloc (m * sizeof(Sphere*));
	if (this->A != NULL){
	    for(int i = 0; i < m; i++) {
	      this->A[i] = (Sphere *) malloc (n * sizeof(Sphere));
	      	if (this->A[i] == NULL){
	        	while(i > 0){
	          		free(this->A[--i]);
	          		this->A[i] = NULL;
	       		}
	        	break;
	      	}
	    }
  	}
}

void MatrixSphere::renderMatrixSphere(int mod, RotationMats U) {

	for (int i = 0; i < this->m; i++)
		for (int j = 0; j < this->n; j++) {
			this->A[i][j].renderSphere(mod, U);
		}
}

void Torus::initTorus(int n, double R, double r, VectorND center) {

	this->n = n;
	this->R = R;
	this->center.initVectorNDType2(3);
	this->center.updateVector3DP(center);

	for (int i = 0; i < 4; i++)
		aux[i].initVectorNDType2(3);

	this->mesh.initMatrixSquare(n, n);

	double stepU = (2.0 * 3.14159265358979) /(double)n;
	double stepV = (2.0 * 3.14159265358979) /(double)n;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			double u1 = (double)i * stepU;
			double v1 = (double)j * stepV;

			double u2 = ((double)i * stepU) + stepU;
			double v2 = (double)j * stepV;

			double u3 = (double)i * stepU + stepU;
			double v3 = (double)j * stepV + stepV;

			double u4 = (double)i * stepU;
			double v4 = (double)j * stepV + stepV;

			this->aux[0].updateVector3D((R + (r * cos(u1))) * cos(v1) + center.access(0), (R + (r * cos(u1))) * sin(v1) + center.access(1), r * sin(u1) + center.access(2));
			this->aux[1].updateVector3D((R + (r * cos(u2))) * cos(v2) + center.access(0), (R + (r * cos(u2))) * sin(v2) + center.access(1), r * sin(u2) + center.access(2));
			this->aux[2].updateVector3D((R + (r * cos(u3))) * cos(v3) + center.access(0), (R + (r * cos(u3))) * sin(v3) + center.access(1), r * sin(u3) + center.access(2));
			this->aux[3].updateVector3D((R + (r * cos(u4))) * cos(v4) + center.access(0), (R + (r * cos(u4))) * sin(v4) + center.access(1), r * sin(u4) + center.access(2));

			this->mesh.A[i][j].initSquare(this->aux[0], this->aux[1], this->aux[2], this->aux[3]);
		}
}

void Torus::renderTorus(int mod, RotationMats U) {

	for (int i = 0; i < this->mesh.m; i++)
		for (int j = 0; j < this->mesh.n; j++)
			this->mesh.A[i][j].renderSquare(mod, U);
}

void MatrixTorus::initMatrixTorus(int m, int n) {

	this->m = m;
	this->n = n;
	this->A = (Torus**) malloc (m * sizeof(Torus*));
	if (this->A != NULL){
	    for(int i = 0; i < m; i++) {
	      this->A[i] = (Torus *) malloc (n * sizeof(Torus));
	      	if (this->A[i] == NULL){
	        	while(i > 0){
	          		free(this->A[--i]);
	          		this->A[i] = NULL;
	       		}
	        	break;
	      	}
	    }
  	}
}

void MatrixTorus::renderMatrixTorus(int mod, RotationMats U) {

	for (int i = 0; i < this->m; i++)
		for (int j = 0; j < this->n; j++) {
			this->A[i][j].renderTorus(mod, U);
		}
}

void MatrixAristaList::initMatrixAristaList(int n) {

	this->n = n;
	this->A = (MatrixArista *) malloc (n * sizeof(MatrixArista));	
}

void MatrixAristaList::inputMatrixArista(int m, MatrixArista matrixArista) {
	
	this->A[m].initMatrixArista(matrixArista.m, matrixArista.n);
	for (int i = 0; i < matrixArista.m; i++)
		for (int j = 0; j < matrixArista.n; j++) {
			this->A[m].inputArista(i, j, matrixArista.getArista(i,j).getHead(), matrixArista.getArista(i,j).getTail());
		}
}