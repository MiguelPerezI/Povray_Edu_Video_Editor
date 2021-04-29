#include <stdarg.h>
#include "VectorND.hpp"
#include "matrix.hpp"
#include "geometry.hpp"

#ifndef TURTLE
#define TURTLE

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

class Turtle {
    private:
        VectorND head;
        VectorND tail;
        VectorND auxVec, perpK, perpKMove;
        Facet plane;
        double initStep;
        double angle;
        RotationMats A;
        int counted;
        int Max;
        int move;
        VectorND a, w, r, u;
        MatrixArista snake;
        double stepLen;

    public:
        void initTurtle(VectorND b, VectorND u, VectorND pp, double theta, double angle, int Max);
        MatrixArista getPath();
        Arista accessPathPiece(int);
        void forwardTurtle(double s);
        VectorND getHead();
        void rotateRightTurtle();
        void rotateLeftTurtle();
};


#endif
