#include <cstdio>
#include <fstream>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include "PovRayWriter.hpp"
#include "VectorND.hpp"
#include "geometry.hpp"
#include "matrix.hpp"
#include "dodecahedron.hpp"
#include "Arrow.hpp"

using namespace std;

// ================ CLASS CONSTRUCTOR ================== //
//Class constructor. Initializes the file writer.

POVRayWriter::POVRayWriter(string path)
{
    writer.open(path.c_str());

    if (writer.is_open())
    {
            filePath = path;
            writer << "// Visualing Topology" << endl;
            writer << "// Miguels Topology Master" << endl << endl;

            writer << "#include \"colors.inc\" " << endl;
            writer << "#include \"textures.inc\" " << endl;
            writer << "#include \"glass.inc\" " << endl;
            writer << "#include \"golds.inc\" " << endl;
            writer << "#include \"metals.inc\" " << endl<<endl;
            writer << "background { color Black } " << endl << endl;
    }

    finish = pigment = checker = defaultFinish = defaultPigment = inBlob = rotation = texture = false;
    pi = 3.14159265358;
    return;
}


//Returns the clock variable of POV-Ray
string POVRayWriter::Clock() {
    return "clock";
}

//Creates a ini animation file with the specified number of frames, starting
//at initClock and ending at endClock. The file will be created in the path specified.
void POVRayWriter::createIniFile(string path, int frames, int initClock, int endClock) {

    iniCreator.open(path.c_str());

    iniCreator << "+W150" << endl;
    iniCreator << "+H150" << endl;
    iniCreator << "Input_File_Name = " << path << endl;
    iniCreator << "Initial_Frame = 0" << endl << "Final_Frame = " << frames << endl;
    iniCreator << "Initial_Clock = " << initClock << endl << "Final_Clock = " << endClock << endl;

    iniCreator.close();
    return;
}

//Create a ini animation file in the path given, with the specified frames.
//InitClock and endClock will be adjusted to make a relation 1:1 between
//frames and clocks; this is useful for arrays.
void POVRayWriter::createIniFile(string path, int frames)
{
    iniCreator.open(path.c_str());

    iniCreator << "; INI File Generated with Victor Buendia's POVRayWriter" << endl;
    iniCreator << "Input_File_Name = " << filePath << endl;
    iniCreator << "Initial_Frame = 0" << endl << "Final_Frame = " << frames << endl;
    iniCreator << "Initial_Clock = 0" << endl << "Final_Clock = " << frames << endl;

    iniCreator.close();
    return;
}

//Allows the user to write custom content.
void POVRayWriter::write(string str)
{
    writer << str;
    return;
}

//Close the final.
//IT'S VERY IMPORTANT TO INVOKE THIS FUNCTION AFTER FINISH.
void POVRayWriter::closePOVRayWriter()
{
    writer.close();
    return;
}


