#include "matrix.hpp"
#include "VectorND.hpp"
#include "geometry.hpp"
#include "simplex.hpp"

#ifndef ARROW
#define ARROW

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class Arrow {

	public:
		int m;
		int n;
		VectorND base;
		VectorND head;
		double width;
		MatrixVectorND points;
		MatrixFacet mesh;
	
		VectorND D;
	
		VectorND h0;
		VectorND h1;
		VectorND h2;
		VectorND h3;
		VectorND center;
		VectorND Z;
		VectorND minusZ;
		VectorND centerM;
		double longitud;

		int reflection;
	
		RotationMats Rz_phi1;
		RotationMats Ry_teta1;
		RotationMats Rz_phi2;
		RotationMats Ry_teta2;
	
		VectorND help;
	
		void arrowGo(VectorND, VectorND, double);
		void arrowUpdate(VectorND, VectorND, double);
		void aristaSet(VectorND, VectorND, double);
		void aristaSetUdate(VectorND, VectorND, double);
		void reflectArista();
		void initTransfom(VectorND);
};

class MatrixArrow {
    public:
        int m, n;
        Arrow * * A;

        void initMatrixArrow(int, int);
        void initA(int, int, VectorND, VectorND, double);
        void updateA(int i, int j, VectorND a, VectorND b, double width);
};

class ArrowTransform {
	public:
		Arrow mainArrow;
		VectorND newHead;
		VectorND newTail;
		MatrixArrow transformation;
		VectorND aux;
		VectorND oldHead, oldBase;
		double width;

		int partition;
		void initTransform(Arrow, VectorND, int, double);
		void updateTransform(Arrow mainArrow, VectorND newHead, double width);
		void initTransformTail(Arrow, VectorND, int, double);
};

class SpaceCurve {
	public:
		int n;
		MatrixArista curve;
		double width;
		VectorND aux[4];
		MatrixAristaList curveList;
		Inversion inversion;

		void initSpaceCurveType1(int, double);
		void initSpaceCurveType2(int, double);
		void initSpaceCurveType3(int, double);
		void initSpaceCurveType4(int, double);
		void initSpaceCurveType5(int, double);
		void initSpaceCurveType6(int, double);
		void initCurveList();
};

#endif