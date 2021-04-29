#include <cstdio>
#include <iostream>
#include <sstream>
#include <cmath>
#include "PovRayWriter.hpp"
#include "VectorND.hpp"
#include "geometry.hpp"
#include "Turtle.hpp"
#include "dodecahedron.hpp"
#include "Arrow.hpp"
#include <string>
#include "simplex.hpp"

using namespace std;

double PI = 3.1415926535897932384626;

VectorND center, I, J, K, minusI, minusJ, minusK, position, lightPosition;
VectorND joker, joker0;
double radius = 0.25;
double theta;
double phi;
double R, newR;

/*Rotation Matrix System*/
RotationMats U;

/*Arrow*/
Arrow flecha, flecha0, flecha1, flecha2;

/*Arrow Matrix*/
MatrixArrow matArrow;
MatrixArrow matArrow2D;
double partition = 1;

/*floor*/
Square fl, fl0, fl1, fl2, fl3, fl4;
VectorND floor0, floor1, floor2, floor3;

/*MatrixVector*/
MatrixVectorND firstBall;

/*1D scene utilities*/
VectorND oneDHead;
VectorND oneDTail;
Arrow oneDArrow;
ArrowTransform oneDArrowAnimation;

/*1D to 2D Part 1*/
VectorND oneDtwoDHead;
VectorND oneDtwoDTail;
Arrow oneDtwoDArrow;
ArrowTransform oneDtwoDArrowAnimation;

/*1D to 2D Part 2*/
VectorND oneDtwoD2Head;
VectorND oneDtwoD2Tail;
Arrow oneDtwoD2Arrow;
ArrowTransform oneDtwoD2ArrowAnimation;

/*1D to 2D Part 2*/
VectorND oneDtwoD3Head;
VectorND oneDtwoD3Tail;
Arrow oneDtwoD3Arrow;
ArrowTransform oneDtwoD3ArrowAnimation;

/*1D to 2D Part 2*/
VectorND oneDtwoD4Head;
VectorND oneDtwoD4Tail;
Arrow oneDtwoD4Arrow;
ArrowTransform oneDtwoD4ArrowAnimation;

/*1D to 2D Part 2*/
VectorND oneDtwoD5Head;
VectorND oneDtwoD5Tail;
Arrow oneDtwoD5Arrow;
ArrowTransform oneDtwoD5ArrowAnimation;

/*1D to 2D Part 2*/
VectorND oneDtwoD6Head;
VectorND oneDtwoD6Tail;
Arrow oneDtwoD6Arrow;
ArrowTransform oneDtwoD6ArrowAnimation;

/*1D to 2D Part 2*/
VectorND oneDtwoD7Head;
VectorND oneDtwoD7Tail;
Arrow oneDtwoD7Arrow;
ArrowTransform oneDtwoD7ArrowAnimation;

/*1D to 2D Part 2*/
VectorND oneDtwoD8Head;
VectorND oneDtwoD8Tail;
Arrow oneDtwoD8Arrow;
ArrowTransform oneDtwoD8ArrowAnimation;

/*1D to 2D Part 2*/
VectorND oneDtwoD9Head;
VectorND oneDtwoD9Tail;
Arrow oneDtwoD9Arrow;
ArrowTransform oneDtwoD9ArrowAnimation;

/*1D to 2D Part 2*/
VectorND oneDtwoD10Head;
VectorND oneDtwoD10Tail;
Arrow oneDtwoD10Arrow;
ArrowTransform oneDtwoD10ArrowAnimation;

/*Unit Vector I*/
VectorND unitIHead;
VectorND unitITail;
Arrow unitIArrow;
ArrowTransform unitIArrowAnimation;

/*Unit Vector J*/
VectorND unitJHead;
VectorND unitJTail;
Arrow unitJArrow;
ArrowTransform unitJArrowAnimation;

/*Unit Vector K*/
VectorND unitKHead;
VectorND unitKTail;
Arrow unitKArrow;
ArrowTransform unitKArrowAnimation;


