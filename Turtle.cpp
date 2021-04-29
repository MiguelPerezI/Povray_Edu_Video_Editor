#include <cstdio>
#include <iostream>
#include <cmath>
#include "VectorND.hpp"
#include "geometry.hpp"
#include "matrix.hpp"
#include "Turtle.hpp"

void Turtle::initTurtle(VectorND b, VectorND u, VectorND pp, double theta, double angle, int Max) {

	printf("\n\n_____Init Turle_____\n\n");
	this->counted = 0;
	this->Max = Max;
	this->initStep = theta;
	this->angle = angle;

	this->head.initVectorNDType2(3);
	this->tail.initVectorNDType2(3);
	this->auxVec.initVectorNDType2(3);
	this->a.initVectorNDType2(3);
	this->w.initVectorNDType2(3);
	this->r.initVectorNDType2(3);
	this->u.initVectorNDType2(3);

	this->auxVec.updateVector3D(pp.access(0), pp.access(1), pp.access(2));
	
	this->plane.initFacet(b, pp, u);
	this->perpK.initVectorND(3, this->plane.normalK().access(0), this->plane.normalK().access(1), this->plane.normalK().access(2));
	this->perpK.unit();
	this->perpKMove.initVectorNDType2(3);

	this->tail.updateVector3D(b.access(0), b.access(1), b.access(2));
	printf("-->Se inicializo cola de tortuga := \n");
	this->tail.escVectorND();
	this->a.SumVectorND(b, u);
	this->r.subVectorND(a, b);
	this->r.unit();
	this->w.scaleVectorND(this->initStep, this->r);

	this->head.updateVector3D(w.access(0), w.access(1), w.access(2));
	printf("\n-->Se inicializo cabeza de tortuga\n");
	this->head.escVectorND();printf("\n\n");

	this->stepLen = this->head.distance(this->tail);
	this->snake.initMatrixArista(1, this->Max);

	this->perpKMove.SumVectorND(this->tail, this->perpK);
	this->A.initAxeRotation(this->perpKMove, this->tail,-this->angle);
}

MatrixArista Turtle::getPath() {
	return this->snake;
}

Arista Turtle::accessPathPiece(int i) {
	return this->snake.getArista(0, i);
}

VectorND Turtle::getHead() {
	return this->head;
}

void Turtle::forwardTurtle(double s) {

	if (this->counted < this->Max) {
		
		this->snake.inputArista(0, this->counted, this->head, this->tail);
		this->counted += 1;
		this->u.subVectorND(this->head, this->tail);
		this->u.unit();
		this->u.scaleVectorND(this->initStep, this->u);
		this->a.SumVectorND(this->head, this->u);
		this->r.subVectorND(a, this->head);
		this->r.unit();
		this->w.scaleVectorND(s * this->initStep, this->r);
		this->w.AddVector3D(this->head);
		this->tail.updateVector3D(this->head.access(0), this->head.access(1), this->head.access(2));
		this->head.updateVector3D(this->w.access(0), this->w.access(1), this->w.access(2));
		this->stepLen = this->head.distance(this->tail);
	}
}

void Turtle::rotateRightTurtle() {

	this->perpKMove.SumVectorND(this->tail, this->perpK);
	this->A.updateAxeRotation(this->perpKMove, this->tail, this->angle);
	A.rot3DAxe(this->head);
}

void Turtle::rotateLeftTurtle() {

	this->perpKMove.SumVectorND(this->tail, this->perpK);
	this->A.updateAxeRotation(this->perpKMove, this->tail,-this->angle);
	A.rot3DAxe(this->head);
}