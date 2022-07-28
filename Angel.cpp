#include "Angel.hpp"
#include <glad/glad.h>
#include <iostream>

int Angel::m_width = 1280;
int Angel::m_height = 720;

unsigned int Angel::m_ID = 0;
unsigned int Angel::m_shader_ID = 0;

const char *vShaderSource = R"glsl(
#version 330 core
layout (location = 0) in vec3 aPos;
void main(){
gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
}
)glsl";

const char *fShaderSource = R"glsl(
#version 330 core
out vec4 FragColor;
uniform vec4 color;
void main(){
FragColor = vec4(color);
}
)glsl";

void Angel::init(unsigned int width = Angel::m_width,
                 unsigned int height = Angel::m_height) {

	const float vertices[] = {
	    -1.0f, -1.0f, 0.0f, // bottom left
	    1.0f,  -1.0f, 0.0f, // bottom right
	    1.0f,  1.0f,  0.0f, // top right
	    1.0f,  1.0f,  0.0f, // top right
	    -1.0f, 1.0f,  0.0f, // top left
	    -1.0f, -1.0f, 0.0f, // bottom left
	};

	unsigned int VAO;
	unsigned int VBO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
	                      (void *)0);
	m_ID = VAO;
	m_width = width;
	m_height = height;
	glBindVertexArray(0);
	// setup vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderSource, nullptr);
	glCompileShader(vertexShader);

	// check compilation status of vertex shader
	int success;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		throw "Failed to compile Verted Shader";
	}

	// setup fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderSource, nullptr);
	glCompileShader(fragmentShader);

	// check compilation status of the fragment shader
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		throw "Failed to compile fragment shader!";
	}

	m_shader_ID = glCreateProgram();
	glAttachShader(m_shader_ID, vertexShader);
	glAttachShader(m_shader_ID, fragmentShader);
	glLinkProgram(m_shader_ID);

	glGetProgramiv(m_shader_ID, GL_LINK_STATUS, &success);
	if (!success) {
		throw "Unable to link shader program!";
	}
}

void Angel::enable() {
	glBindVertexArray(m_ID);
	glUseProgram(m_shader_ID);
}

void Angel::disable() {
	glUseProgram(0);
	glBindVertexArray(0);
}

unsigned int Angel::getWidth() { return m_width; }
void Angel::setWidth(unsigned int width) { m_width = width; }

unsigned int Angel::getHeight() { return m_height; }
void Angel::setHeight(unsigned int height) { m_height = height; }

void Angel::putPixel(float x, float y, int thickness, Color c) {
	enable();

	int vertexColorLocation = glGetUniformLocation(m_shader_ID, "color");
	glUniform4f(vertexColorLocation, c.r, c.g, c.b, c.a);

	glEnable(GL_SCISSOR_TEST);
	glScissor(x, y, thickness, thickness);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisable(GL_SCISSOR_TEST);
	disable();
}

void Angel::drawAxes(Color c) {
	for (float i = -1.0f; i <= 1.0f; i += 0.001f) {
		putPixel(0, i, 1, c);
		putPixel(i, 0, 1, c);
	}
}