void setup() {

	printf("\n\n<<<<<<<<<<<<>>>>> Terminus POV-Ray <<<<<>>>>>>>>>>>>>\n\n                  ---> Memory Setup ---> \n\n");

          ///////////////////
          /*  Base for R3  */
          ///////////////////
          center.zeroVectorND(3);
          I.initVectorND(3, 1.0, 0.0, 0.0);
          J.initVectorND(3, 0.0, 1.0, 0.0);
          K.initVectorND(3, 0.0, 0.0, 1.0);
          minusI.initVectorND(3,-1.0, 0.0, 0.0);
          minusJ.initVectorND(3, 0.0,-1.0, 0.0);
          minusK.initVectorND(3, 0.0, 0.0,-1.0);

          ///////////////////
          /*Camara position*/
          ///////////////////
          theta = 0.4 * PI; 
          phi = 0.75 * PI;
          R = 250;
          double X = R * sin(theta) * cos(phi);
          double Z = R * sin(theta) * sin(phi);
          double Y = R * cos(theta);
          position.initVectorND(3, X, Y, Z);

          ///////////////////
          /*Light position*/
          ///////////////////
          lightPosition.initVectorND(3,-2.0, 4.0, 1.0);

          
          joker.initVectorND(3, 2.0, 0.0, 0.0);
          joker0.initVectorND(3, 2.0, 0.0, 0.0);

          ///////////////////
          /*SkyBox         */
          ///////////////////
          double far = 15.0;
          double wid = 20.0;
          floor0.initVectorND(3, wid, -2.0, wid);
          floor1.initVectorND(3,-wid, -2.0, wid);
          floor2.initVectorND(3,-wid, -2.0,-wid);
          floor3.initVectorND(3, wid, -2.0,-wid);
          fl.initSquare(floor0, floor1, floor2, floor3);
          printf("-->Floor setup succesful\n");

          ///////////////////
          /*Rotation Matrix*/
          ///////////////////
          U.initRotationMats(0.0);

          ///////////////////
          /*Geometry       */
          ///////////////////
          firstBall.initMatrixVectorND(1, 50);
          printf("-->Curve animation setup succesful\n");


          ////////////////////
          /*Vector Animation*/
          ////////////////////
          int count = 0;
          while (count < 150) {

            if (count < 50) {
              firstBall.A[0][count].initVectorND(3, 2.0, 0.0, 2.0);
              }

            count += 1;
          }

          printf("-->Animation setup succesful\n");

          joker.updateVector3D(0.0, 3.0, 0.0);
          joker0.updateVector3D(0.0,-3.0, 0.0);
          flecha0.aristaSet(joker, joker0, 0.1);
          joker.updateVector3D(3.0, 0.0, 0.0);
          joker0.updateVector3D(-3.0, 0.0, 0.0);
          flecha1.aristaSet(joker, joker0, 0.1);
          joker.updateVector3D(0.0, 0.0, 3.0);
          joker0.updateVector3D(0.0, 0.0,-3.0);
          flecha2.aristaSet(joker, joker0, 0.1);

          ////////////////////
          /*RED VECTOR*/
          ////////////////////
          joker.updateVector3D(2.0, 0.0, 2.0);

          oneDHead.initVectorND(3, 0.01, 0.0, 0.01);
          oneDTail.initVectorND(3, 0.00, 0.0, 0.0);
          oneDArrow.aristaSet(oneDHead, oneDTail, 0.3);
          oneDArrowAnimation.initTransform(oneDArrow, joker, 50, 0.15);

          ////////////////////
          /*BLUE VECTOR*/
          ////////////////////
          joker.updateVector3D(2.0, 0.0, 0.0);

          oneDtwoDHead.initVectorND(3, 0.01, 0.0, 0.0);
          oneDtwoDTail.initVectorND(3, 0.00, 0.0, 0.0);
          oneDtwoDArrow.aristaSet(oneDtwoDHead, oneDtwoDTail, 0.3);
          oneDtwoDArrowAnimation.initTransform(oneDtwoDArrow, joker, 50, 0.15);

          ////////////////////
          /*GREEN VECTOR*/
          ////////////////////
          joker.updateVector3D(2.0, 0.0, 2.0);

          oneDtwoD2Head.initVectorND(3, 2.0, 0.0, 0.01);
          oneDtwoD2Tail.initVectorND(3, 2.0, 0.0, 0.0);
          oneDtwoD2Arrow.aristaSet(oneDtwoD2Head, oneDtwoD2Tail, 0.3);
          oneDtwoD2ArrowAnimation.initTransform(oneDtwoD2Arrow, joker, 50, 0.15);

          ////////////////////
          /*ORANGE VECTOR*/
          ////////////////////
          joker.updateVector3D(2.0, 2.0, 2.0);

          oneDtwoD3Head.initVectorND(3, 2.0, 0.5, 2.0);
          oneDtwoD3Tail.initVectorND(3, 2.0, 0.0, 2.0);
          oneDtwoD3Arrow.aristaSet(oneDtwoD3Head, oneDtwoD3Tail, 0.3);
          oneDtwoD3ArrowAnimation.initTransform(oneDtwoD3Arrow, joker, 50, 0.15);

          ////////////////////
          /*UNIT I VECTOR*/
          ////////////////////
          joker.updateVector3D(1.0, 0.0, 0.0);

          unitIHead.initVectorND(3, 0.01, 0.0, 0.0);
          unitITail.initVectorND(3, 0.0, 0.0, 0.0);
          unitIArrow.aristaSet(unitIHead, unitITail, 0.45);
          unitIArrowAnimation.initTransform(unitIArrow, joker, 50, 0.2);

          ////////////////////
          /*UNIT J VECTOR*/
          ////////////////////
          joker.updateVector3D(0.0, 0.0, 1.0);

          unitJHead.initVectorND(3, 0.0, 0.0, 0.01);
          unitJTail.initVectorND(3, 0.0, 0.0, 0.0);
          unitJArrow.aristaSet(unitJHead, unitJTail, 0.45);
          unitJArrowAnimation.initTransform(unitJArrow, joker, 50, 0.2);

          ////////////////////
          /*UNIT K VECTOR*/
          ////////////////////
          joker.updateVector3D(0.0, 1.0, 0.0);

          unitKHead.initVectorND(3, 0.0, 0.01, 0.0);
          unitKTail.initVectorND(3, 0.0, 0.0, 0.0);
          unitKArrow.aristaSet(unitIHead, unitITail, 0.45);
          unitKArrowAnimation.initTransform(unitIArrow, joker, 50, 0.2);

}

