#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include "matrix.hpp"
#include "VectorND.hpp"
#include "geometry.hpp"
#include "simplex.hpp"
#include "Arrow.hpp"

int equalDouble(double a, double b) {

	double epsilon = 0.00000000000001;
	double cc = (a - b) * (a - b);
	if (sqrt(cc) < epsilon)
		return 1;
	else
		return 0;
}

void Arrow::arrowGo(VectorND a, VectorND b, double width) {

	//printf("\n\n-->Arrow Constructor\n");
	this->head.initVectorND(3, a.access(0), a.access(1), a.access(2));// = VectorND({a[0], a[1], a[2]});
	this->base.initVectorND(3, b.access(0), b.access(1), b.access(2));// = VectorND({b[0], b[1], b[2]});
	this->D.initVectorND(3, 0.0, 0.0, 0.0);// = VectorND({0, 0, 0});
	this->center.initVectorND(3, 0.0, 0.0, 0.0);
	this->centerM.initVectorND(3, 0.0, 0.0, 0.0);
	this->centerM.SumVectorND(a, b);
	this->centerM.scaleND(0.5);

	//printf("-->Restamos a y b\n");
	this->D.subVectorND(a, b);

	//printf("-->Definimos los h0, ..., h3\n");
	this->h0.initVectorND(3, this->D.access(0), this->D.access(1), 		0.0);// = VectorND({this->D[0], this->D[1], 		  0});
	this->h1.initVectorND(3, this->D.access(0), this->D.access(1), this->D.access(2));// = VectorND({this->D[0], this->D[1], this->D[2]});
	this->h2.initVectorND(3, 		0.0, 		0.0, this->D.access(2));// = VectorND({		  0, 		  0, this->D[2]});
	this->h3.initVectorND(3,
		(0.5 * this->D.access(0)) + this->base.access(0),
		(0.5 * this->D.access(1)) + this->base.access(1),
		(0.5 * this->D.access(2)) + this->base.access(2));

	//printf("-->Definimos la longitud de Flecha\n");
	this->longitud = 0.5 * this->D.norm();
	//printf("-->longitud es %lg\n", this->longitud);
	this->Z.initVectorND(3, 0.0, 0.0, this->longitud);
	this->minusZ.initVectorND(3, 0.0, 0.0,-this->longitud);

	//printf("-->Inicializando Puntos Vectoriales del Mesh\n");
	this->m = 4;
	this->n = 15;
	this->points.initMatrixVectorND(this->m, this->n + 1);

	double r = width;
	//printf("-->Rellenando Matriz Vectorial\n");
	for (int j = 0; j < this->n + 1; j++) {
		this->points.A[0][j].initVectorND(3, 
			0.01 * r * cos(j * (2 * M_PI) / this->n) + Z.access(0), 
			0.01 * r * sin(j * (2 * M_PI) / this->n) + Z.access(1), 
			Z.access(2));
		this->points.A[1][j].initVectorND(3,
			r * cos(j * (2 * M_PI) / this->n), 
			r * sin(j * (2 * M_PI) / this->n), 
			(this->longitud) - 0.5);
		this->points.A[2][j].initVectorND(3,
			0.3 * r * cos(j * (2 * M_PI) / this->n), 
			0.3 * r * sin(j * (2 * M_PI) / this->n), 
			(this->longitud) - 0.5);
		this->points.A[3][j].initVectorND(3,
			0.3 * r * cos(j * (2 * M_PI) / this->n) + minusZ.access(0), 
			0.3 * r * sin(j * (2 * M_PI) / this->n) + minusZ.access(1), 
			minusZ.access(2));
	}

	//printf("-->Calculando Angulo Phi\n");
	double P_pro_p_k = this->h0.access(0);
	double abs_pro_p = this->h0.norm();
	double phi = acos(P_pro_p_k / abs_pro_p);
	//printf("-->phi := %lg\n", phi);

	double P_p_k;
	int k;

	if (this->h1[2] > 0.0)
		P_p_k = this->h1.access(2);
	else
		P_p_k = -this->h1.access(2);
	//printf("-->Calculando Angulo Teta\n");
	double abs_p = this->h1.norm();
	double teta = acos(P_p_k / abs_p);
	//printf("-->teta := %lg\n", teta);

	//printf("-->Inicializando Matrices de Rotacion\n");
	this->Rz_phi1.initRotationMats(phi);
	this->Rz_phi2.initRotationMats(-phi);
	this->Ry_teta2.initRotationMatsY(-teta);
	this->Ry_teta1.initRotationMatsY(teta);


	if (equalDouble(teta, 0) == 1) {
		//printf("-->Here\n");
		for (int j = 0; j < this->n + 1; j++) {
			for (int i = 0; i < this->m; i++) 
			this->points.A[i][j].SumVectorND(this->points.A[i][j], this->h3);
		}
	}
	else {
		if (this->D.access(1) > 0.0) {
			//printf("-->Here0\n");
			for (int j = 0; j < this->n + 1; j++) {
				for (int i = 0; i < this->m; i++) {
					this->Ry_teta1.rot3D(this->points.A[i][j]);
					this->points.A[i][j].updateVector3DP(this->Ry_teta1.getAux());
					this->Rz_phi2.rot3D(this->points.A[i][j]);
					this->points.A[i][j].updateVector3DP(this->Rz_phi2.getAux());	
				}
			}
		} else {
			//printf("-->Here1\n");
			for (int j = 0; j < this->n + 1; j++) {
				for (int i = 0; i < this->m; i++) {
					this->Ry_teta1.rot3D(this->points.A[i][j]);
					this->points.A[i][j].updateVector3DP(this->Ry_teta1.getAux());
					this->Rz_phi1.rot3D(this->points.A[i][j]);
					this->points.A[i][j].updateVector3DP(this->Rz_phi1.getAux());
				}
			}			
		}

		for (int j = 0; j < this->n + 1; j++) {
			for (int i = 0; i < this->m; i++) 
				this->points.A[i][j].SumVectorND(this->points.A[i][j], this->h3);
		}
	}

	//printf("-->Rellenando Matriz Mesh\n");
	this->mesh.initMatrixFacet(2 * this->m, this->n);

	for (int j = 0; j < this->n; j++) {
		this->mesh.inputFacet(0, j,   this->points.A[0][j], this->points.A[0][j+1], this->points.A[1][j]);
		this->mesh.inputFacet(1, j, this->points.A[0][j+1], this->points.A[1][j+1], this->points.A[1][j]);
		this->mesh.inputFacet(2, j,   this->points.A[1][j], this->points.A[1][j+1], this->points.A[2][j]);
		this->mesh.inputFacet(3, j, this->points.A[1][j+1], this->points.A[2][j+1], this->points.A[2][j]);
		this->mesh.inputFacet(4, j,   this->points.A[2][j], this->points.A[2][j+1], this->points.A[3][j]);
		this->mesh.inputFacet(5, j, this->points.A[2][j+1], this->points.A[3][j+1], this->points.A[3][j]);
	}
	//printf("\n\n\n");
}

