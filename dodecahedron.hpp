#include <stdarg.h>
#include "VectorND.hpp"
#include "matrix.hpp"
#include "geometry.hpp"

#ifndef DODECAHEDRON
#define DODECAHEDRON

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class Dodecahedron {
    private:
        int n;
        double radius, gold, g1, g2;
        VectorND center;
        MatrixFacet mesh;
        MatrixArista arista;
        CrackFacet aux;
        Inversion inversion;
        
    public:
        VectorND vertex[20];
        MatrixFacetList complex;
        void initDodecahedron(double, VectorND);
        void renderDodecahedron(int, RotationMats);
        void initSmooth(int);
        MatrixFacet getMesh(int);
        Arista getArista(int, int);
        void updateArista();
        void updateMesh();
        void updateDodecahedron(double, VectorND);
        void updateSmooth();
        void updateDodecahedronInversion();
        void updateSmoothInversion();
        Dodecahedron dilateDodecahedron(VectorND, double);
};

class MatrixDodecahedron {
    public:
        int m, n;
        Dodecahedron * * A;
        RotationMats U;

        void initMatrixDodecahedron(int, int);
        void initMatrixDodecahedronRotation(VectorND, VectorND, double);
        void updateMatrixDodecahedronRotation(VectorND, VectorND, double);
        void rotateA(int, int);
        void initA(int, int, double, VectorND);
        void renderMatrixDodecahedron(int, RotationMats);
};

#endif