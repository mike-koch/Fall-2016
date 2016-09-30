/*
 Mike Koch
 EECS 4530
 Project 2 - Crowd Scene
 */

#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "vgl.h"
#include "vmath.h"
#include "LoadShaders.h"
#include "OBJReader.h"

// Some global variables, taken from IcosahedronExample
#define BUFFER_OFFSET(x)  ((const void*) (x))
GLuint vertexBuffers[10], arrayBuffers[10], elementBuffers[10];

GLint transformLocation, colorLocation,
lightPositionLocation, ambientLightColorLocation,
diffuseLightColorLocation, specularLightColorLocation,
specularPowerLocation, eyePositionLocation, normalTransformLocation, materialAmbientLocation, materialDiffuseLocation, materialEmissiveLocation, materialSpecularLocation, materialShininessLocation;
float rotationAngle;
int nbrTriangles;

const unsigned int NUMBER_OF_FRAMES_TO_PEAK = 45;
bool rotationIsClockwise = true;
unsigned int numberOfFrames = 0;

// This is purely a magic number: the max number of rows before the cows start turning around
const unsigned int TOTAL_NUMBER_OF_ROWS_OF_COWS = 8;

// Choosing a row value beyond the max row number to prevent accidentally moving a row on start
int currentRowBeingMoved = TOTAL_NUMBER_OF_ROWS_OF_COWS;
int previousRow = TOTAL_NUMBER_OF_ROWS_OF_COWS;

void handleKeypress(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		rotationAngle -= 1.0f;
		break;
	case GLUT_KEY_RIGHT:
		rotationAngle += 1.0f;
		break;
	default:
		break;
	}
}

void timer(int value) {
	// Add to the # of frames. If at NUMBER_OF_FRAMES_TO_PEAK, start moving the original row of cows down, and start raising the next row
	if (++numberOfFrames == NUMBER_OF_FRAMES_TO_PEAK) {
		numberOfFrames = 0;
		previousRow = currentRowBeingMoved;
		currentRowBeingMoved = currentRowBeingMoved - 1 == -1 
			? 7 
			: currentRowBeingMoved - 1;
		cout << "Row " << currentRowBeingMoved << " of cows is moving " << endl;
	}

	// Keyboard check. If the user is holding an arrow key, rotate negative for left / positive for right. Need to use SpecialFunc instead of KeyboardFunc since I'm looking for arrow keys
	glutSpecialFunc(handleKeypress);

	glutPostRedisplay();
	glutTimerFunc(1000 / 60, timer, 1);
}