void Arrow::arrowUpdate(VectorND a, VectorND b, double width) {

	//printf("\n\n-->Arrow Constructor\n");
	this->head.updateVector3D(a.access(0), a.access(1), a.access(2));// = VectorND({a[0], a[1], a[2]});
	this->base.updateVector3D(b.access(0), b.access(1), b.access(2));// = VectorND({b[0], b[1], b[2]});
	this->centerM.SumVectorND(a, b);
	this->centerM.scaleND(0.5);

	//printf("-->Restamos a y b\n");
	this->D.subVectorND(a, b);

	//printf("-->Definimos los h0, ..., h3\n");
	this->h0.updateVector3D( this->D.access(0), this->D.access(1), 		0.0);// = VectorND({this->D[0], this->D[1], 		  0});
	this->h1.updateVector3D( this->D.access(0), this->D.access(1), this->D.access(2));// = VectorND({this->D[0], this->D[1], this->D[2]});
	this->h2.updateVector3D( 		0.0, 		0.0, this->D.access(2));// = VectorND({		  0, 		  0, this->D[2]});
	this->h3.updateVector3D(
		(0.5 * this->D.access(0)) + this->base.access(0),
		(0.5 * this->D.access(1)) + this->base.access(1),
		(0.5 * this->D.access(2)) + this->base.access(2));

	//printf("-->Definimos la longitud de Flecha\n");
	this->longitud = 0.5 * this->D.norm();
	//printf("-->longitud es %lg\n", this->longitud);
	this->Z.updateVector3D(0.0, 0.0, this->longitud);
	this->minusZ.updateVector3D(0.0, 0.0,-this->longitud);

	double r = width;
	//printf("-->Rellenando Matriz Vectorial\n");
	for (int j = 0; j < this->n + 1; j++) {
		this->points.A[0][j].updateVector3D( 
			0.01 * r * cos(j * (2 * M_PI) / this->n) + Z.access(0), 
			0.01 * r * sin(j * (2 * M_PI) / this->n) + Z.access(1), 
			Z.access(2));
		this->points.A[1][j].updateVector3D(
			r * cos(j * (2 * M_PI) / this->n), 
			r * sin(j * (2 * M_PI) / this->n), 
			(this->longitud) - 0.5);
		this->points.A[2][j].updateVector3D(
			0.3 * r * cos(j * (2 * M_PI) / this->n), 
			0.3 * r * sin(j * (2 * M_PI) / this->n), 
			(this->longitud) - 0.5);
		this->points.A[3][j].updateVector3D(
			0.3 * r * cos(j * (2 * M_PI) / this->n) + minusZ.access(0), 
			0.3 * r * sin(j * (2 * M_PI) / this->n) + minusZ.access(1), 
			minusZ.access(2));
	}

	//printf("-->Calculando Angulo Phi\n");
	double P_pro_p_k = this->h0.access(0);
	double abs_pro_p = this->h0.norm();
	double phi = acos(P_pro_p_k / abs_pro_p);
	//printf("-->phi := %lg\n", phi);

	double P_p_k;
	int k;

	if (this->h1[2] > 0.0)
		P_p_k = this->h1.access(2);
	else
		P_p_k = -this->h1.access(2);
	//printf("-->Calculando Angulo Teta\n");
	double abs_p = this->h1.norm();
	double teta = acos(P_p_k / abs_p);
	//printf("-->teta := %lg\n", teta);

	//printf("-->Inicializando Matrices de Rotacion\n");
	this->Rz_phi1.updateRotationMats(phi);
	this->Rz_phi2.updateRotationMats(-phi);
	this->Ry_teta2.updateRotationMatsY(-teta);
	this->Ry_teta1.updateRotationMatsY(teta);


	if (equalDouble(teta, 0) == 1) {
		//printf("-->Here\n");
		for (int j = 0; j < this->n + 1; j++) {
			for (int i = 0; i < this->m; i++) 
			this->points.A[i][j].SumVectorND(this->points.A[i][j], this->h3);
		}
	}
	else {
		if (this->D.access(1) > 0.0) {
			//printf("-->Here0\n");
			for (int j = 0; j < this->n + 1; j++) {
				for (int i = 0; i < this->m; i++) {
					this->Ry_teta1.rot3D(this->points.A[i][j]);
					this->points.A[i][j].updateVector3DP(this->Ry_teta1.getAux());
					this->Rz_phi2.rot3D(this->points.A[i][j]);
					this->points.A[i][j].updateVector3DP(this->Rz_phi2.getAux());	
				}
			}
		} else {
			//printf("-->Here1\n");
			for (int j = 0; j < this->n + 1; j++) {
				for (int i = 0; i < this->m; i++) {
					this->Ry_teta1.rot3D(this->points.A[i][j]);
					this->points.A[i][j].updateVector3DP(this->Ry_teta1.getAux());
					this->Rz_phi1.rot3D(this->points.A[i][j]);
					this->points.A[i][j].updateVector3DP(this->Rz_phi1.getAux());
				}
			}			
		}

		for (int j = 0; j < this->n + 1; j++) {
			for (int i = 0; i < this->m; i++) 
				this->points.A[i][j].SumVectorND(this->points.A[i][j], this->h3);
		}
	}

	for (int j = 0; j < this->n; j++) {
		this->mesh.updateFacet(0, j,   this->points.A[0][j], this->points.A[0][j+1], this->points.A[1][j]);
		this->mesh.updateFacet(1, j, this->points.A[0][j+1], this->points.A[1][j+1], this->points.A[1][j]);
		this->mesh.updateFacet(2, j,   this->points.A[1][j], this->points.A[1][j+1], this->points.A[2][j]);
		this->mesh.updateFacet(3, j, this->points.A[1][j+1], this->points.A[2][j+1], this->points.A[2][j]);
		this->mesh.updateFacet(4, j,   this->points.A[2][j], this->points.A[2][j+1], this->points.A[3][j]);
		this->mesh.updateFacet(5, j, this->points.A[2][j+1], this->points.A[3][j+1], this->points.A[3][j]);
	}
	//printf("\n\n\n");
}