// ================= PRIMITIVE CREATION ============================ //
    void POVRayWriter::rotClockZ() {
      writer << endl << "rotate <clock*360, -clock*360, clock*360>" << endl;
    }

    void POVRayWriter::rotClockY() {
      writer << endl << "rotate <0, -clock*360, 0>" << endl;
    }

    void POVRayWriter::ultra_wide_camera(VectorND position, VectorND lookAt, double angle) {
        writer << "camera { " << endl;
        writer << "  ultra_wide_angle " << endl;
        writer << "  location ";
        writeVector(position.access(0), position.access(1), position.access(2));
        writer << endl << "  look_at ";
        writeVector(lookAt.access(0), lookAt.access(1), lookAt.access(2));
        writer << "  right x*image_width/image_height" << endl;
        writer << "angle "; writer << angle << endl;
        writer << "} " << endl << endl;
    }

    void POVRayWriter::ultra_wide_camera_TETA(int go) {
        /*
        double X = R * sin(theta) * cos(phi);
        double Z = R * sin(theta) * sin(phi);
        double Y = R * cos(theta);
        phi = 0.75 * PI;
        teta = 0.4 * 3.1415;
        */
        string teta = to_string(0.05 * 3.1415);
        string phi = to_string((1.75) * 3.1415);
        if (go == 0) {
          writer << "camera { " << endl;
          writer << "  ultra_wide_angle " << endl;
          writer << "  location ";
          writer << "  <250 * sin("<< teta <<") * cos("<< phi <<"), 250 * cos("<< teta <<"), 250 * sin("<< teta <<") * sin("<< phi <<")> ";
          writer << endl << "  look_at ";
          writeVector(0.0, 0.0, 0.0);
          writer << "  right x*image_width/image_height" << endl;
          writer << "angle "; writer << 0.5 * 3.1415 << endl;
          writer << "} " << endl << endl;  
        } else {
          writer << "camera { " << endl;
          writer << "  ultra_wide_angle " << endl;
          writer << "  location ";

          string alfa = phi + " - " + "0.33333"; 

          writer << "  <250 * sin("<< teta <<") * cos(clock + "<< phi <<"), 250 * cos("<< teta <<"), 250 * sin("<< teta <<") * sin(clock + "<< phi <<")> ";
          writer << endl << "  look_at ";
          writeVector(0.0, 0.0, 0.0);
          writer << "  right x*image_width/image_height" << endl;
          writer << "angle "; writer << 0.5 * 3.1415 << endl;
          writer << "} " << endl << endl;
        } 
    }

    void POVRayWriter::ultra_wide_camera_Update(double theta, double phii, double radius) {
        
          string teta = to_string(theta);
          string phi = to_string(phii);
          string rad = to_string(radius);
          writer << "camera { " << endl;
          writer << "  ultra_wide_angle " << endl;
          writer << "  location ";
          writer << "  <"<< rad <<" * sin("<< teta <<") * cos("<< phi <<"), " << rad << "* cos("<< teta <<"), " << rad << " * sin("<< teta <<") * sin("<< phi <<")> ";
          writer << endl << "  look_at ";
          writeVector(0.0, 0.0, 0.0);
          writer << "  right x*image_width/image_height" << endl;
          writer << "angle "; writer << 0.5 * 3.1415 << endl;
          writer << "} " << endl << endl;  
         
    }

    void POVRayWriter::createLight(VectorND position) {
        writer << "light_source {" << endl;
        writeVector(position.access(0), position.access(1), position.access(2));
        writer << endl << "color rgb <0.5, 0.5, 0.5>" << endl;
        writer << "} " << endl << endl;
        
        return;
    }

    void POVRayWriter::createSphere(double r, VectorND center, int mod) {
        writer << "sphere {" << endl;
        writeVector(center.access(0), center.access(1), center.access(2));
        writer << r << endl;

        if (mod%13 == 0) mirrorTexture();
        if (mod%13 == 1) glassTexture1();
        if (mod%13 == 2) glassTexture2();
        if (mod%13 == 3) glassTexture3();
        if (mod%13 == 4) marbleTexture1();
        if (mod%13 == 5) T_Gold_1A();
        if (mod%13 == 6) T_Chrome_5A();
        if (mod%13 == 7) Paint0(0);
        if (mod%13 == 8) Paint0(1);
        if (mod%13 == 9) Paint0(2);
        if (mod%13 == 10) Paint0(3);
        if (mod%13 == 11) Paint0(4);
        if (mod%13 == 12) Paint0(5);
        
        //rotClockY();
        writer << "}" << endl << endl;
    }

    void POVRayWriter::cylinder(VectorND a, VectorND b, double r, int mod) {
        if (a.equalVector(b) == 0) {
          writer << "cylinder {" << endl;
          writeVector(b.access(0), b.access(1), b.access(2));
          writeVector(a.access(0), a.access(1), a.access(2));
          writer << r; //<< endl;
        if (mod%13 == 0) mirrorTexture();
        if (mod%13 == 1) glassTexture1();
        if (mod%13 == 2) glassTexture2();
        if (mod%13 == 3) glassTexture3();
        if (mod%13 == 4) marbleTexture1();
        if (mod%13 == 5) T_Gold_1A();
        if (mod%13 == 6) T_Chrome_5A();
        if (mod%13 == 7) Paint0(0);
        if (mod%13 == 8) Paint0(1);
        if (mod%13 == 9) Paint0(2);
        if (mod%13 == 10) Paint0(3);
        if (mod%13 == 11) Paint0(4);
        if (mod%13 == 12) Paint0(5);

          //rotClockY();
          writer << "}" << endl << endl;
        }
          
    }

    void POVRayWriter::renderFacetPOVRay(Facet facet, int mod, RotationMats U) {

        writer << "polygon {" << endl;
        writer << 3 << endl;
    
        writeVector(facet.pointA().access(0), facet.pointA().access(1), facet.pointA().access(2));
        writeVector(facet.pointB().access(0), facet.pointB().access(1), facet.pointB().access(2));
        writeVector(facet.pointC().access(0), facet.pointC().access(1), facet.pointC().access(2));
    
        if (mod%15 == 0) mirrorTexture();
        if (mod%15 == 1) glassTexture1();
        if (mod%15 == 2) glassTexture2();
        if (mod%15 == 3) glassTexture3();
        if (mod%15 == 4) marbleTexture1();
        if (mod%15 == 5) T_Gold_1A();
        if (mod%15 == 6) T_Chrome_5A();
        if (mod%15 == 7) Paint0(0);
        if (mod%15 == 8) Paint0(1);
        if (mod%15 == 9) Paint0(2);
        if (mod%15 == 10) Paint0(3);
        if (mod%15 == 11) Paint0(4);
        if (mod%15 == 12) Paint0(5);
        if (mod%15 == 13) Paint0(6);
        if (mod%15 == 14) Paint0(6);
      
        //rotClockY();
        writer << "}" << endl << endl;

        //cylinder(facet.pointA(), facet.pointB(), 0.005);
        //cylinder(facet.pointA(), facet.pointC(), 0.005);
        //cylinder(facet.pointC(), facet.pointB(), 0.005);
    }

    void POVRayWriter::renderSquare(Square square, RotationMats U, int n) {

      renderFacetPOVRay(square.mesh.getFacet(0, 0), n, U);
      renderFacetPOVRay(square.mesh.getFacet(0, 1), n, U); 
    }

    void POVRayWriter::renderCubeNeighborhood(CubeNeighborhood cube, RotationMats U) {

        double width = 0.05 * cube.getRadius();
        cylinder(cube.getVertex(0), cube.getVertex(1), width, 7);
        cylinder(cube.getVertex(1), cube.getVertex(2), width, 7);
        cylinder(cube.getVertex(2), cube.getVertex(3), width, 7);
        cylinder(cube.getVertex(3), cube.getVertex(0), width, 7);

        cylinder(cube.getVertex(0 + 4), cube.getVertex(3 + 4), width, 7);
        cylinder(cube.getVertex(3 + 4), cube.getVertex(2 + 4), width, 7);
        cylinder(cube.getVertex(2 + 4), cube.getVertex(1 + 4), width, 7);
        cylinder(cube.getVertex(1 + 4), cube.getVertex(0 + 4), width, 7);

        cylinder(cube.getVertex(0), cube.getVertex(4), width, 7);
        cylinder(cube.getVertex(1), cube.getVertex(5), width, 7);
        cylinder(cube.getVertex(2), cube.getVertex(6), width, 7);
        cylinder(cube.getVertex(3), cube.getVertex(7), width, 7);

        for (int i = 0; i < 8; i++)
            createSphere(0.1 * cube.getRadius(), cube.getVertex(i), 6);

        renderFacetPOVRay(cube.getFacet(0), 1, U);
        renderFacetPOVRay(cube.getFacet(1), 1, U);
        renderFacetPOVRay(cube.getFacet(2), 1, U);
        renderFacetPOVRay(cube.getFacet(3), 1, U);
        renderFacetPOVRay(cube.getFacet(4), 1, U);
        renderFacetPOVRay(cube.getFacet(5), 1, U);

    }

    void POVRayWriter::renderDodecahedron(Dodecahedron dodeca, RotationMats U) {

      double width = 0.05 * dodeca.getArista(0, 0).getLength();
      for (int i = 0; i < 30; i++)
        cylinder(dodeca.getArista(0, i).getHead(), dodeca.getArista(0, i).getTail(), width, 7);

      //for (int i = 0; i < 12; i++)
      //  for (int j = 0; j < 3*6*6; j++)
      //    renderFacetPOVRay(dodeca.getMesh(2).getFacet(i, j), 5, U);
    }

    void POVRayWriter::renderLattice2D(Lattice2D lattice2D, RotationMats U) {

      for (int i = 0; i < lattice2D.getM(); i++)
        for (int j = 0; j < lattice2D.getN(); j++) {
          this->renderCubeNeighborhood(lattice2D.getCell(i, j), U);
          this->renderCubeNeighborhood(lattice2D.getCell0(i, j), U);
          this->renderCubeNeighborhood(lattice2D.getCell1(i, j), U);
          this->renderCubeNeighborhood(lattice2D.getCell2(i, j), U);
        }
    }

    void POVRayWriter::renderArista(Arista arista, RotationMats U) {

      cylinder(arista.getHead(), arista.getTail(), 0.05 * arista.getLength(), 0);
    }

    void POVRayWriter::renderAristaType1(Arista arista, RotationMats U, double width, int mod) {

      cylinder(arista.getHead(), arista.getTail(), width, mod);
    }

    void POVRayWriter::renderMatrixArista(MatrixArista setOfCurves, RotationMats U, double width, int mod) {

      for (int i = 0; i < setOfCurves.m; i++) {
        for (int j = 0; j < setOfCurves.n; j++)  {

          renderAristaType1(setOfCurves.getArista(i, j), U, width, mod);
        }
      }
    }

    void POVRayWriter::renderSpaceCurve(SpaceCurve camino, RotationMats U, int mod) {

      for (int i = 0; i < camino.n; i++) {
        renderAristaType1(camino.curve.getArista(0, i), U, 0.1, mod);
      }
    }

    void POVRayWriter::renderTurtleHead(Turtle turtle, RotationMats U) {

      createSphere(0.2, turtle.getHead(), 6);
    }

    void POVRayWriter::renderArrow(Arrow arrow, RotationMats U, int mod) {

      for (int j = 0; j < arrow.n; j++) {
        for (int i = 0; i < arrow.m*2; i++)
        renderFacetPOVRay(arrow.mesh.getFacet(0, j), mod, U);
        renderFacetPOVRay(arrow.mesh.getFacet(1, j), mod, U);
        renderFacetPOVRay(arrow.mesh.getFacet(2, j), mod, U);
        renderFacetPOVRay(arrow.mesh.getFacet(3, j), mod, U);
        renderFacetPOVRay(arrow.mesh.getFacet(4, j), mod, U);
        renderFacetPOVRay(arrow.mesh.getFacet(5, j), mod, U);
      }
    }