int main(void)
{	
  	setup();
  	POVRayWriter pov("topology.pov");

    pov.renderSquare(fl, U, 10);        //floor
  	pov.createLight(lightPosition);
    //joker.updateVector3D(2.0, 0.0, 2.0);
    //pov.createSphere(0.2, joker, 6);  //Origen
    pov.renderArrow(flecha0, U, 6);     //Y-axis
    pov.renderArrow(flecha1, U, 6);     //X-axis
    pov.renderArrow(flecha2, U, 6);     //Z-axis
    
    string str, strAux0, strAux1, strAux2, strAux3;

    //pov.ultra_wide_camera(position, center, 0.5 * PI);
    pov.writer << "#if(0.0 <= clock & clock <= 0.3125)" << endl;
    pov.ultra_wide_camera_Update(0.11 * PI, 1.75 * PI, 250);
    pov.writer << "#end" << endl;
//
    //pov.text("het", 0.7, center, 90, "Red");

      ////////////////////
      //                //
      /*    1D scene    */
      //                //
      ////////////////////

      printf("\n-->1D scene\n");
      printf("-->Time 1\n");

      for (int i = 0; i < 50; i++) {
        str = "   #if (";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821 <= clock & clock <= ";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.createSphere(0.004 * (double)i, firstBall.getA(0, i), 6);
        pov.writer << "   #end" << endl;
      }

        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 1*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 7*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.createSphere(0.2, firstBall.getA(0, 49), 6);
        pov.writer << "   #end" << endl;

      printf("-->Time 2\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDArrowAnimation.transformation.A[0][i], U, 7);
        pov.writer << "   #end" << endl;
      }

        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 2*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 7*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDArrowAnimation.transformation.A[0][49], U, 7);
        pov.writer << "   #end" << endl;

      printf("-->Time 3\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 2*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 2*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoDArrowAnimation.transformation.A[0][i], U, 9);
        pov.writer << "   #end" << endl;
      }

        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 3*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 7*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoDArrowAnimation.transformation.A[0][49], U, 9);
        pov.writer << "   #end" << endl;

      printf("-->Time 4\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 3*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 3*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD2ArrowAnimation.transformation.A[0][i], U, 8);

        pov.writer << "   #end" << endl;
      }

        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 4*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 7*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD2ArrowAnimation.transformation.A[0][49], U, 8);
        pov.writer << "   #end" << endl;

//      printf("-->Time 5\n");
//      for (int i = 0; i < 50; i++) {
//        str = "   #if ((";
//        strAux0 = to_string(i);
//        strAux1 = "*0.000512821) + 4*0.025641026 < clock & clock <= (";
//        strAux2 = to_string(i+1);
//        strAux3 = "*0.000512821) + 4*0.025641026)";
//  
//        str += strAux0;
//        str += strAux1;
//        str += strAux2;
//        str += strAux3;
//  
//        pov.writer << str << endl;
//        pov.renderArrow(oneDArrowAnimation.transformation.A[0][49], U, 7);
//        pov.renderArrow(oneDtwoDArrowAnimation.transformation.A[0][49], U, 9);
//        pov.renderArrow(oneDtwoD2ArrowAnimation.transformation.A[0][49], U, 8);
//        pov.createSphere(0.2, firstBall.getA(0, 49), 6);
//
//        pov.writer << "   #end" << endl;
//      }

      printf("-->Time 6\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 5*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 5*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(unitIArrowAnimation.transformation.A[0][i], U, 12);
        pov.writer << "   #end" << endl;
      }

        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 6*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 20*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(unitIArrowAnimation.transformation.A[0][49], U, 12);
        pov.writer << "   #end" << endl;

      printf("-->Time 7\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 6*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 6*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(unitJArrowAnimation.transformation.A[0][i], U, 12);
        pov.createSphere(0.2, firstBall.getA(0, 49), 6);
        pov.writer << "   #end" << endl;
      }

      str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 7*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 20*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(unitJArrowAnimation.transformation.A[0][49], U, 12);
        pov.writer << "   #end" << endl;