void Arrow::reflectArista() {
	
	for (int j = 0; j < this->n + 1; j++) {
		this->points.A[0][j].dilate(this->points.A[0][j], this->centerM, -1);
		this->points.A[1][j].dilate(this->points.A[1][j], this->centerM, -1);
		this->points.A[2][j].dilate(this->points.A[2][j], this->centerM, -1);
		this->points.A[3][j].dilate(this->points.A[3][j], this->centerM, -1);
	}	

	for (int j = 0; j < this->n; j++) {
		this->mesh.updateFacet(0, j,   this->points.A[0][j], this->points.A[0][j+1], this->points.A[1][j]);
		this->mesh.updateFacet(1, j, this->points.A[0][j+1], this->points.A[1][j+1], this->points.A[1][j]);
		this->mesh.updateFacet(2, j,   this->points.A[1][j], this->points.A[1][j+1], this->points.A[2][j]);
		this->mesh.updateFacet(3, j, this->points.A[1][j+1], this->points.A[2][j+1], this->points.A[2][j]);
		this->mesh.updateFacet(4, j,   this->points.A[2][j], this->points.A[2][j+1], this->points.A[3][j]);
		this->mesh.updateFacet(5, j, this->points.A[2][j+1], this->points.A[3][j+1], this->points.A[3][j]);
	}
}

