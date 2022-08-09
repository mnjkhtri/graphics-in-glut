#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include "includes/scanalgorithms.hpp"
#include "includes/threeDtransformations.hpp"
#include "includes/twoDtransformations.hpp"
#include "includes/Angel.hpp"
#include "includes/lighting.hpp"

#define SCREEN_W 2000
#define SCREEN_H 1000

int default_x = 200;
int default_y = 0;
int default_z = -10;
int default_xx = 0;
int default_yy = 0;
int default_zz = 1;

tCoord lightPosition = tCoord(800,500,0);
float angle = 0;
tCoord reference(200,0,-10);
tCoord Nvector(0,0,1);
tCoord Vvector(0,1,0);
tCoord vanishpoint(500,300,-1000);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCREEN_W, SCREEN_H, "Computer Graphics III/I", NULL, NULL);
    if (window == NULL)
    {
        printf("Failed to create a window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD");
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    cube Sun;
    Sun.triangles = 
    {
        {tCoord(10,0,0), tCoord(10,10,0), tCoord(10,10,10), Color(1,1,1)},
		{tCoord(10,0,0), tCoord(10,10,10), tCoord(10,0,10), Color(1,1,1)},

		{tCoord(10,0,10), tCoord(10,10,10), tCoord(0,10,10), Color(1,1,1)},
		{tCoord(10,0,10), tCoord(0,10,10), tCoord(0,0,10), Color(1,1,1)},

		{tCoord(0,0,10), tCoord(0,10,10), tCoord(0,10,0), Color(1,1,1)},
		{tCoord(0,0,10), tCoord(0,10,0), tCoord(0,0,0), Color(1,1,1)},

		{tCoord(0,10,0), tCoord(0,10,10), tCoord(10,10,10), Color(1,1,1)},
		{tCoord(0,10,0), tCoord(10,10,10), tCoord(10,10,0), Color(1,1,1)},

		{tCoord(10,0,10), tCoord(0,0,10), tCoord(0,0,0), Color(1,1,1)},
		{tCoord(10,0,10), tCoord(0,0,0), tCoord(10,0,0), Color(1,1,1)},
    };
    DoTranslateMatrix(lightPosition.x,lightPosition.y,lightPosition.z,Sun);

	cube Block1;
    Block1.triangles= 
    {
		{tCoord(0,0,0), tCoord(0,100,0), tCoord(100,100,0), Color(0.79,0.25,0.32)},
		{tCoord(0,0,0), tCoord(100,100,0), tCoord(100,0,0), Color(0.79,0.25,0.32)},

        //Front face
		{tCoord(100,0,0), tCoord(100,100,0), tCoord(100,100,100), Color(0.75,0.25,0.32)},
		{tCoord(100,0,0), tCoord(100,100,100), tCoord(100,0,100), Color(0.75,0.25,0.32)},

		{tCoord(100,0,100), tCoord(100,100,100), tCoord(0,100,100), Color(0.79,0.25,0.32)},
		{tCoord(100,0,100), tCoord(0,100,100), tCoord(0,0,100), Color(0.79,0.25,0.32)},

		{tCoord(0,0,100), tCoord(0,100,100), tCoord(0,100,0), Color(0.79,0.25,0.32)},
		{tCoord(0,0,100), tCoord(0,100,0), tCoord(0,0,0), Color(0.79,0.25,0.32)},

		{tCoord(0,100,0), tCoord(0,100,100), tCoord(100,100,100), Color(0.79,0.25,0.32)},
		{tCoord(0,100,0), tCoord(100,100,100), tCoord(100,100,0), Color(0.79,0.25,0.32)},

		{tCoord(100,0,100), tCoord(0,0,100), tCoord(0,0,0), Color(0.79,0.25,0.32)},
		{tCoord(100,0,100), tCoord(0,0,0), tCoord(100,0,0), Color(0.79,0.25,0.32)},

        //Second floor
        {tCoord{0+100,115+0,0}, tCoord{10+100,110+0,0}, tCoord{0+100,115+0,100}, Color(0.59,0.25,0.32)},
        {tCoord{10+100,110+0,0}, tCoord{0+100,115+0,100}, tCoord{10+100,110+0,100}, Color(0.59,0.25,0.32)},
        //Actual second floor

		{tCoord(0,100,0), tCoord(0,200,0), tCoord(100,200,0), Color(0.79,0.25,0.32)},
		{tCoord(0,100,0), tCoord(100,200,0), tCoord(100,100,0), Color(0.79,0.25,0.32)},

		{tCoord(100,100,0), tCoord(100,200,0), tCoord(100,200,100), Color(0.75,0.25,0.32)},
		{tCoord(100,100,0), tCoord(100,200,100), tCoord(100,100,100), Color(0.75,0.25,0.32)},

		{tCoord(100,100,100), tCoord(100,200,100), tCoord(0,200,100), Color(0.79,0.25,0.32)},
		{tCoord(100,100,100), tCoord(0,200,100), tCoord(0,100,100), Color(0.79,0.25,0.32)},

		{tCoord(0,100,100), tCoord(0,200,100), tCoord(0,200,0), Color(0.79,0.25,0.32)},
		{tCoord(0,100,100), tCoord(0,200,0), tCoord(0,100,0), Color(0.79,0.25,0.32)},

		{tCoord(0,200,0), tCoord(0,200,100), tCoord(100,200,100), Color(0.79,0.25,0.32)},
	    {tCoord(0,200,0), tCoord(100,200,100), tCoord(100,200,0), Color(0.79,0.25,0.32)},

		{tCoord(100,100,100), tCoord(0,100,100), tCoord(0,100,0), Color(0.79,0.25,0.32)},
		{tCoord(100,100,100), tCoord(0,100,0), tCoord(100,100,0), Color(0.79,0.25,0.32)},

         //top floor
        {tCoord{0,0+200,0}, tCoord{0,0+200,100}, tCoord{0,30+200,100}, Color(0.63,0.32,0.34)},
        {tCoord{0,0+200,0}, tCoord{0,30+200,0}, tCoord{0,30+200,100}, Color(0.63,0.33,0.34)},

        {tCoord{100,0+200,0}, tCoord{100,0+200,100}, tCoord{100,30+200,100}, Color(0.63,0.33,0.34)},
        {tCoord{100,0+200,0}, tCoord{100,30+200,0}, tCoord{100,30+200,100}, Color(0.63,0.33,0.34)},

        {tCoord(0,200+0,0), tCoord(100,200+0,0), tCoord(0,200+30,0), Color(0.63,0.33,0.34)},
        {tCoord(0,200+30,0), tCoord(100,200+30,0), tCoord(100,200+0,0), Color(0.63,0.33,0.34)},

        {tCoord(0,200+0,100), tCoord(100,200+0,100), tCoord(0,200+30,100), Color(0.63,0.33,0.34)},
        {tCoord(0,200+30,100), tCoord(100,200+30,100), tCoord(100,200+0,100), Color(0.63,0.33,0.34)},

        //Windows:
        {tCoord(100,60,10), tCoord(100,90,10), tCoord(100,90,40), Color(0.78,0.72,0.89)},
        {tCoord(100,60,10), tCoord(100,90,40), tCoord(100,60,40), Color(0.78,0.72,0.89)},
        {tCoord(100,60,60), tCoord(100,90,60), tCoord(100,90,90), Color(0.78,0.72,0.89)},
        {tCoord(100,60,60), tCoord(100,90,90), tCoord(100,60,90), Color(0.78,0.72,0.89)},

        //Second floor
        {tCoord(100,60+90,10), tCoord(100,90+90,10), tCoord(100,90+90,40), Color(0.78,0.72,0.89)},
        {tCoord(100,60+90,10), tCoord(100,90+90,40), tCoord(100,60+90,40), Color(0.78,0.72,0.89)},
        {tCoord(100,60+90,60), tCoord(100,90+90,60), tCoord(100,90+90,90), Color(0.78,0.72,0.89)},
        {tCoord(100,60+90,60), tCoord(100,90+90,90), tCoord(100,60+90,90), Color(0.78,0.72,0.89)},


        //Door
        {tCoord(100,0,40), tCoord(100,50,40), tCoord(100,50,60), Color(0.79,0.5,0.34)},
        {tCoord(100,50,60), tCoord(100,0,60), tCoord(100,0,40), Color(0.79,0.5,0.34)},
        {tCoord(100,0,40), tCoord(100,50,40), tCoord(100,50,60), Color(0.79,0.5,0.34)},
        {tCoord(100,50,60), tCoord(100,0,60), tCoord(100,0,40), Color(0.79,0.5,0.34)},
    };

    cube Block2 = Block1;
    DoTranslateMatrix(0,0,1200,Block2);

    cube Block3;
    Block3.triangles= 
    {
		{tCoord(0,0,0), tCoord(0,100,0), tCoord(100,100,0), Color(0.79,0.25,0.32)},
		{tCoord(0,0,0), tCoord(100,100,0), tCoord(100,0,0), Color(0.79,0.25,0.32)},

		{tCoord(100,0,0), tCoord(100,100,0), tCoord(100,100,100), Color(0.79,0.25,0.32)},
		{tCoord(100,0,0), tCoord(100,100,100), tCoord(100,0,100), Color(0.79,0.25,0.32)},

		{tCoord(100,0,100), tCoord(100,100,100), tCoord(0,100,100), Color(0.79,0.25,0.32)},
		{tCoord(100,0,100), tCoord(0,100,100), tCoord(0,0,100), Color(0.79,0.25,0.32)},

		{tCoord(0,0,100), tCoord(0,100,100), tCoord(0,100,0), Color(0.79,0.25,0.32)},
		{tCoord(0,0,100), tCoord(0,100,0), tCoord(0,0,0), Color(0.79,0.25,0.32)},

		{tCoord(0,100,0), tCoord(0,100,100), tCoord(100,100,100), Color(0.79,0.25,0.32)},
		{tCoord(0,100,0), tCoord(100,100,100), tCoord(100,100,0), Color(0.79,0.25,0.32)},

		{tCoord(100,0,100), tCoord(0,0,100), tCoord(0,0,0), Color(0.79,0.25,0.32)},
		{tCoord(100,0,100), tCoord(0,0,0), tCoord(100,0,0), Color(0.79,0.25,0.32)},

        //Windows:
        {tCoord(100,60,10), tCoord(100,90,10), tCoord(100,90,40), Color(0.78,0.72,0.89)},
        {tCoord(100,60,10), tCoord(100,90,40), tCoord(100,60,40), Color(0.78,0.72,0.89)},
        {tCoord(100,60,60), tCoord(100,90,60), tCoord(100,90,90), Color(0.78,0.72,0.89)},
        {tCoord(100,60,60), tCoord(100,90,90), tCoord(100,60,90), Color(0.78,0.72,0.89)},

        //Door
        {tCoord(100,0,40), tCoord(100,50,40), tCoord(100,50,60), Color(0.79,0.5,0.34)},
        {tCoord(100,50,60), tCoord(100,0,60), tCoord(100,0,40), Color(0.79,0.5,0.34)},
        {tCoord(100,0,40), tCoord(100,50,40), tCoord(100,50,60), Color(0.79,0.5,0.34)},
        {tCoord(100,50,60), tCoord(100,0,60), tCoord(100,0,40), Color(0.79,0.5,0.34)},

        //Roof
        {tCoord(0,100,0), tCoord(0,100,100), tCoord(50,50+100,50), Color(0.63,0.32,0.34)},
        {tCoord(0,100,0), tCoord(100,100,0), tCoord(50,50+100,50), Color(0.63,0.32,0.34)},
        {tCoord(100,100,0), tCoord(100,100,100), tCoord(50,50+100,50), Color(0.63,0.32,0.34)},
        {tCoord(0,100,100), tCoord(100,100,100), tCoord(50,50+100,50), Color(0.63,0.32,0.34)},
    };
    DoTranslateMatrix(0,0,1000,Block3);

    cube Block4 = Block3;
    DoTranslateMatrix(0,0,1100,Block4);

    cube Highway;
    Highway.triangles = 
    {
        //SOILS
        {tCoord(0,0,0), tCoord(150,0,0), tCoord(0,0,3500), Color(0.6,0.46,0.325)},
        {tCoord(150,0,0), tCoord(0,0,3500), tCoord(150,0,3500), Color(0.6,0.46,0.325)},

        //SOILS ON RIGHT
        {tCoord(500,0,0), tCoord(650,0,0), tCoord(500,0,3500), Color(0.6,0.46,0.325)},
        {tCoord(650,0,0), tCoord(500,0,3500), tCoord(650,0,3500), Color(0.6,0.46,0.325)},

        //HIGHWAY
        {tCoord(150,0,0), tCoord(500,0,0), tCoord(150,0,3500), Color(0.36,0.32,0.25)},
        {tCoord(500,0,0), tCoord(150,0,3500), tCoord(500,0,3500), Color(0.36,0.32,0.25)},


        {tCoord(300,0,0), tCoord(320,0,0), tCoord(300,0,100), Color(1.0,1.0,1.0)},
        {tCoord(320,0,0), tCoord(300,0,100), tCoord(320,0,100), Color(1.0,1.0,1.0)},

        {tCoord(300,0,150+0), tCoord(320,0,150+0), tCoord(300,0,150+100), Color(1.0,1.0,1.0)},
        {tCoord(320,0,150+0), tCoord(300,0,150+100), tCoord(320,0,150+100), Color(1.0,1.0,1.0)},

        {tCoord(300,0,150+150+0), tCoord(320,0,150+150+0), tCoord(300,0,150+150+100), Color(1.0,1.0,1.0)},
        {tCoord(320,0,150+150+0), tCoord(300,0,150+150+100), tCoord(320,0,150+150+100), Color(1.0,1.0,1.0)},

        {tCoord(300,0,150+150+150+0), tCoord(320,0,150+150+150+0), tCoord(300,0,150+150+150+100), Color(1.0,1.0,1.0)},
        {tCoord(320,0,150+150+150+0), tCoord(300,0,150+150+150+100), tCoord(320,0,150+150+150+100), Color(1.0,1.0,1.0)},

        {tCoord(300,0,150+150+150+150+0), tCoord(320,0,150+150+150+150+0), tCoord(300,0,150+150+150+150+100), Color(1.0,1.0,1.0)},
        {tCoord(320,0,150+150+150+150+0), tCoord(300,0,150+150+150+150+100), tCoord(320,0,150+150+150+150+100), Color(1.0,1.0,1.0)},

        {tCoord(300,0,150+150+150+150+150+0), tCoord(320,0,150+150+150+150+150+0), tCoord(300,0,150+150+150+150+150+100), Color(1.0,1.0,1.0)},
        {tCoord(320,0,150+150+150+150+150+0), tCoord(300,0,150+150+150+150+150+100), tCoord(320,0,150+150+150+150+150+100), Color(1.0,1.0,1.0)},

        {tCoord(300,0,150+150+150+150+150+150+0), tCoord(320,0,150+150+150+150+150+150+0), tCoord(300,0,150+150+150+150+150+150+100), Color(1.0,1.0,1.0)},
        {tCoord(320,0,150+150+150+150+150+150+0), tCoord(300,0,150+150+150+150+150+150+100), tCoord(320,0,150+150+150+150+150+150+100), Color(1.0,1.0,1.0)},

        {tCoord(300,0,150+150+150+150+150+150+150+0), tCoord(320,0,150+150+150+150+150+150+150+0), tCoord(300,0,150+150+150+150+150+150+150+100), Color(1.0,1.0,1.0)},
        {tCoord(320,0,150+150+150+150+150+150+150+0), tCoord(300,0,150+150+150+150+150+150+150+100), tCoord(320,0,150+150+150+150+150+150+150+100), Color(1.0,1.0,1.0)},

        {tCoord(300,0,1200+0), tCoord(320,0,1200+0), tCoord(300,0,1200+100), Color(1.0,1.0,1.0)},
        {tCoord(320,0,1200+0), tCoord(300,0,1200+100), tCoord(320,0,1200+100), Color(1.0,1.0,1.0)},
    };

    cube Rotating_body1;
    Rotating_body1.triangles = 
    {
		{tCoord(0,0,0), tCoord(0,100,0), tCoord(1,100,0),Color(0.0f,0.0f,1.0f)},
		{tCoord(0,0,0), tCoord(1,100,0), tCoord(1,0,0),Color(0.0f,0.0f,1.0f)},

		{tCoord(1,0,0), tCoord(1,100,0), tCoord(1,100,1),Color(0.0f,0.0f,1.0f)},
		{tCoord(1,0,0), tCoord(1,100,1), tCoord(1,0,1),Color(0.0f,0.0f,1.0f)},

		{tCoord(1,0,1), tCoord(1,100,1), tCoord(0,100,1),Color(0.0f,0.0f,1.0f)},
		{tCoord(1,0,1), tCoord(0,100,1), tCoord(0,0,1),Color(0.0f,0.0f,1.0f)},

		{tCoord(0,0,1), tCoord(0,100,1), tCoord(0,100,0),Color(0.0f,0.0f,1.0f)},
		{tCoord(0,0,1), tCoord(0,100,0), tCoord(0,0,0),Color(0.0f,0.0f,1.0f)},

		{tCoord(0,100,0), tCoord(0,100,1), tCoord(1,100,1),Color(0.0f,0.0f,1.0f)},
		{tCoord(0,100,0), tCoord(1,100,1), tCoord(1,100,0),Color(0.0f,0.0f,1.0f)},

		{tCoord(1,0,1), tCoord(0,0,1), tCoord(0,0,0),Color(0.0f,0.0f,1.0f)},
		{tCoord(1,0,1), tCoord(0,0,0), tCoord(1,0,0),Color(0.0f,0.0f,1.0f)},

        //Head:
        {tCoord(5,100,0), tCoord(5,70,0), tCoord(5,70,20), Color(1.0f,0.0f,0.0f)},
        {tCoord(5,70,0), tCoord(5,40,0), tCoord(5,40,20), Color(1.0f,0.0f,0.0f)},
    };
    DoTranslateMatrix(90,200,90,Rotating_body1);

    cube Chair;
    Chair.triangles =
    {
        //First leg:
		{tCoord(0,0,0), tCoord(0,20,0), tCoord(1,20,0), Color(0.62,0.54,0.46)},
		{tCoord(0,0,0), tCoord(1,20,0), tCoord(1,0,0), Color(0.62,0.54,0.46)},

		{tCoord(1,0,0), tCoord(1,20,0), tCoord(1,20,1), Color(0.62,0.54,0.46)},
		{tCoord(1,0,0), tCoord(1,20,1), tCoord(1,0,1), Color(0.62,0.54,0.46)},

		{tCoord(1,0,1), tCoord(1,20,1), tCoord(0,20,1), Color(0.62,0.54,0.46)},
		{tCoord(1,0,1), tCoord(0,20,1), tCoord(0,0,1), Color(0.62,0.54,0.46)},

		{tCoord(0,0,1), tCoord(0,20,1), tCoord(0,20,0), Color(0.62,0.54,0.46)},
		{tCoord(0,0,1), tCoord(0,20,0), tCoord(0,0,0), Color(0.62,0.54,0.46)},

		{tCoord(0,20,0), tCoord(0,20,1), tCoord(1,20,1), Color(0.62,0.54,0.46)},
		{tCoord(0,20,0), tCoord(1,20,1), tCoord(1,20,0), Color(0.62,0.54,0.46)},

		{tCoord(1,0,1), tCoord(0,0,1), tCoord(0,0,0), Color(0.62,0.54,0.46)},
		{tCoord(1,0,1), tCoord(0,0,0), tCoord(1,0,0), Color(0.62,0.54,0.46)},

        //Second
		{tCoord(20,0,0), tCoord(20,20,0), tCoord(21,20,0), Color(0.62,0.54,0.46)},
		{tCoord(20,0,0), tCoord(21,20,0), tCoord(21,0,0), Color(0.62,0.54,0.46)},

		{tCoord(21,0,0), tCoord(21,20,0), tCoord(21,20,1), Color(0.62,0.54,0.46)},
		{tCoord(21,0,0), tCoord(21,20,1), tCoord(21,0,1), Color(0.62,0.54,0.46)},

		{tCoord(21,0,1), tCoord(21,20,1), tCoord(20,20,1), Color(0.62,0.54,0.46)},
		{tCoord(21,0,1), tCoord(20,20,1), tCoord(20,0,1), Color(0.62,0.54,0.46)},

		{tCoord(20,0,1), tCoord(20,20,1), tCoord(20,20,0), Color(0.62,0.54,0.46)},
		{tCoord(20,0,1), tCoord(20,20,0), tCoord(20,0,0), Color(0.62,0.54,0.46)},

		{tCoord(20,20,0), tCoord(20,20,1), tCoord(21,20,1), Color(0.62,0.54,0.46)},
		{tCoord(20,20,0), tCoord(21,20,1), tCoord(21,20,0), Color(0.62,0.54,0.46)},

		{tCoord(21,0,1), tCoord(20,0,1), tCoord(20,0,0), Color(0.62,0.54,0.46)},
		{tCoord(21,0,1), tCoord(20,0,0), tCoord(21,0,0), Color(0.62,0.54,0.46)},

        //First leg:
		{tCoord(0,0,30), tCoord(0,20,30), tCoord(1,20,30), Color(0.62,0.54,0.46)},
		{tCoord(0,0,30), tCoord(1,20,30), tCoord(1,0,30), Color(0.62,0.54,0.46)},

		{tCoord(1,0,30), tCoord(1,20,30), tCoord(1,20,31), Color(0.62,0.54,0.46)},
		{tCoord(1,0,30), tCoord(1,20,31), tCoord(1,0,31), Color(0.62,0.54,0.46)},

		{tCoord(1,0,31), tCoord(1,20,31), tCoord(0,20,31), Color(0.62,0.54,0.46)},
		{tCoord(1,0,31), tCoord(0,20,31), tCoord(0,0,31), Color(0.62,0.54,0.46)},

		{tCoord(0,0,31), tCoord(0,20,31), tCoord(0,20,30), Color(0.62,0.54,0.46)},
		{tCoord(0,0,31), tCoord(0,20,30), tCoord(0,0,30), Color(0.62,0.54,0.46)},

		{tCoord(0,20,30), tCoord(0,20,31), tCoord(1,20,31), Color(0.62,0.54,0.46)},
		{tCoord(0,20,30), tCoord(1,20,31), tCoord(1,20,30), Color(0.62,0.54,0.46)},

		{tCoord(1,0,31), tCoord(0,0,31), tCoord(0,0,30), Color(0.62,0.54,0.46)},
		{tCoord(1,0,31), tCoord(0,0,30), tCoord(1,0,30), Color(0.62,0.54,0.46)},

        //Final
        {tCoord(20,0,30), tCoord(20,20,30), tCoord(21,20,30), Color(0.62,0.54,0.46)},
		{tCoord(20,0,30), tCoord(21,20,30), tCoord(21,0,30), Color(0.62,0.54,0.46)},

		{tCoord(21,0,30), tCoord(21,20,30), tCoord(21,20,31), Color(0.62,0.54,0.46)},
		{tCoord(21,0,30), tCoord(21,20,31), tCoord(21,0,31), Color(0.62,0.54,0.46)},

		{tCoord(21,0,31), tCoord(21,20,31), tCoord(20,20,31), Color(0.62,0.54,0.46)},
		{tCoord(21,0,31), tCoord(20,20,31), tCoord(20,0,31), Color(0.62,0.54,0.46)},

		{tCoord(20,0,31), tCoord(20,20,31), tCoord(20,20,30), Color(0.62,0.54,0.46)},
		{tCoord(20,0,31), tCoord(20,20,30), tCoord(20,0,30), Color(0.62,0.54,0.46)},

		{tCoord(20,20,30), tCoord(20,20,31), tCoord(21,20,31), Color(0.62,0.54,0.46)},
		{tCoord(20,20,30), tCoord(21,20,31), tCoord(21,20,30), Color(0.62,0.54,0.46)},

		{tCoord(21,0,31), tCoord(20,0,31), tCoord(20,0,30), Color(0.62,0.54,0.46)},
		{tCoord(21,0,31), tCoord(20,0,30), tCoord(21,0,30), Color(0.62,0.54,0.46)},


        //Body
        {tCoord(0,20,0), tCoord(20,20,0), tCoord(20,20,30), Color(0.88,0.73,0.36)},
		{tCoord(0,20,0), tCoord(0,20,30), tCoord(20,20,30), Color(0.88,0.73,0.36)},

        {tCoord(20,20,0), tCoord(20,20,30), tCoord(25,40,30), Color(0.62,0.74,0.56)},
		{tCoord(25,40,30), tCoord(25,40,0), tCoord(20,20,0), Color(0.62,0.74,0.56)},
    };
    cube Chair2 = Chair;
    cube Chair3 = Chair;
    DoRotateMatrix(270,tCoord(0,1,0),Chair2);
    DoRotateMatrix(180,tCoord(0,1,0),Chair3);
    DoTranslateMatrix(600,0,100,Chair);
    DoTranslateMatrix(580,0,200,Chair2);
    DoTranslateMatrix(540,0,130,Chair3);

    cube Human;
    Human.triangles =
    {
        //Firt leg
        {tCoord(0,0,0), tCoord(0,10,0), tCoord(1,10,0), Color(0.98,0.85,0.6)},
		{tCoord(0,0,0), tCoord(1,10,0), tCoord(1,0,0), Color(0.98,0.85,0.6)},

		{tCoord(1,0,0), tCoord(1,10,0), tCoord(1,10,1), Color(0.98,0.85,0.6)},
		{tCoord(1,0,0), tCoord(1,10,1), tCoord(1,0,1), Color(0.98,0.85,0.6)},

		{tCoord(1,0,1), tCoord(1,10,1), tCoord(0,10,1), Color(0.98,0.85,0.6)},
		{tCoord(1,0,1), tCoord(0,10,1), tCoord(0,0,1), Color(0.98,0.85,0.6)},

		{tCoord(0,0,1), tCoord(0,10,1), tCoord(0,10,0), Color(0.98,0.85,0.6)},
		{tCoord(0,0,1), tCoord(0,10,0), tCoord(0,0,0), Color(0.98,0.85,0.6)},

		{tCoord(0,10,0), tCoord(0,10,1), tCoord(1,10,1), Color(0.98,0.85,0.6)},
		{tCoord(0,10,0), tCoord(1,10,1), tCoord(1,10,0), Color(0.98,0.85,0.6)},

		{tCoord(1,0,1), tCoord(0,0,1), tCoord(0,0,0), Color(0.98,0.85,0.6)},
		{tCoord(1,0,1), tCoord(0,0,0), tCoord(1,0,0), Color(0.98,0.85,0.6)},

        //Second leg
        {tCoord(5,0,0), tCoord(5,10,0), tCoord(6,10,0), Color(0.98,0.85,0.6)},
		{tCoord(5,0,0), tCoord(6,10,0), tCoord(6,0,0), Color(0.98,0.85,0.6)},

		{tCoord(6,0,0), tCoord(6,10,0), tCoord(6,10,1), Color(0.98,0.85,0.6)},
		{tCoord(6,0,0), tCoord(6,10,1), tCoord(6,0,1), Color(0.98,0.85,0.6)},

		{tCoord(6,0,1), tCoord(6,10,1), tCoord(5,10,1), Color(0.98,0.85,0.6)},
		{tCoord(6,0,1), tCoord(5,10,1), tCoord(5,0,1), Color(0.98,0.85,0.6)},

		{tCoord(5,0,1), tCoord(5,10,1), tCoord(5,10,0), Color(0.98,0.85,0.6)},
		{tCoord(5,0,1), tCoord(5,10,0), tCoord(5,0,0), Color(0.98,0.85,0.6)},

		{tCoord(5,10,0), tCoord(5,10,1), tCoord(6,10,1), Color(0.98,0.85,0.6)},
		{tCoord(5,10,0), tCoord(6,10,1), tCoord(6,10,0), Color(0.98,0.85,0.6)},

		{tCoord(6,0,1), tCoord(5,0,1), tCoord(5,0,0), Color(0.98,0.85,0.6)},
		{tCoord(6,0,1), tCoord(5,0,0), tCoord(6,0,0), Color(0.98,0.85,0.6)},

        //Body:
		{tCoord(-3,10,0), tCoord(8,10,0), tCoord(8,25,0), Color(0.98,0.85,0.6)},
        {tCoord(-3,10,0), tCoord(-3,25,0), tCoord(8,25,0), Color(0.98,0.85,0.6)}, 

        //Neck:
        {tCoord(2,25,0), tCoord(2,28,0), tCoord(3,28,0), Color(0.98,0.85,0.6)},
		{tCoord(2,25,0), tCoord(3,28,0), tCoord(3,25,0), Color(0.98,0.85,0.6)},

		{tCoord(3,25,0), tCoord(3,28,0), tCoord(3,28,1), Color(0.98,0.85,0.6)},
		{tCoord(3,25,0), tCoord(3,28,1), tCoord(3,25,1), Color(0.98,0.85,0.6)},

		{tCoord(3,25,1), tCoord(3,28,1), tCoord(2,28,1), Color(0.98,0.85,0.6)},
		{tCoord(3,25,1), tCoord(2,28,1), tCoord(2,25,1), Color(0.98,0.85,0.6)},

		{tCoord(2,25,1), tCoord(2,28,1), tCoord(2,28,0), Color(0.98,0.85,0.6)},
		{tCoord(2,25,1), tCoord(2,28,0), tCoord(2,25,0), Color(0.98,0.85,0.6)},

		{tCoord(2,28,0), tCoord(2,28,1), tCoord(3,28,1), Color(0.98,0.85,0.6)},
		{tCoord(2,28,0), tCoord(3,28,1), tCoord(3,28,0), Color(0.98,0.85,0.6)},

		{tCoord(3,25,1), tCoord(2,25,1), tCoord(2,25,0), Color(0.98,0.85,0.6)},
		{tCoord(3,25,1), tCoord(2,25,0), tCoord(3,25,0), Color(0.98,0.85,0.6)},

        //GeadL
        {tCoord(-1,28,0), tCoord(6,28,0), tCoord(6,31,0), Color(0.98,0.85,0.6)},
        {tCoord(-1,28,0), tCoord(-1,31,0), tCoord(6,31,0), Color(0.98,0.85,0.6)}, 
    };
    DoTranslateMatrix(410,0,0,Human);

    cube Human2 = Human;
    DoTranslateMatrix(-300,0,1000,Human2);

    cube Tree;
    Tree.triangles = 
    {
        {tCoord(0,0,0), tCoord(0,0,10), tCoord(0,30,0), Color(0.46,0.36,0.28)},
        {tCoord(0,0,10), tCoord(0,30,0), tCoord(0,30,10), Color(0.46,0.36,0.28)},

        {tCoord(0,0+30,-20), tCoord(0,0+30,30), tCoord(0,30+30,5), Color(0.188,0.73,0)},
        {tCoord(0,0+30+10,-20), tCoord(0,0+30+10,30), tCoord(0,30+30+10,5), Color(0.188,0.73,0)},
        {tCoord(0,0+30+20,-20), tCoord(0,0+30+20,30), tCoord(0,30+30+20,5), Color(0.188,0.73,0)},
        {tCoord(0,0+30+30,-20), tCoord(0,0+30+30,30), tCoord(0,30+30+30,5), Color(0.188,0.73,0)},
    };
    DoTranslateMatrix(100,0,250,Tree);

    const int forest_count = 40;
    cube Forest[forest_count];
    for (int i = 0; i < forest_count; ++i)
    {
        if (i < forest_count/2)
        {
            if (i < forest_count/4)
            {
                Forest[i] = Tree;
                DoTranslateMatrix(0,0,(i+1)*60,Forest[i]);
            }
            else
            {
                Forest[i] = Tree;
                DoTranslateMatrix(0,0,(i+1)*60+500,Forest[i]);
            }
        }
        else
        {
            if (i < (forest_count*3)/4)
            {
                Forest[i] = Tree;
                DoTranslateMatrix(-60,0,(i-forest_count/2.0f)*60,Forest[i]);
            }
            else
            {
                Forest[i] = Tree;
                DoTranslateMatrix(-60,0,(i-forest_count/2.0f)*60+500,Forest[i]);
            }
        }
    }

    Angel::init(SCREEN_W, SCREEN_H);
	std::unordered_map<std::string, float> zbuffer;

    int Humanposition = 0;
    int direction = 1;
    while (!glfwWindowShouldClose(window)) 
    {
        processInput(window);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //MAIN BEGINS HERE
        
        //Make temporary copy of the coordinates:
        cube Sun_temp = Sun;
        cube Block1_temp = Block1;
        cube Highway_temp = Highway;
        cube Rotating_body1_temp = Rotating_body1;
        cube Chair_temp = Chair;
        cube Chair2_temp = Chair2;
        cube Chair3_temp = Chair3;
        cube Human_temp = Human;
        cube Human2_temp = Human2;
        cube Tree_temp = Tree;
        cube Block2_temp = Block2;
        cube Block3_temp = Block3;
        cube Block4_temp = Block4;
        cube Forest_temp[forest_count];
        for (int i = 0; i < forest_count; ++i)
        {
            Forest_temp[i] = Forest[i];
        }

        DoTranslateMatrix(0,0,Humanposition, Human_temp);
        DoTranslateMatrix(0,0,Humanposition+100, Human2_temp);
        Humanposition += direction*100;
        if (Humanposition > 2500 || Humanposition < 9)
        {
            direction = (-1)*direction;
        }

		//lighting

		Dolighting(Block1_temp, reference, lightPosition);
		Dolighting(Block2_temp, reference, lightPosition);
	//	Dolighting(Highway_temp, reference, lightPosition);
		Dolighting(Rotating_body1_temp, reference, lightPosition);
		Dolighting(Chair_temp, reference, lightPosition);
		Dolighting(Chair2_temp, reference, lightPosition);
		Dolighting(Chair3_temp, reference, lightPosition);
		Dolighting(Human_temp, reference, lightPosition);
		Dolighting(Human2_temp, reference, lightPosition);
		Dolighting(Tree_temp, reference, lightPosition);
		Dolighting(Block3_temp, reference, lightPosition);
		Dolighting(Block4_temp, reference, lightPosition);
		for (int i = 0; i < forest_count; ++i)
        {
            Dolighting(Forest_temp[i], reference, lightPosition);
        }


	
        //Make a view matrix:
        tMatrix ourViewMatrix;
        viewMatrix(&ourViewMatrix, &reference, &Nvector, &Vvector);
        DoviewMatrix(&ourViewMatrix, Sun_temp);
        DoviewMatrix(&ourViewMatrix, Block1_temp);
        DoviewMatrix(&ourViewMatrix, Block2_temp);
        DoviewMatrix(&ourViewMatrix, Highway_temp);
        DoviewMatrix(&ourViewMatrix, Rotating_body1_temp);
        DoviewMatrix(&ourViewMatrix, Chair_temp);
        DoviewMatrix(&ourViewMatrix, Chair2_temp);
        DoviewMatrix(&ourViewMatrix, Chair3_temp);
        DoviewMatrix(&ourViewMatrix, Human_temp);
        DoviewMatrix(&ourViewMatrix, Human2_temp);
        DoviewMatrix(&ourViewMatrix, Tree_temp);
        DoviewMatrix(&ourViewMatrix, Block3_temp);
        DoviewMatrix(&ourViewMatrix, Block4_temp);
        for (int i = 0; i < forest_count; ++i)
        {
            DoviewMatrix(&ourViewMatrix, Forest_temp[i]);
        }
        DoperspectiveMatrix(&vanishpoint, Sun_temp);
        DoperspectiveMatrix(&vanishpoint, Block1_temp);
        DoperspectiveMatrix(&vanishpoint, Block2_temp);
        DoperspectiveMatrix(&vanishpoint, Highway_temp);
        DoperspectiveMatrix(&vanishpoint, Rotating_body1_temp);
        DoperspectiveMatrix(&vanishpoint, Chair_temp);
        DoperspectiveMatrix(&vanishpoint, Chair2_temp);
        DoperspectiveMatrix(&vanishpoint, Chair3_temp);
        DoperspectiveMatrix(&vanishpoint, Human_temp);
        DoperspectiveMatrix(&vanishpoint, Human2_temp);
        DoperspectiveMatrix(&vanishpoint, Tree_temp);
        DoperspectiveMatrix(&vanishpoint, Block3_temp);
        DoperspectiveMatrix(&vanishpoint, Block4_temp);
        for (int i = 0; i < forest_count; ++i)
        {
            DoperspectiveMatrix(&vanishpoint, Forest_temp[i]);
        }
		//int n = 0;
	    for(auto& tr:Sun_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, tr.color);
		}		
	    for(auto& tr:Block1_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, tr.color);
		}		
	    for(auto& tr:Block2_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, tr.color);
		}		
		for(auto& tr:Highway_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, tr.color);
		}
		for(auto& tr:Rotating_body1_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, tr.color);
		}
		for(auto& tr:Chair_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, tr.color);
		}
		for(auto& tr:Chair2_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, tr.color);
		}
		for(auto& tr:Chair3_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, tr.color);
		}
		for(auto& tr:Human_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, tr.color);
		}
		for(auto& tr:Human2_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, tr.color);
		}
		for(auto& tr:Tree_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, tr.color);
		}
		for(auto& tr:Block3_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, tr.color);
		}
		for(auto& tr:Block4_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, tr.color);
		}
        for (int i = 0; i < forest_count; ++i)
        {
            for(auto& tr:Forest_temp[i].triangles)
            {
                RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, tr.color);
            }
        }

		//clear all the conatiners
        zbuffer.erase(zbuffer.begin(),zbuffer.end());


    //MAIN ENDS HERE
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glfwTerminate();
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    return glViewport(0,0,width,height);
}
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        reference.z += 15;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        reference.z -= 15;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        reference.x += 15;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        reference.x -= 15;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        reference.y += 15;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        reference.y -= 15;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        //This increases the x-component of the vector 
        if (angle < 3.14/2.0)
        {
            angle += 0.05;
        }           
        Nvector.z = cos(angle)*cos(angle);
        Nvector.x = sin(angle)*sin(angle);
    }
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
    {
        //This increases the z-component of the vector
        if (angle > 0)
        {
            angle -= 0.1;

        }
        Nvector.z = cos(angle)*cos(angle);
        Nvector.x = sin(angle)*sin(angle);
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        reference.x = default_x;
        reference.y = default_y;
        reference.z = default_z;

        Nvector.x = default_xx;
        Nvector.y = default_yy;
        Nvector.z = default_zz;
    }

}
