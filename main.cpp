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

float angle = 0;
tCoord reference(200,0,-10);
tCoord Nvector(0,0,1);
tCoord Vvector(0,1,0);
tCoord vanishpoint(500,300,-1000);

/*
1) OpenGL takes in 3D coordinates and transfroms them into 2D pixels through the process of pipelining.
2) The pipelining consists of small parallel programs called shaders:
    a) Vertex Shader: a vertex (attributes) -> a processed vertex
    b) Shape Assembly: 
    c) Geometry Shader:
    d) Rasterization:
    e) Fragement Shader: 
    f) Tests and Blending:
Go to main now:
*/
//GLSL has data types called vec2, vec3 and vec4 which are 2, 3, and 4-component vector equivalent where each component is a GL_FLOAT
//Version 330 corresponds to OpenGL 3.3

//vertexShader will expect vertex attributes as input (in this case position; a vec3) and set up the predefined output variable (a vec4)
//Set the layout of vec3 input variable 'aPos' at location 0
//Set the predefined gl_Position using the input aPos
const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
//vertexShader will expect at the location 0, a vec3 attribute

//fragmentShader will create an output variable (a vec4) and initialize it with a color
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);\n"
    "}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCREEN_W, SCREEN_H, "LearnOpenGL", NULL, NULL);
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

    //Program the required shaders and link them:

    //Create a vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    //Attach the source code to it
    glShaderSource(vertexShader,1,&vertexShaderSource,NULL);
    //Compile it
    glCompileShader(vertexShader);

    //Check for compilation errors:
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n",infoLog);
    }

    //Create a fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    //Attach the source code to it
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    //Compile it
    glCompileShader(fragmentShader);

    //Check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n",infoLog);
    }

    //Combine shaders to link the inputs and outputs of one another
    unsigned int shaderProgram = glCreateProgram();
    //Attach the vertex shader
    glAttachShader(shaderProgram, vertexShader);
    //Attach the fragement shader
    glAttachShader(shaderProgram, fragmentShader);
    //Link them
    glLinkProgram(shaderProgram);
    
    //Check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s\n",infoLog);
    }
    //Now longer need the original shader objects after linking them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //Resulting is the shaderProgram final linked version of multiple shaders combined, later will activate it

    //Send vertices to video memory at once
    // float vertices[] = {
    //     -0.5f, -0.5f, 0.0f,
    //      0.5f, -0.5f, 0.0f,
    //      0.0f,  0.5f, 0.0f 
    // };

    // //OpenGL objects are construct that contains some state, when are bound to the context, they state they contain is mapped into context's state
    // //>Buffer objects store an array of unformatted memory allocated by the OpenGL context; is bound with a target that specifies its use
    //     //>GL_ARRAY_BUFFER target implies that buffer is to be used for vertex attribute data
    // //>Vertex array objects store all of the state needed to supply vertex data; references the VBOs bound together with it
    
    // unsigned int VBO, VAO;
    // //Generate the buffer ID
    // glGenBuffers(1, &VBO);
    // glGenVertexArrays(1, &VAO);
    
    // //Bind the VAO first
    // glBindVertexArray(VAO);
    // //Bind the VBO as GL_ARRAY_BUFFER
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // //Now any calls on GL_ARRAY_BUFFER target will be used to configure VBO

    // //To copy the vertex data into buffer's memory:
    // //First Arg: the type of buffer we want to copy data into
    // //Second Arg: size of the data
    // //Third Arg: actual array of data
    // //Fourth Arg: how graphics card manage the data; 
    //     //GL_STATIC_DRAW: likely not change or very rarely
    //     //GL_DYNAMIC_DRAW: likely to change a lot
    //     //GL_STREAM_DRAW: change every time it is drawn
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // //NOTE: Now that we have our shaders setup and our data into the memory: lets make a path to send that data into the shaders

    // //Give knowledge on how to interpret the data when getting it from the currently bounded VAO:

    // //First Arg: that the data will go to location 0
    // //Second Arg: that the location 0 is to receive 3 values of ...
    // //Third Arg: type GL_FLOAT
    // //Forth Arg: not requring it to normalize
    // //Fifth Arg: such that the next attribute will come after 3*sizeof(float)
    // //Sixth Arg: starting from the offset (void*)0
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    // //Enable the vertex attribute giving the location as its argument
    // glEnableVertexAttribArray(0);

    // //NOTE: The VAO followed by VBO must be bound before we specify the format of the locations

    // //Unbind the VBO for later use
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // //Unbind the VAO for later use
    // glBindVertexArray(0);


	cube Block1, Block1_windows, Block1_door;
    Block1.triangles= 
    {
		{tCoord(0,0,0), tCoord(0,100,0), tCoord(100,100,0)},
		{tCoord(0,0,0), tCoord(100,100,0), tCoord(100,0,0)},

		{tCoord(100,0,0), tCoord(100,100,0), tCoord(100,100,100)},
		{tCoord(100,0,0), tCoord(100,100,100), tCoord(100,0,100)},

		{tCoord(100,0,100), tCoord(100,100,100), tCoord(0,100,100)},
		{tCoord(100,0,100), tCoord(0,100,100), tCoord(0,0,100)},

		{tCoord(0,0,100), tCoord(0,100,100), tCoord(0,100,0)},
		{tCoord(0,0,100), tCoord(0,100,0), tCoord(0,0,0)},

		{tCoord(0,100,0), tCoord(0,100,100), tCoord(100,100,100)},
		{tCoord(0,100,0), tCoord(100,100,100), tCoord(100,100,0)},

		{tCoord(100,0,100), tCoord(0,0,100), tCoord(0,0,0)},
		{tCoord(100,0,100), tCoord(0,0,0), tCoord(100,0,0)},

        //Second floor
		{tCoord(0,100,0), tCoord(0,200,0), tCoord(100,200,0)},
		{tCoord(0,100,0), tCoord(100,200,0), tCoord(100,100,0)},

		{tCoord(100,100,0), tCoord(100,200,0), tCoord(100,200,100)},
		{tCoord(100,100,0), tCoord(100,200,100), tCoord(100,100,100)},

		{tCoord(100,100,100), tCoord(100,200,100), tCoord(0,200,100)},
		{tCoord(100,100,100), tCoord(0,200,100), tCoord(0,100,100)},

		{tCoord(0,100,100), tCoord(0,200,100), tCoord(0,200,0)},
		{tCoord(0,100,100), tCoord(0,200,0), tCoord(0,100,0)},

		{tCoord(0,200,0), tCoord(0,200,100), tCoord(100,200,100)},
		{tCoord(0,200,0), tCoord(100,200,100), tCoord(100,200,0)},

		{tCoord(100,100,100), tCoord(0,100,100), tCoord(0,100,0)},
		{tCoord(100,100,100), tCoord(0,100,0), tCoord(100,100,0)},

        //top floor
        {tCoord{0,0+200,0}, tCoord{0,0+200,100}, tCoord{0,30+200,100}},
        {tCoord{0,0+200,0}, tCoord{0,30+200,0}, tCoord{0,30+200,100}},

        {tCoord{100,0+200,0}, tCoord{100,0+200,100}, tCoord{100,30+200,100}},
        {tCoord{100,0+200,0}, tCoord{100,30+200,0}, tCoord{100,30+200,100}},

    };
    Block1_windows.triangles = 
    {
        {tCoord(100,60,10), tCoord(100,90,10), tCoord(100,90,40)},
        {tCoord(100,60,10), tCoord(100,90,40), tCoord(100,60,40)},
        {tCoord(100,60,60), tCoord(100,90,60), tCoord(100,90,90)},
        {tCoord(100,60,60), tCoord(100,90,90), tCoord(100,60,90)},

        //Second floor
        {tCoord(100,60+100,10), tCoord(100,90+100,10), tCoord(100,90+100,40)},
        {tCoord(100,60+100,10), tCoord(100,90+100,40), tCoord(100,60+100,40)},
        {tCoord(100,60+100,60), tCoord(100,90+100,60), tCoord(100,90+100,90)},
        {tCoord(100,60+100,60), tCoord(100,90+100,90), tCoord(100,60+100,90)}
    };
    Block1_door.triangles = 
    {
        {tCoord(100,0,40), tCoord(100,50,40), tCoord(100,50,60)},
        {tCoord(100,50,60), tCoord(100,0,60), tCoord(100,0,40)},
        {tCoord(100,0,40), tCoord(100,50,40), tCoord(100,50,60)},
        {tCoord(100,50,60), tCoord(100,0,60), tCoord(100,0,40)},
    };

    cube Highway;
    Highway.triangles = 
    {
        {tCoord(150,0,0), tCoord(500,0,0), tCoord(150,0,5000)},
        {tCoord(500,0,0), tCoord(150,0,5000), tCoord(500,0,5000)},
    };
    //LENGTH IS FROM 0 TO 1000, WIDTH FROM 150 to 500

    cube Highwaystrips;
    Highwaystrips.triangles =
    {
        {tCoord(300,0,0), tCoord(320,0,0), tCoord(300,0,100)},
        {tCoord(320,0,0), tCoord(300,0,100), tCoord(320,0,100)},
        {tCoord(300,0,150+0), tCoord(320,0,150+0), tCoord(300,0,150+100)},
        {tCoord(320,0,150+0), tCoord(300,0,150+100), tCoord(320,0,150+100)},
        {tCoord(300,0,150+150+0), tCoord(320,0,150+150+0), tCoord(300,0,150+150+100)},
        {tCoord(320,0,150+150+0), tCoord(300,0,150+150+100), tCoord(320,0,150+150+100)},
        {tCoord(300,0,150+150+150+0), tCoord(320,0,150+150+150+0), tCoord(300,0,150+150+150+100)},
        {tCoord(320,0,150+150+150+0), tCoord(300,0,150+150+150+100), tCoord(320,0,150+150+150+100)},
        {tCoord(300,0,150+150+150+150+0), tCoord(320,0,150+150+150+150+0), tCoord(300,0,150+150+150+150+100)},
        {tCoord(320,0,150+150+150+150+0), tCoord(300,0,150+150+150+150+100), tCoord(320,0,150+150+150+150+100)},
        {tCoord(300,0,150+150+150+150+150+0), tCoord(320,0,150+150+150+150+150+0), tCoord(300,0,150+150+150+150+150+100)},
        {tCoord(320,0,150+150+150+150+150+0), tCoord(300,0,150+150+150+150+150+100), tCoord(320,0,150+150+150+150+150+100)},
    };

    cube Rotating_body1;
    Rotating_body1.triangles = 
    {
		{tCoord(0,0,0), tCoord(0,100,0), tCoord(1,100,0)},
		{tCoord(0,0,0), tCoord(1,100,0), tCoord(1,0,0)},

		{tCoord(1,0,0), tCoord(1,100,0), tCoord(1,100,1)},
		{tCoord(1,0,0), tCoord(1,100,1), tCoord(1,0,1)},

		{tCoord(1,0,1), tCoord(1,100,1), tCoord(0,100,1)},
		{tCoord(1,0,1), tCoord(0,100,1), tCoord(0,0,1)},

		{tCoord(0,0,1), tCoord(0,100,1), tCoord(0,100,0)},
		{tCoord(0,0,1), tCoord(0,100,0), tCoord(0,0,0)},

		{tCoord(0,100,0), tCoord(0,100,1), tCoord(1,100,1)},
		{tCoord(0,100,0), tCoord(1,100,1), tCoord(1,100,0)},

		{tCoord(1,0,1), tCoord(0,0,1), tCoord(0,0,0)},
		{tCoord(1,0,1), tCoord(0,0,0), tCoord(1,0,0)},
    };
    DoTranslateMatrix(100,0,120,Rotating_body1);

    cube Rotating_head1;
    Rotating_head1.triangles = 
    {
        {tCoord(5,100,0), tCoord(5,70,0), tCoord(5,70,20)},
        {tCoord(5,70,0), tCoord(5,40,0), tCoord(5,40,20)},
    };
    DoTranslateMatrix(100,0,120,Rotating_head1);

    cube Chair;
    Chair.triangles =
    {
        //First leg:
		{tCoord(0,0,0), tCoord(0,20,0), tCoord(1,20,0)},
		{tCoord(0,0,0), tCoord(1,20,0), tCoord(1,0,0)},

		{tCoord(1,0,0), tCoord(1,20,0), tCoord(1,20,1)},
		{tCoord(1,0,0), tCoord(1,20,1), tCoord(1,0,1)},

		{tCoord(1,0,1), tCoord(1,20,1), tCoord(0,20,1)},
		{tCoord(1,0,1), tCoord(0,20,1), tCoord(0,0,1)},

		{tCoord(0,0,1), tCoord(0,20,1), tCoord(0,20,0)},
		{tCoord(0,0,1), tCoord(0,20,0), tCoord(0,0,0)},

		{tCoord(0,20,0), tCoord(0,20,1), tCoord(1,20,1)},
		{tCoord(0,20,0), tCoord(1,20,1), tCoord(1,20,0)},

		{tCoord(1,0,1), tCoord(0,0,1), tCoord(0,0,0)},
		{tCoord(1,0,1), tCoord(0,0,0), tCoord(1,0,0)},

        //Second
		{tCoord(20,0,0), tCoord(20,20,0), tCoord(21,20,0)},
		{tCoord(20,0,0), tCoord(21,20,0), tCoord(21,0,0)},

		{tCoord(21,0,0), tCoord(21,20,0), tCoord(21,20,1)},
		{tCoord(21,0,0), tCoord(21,20,1), tCoord(21,0,1)},

		{tCoord(21,0,1), tCoord(21,20,1), tCoord(20,20,1)},
		{tCoord(21,0,1), tCoord(20,20,1), tCoord(20,0,1)},

		{tCoord(20,0,1), tCoord(20,20,1), tCoord(20,20,0)},
		{tCoord(20,0,1), tCoord(20,20,0), tCoord(20,0,0)},

		{tCoord(20,20,0), tCoord(20,20,1), tCoord(21,20,1)},
		{tCoord(20,20,0), tCoord(21,20,1), tCoord(21,20,0)},

		{tCoord(21,0,1), tCoord(20,0,1), tCoord(20,0,0)},
		{tCoord(21,0,1), tCoord(20,0,0), tCoord(21,0,0)},

        //First leg:
		{tCoord(0,0,30), tCoord(0,20,30), tCoord(1,20,30)},
		{tCoord(0,0,30), tCoord(1,20,30), tCoord(1,0,30)},

		{tCoord(1,0,30), tCoord(1,20,30), tCoord(1,20,31)},
		{tCoord(1,0,30), tCoord(1,20,31), tCoord(1,0,31)},

		{tCoord(1,0,31), tCoord(1,20,31), tCoord(0,20,31)},
		{tCoord(1,0,31), tCoord(0,20,31), tCoord(0,0,31)},

		{tCoord(0,0,31), tCoord(0,20,31), tCoord(0,20,30)},
		{tCoord(0,0,31), tCoord(0,20,30), tCoord(0,0,30)},

		{tCoord(0,20,30), tCoord(0,20,31), tCoord(1,20,31)},
		{tCoord(0,20,30), tCoord(1,20,31), tCoord(1,20,30)},

		{tCoord(1,0,31), tCoord(0,0,31), tCoord(0,0,30)},
		{tCoord(1,0,31), tCoord(0,0,30), tCoord(1,0,30)},

        //Final
        {tCoord(20,0,30), tCoord(20,20,30), tCoord(21,20,30)},
		{tCoord(20,0,30), tCoord(21,20,30), tCoord(21,0,30)},

		{tCoord(21,0,30), tCoord(21,20,30), tCoord(21,20,31)},
		{tCoord(21,0,30), tCoord(21,20,31), tCoord(21,0,31)},

		{tCoord(21,0,31), tCoord(21,20,31), tCoord(20,20,31)},
		{tCoord(21,0,31), tCoord(20,20,31), tCoord(20,0,31)},

		{tCoord(20,0,31), tCoord(20,20,31), tCoord(20,20,30)},
		{tCoord(20,0,31), tCoord(20,20,30), tCoord(20,0,30)},

		{tCoord(20,20,30), tCoord(20,20,31), tCoord(21,20,31)},
		{tCoord(20,20,30), tCoord(21,20,31), tCoord(21,20,30)},

		{tCoord(21,0,31), tCoord(20,0,31), tCoord(20,0,30)},
		{tCoord(21,0,31), tCoord(20,0,30), tCoord(21,0,30)},


        //Body
        {tCoord(0,20,0), tCoord(20,20,0), tCoord(20,20,30)},
		{tCoord(0,20,0), tCoord(0,20,30), tCoord(20,20,30)},

        {tCoord(20,20,0), tCoord(20,20,30), tCoord(25,40,30)},
		{tCoord(25,40,30), tCoord(25,40,0), tCoord(20,20,0)},
    };
    DoTranslateMatrix(540,0,0,Chair);

    cube Human;
    Human.triangles =
    {
        //Firt leg
        {tCoord(0,0,0), tCoord(0,10,0), tCoord(1,10,0)},
		{tCoord(0,0,0), tCoord(1,10,0), tCoord(1,0,0)},

		{tCoord(1,0,0), tCoord(1,10,0), tCoord(1,10,1)},
		{tCoord(1,0,0), tCoord(1,10,1), tCoord(1,0,1)},

		{tCoord(1,0,1), tCoord(1,10,1), tCoord(0,10,1)},
		{tCoord(1,0,1), tCoord(0,10,1), tCoord(0,0,1)},

		{tCoord(0,0,1), tCoord(0,10,1), tCoord(0,10,0)},
		{tCoord(0,0,1), tCoord(0,10,0), tCoord(0,0,0)},

		{tCoord(0,10,0), tCoord(0,10,1), tCoord(1,10,1)},
		{tCoord(0,10,0), tCoord(1,10,1), tCoord(1,10,0)},

		{tCoord(1,0,1), tCoord(0,0,1), tCoord(0,0,0)},
		{tCoord(1,0,1), tCoord(0,0,0), tCoord(1,0,0)},

        //Second leg
        {tCoord(5,0,0), tCoord(5,10,0), tCoord(6,10,0)},
		{tCoord(5,0,0), tCoord(6,10,0), tCoord(6,0,0)},

		{tCoord(6,0,0), tCoord(6,10,0), tCoord(6,10,1)},
		{tCoord(6,0,0), tCoord(6,10,1), tCoord(6,0,1)},

		{tCoord(6,0,1), tCoord(6,10,1), tCoord(5,10,1)},
		{tCoord(6,0,1), tCoord(5,10,1), tCoord(5,0,1)},

		{tCoord(5,0,1), tCoord(5,10,1), tCoord(5,10,0)},
		{tCoord(5,0,1), tCoord(5,10,0), tCoord(5,0,0)},

		{tCoord(5,10,0), tCoord(5,10,1), tCoord(6,10,1)},
		{tCoord(5,10,0), tCoord(6,10,1), tCoord(6,10,0)},

		{tCoord(6,0,1), tCoord(5,0,1), tCoord(5,0,0)},
		{tCoord(6,0,1), tCoord(5,0,0), tCoord(6,0,0)},

        //Body:
		{tCoord(-3,10,0), tCoord(8,10,0), tCoord(8,25,0)},
        {tCoord(-3,10,0), tCoord(-3,25,0), tCoord(8,25,0)}, 

        //Neck:
        {tCoord(2,25,0), tCoord(2,28,0), tCoord(3,28,0)},
		{tCoord(2,25,0), tCoord(3,28,0), tCoord(3,25,0)},

		{tCoord(3,25,0), tCoord(3,28,0), tCoord(3,28,1)},
		{tCoord(3,25,0), tCoord(3,28,1), tCoord(3,25,1)},

		{tCoord(3,25,1), tCoord(3,28,1), tCoord(2,28,1)},
		{tCoord(3,25,1), tCoord(2,28,1), tCoord(2,25,1)},

		{tCoord(2,25,1), tCoord(2,28,1), tCoord(2,28,0)},
		{tCoord(2,25,1), tCoord(2,28,0), tCoord(2,25,0)},

		{tCoord(2,28,0), tCoord(2,28,1), tCoord(3,28,1)},
		{tCoord(2,28,0), tCoord(3,28,1), tCoord(3,28,0)},

		{tCoord(3,25,1), tCoord(2,25,1), tCoord(2,25,0)},
		{tCoord(3,25,1), tCoord(2,25,0), tCoord(3,25,0)},

        //GeadL
        {tCoord(-1,28,0), tCoord(6,28,0), tCoord(6,31,0)},
        {tCoord(-1,28,0), tCoord(-1,31,0), tCoord(6,31,0)}, 
    };
    DoTranslateMatrix(410,0,0,Human);
    
    Angel::init(SCREEN_W, SCREEN_H);
	std::unordered_map<std::string, float> zbuffer;

    int Humanposition = 0;
    int direction = 1;

	Material material;
	material.ambient = tCoord(0.65f, 0.00f, 0.0f);
	material.diffuse = tCoord(0.5f, 0.0f, 0.0f);
	material.specular = tCoord(0.7f, 0.04f, 0.04f);
	material.shininess = 0.078125;

	Light light;
	light.position = tCoord(300.0f,150.0f,50.0f);
	light.ambient = tCoord(0.2f, 0.2f, 0.2f);
	light.diffuse = tCoord(1.0f, 1.0f, 1.0f);
	light.specular = tCoord(1.0f, 1.0f, 1.0f);

	std::vector<tCoord> Block_Color;
    while (!glfwWindowShouldClose(window)) 
    {
        processInput(window);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //MAIN BEGINS HERE
        
        //Make temporary copy of the coordinates:

        cube Block1_temp = Block1;
        cube Block1_windows_temp = Block1_windows;
        cube Block1_door_temp = Block1_door;
        cube Highway_temp = Highway;

        cube Rotating_body1_temp = Rotating_body1;
        cube Rotating_head1_temp = Rotating_head1;
        cube Highwaystrips_temp = Highwaystrips;

        cube Chair_temp = Chair;
        cube Human_temp = Human;
        DoTranslateMatrix(0,0,Humanposition, Human_temp);
        Humanposition += direction*100;
        if (Humanposition > 5000 || Humanposition < 9)
        {
            direction = (-1)*direction;
        }

		// //lighting

		// for(auto& tr:Block1.triangles )
		// {
		// 	tCoord c = Dolighting(material, light, tr, reference);
		// 	Block_Color.push_back(c);
		// }



        //Make a view matrix:
        tMatrix ourViewMatrix;
        viewMatrix(&ourViewMatrix, &reference, &Nvector, &Vvector);

        DoviewMatrix(&ourViewMatrix, Block1_temp);
        DoviewMatrix(&ourViewMatrix, Block1_windows_temp);
        DoviewMatrix(&ourViewMatrix, Block1_door_temp);
        DoviewMatrix(&ourViewMatrix, Highway_temp);
        DoviewMatrix(&ourViewMatrix, Rotating_body1_temp);
        DoviewMatrix(&ourViewMatrix, Rotating_head1_temp);
        DoviewMatrix(&ourViewMatrix, Highwaystrips_temp);
        DoviewMatrix(&ourViewMatrix, Chair_temp);
        DoviewMatrix(&ourViewMatrix, Human_temp);

        DoperspectiveMatrix(&vanishpoint, Block1_temp);
        DoperspectiveMatrix(&vanishpoint, Block1_windows_temp);
        DoperspectiveMatrix(&vanishpoint, Block1_door_temp);
        DoperspectiveMatrix(&vanishpoint, Highway_temp);
        DoperspectiveMatrix(&vanishpoint, Rotating_body1_temp);
        DoperspectiveMatrix(&vanishpoint, Rotating_head1_temp);
        DoperspectiveMatrix(&vanishpoint, Highwaystrips_temp);
        DoperspectiveMatrix(&vanishpoint, Chair_temp);
        DoperspectiveMatrix(&vanishpoint, Human_temp);


		//int n = 0;
	    for(auto& tr:Block1_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, Color(1.0f, 0.0f, 0.0f));
		}		
        for(auto& tr:Block1_windows_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, Color(1.0f, 1.0f, 0.0f));
		}	
		for(auto& tr:Block1_door_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, Color(1.0f, 1.0f, 0.0f));
        }
		for(auto& tr:Highway_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, Color(0.36f, 0.32f, 0.25f));
		}
		for(auto& tr:Rotating_body1_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, Color(0.0f, 1.0f, 0.0f));
		}
		for(auto& tr:Rotating_head1_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, Color(1.0f, 0.0f, 0.0f));
		}
		for(auto& tr:Highwaystrips_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, Color(1.0f, 1.0f, 1.0f));
		}
		for(auto& tr:Chair_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, Color(0.88f, 0.71f, 0.50f));
		}
		for(auto& tr:Human_temp.triangles)
		{
			RasterizeTriangle(tr.tri[0], tr.tri[1], tr.tri[2], zbuffer, Color(1.0f, 0.8f, 0.60f));
		}
		//clear all the conatiners
        zbuffer.erase(zbuffer.begin(),zbuffer.end());
		Block_Color.clear();


    //MAIN ENDS HERE
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //Free the allocated resources
    glDeleteProgram(shaderProgram);

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
        reference.z += 5;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        reference.z -= 5;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        reference.x += 5;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        reference.x -= 5;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        reference.y += 5;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        reference.y -= 5;
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        //This increases the x-component of the vector 
        if (angle < 3.14/2.0)
        {
            angle += 0.05;
        }           
        std::cout << angle << std::endl;
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
        std::cout << angle << std::endl;
        Nvector.z = cos(angle)*cos(angle);
        Nvector.x = sin(angle)*sin(angle);
    }
}

/*
What just happened?

>Initialze the GLFW
>Create an window object
>Make it current context
>Initialize GLAD
>Register the traceback functions

>Create the vertex shader expecting position attribute at some location and fragment shaders delivering the output own its own
>Compile them
>Link them into a shader program

>Initialize the vertices
>Create VBO(s) to store the vertices and VAO(s) to supply them
>Bind VAO(s) followed by VBO(s)
>Copy the vertices into VBO(s)
>Tell OpenGL how we to interpret the data on current buffer when it enters the vertex shader
......

>Unbind VBO and VAO (optional)

>Create an rendering loop:
    >Input functionalities
    >Clear screen

    >Activate the shader program
    >Bind the VAO
    >Draw the triangle

    >Swap buffers
    >Communicate with window system (define tracebacks)
*/