//      printf("-->Time 8\n");
//      for (int i = 0; i < 50; i++) {
//        str = "   #if ((";
//        strAux0 = to_string(i);
//        strAux1 = "*0.000512821) + 7*0.025641026 < clock & clock <= (";
//        strAux2 = to_string(i+1);
//        strAux3 = "*0.000512821) + 7*0.025641026)";
//  
//        str += strAux0;
//        str += strAux1;
//        str += strAux2;
//        str += strAux3;
//  
//        pov.writer << str << endl;
//        pov.renderArrow(oneDArrowAnimation.transformation.A[0][49], U, 7);
//        pov.renderArrow(oneDtwoDArrowAnimation.transformation.A[0][49], U, 9);
//        pov.renderArrow(oneDtwoD2ArrowAnimation.transformation.A[0][49], U, 8);
//        pov.renderArrow(unitIArrowAnimation.transformation.A[0][49], U, 12);
//        pov.renderArrow(unitJArrowAnimation.transformation.A[0][49], U, 12);
//        pov.createSphere(0.2, firstBall.getA(0, 49), 6);
//        pov.writer << "   #end" << endl;
//      }

      printf("-->Time 9\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 8*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 8*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDArrowAnimation.transformation.A[0][49-i], U, 7);
        pov.renderArrow(oneDtwoDArrowAnimation.transformation.A[0][49-i], U, 9);
        pov.renderArrow(oneDtwoD2ArrowAnimation.transformation.A[0][49-i], U, 8);
        pov.createSphere(0.2001-(0.004*(double)i), firstBall.getA(0, 49-i), 6);
        pov.writer << "   #end" << endl;
      }

//      printf("-->Time 10\n");
//      for (int i = 0; i < 50; i++) {
//        str = "   #if ((";
//        strAux0 = to_string(i);
//        strAux1 = "*0.000512821) + 9*0.025641026 < clock & clock <= (";
//        strAux2 = to_string(i+1);
//        strAux3 = "*0.000512821) + 9*0.025641026)";
//  
//        str += strAux0;
//        str += strAux1;
//        str += strAux2;
//        str += strAux3;
//  
//        pov.writer << str << endl;
//        pov.renderArrow(unitIArrowAnimation.transformation.A[0][49], U, 12);
//        pov.renderArrow(unitJArrowAnimation.transformation.A[0][49], U, 12);
//        pov.writer << "   #end" << endl;
//      }

      printf("-->Time 11\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 10*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 10*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.ultra_wide_camera_Update((0.11 * PI) + (0.015079 * (double )i), (1.75 * PI) + (0.031415*(double)i), 250);
        pov.renderArrow(unitKArrowAnimation.transformation.A[0][i], U, 12);
        pov.writer << "   #end" << endl;
      }

        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 11*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 20*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(unitKArrowAnimation.transformation.A[0][49], U, 12);
        pov.writer << "   #end" << endl;

        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 11*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 15*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.ultra_wide_camera_Update(0.35*PI, 0.25*PI, 250);
        pov.writer << "   #end" << endl;

      //oneDtwoDArrowAnimation.initTransform(oneDtwoDArrow, joker, 0.15);

      printf("-->Time 12\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 11*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 11*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoDArrowAnimation.transformation.A[0][i], U, 9);
        pov.writer << "   #end" << endl;
      }

        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 12*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 20*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoDArrowAnimation.transformation.A[0][49], U, 9);
        pov.writer << "   #end" << endl;

      printf("-->Time 13\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 12*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 12*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.ultra_wide_camera_Update(0.35*PI, 0.25*PI, 250);
        pov.renderArrow(oneDtwoD2ArrowAnimation.transformation.A[0][i], U, 8);
        pov.writer << "   #end" << endl;
      }

        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 13*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 20*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD2ArrowAnimation.transformation.A[0][49], U, 8);
        pov.writer << "   #end" << endl;

      printf("-->Time 14\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 13*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 13*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD3ArrowAnimation.transformation.A[0][i], U, 14);
        pov.writer << "   #end" << endl;
      }

        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 14*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 20*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD3ArrowAnimation.transformation.A[0][49], U, 14);
        pov.writer << "   #end" << endl;

//      printf("-->Time 15\n");
//      for (int i = 0; i < 50; i++) {
//        str = "   #if ((";
//        strAux0 = to_string(i);
//        strAux1 = "*0.000512821) + 14*0.025641026 < clock & clock <= (";
//        strAux2 = to_string(i+1);
//        strAux3 = "*0.000512821) + 14*0.025641026)";
//  
//        str += strAux0;
//        str += strAux1;
//        str += strAux2;
//        str += strAux3;
//  
//        pov.writer << str << endl;
//        pov.renderArrow(oneDtwoDArrowAnimation.transformation.A[0][49], U, 9);
//        pov.renderArrow(oneDtwoD2ArrowAnimation.transformation.A[0][49], U, 8);
//        pov.renderArrow(oneDtwoD3ArrowAnimation.transformation.A[0][49], U, 14);
//        pov.writer << "   #end" << endl;
//      }

