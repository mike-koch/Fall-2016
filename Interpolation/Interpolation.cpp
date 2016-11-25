#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string>
#include <iostream>
#include <cstdlib>
#include "LoadShaders.h"
#include "vmath.h"
#include "vgl.h"
#include <map>

using namespace std;

#define BUFFER_OFFSET(x)  ((const void*) (x))

GLuint programID;
/*
* Arrays to store the indices/names of the Vertex Array Objects and
* Buffers.  Rather than using the books enum approach I've just
* gone out and made a bunch of them and will use them as needed.
*
* Not the best choice I'm sure.
*/

GLuint vertexBuffers[10], arrayBuffers[10], elementBuffers[10];
/*
* Global variables
*   The location for the transformation and the current rotation
*   angle are set up as globals since multiple methods need to
*   access them.
*/
float rotationAngle;
int nbrTriangles;
GLint light0OnLocation, light1OnLocation, light2OnLocation;
bool light0On = true;
bool light1On = true;
bool light2On = true; // The vertex shader initializes all of these to true initially

map<string, GLuint> locationMap;

// Prototypes
GLuint buildProgram(string vertexShaderName, string fragmentShaderName);
int glutStartUp(int & argCount, char *argValues[], 
	            string windowTitle="", int width = 500, int height = 500);
float *readOBJFile(string filename, int &nbrTriangles, float * &normalArray);
void setAttributes(float lineWidth = 1.0, GLenum face = GL_FRONT_AND_BACK, 
	               GLenum fill = GL_FILL);
void buildObjects();
void getLocations();
void init(string vertexShader, string fragmentShader);

/*
 * Routine to encapsulate some of the startup routines for GLUT.  It returns the window ID of the
 * single window that is created.
 */
int glutStartUp(int & argCount, char *argValues[], string title, int width, int height) {
	int windowID;
	GLenum glewErrCode;

	glutInit(&argCount, argValues);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	windowID = glutCreateWindow(title.c_str());

	glutInitContextVersion(3, 1);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glewErrCode = glewInit();
	if (glewErrCode != GLEW_OK) {
		cerr << "Glew init failed " << glewErrCode << endl;
		exit(EXIT_FAILURE);
	}
	return windowID;
}


/*
 * Use the author's routines to build the program and return the program ID.  
 */
GLuint buildProgram(string vertexShaderName, string fragmentShaderName) {

	/*
	*  Use the Books code to load in the shaders.
	*/
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, vertexShaderName.c_str() },
		{ GL_FRAGMENT_SHADER, fragmentShaderName.c_str() },
		{ GL_NONE, NULL }
	};
	GLuint program = LoadShaders(shaders);
	if (program == 0) {
		cerr << "GLSL Program didn't load.  Error \n" << endl
			<< "Vertex Shader = " << vertexShaderName << endl
			<< "Fragment Shader = " << fragmentShaderName << endl;
	}
	glUseProgram(program);
	return program;
}

/*
 * Set up the clear color, lineWidth, and the fill type for the display.
 */
void setAttributes(float lineWidth,GLenum face, GLenum fill ) {
	/*
	* I'm using wide lines so that they are easier to see on the screen.
	* In addition, this version fills in the polygons rather than leaving it
	* as lines.
	*/
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glLineWidth(lineWidth);
	glPolygonMode(face, fill);
	glPolygonMode(GL_FRONT, GL_FILL);

}

/*
 * read and/or build the objects to be displayed.  Also sets up attributes that are 
 * vertex related.
 */

