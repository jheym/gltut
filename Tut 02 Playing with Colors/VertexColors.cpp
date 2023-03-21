
#include <string>
#include <vector>
#include <math.h>
#include <stdio.h>
#include <glload/gl_3_3.h>
#include <GL/freeglut.h>
#include "../framework/framework.h"

#define ARRAY_COUNT( array ) (sizeof( array ) / (sizeof( array[0] ) * (sizeof( array ) != sizeof(void*) || sizeof( array[0] ) <= sizeof(void*))))

GLuint theProgram;

void InitializeProgram()
{
	std::vector<GLuint> shaderList;

	shaderList.push_back(Framework::LoadShader(GL_VERTEX_SHADER, "VertexColors.vert"));
	shaderList.push_back(Framework::LoadShader(GL_FRAGMENT_SHADER, "VertexColors.frag"));

	theProgram = Framework::CreateProgram(shaderList);
}

// Two consecutive arrays are being stored here. Vertex offset = [0] and color offset = [12]
// Data is prepared to be used with vec4 types. sizeof(vec4) = 4 * sizeof(float) = 16 bytes
const float vertexData[] = {
	 0.0f,    0.5f, 0.0f, 1.0f,	// top
	 0.5f, -0.366f, 0.0f, 1.0f,	// bottom right
	-0.5f, -0.366f, 0.0f, 1.0f,	// bottom left
	 1.0f,    0.0f, 0.0f, 1.0f, // R
	 0.0f,    1.0f, 0.0f, 1.0f,	// G
	 0.0f,    0.0f, 1.0f, 1.0f,	// B
};

GLuint vertexBufferObject;
GLuint vao;

// This is all the same as it was in Tut1.cpp
void InitializeVertexBuffer()
{
	glGenBuffers(1, &vertexBufferObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//Called after the window and OpenGL are initialized. Called exactly once, before the main loop.
void init()
{
	InitializeProgram();
	InitializeVertexBuffer();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

//Called to update the display.
//You should call glutSwapBuffers after all of your rendering to display what you rendered.
//If you need continuous updates of the screen, call glutPostRedisplay() at the end of the function.
void display()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(theProgram);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glEnableVertexAttribArray(0); // layer 0
	glEnableVertexAttribArray(1); // layer 1
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)48); // The offset of the color data is 12 floats = 48 bytes
	
	// Sends both arrays to the vertex shader
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glUseProgram(0);

	glutSwapBuffers(); // 
	glutPostRedisplay();
}

//Called whenever the window is resized. The new window size is given, in pixels.
//This is an opportunity to call glViewport or glScissor to keep up with the change in size.
void reshape (int w, int h)
{
	glViewport(100, 100, (GLsizei) w, (GLsizei) h);
}

//Called whenever a key on the keyboard was pressed.
//The key is given by the ''key'' parameter, which is in ASCII.
//It's often a good idea to have the escape key (ASCII value 27) call glutLeaveMainLoop() to 
//exit the program.
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		glutLeaveMainLoop();
		return;
	}
}


unsigned int defaults(unsigned int displayMode, int &width, int &height) {return displayMode;}
