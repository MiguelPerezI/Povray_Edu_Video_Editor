#ifndef POVRAYWRITER
#define POVRAYWRITER

using namespace std;

#include <iostream>
#include <math.h>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include "VectorND.hpp"
#include "matrix.hpp"
#include "geometry.hpp"
#include "Turtle.hpp"
#include "dodecahedron.hpp"
#include "Arrow.hpp"

class POVRayWriter
{
    private:
        //Variables imprescindibles
    string filePath;
    //////////////////////////////////ofstream writer;
    ofstream iniCreator;

        //Control default
    bool defaultFinish;
    bool defaultPigment;

        //Control de finish
    double phongToAdd;
    double ambientToAdd;
    double diffuseToAdd;
    bool finish;
        //Control de pigment
    string colorToAdd;
    string checkerColorToAdd[2];
    double transmitToAdd;
    double filterToAdd;
    bool pigment;
    bool checker;
        //Control de burbujas
    double powerToAdd;
    bool inBlob;
        //Control de vectores
    string nameToUse;
    string indexToUse;
    bool useVector;
        //Control de rotación
    bool rad;
    string rotationToAdd;
    bool rotation;
    double pi;
        //Control de texturas
    string textureToAdd;
    bool texture;


        //Funciones auxiliares
    void writeVector(double x, double y, double z);
    void writeScaleVector(double x, double y, double z);

    public:
    ofstream writer;
    POVRayWriter(string path);

    void createIniFile(string path, int frames, int initClock, int endClock);
    void createIniFile(string path, int frames);
    string Clock();
    void writeFinish();
    void addPowerToNextObjects(double power);
    void addElementToVectorArray(double x, double y, double z);
    void write(string str);
    void closePOVRayWriter();
    void rotClockZ();
    void rotClockY();

    //geometry
    void createSphere(double r, VectorND centro, int mod);
    void cylinder(VectorND a, VectorND b, double r, int);
    void cylinderCube(VectorND a, VectorND b, double r);
    void renderFacetPOVRay(Facet facet, int mod, RotationMats U);
    void renderCubeNeighborhood(CubeNeighborhood cube, RotationMats U);
    void renderArista(Arista arista, RotationMats U);
    void renderLattice2D(Lattice2D, RotationMats);
    void renderTurtleHead(Turtle turtle, RotationMats U);
    void renderDodecahedron(Dodecahedron, RotationMats);
    void renderArrow(Arrow arrow, RotationMats, int);
    void renderSquare(Square square, RotationMats, int);
    void renderSpaceCurve(SpaceCurve, RotationMats, int);
    void renderAristaType1(Arista, RotationMats, double, int);
    void renderMatrixArista(MatrixArista, RotationMats, double, int);

    void text(string tex, double size, VectorND position, double angleRotY, string color);

    //textures
    void woodTexture();
    void glassTexture1();
    void glassTexture2();
    void glassTexture3();
    void marbleTexture1();
    void T_Gold_1A();
    void T_Chrome_5A();
    void mirrorTexture();
    void Paint0(int);

    //cameras
    void ultra_wide_camera(VectorND position, VectorND lookAt, double angle);
    void ultra_wide_camera_TETA(int);
    void ultra_wide_camera_Update(double, double, double);
    //lights
    void createLight(VectorND position);

    //conditionals
    void ifStatement(const char*);

};

#endif