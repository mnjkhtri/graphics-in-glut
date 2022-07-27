#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include "includes/scanalgorithms.hpp"
#include "includes/twoDtransformations.hpp"
#include "includes/threeDtransformations.hpp"
#include "includes/coordinates.hpp"
//#include "includes/camera.hpp"
#include <iostream>

//camera settings 

//Camera camera ;

void render()
{
   glClear(GL_COLOR_BUFFER_BIT);
   
   tCoord reference(10,50,-10);
   tCoord Nvector(0,0,1);
   tCoord Vvector(0,1,0);
   tMatrix ourViewMatrix;
   viewMatrix(&ourViewMatrix, &reference, &Nvector, &Vvector);
 //  tCoord direction = camera.Position + camera.Front ;
  // viewMatrix(&ourViewMatrix, &camera.Position,&direction, &camera.WorldUp );
  // ourViewMatrix.show();
   //Coordinates of a cube (will act as a buffer)
   const int COUNT = 36;
   tCoord coordinates1[] = 
   {
	   tCoord(0,0,0), tCoord(0,100,0), tCoord(100,100,0),
	   tCoord(0,0,0), tCoord(100,100,0), tCoord(100,0,0),

	   tCoord(100,0,0), tCoord(100,100,0), tCoord(100,100,100),
	   tCoord(100,0,0), tCoord(100,100,100), tCoord(100,0,100),

	   tCoord(100,0,100), tCoord(100,100,100), tCoord(0,100,100),
	   tCoord(100,0,100), tCoord(0,100,100), tCoord(0,0,100),

	   tCoord(0,0,100), tCoord(0,100,100), tCoord(0,100,0),
	   tCoord(0,0,100), tCoord(0,100,0), tCoord(0,0,0),

	   tCoord(0,100,0), tCoord(0,100,100), tCoord(100,100,100),
	   tCoord(0,100,0), tCoord(100,100,100), tCoord(100,100,0),

	   tCoord(100,0,100), tCoord(0,0,100), tCoord(0,0,0),
	   tCoord(100,0,100), tCoord(0,0,0), tCoord(100,0,0)
         };

   DoviewMatrix(&ourViewMatrix, coordinates1, COUNT);
//   DocabinetMatrix(45, coordinates1, COUNT);

 // zbuffer=Dozbuffer( coordinates1, COUNT,reference);
   tCoord vanishpoint(150,300,-150);
   DoperspectiveMatrix(&vanishpoint, coordinates1, COUNT);

	std::vector<bool> zbuffer;
  	zbuffer=Dozbuffer( coordinates1, COUNT,reference);

	Plotvertices(coordinates1,zbuffer, COUNT);

   tCoord coordinates2[] = 
   {
       tCoord(0,0,0), tCoord(0,100,0), tCoord(100,100,0),
	   tCoord(0,0,0), tCoord(100,100,0), tCoord(100,0,0),

	   tCoord(100,0,0), tCoord(100,100,0), tCoord(100,100,100),
	   tCoord(100,0,0), tCoord(100,100,100), tCoord(100,0,100),

	   tCoord(100,0,100), tCoord(100,100,100), tCoord(0,100,100),
	   tCoord(100,0,100), tCoord(0,100,100), tCoord(0,0,100),

	   tCoord(0,0,100), tCoord(0,100,100), tCoord(0,100,0),
	   tCoord(0,0,100), tCoord(0,100,0), tCoord(0,0,0),

	   tCoord(0,100,0), tCoord(0,100,100), tCoord(100,100,100),
	   tCoord(0,100,0), tCoord(100,100,100), tCoord(100,100,0),

	   tCoord(100,0,100), tCoord(0,0,100), tCoord(0,0,0),
	   tCoord(100,0,100), tCoord(0,0,0), tCoord(100,0,0)
  };
   DoTranslateMatrix(0,100,0, coordinates2, COUNT);

   DoviewMatrix(&ourViewMatrix, coordinates2, COUNT);
   //DocabinetMatrix(45, coordinates1, COUNT);
   DoperspectiveMatrix(&vanishpoint, coordinates2, COUNT);
   //Plotvertices(coordinates2, COUNT);

   tCoord coordinates3[] = 
   {
       tCoord(0,0,0), tCoord(0,100,0), tCoord(100,100,0),
	   tCoord(0,0,0), tCoord(100,100,0), tCoord(100,0,0),

	   tCoord(100,0,0), tCoord(100,100,0), tCoord(100,100,100),
	   tCoord(100,0,0), tCoord(100,100,100), tCoord(100,0,100),

	   tCoord(100,0,100), tCoord(100,100,100), tCoord(0,100,100),
	   tCoord(100,0,100), tCoord(0,100,100), tCoord(0,0,100),

	   tCoord(0,0,100), tCoord(0,100,100), tCoord(0,100,0),
	   tCoord(0,0,100), tCoord(0,100,0), tCoord(0,0,0),

	   tCoord(0,100,0), tCoord(0,100,100), tCoord(100,100,100),
	   tCoord(0,100,0), tCoord(100,100,100), tCoord(100,100,0),

	   tCoord(100,0,100), tCoord(0,0,100), tCoord(0,0,0),
	   tCoord(100,0,100), tCoord(0,0,0), tCoord(100,0,0)
 };
   DoTranslateMatrix(0,200,0, coordinates3, COUNT);

   DoviewMatrix(&ourViewMatrix, coordinates3, COUNT);
   //DocabinetMatrix(45, coordinates1, COUNT);
   DoperspectiveMatrix(&vanishpoint, coordinates3, COUNT);
   //Plotvertices(coordinates3, COUNT);
}

void Init()
{
   glClearColor(0.0,0.0,0.0,0.0);
   glColor3f(1.0,1.0,1.0);
   gluOrtho2D(0,1000,0,1000);
}
/*void handleKeyboardEvents(unsigned char key, int x, int y)
{
  if(key == 'w' || 'W')
  {
	  camera.ProcessKeyboard(FORWARD);
  }
  if(key == 'a' || 'A')
  {
	  camera.ProcessKeyboard(LEFT);
   }
  if(key == 's' || 'S')
	  camera.ProcessKeyboard(BACKWARD);
  if (key == 'd' || 'D' )
	  camera.ProcessKeyboard(RIGHT);
}*/
int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
   glutInitWindowPosition(0, 0);
   glutInitWindowSize(1000, 1000);
   glutCreateWindow("GLUT");
   Init();
  // glutKeyboardFunc(handleKeyboardEvents);
   glutDisplayFunc(render);
   glFlush();  

   glutMainLoop();
}
