#include <GL/glut.h>
#include <stdio.h>
#include "scanalgorithms.hpp"
#include "twoDtransformations.hpp"
#include "threeDtransformations.hpp"
#include "coordinates.hpp"
#include <iostream>
void render()
{
   glClear(GL_COLOR_BUFFER_BIT);
   
   tCoord reference(0,0,0);
   tCoord Nvector(0,0,1);
   tCoord Vvector(0,1,0);
   tMatrix ourViewMatrix;
   viewMatrix(&ourViewMatrix, &reference, &Nvector, &Vvector);
   ourViewMatrix.show();
   //Coordinates of a cube (will act as a buffer)
   const int COUNT = 16;
   tCoord coordinates1[] = 
   {
      tCoord(0,0,0), tCoord(0,0,100), tCoord(0,100,100), tCoord(0,100,0), tCoord(0,0,0),
      tCoord(100,0,0), tCoord(100,0,100), tCoord(0,0,100), tCoord(100,0,100),
      tCoord(100,100,100), tCoord(100,100,0), tCoord(100,0,0), tCoord(100,100,0),
      tCoord(0,100,0), tCoord(0,100,100), tCoord(100,100,100),
   };
   DoviewMatrix(&ourViewMatrix, coordinates1, COUNT);
   //DocabinetMatrix(45, coordinates1, COUNT);

   tCoord vanishpoint(150,100,-100);
   DoperspectiveMatrix(&vanishpoint, coordinates1, COUNT);
   Plotvertices(coordinates1, COUNT);

   tCoord coordinates2[] = 
   {
      tCoord(0,0,0), tCoord(0,0,100), tCoord(0,100,100), tCoord(0,100,0), tCoord(0,0,0),
      tCoord(100,0,0), tCoord(100,0,100), tCoord(0,0,100), tCoord(100,0,100),
      tCoord(100,100,100), tCoord(100,100,0), tCoord(100,0,0), tCoord(100,100,0),
      tCoord(0,100,0), tCoord(0,100,100), tCoord(100,100,100),
   };
   DoTranslateMatrix(0,100,0, coordinates2, COUNT);

   DoviewMatrix(&ourViewMatrix, coordinates2, COUNT);
   //DocabinetMatrix(45, coordinates1, COUNT);
   DoperspectiveMatrix(&vanishpoint, coordinates2, COUNT);
   Plotvertices(coordinates2, COUNT);

   tCoord coordinates3[] = 
   {
      tCoord(0,0,0), tCoord(0,0,100), tCoord(0,100,100), tCoord(0,100,0), tCoord(0,0,0),
      tCoord(100,0,0), tCoord(100,0,100), tCoord(0,0,100), tCoord(100,0,100),
      tCoord(100,100,100), tCoord(100,100,0), tCoord(100,0,0), tCoord(100,100,0),
      tCoord(0,100,0), tCoord(0,100,100), tCoord(100,100,100),
   };
   DoTranslateMatrix(0,200,0, coordinates3, COUNT);

   DoviewMatrix(&ourViewMatrix, coordinates3, COUNT);
   //DocabinetMatrix(45, coordinates1, COUNT);
   DoperspectiveMatrix(&vanishpoint, coordinates3, COUNT);
   Plotvertices(coordinates3, COUNT);
}

void Init()
{
   glClearColor(1.0,1.0,1.0,0.0);
   glColor3f(0.0,0.0,0.0);
   gluOrtho2D(0,1000,0,1000);
}
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition(0, 0);
   glutInitWindowSize(1000, 1000);
   glutCreateWindow("GLUT");
   Init();
   glutDisplayFunc(render);
   glFlush();  

   glutMainLoop();
}