//      printf("-->Time 16\n");
//      for (int i = 0; i < 50; i++) {
//        str = "   #if ((";
//        strAux0 = to_string(i);
//        strAux1 = "*0.000512821) + 15*0.025641026 < clock & clock <= (";
//        strAux2 = to_string(i+1);
//        strAux3 = "*0.000512821) + 15*0.025641026)";
//  
//        str += strAux0;
//        str += strAux1;
//        str += strAux2;
//        str += strAux3;
//  
//        pov.writer << str << endl;
//        pov.ultra_wide_camera_Update(0.35*PI, 0.25*PI, 250);
//        pov.renderArrow(oneDtwoDArrowAnimation.transformation.A[0][49], U, 9);
//        pov.renderArrow(oneDtwoD2ArrowAnimation.transformation.A[0][49], U, 8);
//        pov.renderArrow(oneDtwoD3ArrowAnimation.transformation.A[0][49], U, 14);
//        pov.writer << "   #end" << endl;
//      }

      printf("-->Time 17\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 16*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 16*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.ultra_wide_camera_Update(0.35*PI, (0.25*PI - (0.007853 * (double)i)), 250);
        pov.writer << "   #end" << endl;
      }

        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 17*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 20*0.025641026)";////////////////////////////////////////////////////////////////
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.ultra_wide_camera_Update(0.35*PI, 0.125*PI, 250);
        pov.writer << "   #end" << endl;

      joker.updateVector3D(2.0, 0.0, 0.0);
      oneDArrowAnimation.updateTransform(oneDArrow, joker, 0.18);

      printf("-->Time 18\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 17*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 17*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDArrowAnimation.transformation.A[0][i], U, 7);
        pov.writer << "   #end" << endl;
      }

      ////////////////////
      /*BLUE VECTOR*/
      ////////////////////
      joker.updateVector3D(2.0, 0.0, 2.0);

      oneDtwoD4Head.initVectorND(3, 2.0, 0.0, 0.0);
      oneDtwoD4Tail.initVectorND(3, 0.0, 0.0, 0.0);
      oneDtwoD4Arrow.aristaSet(oneDtwoD4Head, oneDtwoD4Tail, 0.3);
      oneDtwoD4ArrowAnimation.initTransform(oneDtwoD4Arrow, joker, 50, 0.18);

      printf("-->Time 19\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 18*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 18*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD4ArrowAnimation.transformation.A[0][i], U, 7);
        pov.writer << "   #end" << endl;
      }

      joker.updateVector3D(2.0, 2.0, 2.0);
      joker0.updateVector3D(2.0, 0.0, 2.0);
      oneDtwoD4Arrow.aristaSetUdate(joker0, center, 0.3);
      oneDtwoD4ArrowAnimation.updateTransform(oneDtwoD4Arrow, joker, 0.18);

      printf("-->Time 20\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 19*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 19*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD4ArrowAnimation.transformation.A[0][i], U, 7);
        pov.writer << "   #end" << endl;
      }

        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 20*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 20*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD4ArrowAnimation.transformation.A[0][49], U, 7);
        pov.writer << "   #end" << endl;







































      /////////////////////////
      //                     //
      //      PART 2         //
      //                     //
      /////////////////////////


        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 21*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 23*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.ultra_wide_camera_Update(0.35*PI, 0.125*PI, 250);
        pov.writer << "   #end" << endl;


        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 21*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 29*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD2ArrowAnimation.transformation.A[0][49], U, 8);
        pov.renderArrow(oneDtwoD3ArrowAnimation.transformation.A[0][49], U, 14);
        pov.writer << "   #end" << endl;

        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 21*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 30*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoDArrowAnimation.transformation.A[0][49], U, 9);
        pov.writer << "   #end" << endl;


        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 21*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 22*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD4ArrowAnimation.transformation.A[0][49], U, 7);
        pov.writer << "   #end" << endl;

        //disapear black unit vectors
      printf("-->Time 22\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 21*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 21*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.ultra_wide_camera_Update(0.35*PI, 0.125*PI, 250);
        pov.renderArrow(unitIArrowAnimation.transformation.A[0][49-i], U, 12);
        pov.renderArrow(unitJArrowAnimation.transformation.A[0][49-i], U, 12);
        pov.renderArrow(unitKArrowAnimation.transformation.A[0][49-i], U, 12);
        pov.writer << "   #end" << endl;
      }

      joker.updateVector3D(-1.5, 2.0, 2.0);

      oneDtwoD5Head.initVectorND(3, 1.5, 2.0, 2.0);
      oneDtwoD5Tail.initVectorND(3, 2.0, 2.0, 2.0);
      oneDtwoD5Arrow.aristaSet(oneDtwoD5Head, oneDtwoD5Tail, 0.3);
      oneDtwoD5ArrowAnimation.initTransform(oneDtwoD5Arrow, joker, 50, 0.18);


      //Draw blue vector
      printf("-->Time 23\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 22*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 22*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD5ArrowAnimation.transformation.A[0][i], U, 9);
        pov.writer << "   #end" << endl;
      }

      joker.updateVector3D(-1.5, 2.0, 2.0);
      joker0.updateVector3D(2.0, 2.0, 2.0);
      oneDtwoD4Arrow.aristaSetUdate(joker0, center, 0.3);
      oneDtwoD4ArrowAnimation.updateTransform(oneDtwoD4Arrow, joker, 0.18);


      str = "   #if ((";
      strAux0 = to_string(0);
      strAux1 = "*0.000512821) + 23*0.025641026 < clock & clock <= (";
      strAux2 = to_string(50);
      strAux3 = "*0.000512821) + 29*0.025641026)";
  
      str += strAux0;
      str += strAux1;
      str += strAux2;
      str += strAux3;
  
      pov.writer << str << endl;
      pov.renderArrow(oneDtwoD5ArrowAnimation.transformation.A[0][49], U, 9);
      pov.writer << "   #end" << endl;

      //draw red vector
      printf("-->Time 24\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 23*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 23*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.ultra_wide_camera_Update(0.35*PI, 0.125*PI - (0.003926991 * (double)i), 250);
        pov.renderArrow(oneDtwoD4ArrowAnimation.transformation.A[0][i], U, 7);
        pov.writer << "   #end" << endl;
      }

        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 24*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 27*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.ultra_wide_camera_Update(0.35*PI, 0.0625*PI, 250);
        pov.writer << "   #end" << endl;

      str = "   #if ((";
      strAux0 = to_string(0);
      strAux1 = "*0.000512821) + 24*0.025641026 < clock & clock <= (";
      strAux2 = to_string(50);
      strAux3 = "*0.000512821) + 24*0.025641026)";
  
      str += strAux0;
      str += strAux1;
      str += strAux2;
      str += strAux3;
  
      pov.writer << str << endl;
      pov.renderArrow(oneDtwoD4ArrowAnimation.transformation.A[0][49], U, 7);
      pov.writer << "   #end" << endl;

      joker.updateVector3D(-1.5, 2.0, 3.0);

      oneDtwoD6Head.initVectorND(3, -1.5, 2.0, 2.1);
      oneDtwoD6Tail.initVectorND(3, -1.5, 2.0, 2.0);
      oneDtwoD6Arrow.aristaSet(oneDtwoD6Head, oneDtwoD6Tail, 0.3);
      oneDtwoD6ArrowAnimation.initTransform(oneDtwoD6Arrow, joker, 50, 0.18);

      joker.updateVector3D(-1.5, 2.0, 3.0);
      joker0.updateVector3D(-1.5, 2.0, 2.0);
      oneDtwoD4Arrow.aristaSetUdate(joker0, center, 0.3);
      oneDtwoD4ArrowAnimation.updateTransform(oneDtwoD4Arrow, joker, 0.18);

      //draw green vector
      printf("-->Time 25\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 24*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 24*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD6ArrowAnimation.transformation.A[0][i], U, 8);
        pov.writer << "   #end" << endl;
      }

      str = "   #if ((";
      strAux0 = to_string(0);
      strAux1 = "*0.000512821) + 25*0.025641026 < clock & clock <= (";
      strAux2 = to_string(50);
      strAux3 = "*0.000512821) + 29*0.025641026)";
  
      str += strAux0;
      str += strAux1;
      str += strAux2;
      str += strAux3;
  
      pov.writer << str << endl;
      pov.renderArrow(oneDtwoD6ArrowAnimation.transformation.A[0][49], U, 8);
      pov.writer << "   #end" << endl;

      //draw red Vector
      printf("-->Time 26\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 25*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 25*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD4ArrowAnimation.transformation.A[0][i], U, 7);
        pov.writer << "   #end" << endl;
      }

      str = "   #if ((";
      strAux0 = to_string(0);
      strAux1 = "*0.000512821) + 26*0.025641026 < clock & clock <= (";
      strAux2 = to_string(50);
      strAux3 = "*0.000512821) + 26*0.025641026)";
  
      str += strAux0;
      str += strAux1;
      str += strAux2;
      str += strAux3;
  
      pov.writer << str << endl;
      pov.renderArrow(oneDtwoD4ArrowAnimation.transformation.A[0][49], U, 7);
      pov.writer << "   #end" << endl;

      joker.updateVector3D(-1.5, 3.4, 3.0);

      oneDtwoD7Head.initVectorND(3,-1.5, 2.1, 3.0);
      oneDtwoD7Tail.initVectorND(3,-1.5, 2.0, 3.0);
      oneDtwoD7Arrow.aristaSet(oneDtwoD7Head, oneDtwoD7Tail, 0.3);
      oneDtwoD7ArrowAnimation.initTransform(oneDtwoD7Arrow, joker, 50, 0.18);

      joker.updateVector3D(-1.5, 3.4, 3.0);
      joker0.updateVector3D(-1.5, 2.0, 3.0);
      oneDtwoD4Arrow.aristaSetUdate(joker0, center, 0.3);
      oneDtwoD4ArrowAnimation.updateTransform(oneDtwoD4Arrow, joker, 0.18);

      //draw orange vector
      printf("-->Time 27\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 26*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 26*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD7ArrowAnimation.transformation.A[0][i], U, 14);
        pov.writer << "   #end" << endl;
      }

      str = "   #if ((";
      strAux0 = to_string(0);
      strAux1 = "*0.000512821) + 27*0.025641026 < clock & clock <= (";
      strAux2 = to_string(50);
      strAux3 = "*0.000512821) + 29*0.025641026)";
  
      str += strAux0;
      str += strAux1;
      str += strAux2;
      str += strAux3;
  
      pov.writer << str << endl;
      pov.renderArrow(oneDtwoD7ArrowAnimation.transformation.A[0][49], U, 14);
      pov.writer << "   #end" << endl;

      //draw red Vector
      printf("-->Time 28\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 27*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 27*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD4ArrowAnimation.transformation.A[0][i], U, 7);
        pov.writer << "   #end" << endl;
      }

        str = "   #if ((";
        strAux0 = to_string(0);
        strAux1 = "*0.000512821) + 28*0.025641026 < clock & clock <= (";
        strAux2 = to_string(50);
        strAux3 = "*0.000512821) + 29*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD4ArrowAnimation.transformation.A[0][49], U, 7);
        pov.writer << "   #end" << endl;

    //move camera
      printf("-->Time 29\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 28*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 28*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.ultra_wide_camera_Update(0.35*PI, 0.0625*PI + (0.043196899 * (double)i), 250);
        pov.writer << "   #end" << endl;
      }

      printf("-->Time 30\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 29*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 29*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.ultra_wide_camera_Update(0.35*PI, 0.75*PI - (0.043196899 * (double)i), 250);
        pov.writer << "   #end" << endl;
      }

      str = "   #if ((";
      strAux0 = to_string(0);
      strAux1 = "*0.000512821) + 30*0.025641026 < clock & clock <= (";
      strAux2 = to_string(50);
      strAux3 = "*0.000512821) + 36*0.025641026)";
  
      str += strAux0;
      str += strAux1;
      str += strAux2;
      str += strAux3;
  
      pov.writer << str << endl;
      pov.ultra_wide_camera_Update(0.35*PI, 0.0625*PI, 250);
      pov.writer << "   #end" << endl;

      joker.updateVector3D(-1.5, 3.4, 3.0);
      joker0.updateVector3D(0.0, 0.01, 0.01);
      oneDtwoD4Arrow.aristaSetUdate(joker0, center, 0.3);
      oneDtwoD4ArrowAnimation.updateTransform(oneDtwoD4Arrow, joker, 0.18);

      printf("-->Time 31\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 30*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 30*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD4ArrowAnimation.transformation.A[0][49-i], U, 7);
        pov.renderArrow(oneDtwoD7ArrowAnimation.transformation.A[0][49-i], U, 14);
        pov.renderArrow(oneDtwoD6ArrowAnimation.transformation.A[0][49-i], U, 8);
        pov.renderArrow(oneDtwoD5ArrowAnimation.transformation.A[0][49-i], U, 9);
        pov.renderArrow(oneDtwoD2ArrowAnimation.transformation.A[0][49-i], U, 8);
        pov.renderArrow(oneDtwoD3ArrowAnimation.transformation.A[0][49-i], U, 14);
        pov.writer << "   #end" << endl;
      }



      //FINAL BLUE VECTOR

      joker.updateVector3D(-1.5, 0.0, 0.0);

      oneDtwoD8Head.initVectorND(3, 2.0, 0.0, 0.0);
      oneDtwoD8Tail.initVectorND(3, 0.0, 0.0, 0.0);
      oneDtwoD8Arrow.aristaSet(oneDtwoD8Head, oneDtwoD8Tail, 0.3);
      oneDtwoD8ArrowAnimation.initTransform(oneDtwoD8Arrow, joker, 50, 0.18);

      printf("-->Time 32\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 31*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 31*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD8ArrowAnimation.transformation.A[0][i], U, 9);
        pov.writer << "   #end" << endl;
      }

      str = "   #if ((";
      strAux0 = to_string(0);
      strAux1 = "*0.000512821) + 32*0.025641026 < clock & clock <= (";
      strAux2 = to_string(50);
      strAux3 = "*0.000512821) + 38*0.025641026)";
  
      str += strAux0;
      str += strAux1;
      str += strAux2;
      str += strAux3;
  
      pov.writer << str << endl;
      pov.renderArrow(oneDtwoD8ArrowAnimation.transformation.A[0][49], U, 9);
      pov.writer << "   #end" << endl;

      //FINAL GREEM VECTOR

      joker.updateVector3D(-1.5, 0.0, 3.0);

      oneDtwoD9Head.initVectorND(3,-1.5, 0.0, 0.01);
      oneDtwoD9Tail.initVectorND(3,-1.5, 0.0, 0.0);
      oneDtwoD9Arrow.aristaSet(oneDtwoD9Head, oneDtwoD9Tail, 0.3);
      oneDtwoD9ArrowAnimation.initTransform(oneDtwoD9Arrow, joker, 50, 0.18);

      printf("-->Time 33\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 32*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 32*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD9ArrowAnimation.transformation.A[0][i], U, 8);
        pov.writer << "   #end" << endl;
      }

      str = "   #if ((";
      strAux0 = to_string(0);
      strAux1 = "*0.000512821) + 33*0.025641026 < clock & clock <= (";
      strAux2 = to_string(50);
      strAux3 = "*0.000512821) + 38*0.025641026)";
  
      str += strAux0;
      str += strAux1;
      str += strAux2;
      str += strAux3;
  
      pov.writer << str << endl;
      pov.renderArrow(oneDtwoD9ArrowAnimation.transformation.A[0][49], U, 8);
      pov.writer << "   #end" << endl;


      //FINAL ORANGE VECTOR

      joker.updateVector3D(-1.5, 3.4, 3.0);

      oneDtwoD10Head.initVectorND(3,-1.5, 0.01, 3.0);
      oneDtwoD10Tail.initVectorND(3,-1.5, 0.0, 3.0);
      oneDtwoD10Arrow.aristaSet(oneDtwoD10Head, oneDtwoD10Tail, 0.3);
      oneDtwoD10ArrowAnimation.initTransform(oneDtwoD10Arrow, joker, 50, 0.18);

      printf("-->Time 34\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 33*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 33*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD10ArrowAnimation.transformation.A[0][i], U, 14);
        pov.writer << "   #end" << endl;
      }

      str = "   #if ((";
      strAux0 = to_string(0);
      strAux1 = "*0.000512821) + 34*0.025641026 < clock & clock <= (";
      strAux2 = to_string(50);
      strAux3 = "*0.000512821) + 38*0.025641026)";
  
      str += strAux0;
      str += strAux1;
      str += strAux2;
      str += strAux3;
  
      pov.writer << str << endl;
      pov.renderArrow(oneDtwoD10ArrowAnimation.transformation.A[0][49], U, 14);
      pov.writer << "   #end" << endl;

      joker.updateVector3D(-1.5, 0.0, 0.0);
      joker0.updateVector3D(-0.1, 0.0, 0.0);
      oneDtwoD4Arrow.aristaSetUdate(joker0, center, 0.3);
      oneDtwoD4ArrowAnimation.updateTransform(oneDtwoD4Arrow, joker, 0.18);


      printf("-->Time 35\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 34*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 34*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD4ArrowAnimation.transformation.A[0][i], U, 7);
        pov.writer << "   #end" << endl;
      }

      joker.updateVector3D(-1.5, 0.0, 3.0);
      joker0.updateVector3D(-1.5, 0.0, 0.0);
      oneDtwoD4Arrow.aristaSetUdate(joker0, center, 0.3);
      oneDtwoD4ArrowAnimation.updateTransform(oneDtwoD4Arrow, joker, 0.18);


      printf("-->Time 36\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 35*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 35*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD4ArrowAnimation.transformation.A[0][i], U, 7);
        pov.writer << "   #end" << endl;
      }

      joker.updateVector3D(-1.5, 3.4, 3.0);
      joker0.updateVector3D(-1.5, 0.0, 3.0);
      oneDtwoD4Arrow.aristaSetUdate(joker0, center, 0.3);
      oneDtwoD4ArrowAnimation.updateTransform(oneDtwoD4Arrow, joker, 0.18);


      printf("-->Time 37\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 36*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 36*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.renderArrow(oneDtwoD4ArrowAnimation.transformation.A[0][i], U, 7);
        pov.writer << "   #end" << endl;
      }

      str = "   #if ((";
      strAux0 = to_string(0);
      strAux1 = "*0.000512821) + 37*0.025641026 < clock & clock <= (";
      strAux2 = to_string(50);
      strAux3 = "*0.000512821) + 38*0.025641026)";
  
      str += strAux0;
      str += strAux1;
      str += strAux2;
      str += strAux3;
  
      pov.writer << str << endl;
      pov.renderArrow(oneDtwoD4ArrowAnimation.transformation.A[0][49], U, 7);
      pov.writer << "   #end" << endl;

      printf("-->Time 38\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 37*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 37*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.ultra_wide_camera_Update(0.35*PI - (0.006283185*(double)i), 0.0625*PI + (0.043196899 * (double)i), 250 + (double)i);
        pov.writer << "   #end" << endl;
      }

      printf("-->Time 39\n");
      for (int i = 0; i < 50; i++) {
        str = "   #if ((";
        strAux0 = to_string(i);
        strAux1 = "*0.000512821) + 38*0.025641026 < clock & clock <= (";
        strAux2 = to_string(i+1);
        strAux3 = "*0.000512821) + 38*0.025641026)";
  
        str += strAux0;
        str += strAux1;
        str += strAux2;
        str += strAux3;
  
        pov.writer << str << endl;
        pov.ultra_wide_camera_Update(0.25*PI + (0.006283185*(double)i), 0.75*PI - (0.043196899 * (double)i), 300);
        pov.writer << "   #end" << endl;
      }

    pov.closePOVRayWriter();
  	cout << "\n\n\n";
}