void buildObjects() {
	float *fileTriangles;
	float *normalArray;
	/*
	* Read in the OBJ file with the normal data.  The function returns a pointer to the
	* file triangle data, and modifies nbrTriangles, and normalArray to have appropriate
	* values.
	*/
	fileTriangles = readOBJFile("marvinDos2ndTry.obj", nbrTriangles, normalArray);
	/*
	* Create a vertex array for the buffers, generate an array buffer to copy the
	* vertex data and the normal data into.
	*/
	glGenVertexArrays(1, vertexBuffers);
	glBindVertexArray(vertexBuffers[0]);
	glGenBuffers(1, arrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER,
		nbrTriangles * 3 * 4 * sizeof(float) + nbrTriangles * 3 * 3 * sizeof(float),
		NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, nbrTriangles * 3 * 4 * sizeof(float), fileTriangles);
	glBufferSubData(GL_ARRAY_BUFFER, 
		nbrTriangles * 3 * 4 * sizeof(float),
		nbrTriangles * 3 * 3 * sizeof(float), normalArray);

	/*
	* Set up variables into the shader programs (Note:  We need the
	* shaders loaded and built into a program before we do this)
	*/
	GLuint vPosition = glGetAttribLocation(programID, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vNormal = glGetAttribLocation(programID, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(nbrTriangles * 3 * 4 * sizeof(float)));
}

/*
 * This fills in the locations of most of the uniform variables for the program.
 * there are better ways of handling this but this is good in going directly from
 * what we had. 
 *
 * Revised to get the locations and names of the uniforms from OpenGL.  These
 * are then stored in a map so that we can look up a uniform by name when we 
 * need to use it.  The map is still global but it is a little neater than the 
 * version that used all the locations.  The locations are still there right now 
 * in case that is more useful for you.
 *
 */

void getLocations() {
	/*
	 * Find out how many uniforms there are and go out there and get them from the 
	 * shader program.  The locations for each uniform are stored in a global -- locationMap --
	 * for later retrieval.
	 */
	GLint numberBlocks;
	char uniformName[1024];
	int nameLength;
	GLint size;
	GLenum type;
	glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &numberBlocks);
	for (int blockIndex = 0; blockIndex < numberBlocks; blockIndex++) {
		glGetActiveUniform(programID, blockIndex, 1024, &nameLength, &size, &type, uniformName);
		locationMap[string(uniformName)] = blockIndex;
	}
}

void init( string vertexShader, string fragmentShader) {
	GLuint progID = buildProgram(vertexShader, fragmentShader);

	setAttributes( );

	programID = buildProgram(vertexShader, fragmentShader);

	buildObjects();

	getLocations();

}

/*
* Timer routine -- when called it increments the angle by 1 degree,
* tells Glut to redraw the screen, and sets a timer for 1/30 of a
* second later.
*/
float bezierPercentage = 0.0f;
void timer(int value) {
	bezierPercentage += (float) 1 / 30;
	if (bezierPercentage > 1) {
		bezierPercentage = 0.0f;
	}
	rotationAngle += 1.0f;
	if (rotationAngle >= 360.0) {
		rotationAngle = 0.0f;
	}
	glutPostRedisplay();
	glutTimerFunc(1000 / 30, timer, 1);
}

struct BezierPoint {
	float x;
	float y;
	float z;
};