void Arrow::aristaSet(VectorND a, VectorND b, double width) {

	this->help.initVectorND(3);
	this->help.subVectorND(a, b);
	if (this->help.access(2) < 0.0) {
		this->arrowGo(a, b, width);
		this->reflectArista();
		this->reflection = 111;
	}
	else {
		this->arrowGo(b, a, width);
		this->reflection = 110;
	}
}

void Arrow::aristaSetUdate(VectorND a, VectorND b, double width) {

	this->help.subVectorND(a, b);
	if (this->help.access(2) < 0.0) {
		this->arrowUpdate(a, b, width);
		this->reflectArista();
		this->reflection = 111;
	}
	else {
		this->arrowUpdate(b, a, width);
		this->reflection = 110;
	}
}

void MatrixArrow::initMatrixArrow(int m, int n) {
	
	this->m = m;
	this->n = n;

	this->A = (Arrow * *) malloc (m * sizeof(Arrow*));
    for (int i = 0; i < m; i++)
        this->A[i] = (Arrow *) malloc (n * sizeof(Arrow));
}

void MatrixArrow::initA(int i, int j, VectorND a, VectorND b, double width) {

	this->A[i][j].aristaSet(a, b, width);
}

void MatrixArrow::updateA(int i, int j, VectorND a, VectorND b, double width) {

	this->A[i][j].aristaSetUdate(a, b, width);
}