// ============================= DECORATORS =========================== //

void POVRayWriter::woodTexture() {
  writer << "texture{" << endl;
  writer << "pigment{ wood turbulence 0.02 octaves 4 lambda 3"<<endl;
  writer << "scale 10.75  rotate <2, 3, 0>" << endl;
  writer << "color_map {" << endl;
  writer << "[0.0 color rgb <1.00, 0.88, 0.54>]" << endl;
  writer << "[0.1 color rgb <1.00, 0.80, 0.54>]" << endl;
  writer << "[0.5 color rgb <0.70, 0.42, 0.23>]" << endl;
  writer << "[0.7 color rgb <0.70, 0.42, 0.23>]" << endl;
  writer << "[1.0 color rgb <1.00, 0.88, 0.54>]" << endl;
  writer << "}" << endl;
  writer << "}" << endl;
  writer << "finish { phong 1 }" << endl;
  writer << "rotate <0,0, 0>  scale 1  translate <0,0,0>" << endl;
  writer << "}" << endl;
}

void POVRayWriter::glassTexture1() {
  writer << " " << endl;
  writer << "material{ texture{ Glass3  }" << endl;
  writer << "          interior{I_Glass }" << endl;
  writer << "}" << endl << endl;
}

void POVRayWriter::glassTexture2() {
  writer << " " << endl;
  writer << "material{ texture{ NBglass  }" << endl;
  writer << "          interior{I_Glass }" << endl;
  writer << "}" << endl << endl;
}

