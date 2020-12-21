
///////////////////////////////////////////////////////////////////////
//
// 02_Transform.cpp
//
///////////////////////////////////////////////////////////////////////

using namespace std;

#include "stdlib.h"
#include "time.h"
#include "vgl.h"
#include "LoadShaders.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#define FPS 30
#define X_AXIS glm::vec3(1,0,0)
#define Y_AXIS glm::vec3(0,1,0)
#define Z_AXIS glm::vec3(0,0,1)

GLuint vao, points_vbo, colours_vbo, modelID;

GLfloat points[] = {
	-0.9f,  0.9f,  0.0f,
	0.9f,  0.9f,  0.0f,
	0.9f, -0.9f,  0.0f,
	-0.9f, -0.9f,  0.0f
};

GLfloat colours[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f
};

float scale = 1.0f, inc = -0.05f, angle = 0.0f;

void timer(int);

void init(void)
{
	//Specifying the name of vertex and fragment shaders.
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "transform.vert" },
		{ GL_FRAGMENT_SHADER, "square.frag" },
		{ GL_NONE, NULL }
	};

	//Loading and compiling shaders
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);	//My Pipeline is set up

	modelID = glGetUniformLocation(program, "model");
	
	vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	
		points_vbo = 0;
		glGenBuffers(1, &points_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), points, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		colours_vbo = 0;
		glGenBuffers(1, &colours_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, colours_vbo);
		glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(GLfloat), colours, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);
		//glBindBuffer(GL_ARRAY_BUFFER, 0); // Can optionally unbind the buffer to avoid modification.

	//glBindVertexArray(0); // Can optionally unbind the vertex array to avoid modification.
	 
	timer(0); 
}

//---------------------------------------------------------------------
//
// transformModel
//
void transformObject(float scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 translation) {
	glm::mat4 Model;
	Model = glm::mat4(1.0f);
	Model = glm::translate(Model, translation);
	Model = glm::rotate(Model, glm::radians(rotationAngle), rotationAxis);
	Model = glm::scale(Model, glm::vec3(scale));
	glUniformMatrix4fv(modelID, 1, GL_FALSE, &Model[0][0]);
}

//---------------------------------------------------------------------
//
// display
//
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBindVertexArray(vao);
	
	transformObject(scale, Z_AXIS, angle, glm::vec3(0.0f, 0.0f, 0.0f));

	//if ((scale += inc) <= 0.05f) inc = 0.05f;
	//else if (scale >= 1.0f) inc = -0.05f;
	
	//Ordering the GPU to start the pipeline
	glDrawArrays(GL_QUADS, 0, 4);

	//glBindVertexArray(0); // Can optionally unbind the vertex array to avoid modification.

	glFlush(); // Instead of double buffering.
}

//void idle()
//{
//	glutPostRedisplay(); // Tells glut to redisplay the current window.
//}

void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(1000/FPS, timer, 0); // 60 FPS or 16.67ms.
}

//---------------------------------------------------------------------
//
// main
//

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowSize(512, 512);
	glutCreateWindow("Hello World");

	glewInit();	//Initializes the glew and prepares the drawing pipeline.

	init();

	glutDisplayFunc(display);

	//glutIdleFunc(idle); // We cannot use this to set the framerate, but we can set a callback to run when the window receives no events.

	glutMainLoop();

	return 0;
}