void SpaceCurve::initSpaceCurveType1(int n, double width) {

	this->n = n;
	this->width = width;
	this->curve.initMatrixArista(1, n);

	for (int i = 0; i < 2; i++)
		aux[i].initVectorNDType2(3);

	double step = (2.0 * 3.1415) / (double)n;
	VectorND gamma;
	gamma.initVectorND(3.0, 0.0, 0.0, 0.0);
	this->inversion.initInversion(2.0, gamma);

	for (int i = 0; i < n; i++) {
		double u1 = (double)i * step;
		double u2 = ((double)i * step) + step;

		this->aux[0].updateVector3D(3.0 * cos(u1), 2.0 * cos(u1) * sin(u1) * sin(u1) * sin(u1) * sin(u1) * sin(u1) * sin(u1) * sin(u1) * sin(u1) * sin(u1), 3.0 * sin(u1));
		this->aux[1].updateVector3D(3.0 * cos(u2), 2.0 * cos(u2) * sin(u2) * sin(u2) * sin(u2) * sin(u2) * sin(u2) * sin(u2) * sin(u2) * sin(u2) * sin(u2), 3.0 * sin(u2));
	
		//this->inversion.applyInversion(this->aux[0]);
		//this->inversion.applyInversion(this->aux[1]);

		this->curve.inputArista(0, i, this->aux[0], this->aux[1]);
	}
}

void SpaceCurve::initSpaceCurveType2(int n, double width) {

	this->n = n;
	this->width = width;
	this->curve.initMatrixArista(1, 2*n + 1);

	for (int i = 0; i < 2; i++)
		aux[i].initVectorNDType2(3);

	double step = (2.0 * 3.1415) / (double)n;
	VectorND gamma;
	gamma.initVectorND(3.0, 0.0, 0.0, 0.0);
	this->inversion.initInversion(2.0, gamma);

	for (int i = 0; i < n; i++) {
		double u1 = (double)i * step;
		double u2 = ((double)i * step) + step;

		this->aux[0].updateVector3D(0.5 * (2*cos(u1) - cos(2*u1)) - 0.51, 3.0 * cos(u1) * sin(u1), 0.5 * (2*sin(u1) - sin(2*u1)));
		this->aux[1].updateVector3D(0.5 * (2*cos(u2) - cos(2*u2)) - 0.51, 3.0 * cos(u2) * sin(u2), 0.5 * (2*sin(u2) - sin(2*u2)));
	
		//this->inversion.applyInversion(this->aux[0]);
		//this->inversion.applyInversion(this->aux[1]);

		this->curve.inputArista(0, i, this->aux[0], this->aux[1]);
	}
}

void SpaceCurve::initSpaceCurveType3(int n, double width) {

	this->n = n;
	this->width = width;
	this->curve.initMatrixArista(1, 2*n + 1);

	for (int i = 0; i < 2; i++)
		aux[i].initVectorNDType2(3);

	double step = (2.0 * 3.1415) / (double)n;
	VectorND gamma;
	gamma.initVectorND(3.0, 0.0, 0.0, 0.0);
	this->inversion.initInversion(2.0, gamma);

	for (int i = 0; i < n; i++) {
		double u1 = (double)i * step;
		double u2 = ((double)i * step) + step;

		this->aux[0].updateVector3D(0.5 * (2*cos(u1) - cos(2*u1)) - 0.51, 0.0, 0.5 * (2*sin(u1) - sin(2*u1)));
		this->aux[1].updateVector3D(0.5 * (2*cos(u2) - cos(2*u2)) - 0.51, 0.0, 0.5 * (2*sin(u2) - sin(2*u2)));
	
		//this->inversion.applyInversion(this->aux[0]);
		//this->inversion.applyInversion(this->aux[1]);

		this->curve.inputArista(0, i, this->aux[0], this->aux[1]);
	}
}