void POVRayWriter::glassTexture3() {
  writer << " " << endl;
  writer << "texture{ pigment{ rgbf <0.98, 0.98, 0.98, 0.9> }" << endl;
  writer << "         finish {diffuse 0.1 reflection 0.2" << endl;
  writer << "         specular 0.8 roughness 0.0003 phong 1 phong_size 400}" << endl;
  writer << "       }" << endl << endl;
}


void POVRayWriter::marbleTexture1() {
  writer << "texture{ " << endl;
  writer << "         pigment{ Red_Marble }" << endl;
  writer << "         finish { phong 1 }" << endl;
  writer << "         scale 2.0" << endl;
  writer << "       }" << endl;
}

void POVRayWriter::T_Gold_1A() {
  writer << "texture{ T_Gold_1A" << endl;
  writer << "         finish { phong 1 }" << endl;
  writer << "       }" << endl;
}

void POVRayWriter::T_Chrome_5A() {
  writer << "\n texture{ T_Chrome_5A" << endl;
  writer << "         finish { phong 1 }" << endl;
  writer << "       }" << endl;
}

void POVRayWriter::mirrorTexture() {
  writer << "texture{ Polished_Chrome" << endl;
  writer << "         pigment{ color rgb<1, 1, 1> }" << endl;
  //writer << "         normal { crackle 5.5 scale 0.20 }" <<endl;
  writer << "         finish { phong 1 }" << endl;
  writer << "       }" << endl;
return;
}