const float P0[] = {  0.0f, 0.0f,  0.5f };
const float P1[] = { -1.5f, 0.0f,  0.0f };
const float P2[] = {  1.5f, 0.0f, -0.5f };
const float P3[] = {  0.0f, 0.0f,  0.5f };
void calculate_bezier_point(float percentage, BezierPoint* point) {
	/* Formula for a cubic bezier curve:
		B(t) = [(1 - t)^3 * P0] + [3(1-t)^2 * t * P1] + [3 * (1-t) * t^2 * P2] + [t^3 * P3], where 0 <= t <= 1
	*/

	// Handle the first term
	float coefficient = (1 - percentage) * (1 - percentage) * (1 - percentage);
	float calculatedP0x = coefficient * P0[0];
	float calculatedP0y = coefficient * P0[1];
	float calculatedP0z = coefficient * P0[2];

	// Handle the second term
	coefficient = 3 * ((1 - percentage) * (1 - percentage)) * percentage;
	float calculatedP1x = coefficient * P1[0];
	float calculatedP1y = coefficient * P1[1];
	float calculatedP1z = coefficient * P1[2];

	// Handle the third term
	coefficient = 3 * (1 - percentage) * (percentage * percentage);
	float calculatedP2x = coefficient * P2[0];
	float calculatedP2y = coefficient * P2[1];
	float calculatedP2z = coefficient * P2[2];

	// Handle the fourth term
	coefficient = percentage * percentage * percentage;
	float calculatedP3x = coefficient * P3[0];
	float calculatedP3y = coefficient * P3[1];
	float calculatedP3z = coefficient * P3[2];

	// Add each x, y, and z term to get B(t)
	float resultX = calculatedP0x + calculatedP1x + calculatedP2x + calculatedP3x;
	float resultY = calculatedP0y + calculatedP1y + calculatedP2y + calculatedP3y;
	float resultZ = calculatedP0z + calculatedP1z + calculatedP2z + calculatedP3z;

	(*point).x = resultX;
	(*point).y = resultY;
	(*point).z = resultZ;
}

/*
 * The display routine is basically unchanged at this point.
 */
void display() {
		GLfloat eyePosition[] = { 0.0f, 0.0f, 10.0f };
		GLfloat normalTransformation[3][3];
		vmath::mat4 normalTrans;

		vmath::perspective(60.0f, 1.0f, 0.01f, 100.0f); 

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		vmath::mat4 currentMatrix = vmath::scale(0.08f) *
			vmath::rotate(rotationAngle, 0.0f, 1.0f, 0.0f);
		currentMatrix = vmath::scale(0.4f);

		BezierPoint point;

		calculate_bezier_point(bezierPercentage, &point);

		//-- Uncomment to check the calculated position
		/*cout << point.x << endl;
		cout << point.y << endl;
		cout << point.z << endl;
		cout << "=======\n";*/

		vmath::mat4 translation(vmath::vec4(1.0f, 0.0f, 0.0f, point.y), // Y Position
			vmath::vec4(0.0f, 1.0f, 0.0f, point.z), // Z Position
			vmath::vec4(0.0f, 0.0f, 1.0f, point.x), // X Position
			vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		currentMatrix = translation * vmath::scale(0.3f) * vmath::rotate(rotationAngle, 0.0f, 1.0f, 0.0f);
		normalTrans = vmath::scale(0.2f) * vmath::rotate(rotationAngle, 0.0f, 1.0f, 0.0f);
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				normalTransformation[i][j] = normalTrans[i][j];
			}
		}
		glUniformMatrix4fv(locationMap["modelingTransform"], 1, GL_TRUE,
			               currentMatrix);
		glUniformMatrix3fv(locationMap["normalTransform"], 1, GL_TRUE,
			(const GLfloat *)normalTransformation);
		glUniform1i(locationMap["materialID"], 0);
		glBindVertexArray(vertexBuffers[0]);
		glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
		glDrawArrays(GL_TRIANGLES, 0, nbrTriangles * 3);

		glFlush();
}

/*
 * Main program with calls for many of the helper routines.
 */

void keypress(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
	case 'Q': 
		exit(0);
		break;
	case '0':
		light0On = !light0On;
		glUniform1i(locationMap["light0On"], light0On);
		glutPostRedisplay();
		break;
	case '1':
		light1On = !light1On;
		glUniform1i(locationMap["light1On"], light1On);
		glutPostRedisplay();
		break;
	case '2':
		light2On = !light2On;
		glUniform1i(locationMap["light2On"], light2On);
		glutPostRedisplay();
		break;
	}
}
int main(int argCount, char *argValues[]) {

	glutStartUp(argCount, argValues, "Interpolation");
	init("proj3.vert", "proj3.frag");
	glutDisplayFunc(display);
	glutTimerFunc(1000 / 30, timer, 1);
	glutKeyboardFunc(keypress);
	glutMainLoop();
}