void SpaceCurve::initSpaceCurveType4(int n, double width) {

	this->n = n;
	this->width = width;
	this->curve.initMatrixArista(1, 2*n + 1);

	for (int i = 0; i < 2; i++)
		aux[i].initVectorNDType2(3);

	double step = (2.0) / (double)n;
	VectorND gamma;
	gamma.initVectorND(3.0, 0.0, 0.0, 0.0);
	this->inversion.initInversion(2.0, gamma);

	for (int i = 0; i < n; i++) {
		double u1 = (double)i * step;
		double u2 = ((double)i * step) + step;

		this->aux[0].updateVector3D(u1, 0.0, 0.0);
		this->aux[1].updateVector3D(u2, 0.0, 0.0);

		this->curve.inputArista(0, i, this->aux[0], this->aux[1]);
	}
}

void SpaceCurve::initSpaceCurveType5(int n, double width) {

	this->n = n;
	this->width = width;
	this->curve.initMatrixArista(1, 2*n + 1);

	for (int i = 0; i < 2; i++)
		aux[i].initVectorNDType2(3);

	double step = (2.0) / (double)n;
	VectorND gamma;
	gamma.initVectorND(3.0, 0.0, 0.0, 0.0);
	this->inversion.initInversion(2.0, gamma);

	for (int i = 0; i < n; i++) {
		double u1 = (double)i * step;
		double u2 = ((double)i * step) + step;

		this->aux[0].updateVector3D(-u1, 0.0, 0.0);
		this->aux[1].updateVector3D(-u2, 0.0, 0.0);

		this->curve.inputArista(0, i, this->aux[0], this->aux[1]);
	}
}

void SpaceCurve::initSpaceCurveType6(int n, double width) {

	this->n = n;
	this->width = width;
	this->curve.initMatrixArista(1, 2*n + 1);

	for (int i = 0; i < 2; i++)
		aux[i].initVectorNDType2(3);

	double step = (4.0 * 3.1415) / (double)n;
	VectorND gamma;
	gamma.initVectorND(3.0, 0.0, 0.0, 0.0);
	this->inversion.initInversion(2.0, gamma);

	for (int i = 0; i < n; i++) {
		double u1 = (double)i * step;
		double u2 = ((double)i * step) + step;

		this->aux[0].updateVector3D(cos(14*u1) + (cos(14*u1)/2) + (sin(3*u1)/3), 3 * cos(u1)*sin(u1), sin(u1) + (sin(14*u1)/2) + (cos(3*u1)/3));
		this->aux[1].updateVector3D(cos(14*u2) + (cos(14*u2)/2) + (sin(3*u2)/3), 3 * cos(u2)*sin(u2), sin(u2) + (sin(14*u2)/2) + (cos(3*u2)/3));

		this->curve.inputArista(0, i, this->aux[0], this->aux[1]);
	}
}

void SpaceCurve::initCurveList() {

	//printf("-->Preparando Matriz de Aristas\n");
	this->curveList.initMatrixAristaList(this->n);
	int count = 0;
	while (count < this->n) {
		this->curveList.A[count].initMatrixArista(1, count + 1);
		//printf("-->Se construyo matrix de aristas de tamaño := %d\n", count + 1);
		
		for (int i = 0; i < count + 1; i++) {
			this->curveList.A[count].inputArista(0, i, this->curve.getArista(0, i).getHead(), this->curve.getArista(0, i).getTail());
		}

		count += 1;
	}
}