void POVRayWriter::Paint0(int n) {

  if (n == 0) {
    writer << "pigment { Red }" << endl;
    writer << "finish {" << endl;
  writer << "   ambient .1" << endl;
  writer << "   diffuse .1" << endl;
  writer << "   specular 1" << endl;
  writer << "   roughness .001" << endl;
  writer << "   reflection {" << endl;
  writer << "   0.85" << endl;
  writer << "   }" << endl;
  writer << "}" << endl;
  }
  if (n == 1) {
    writer << "pigment { Green }" << endl;
    writer << "finish {" << endl;
  writer << "   ambient .1" << endl;
  writer << "   diffuse .1" << endl;
  writer << "   specular 1" << endl;
  writer << "   roughness .001" << endl;
  writer << "   reflection {" << endl;
  writer << "   0.85" << endl;
  writer << "   }" << endl;
  writer << "}" << endl;
  }
  if (n == 2) {
    writer << "pigment { Blue }" << endl;
    writer << "finish {" << endl;
  writer << "   ambient .1" << endl;
  writer << "   diffuse .1" << endl;
  writer << "   specular 1" << endl;
  writer << "   roughness .001" << endl;
  writer << "   reflection {" << endl;
  writer << "   0.85" << endl;
  writer << "   }" << endl;
  writer << "}" << endl;
  }
  if (n == 3) {
    writer << "pigment { checker Black, White }" << endl;
    writer << "scale 3.0" << endl;
    writer << "finish {" << endl;
  writer << "   ambient .1" << endl;
  writer << "   diffuse .1" << endl;
  writer << "   specular 1" << endl;
  writer << "   roughness .001" << endl;
  writer << "   reflection {" << endl;
  writer << "   0.4" << endl;
  writer << "   }" << endl;
  writer << "}" << endl;}
  if (n == 4) {
    writer << "pigment { White }" << endl;
    writer << "finish {" << endl;
  writer << "   ambient .1" << endl;
  writer << "   diffuse .1" << endl;
  writer << "   specular 1" << endl;
  writer << "   roughness .001" << endl;
  writer << "   reflection {" << endl;
  writer << "   0.85" << endl;
  writer << "   }" << endl;
  writer << "}" << endl;
  }
  if (n == 5) {
    writer << "pigment { Black }" << endl;
    writer << "finish {" << endl;
  writer << "   ambient .1" << endl;
  writer << "   diffuse .1" << endl;
  writer << "   specular 1" << endl;
  writer << "   roughness .001" << endl;
  writer << "   reflection {" << endl;
  writer << "   0.85" << endl;
  writer << "   }" << endl;
  writer << "}" << endl;
  }
  if (n == 6) {
    writer << "pigment { Yellow }" << endl;
    writer << "finish {" << endl;
  writer << "   ambient .1" << endl;
  writer << "   diffuse .1" << endl;
  writer << "   specular 1" << endl;
  writer << "   roughness .001" << endl;
  writer << "   reflection {" << endl;
  writer << "   0.85" << endl;
  writer << "   }" << endl;
  writer << "}" << endl;
  }

  if (n == 7) {
    writer << "pigment { Orange }" << endl;
    writer << "finish {" << endl;
  writer << "   ambient .1" << endl;
  writer << "   diffuse .1" << endl;
  writer << "   specular 1" << endl;
  writer << "   roughness .001" << endl;
  writer << "   reflection {" << endl;
  writer << "   0.85" << endl;
  writer << "   }" << endl;
  writer << "}" << endl;
  }

}

// ===================== ARRAYS AND ROTATIONS=========================== //

// ============================== AUXILIAR FUNCTIONS ===================================== //

//Writes the vector indicated in the file
void POVRayWriter::writeVector(double x, double y, double z) {
    writer << "<" << x << ", " << y << ", " << z << ">   ";
    return;
}

void POVRayWriter::ifStatement(const char* S) {
  writer << "#if ("<< S << ")" << endl;
}