// The main initialization logic. Most of the boilerplate code is similar to the sample provided.  However things change quite a bit once the cows are being rendered.
void init() {
	float *fileTriangles;
	float *normalArray;
	/*
	* Read in the OBJ file with the normal data.  The function returns a pointer to the
	* file triangle data, and modifies nbrTriangles, and normalArray to have appropriate
	* values.
	*/
	fileTriangles = readOBJFile("triangulatedCowDos.obj", nbrTriangles, normalArray);
	glLineWidth(4.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glGenVertexArrays(1, vertexBuffers);
	glBindVertexArray(vertexBuffers[0]);
	glGenBuffers(1, arrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
	glBufferData(GL_ARRAY_BUFFER,
		nbrTriangles * 3 * 4 * sizeof(float) + nbrTriangles * 3 * 3 * sizeof(float),
		NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, nbrTriangles * 3 * 4 * sizeof(float), fileTriangles);
	glBufferSubData(GL_ARRAY_BUFFER, nbrTriangles * 3 * 4 * sizeof(float),
		nbrTriangles * 3 * 3 * sizeof(float), normalArray);

	// Using the book's code to handle shaders
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "pass.vert" },
		{ GL_FRAGMENT_SHADER, "pass.frag" },
		{ GL_NONE, NULL }
	};
	GLuint program = LoadShaders(shaders);
	glUseProgram(program);


	GLuint vPosition = glGetAttribLocation(program, "vPosition");
	glEnableVertexAttribArray(vPosition);
	glVertexAttribPointer(vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

	GLuint vNormal = glGetAttribLocation(program, "vNormal");
	glEnableVertexAttribArray(vNormal);
	glVertexAttribPointer(vNormal, 3, GL_FLOAT, GL_FALSE, 0,
		BUFFER_OFFSET(nbrTriangles * 3 * 4 * sizeof(float)));


	transformLocation = glGetUniformLocation(program, "transform");
	colorLocation = glGetUniformLocation(program, "cowcolor");
	lightPositionLocation = glGetUniformLocation(program, "lightPosition");
	ambientLightColorLocation = glGetUniformLocation(program, "ambientLightColor");
	diffuseLightColorLocation = glGetUniformLocation(program, "diffuseLightColor");
	specularLightColorLocation = glGetUniformLocation(program, "specularLightColor");
	specularPowerLocation = glGetUniformLocation(program, "specularPower");
	eyePositionLocation = glGetUniformLocation(program, "eyeLocation");
	normalTransformLocation = glGetUniformLocation(program, "normalTransform");

	materialAmbientLocation = glGetUniformLocation(program, "material.ambient");
	materialSpecularLocation = glGetUniformLocation(program, "material.specular");
	materialDiffuseLocation = glGetUniformLocation(program, "material.diffuse");
	materialShininessLocation = glGetUniformLocation(program, "material.shininess");
	materialEmissiveLocation = glGetUniformLocation(program, "material.emissive");

	glEnable(GL_DEPTH_TEST);
}

void display() {
	/* MAIN SETUP HERE */
	static GLfloat red[4] = { 1.0f, 0.0f, 0.0f, 1.0f },
		white[4] = { 1.0f, 1.0f, 1.0f, 1.0f },
		green[4] = { 0.0f, 1.0f, 0.0f, 1.0f },
		blue[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

	GLfloat lightPosition[] = { 0.0f, 0.0f, 10.0f };
	GLfloat diffuseLightColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat ambientLightColor[] = { 0.3f, 0.3f, 0.3f };
	GLfloat eyePosition[] = { 0.0f, 0.0f, 10.0f };
	GLfloat specularLightColor[] = { 0.5f, 0.5f, 0.5f };
	GLfloat specularPower[] = { 64.0f };
	GLfloat normalTransformation[3][3];
	vmath::mat4 normalTrans;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	vmath::mat4 currentMatrix = vmath::scale(0.08f) *
		vmath::rotate(rotationAngle, 0.0f, 1.0f, 0.0f);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			normalTransformation[i][j] = currentMatrix[i][j];
		}
	}

	glUniformMatrix3fv(normalTransformLocation, 1, GL_TRUE,
		(const GLfloat *)normalTransformation);
	glUniform3fv(lightPositionLocation, 1, lightPosition);
	glUniform3fv(diffuseLightColorLocation, 1, diffuseLightColor);
	glUniform3fv(ambientLightColorLocation, 1, (const GLfloat *)&ambientLightColor);
	glUniform3fv(eyePositionLocation, 1, eyePosition);
	glUniform3fv(specularLightColorLocation, 1, specularLightColor);
	glUniform1fv(specularPowerLocation, 1, specularPower);
	/* END MAIN SETUP */

	float rowBaseline = -13.0f;
	float rowOffsetZ = 0.0f;
	int row = 0;
	for (int i = 0; i < TOTAL_NUMBER_OF_ROWS_OF_COWS * 8; i++) {
		if (i > 0 && i % 8 == 0) {
			//-- We're going to be moving back and switching to the other offset position.
			rowBaseline = rowBaseline > -14.9f ? -15.0f : -13.0f;
			rowOffsetZ += 3.0f;
			row++;
		}
		GLfloat yPosition = -14.00f + (float)(4 * row);
		GLfloat zPosition = 15.0f - (float)rowOffsetZ;


		// Materials: Pearl
		GLfloat ambient[] = { 0.25f, 0.20725f, 0.20725f };
		GLfloat diffuse[] = { 1.0f, 0.829f, 0.829f };
		GLfloat specular[] = { 0.296648f, 0.296648f, 0.296648f };
		GLfloat shininess = (128.0f*0.088f);

		if (currentRowBeingMoved == row) {
			// Z Position should now be  3.0f * (numberOfFrames/60)
			zPosition = 15.0f - (rowOffsetZ - 3.0f * ((float)numberOfFrames / NUMBER_OF_FRAMES_TO_PEAK));
			ambient[0] = ambient[1] = ambient[2] = 0.25f;
			diffuse[0] = diffuse[1] = diffuse[2] = 0.4f;
			specular[0] = specular[1] = specular[2] = 0.774597f;
			shininess = (128.0f*0.06f);
		}
		else if (previousRow == row) {
			// Move the row back to their original spot by preforming the reverse of the if block above.
			zPosition = 15.0f - (rowOffsetZ - 3.0f * ((float)(NUMBER_OF_FRAMES_TO_PEAK - numberOfFrames) / NUMBER_OF_FRAMES_TO_PEAK));

			ambient[0] = 0.1f;
			ambient[1] = 0.18725f;
			ambient[2] = 0.1745f;
			diffuse[0] = 0.396f;
			diffuse[1] = 0.74151f;
			diffuse[2] = 0.69102f;
			specular[0] = 0.297254f;
			specular[1] = 0.30829f;
			specular[2] = 0.306678f;
			shininess = 128.0f*0.1f;
		}

		GLfloat xPosition = rowBaseline + (float)(4 * (i % 8));

		//-- Actually render the cow
		vmath::mat4 translation(vmath::vec4(1.0f, 0.0f, 0.0f, yPosition), // last value affects the cow's Y position
			vmath::vec4(0.0f, 1.0f, 0.0f, zPosition), // last value affects the cow's Z position
			vmath::vec4(0.0f, 0.0f, 1.0f, xPosition), // last value affects the cow's X position
			vmath::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		currentMatrix = translation * vmath::scale(0.05f) * vmath::rotate(rotationAngle, 0.0f, 1.0f, 0.0f);

		glUniformMatrix4fv(transformLocation, 1, GL_TRUE, currentMatrix);
		glUniform4fv(colorLocation, 1, red);


		glUniform3fv(materialDiffuseLocation, 1, diffuse);
		glUniform3fv(materialAmbientLocation, 1, ambient);
		glUniform3fv(materialSpecularLocation, 1, specular);
		glUniform1fv(materialShininessLocation, 1, &shininess);

		glBindVertexArray(vertexBuffers[0]);
		glBindBuffer(GL_ARRAY_BUFFER, arrayBuffers[0]);
		glDrawArrays(GL_TRIANGLES, 0, nbrTriangles * 3);
	}

	glFlush();
}

/*
* This is the basic main program.  It initializes things and
* sets up the window.
*/
int main(int argCount, char *argValues[]) {
	// Start facing the cows head-on
	rotationAngle = -90.0f;
	glutInit(&argCount, argValues);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Crowd Scene");

	glutInitContextVersion(3, 1);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glewInit();
	init();
	glutDisplayFunc(display);
	glutTimerFunc(1000 / 60, timer, 1);
	glutMainLoop();
	return 0;
}