void ArrowTransform::initTransform(Arrow mainArrow, VectorND newHead, int partition, double width) {

	//printf("    -->reflection := %d\n", mainArrow.reflection);
	this->oldBase.initVectorND(3, mainArrow.head.access(0), mainArrow.head.access(1), mainArrow.head.access(2));
	this->oldHead.initVectorND(3, mainArrow.base.access(0), mainArrow.base.access(1), mainArrow.base.access(2));
	//printf("-->OldHead  :=   "); this->oldHead.escVectorND(); //printf("\n");
	//printf("-->oldBase  :=   "); this->oldBase.escVectorND(); //printf("\n");
	this->width = width;
	//printf("   -->%lg  \n", this->width);
	this->mainArrow.aristaSet(this->oldHead, this->oldBase, this->width);
	
	//printf("\n\n     -->mainArrow set\n");
	this->newHead.initVectorND(3, newHead.access(0), newHead.access(1), newHead.access(2));
	//printf("     -->newHead set\n");
	this->partition = partition;
	//printf("     -->partition set\n");
	this->aux.initVectorND(3, mainArrow.head.access(0), mainArrow.head.access(1), mainArrow.head.access(2));
	//printf("     -->aux vector set\n");

	this->transformation.initMatrixArrow(1, partition);
	//printf("     -->transformation memory space set\n");
	double gamma = 1.0;
	double step = 1.0/(double)partition;
	for (int i = 0; i < partition; i++) {
		gamma -= step;

		this->aux.dilate(this->oldHead, newHead, gamma);
		//this->aux.escVectorND(); //printf("\n");
		this->transformation.initA(0, i, this->aux, this->oldBase, this->width);
	}
	//printf("     -->transformation memory space filled success\n");
}

void ArrowTransform::updateTransform(Arrow mainArrow, VectorND newHead, double width) {

	//printf("    -->reflection := %d\n", mainArrow.reflection);
	this->oldBase.updateVector3D(mainArrow.head.access(0), mainArrow.head.access(1), mainArrow.head.access(2));
	this->oldHead.updateVector3D(mainArrow.base.access(0), mainArrow.base.access(1), mainArrow.base.access(2));
	//printf("-->OldHead  :=   "); this->oldHead.escVectorND(); //printf("\n");
	//printf("-->oldBase  :=   "); this->oldBase.escVectorND(); //printf("\n");
	this->width = width;
	//printf("   -->%lg  \n", this->width);
	this->mainArrow.aristaSetUdate(this->oldHead, this->oldBase, this->width);
	
	//printf("\n\n     -->mainArrow set\n");
	this->newHead.updateVector3D(newHead.access(0), newHead.access(1), newHead.access(2));
	//printf("     -->newHead set\n");
	this->aux.updateVector3D(mainArrow.head.access(0), mainArrow.head.access(1), mainArrow.head.access(2));
	//printf("     -->aux vector set\n");

	double gamma = 1.0;
	double step = 1.0/(double)this->partition;
	for (int i = 0; i < this->partition; i++) {
		gamma -= step;

		this->aux.dilate(this->oldHead, newHead, gamma);
		//this->aux.escVectorND(); //printf("\n");
		this->transformation.updateA(0, i, this->aux, this->oldBase, this->width);
	}
	//printf("     -->transformation memory space filled success\n");
}

void ArrowTransform::initTransformTail(Arrow mainArrow, VectorND newTail, int partition, double width) {

	this->oldBase.initVectorND(3, mainArrow.head.access(0), mainArrow.head.access(1), mainArrow.head.access(2));
	this->oldHead.initVectorND(3, mainArrow.base.access(0), mainArrow.base.access(1), mainArrow.base.access(2));
	this->width = width;
	this->mainArrow.aristaSet(this->oldHead, this->oldBase, this->width);
	
	this->newTail.initVectorND(3, newTail.access(0), newTail.access(1), newTail.access(2));
	this->partition = partition;
	this->aux.initVectorND(3, mainArrow.base.access(0), mainArrow.base.access(1), mainArrow.base.access(2));
	
	this->transformation.initMatrixArrow(1, partition);
	double gamma = 1.0;
	double step = 1.0/(double)partition;
	for (int i = 0; i < partition; i++) {
		gamma -= step;

		this->aux.dilate(this->oldBase, newTail, gamma);
		this->transformation.initA(0, i, this->oldHead, this->aux, this->width);
	}
}