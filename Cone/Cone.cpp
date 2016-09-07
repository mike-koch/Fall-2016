/*
*  Name: Mike Koch
*  Project: 1 - Drawing a Cone
*/

#include "vmath.h"
using namespace std;

const double DEGREES_IN_CIRCLE = 360.0;
const double DEGREES_TO_RADIANS = M_PI / 180;

double cosine(double degrees) {
	return cos(degrees * DEGREES_TO_RADIANS);
}

double sine(double degrees) {
	return sin(degrees * DEGREES_TO_RADIANS);
}

float* generateCone(float baseRadius, float height, float topRadius, int numberOfSteps, int& numberOfValues) {
	// There are 3 vertices per triangle and 3 coordinates for each vertex, so multiply the number of steps by 9.
	float* vertices = new float[numberOfSteps * 9];

	// We'll go around the base of the cone. Take 360 degrees divided by the # of steps to find how many degrees we
	//    should move for each step.
	double degreesPerStep = DEGREES_IN_CIRCLE / (double)numberOfSteps;

	// Take a cross-section of each step. This way we can get the top vertex and lower vertex.
	double currentNumberOfDegreesTraversed = 0.0f;

	const float BASE_VERTEX_Y = 0.0f;
	const float TOP_VERTEX_Y = height;

	while (roundf(currentNumberOfDegreesTraversed) < DEGREES_IN_CIRCLE) {
		// Looking at the cone from the top down, the base is a circle. Using basic trig, we can find the needed points
		float baseVertexX = (float)(baseRadius * cosine(currentNumberOfDegreesTraversed));
		float baseVertexZ = (float)(baseRadius * sine(currentNumberOfDegreesTraversed));

		float topVertexX = (float)(topRadius * cosine(currentNumberOfDegreesTraversed));
		float topVertexZ = (float)(topRadius * sine(currentNumberOfDegreesTraversed));

		// The third vertex is the base vertex of the next cross-section
		float nextBaseVertexX = (float)(baseRadius * cosine(currentNumberOfDegreesTraversed + degreesPerStep));
		float nextBaseVertexZ = (float)(baseRadius * sine(currentNumberOfDegreesTraversed + degreesPerStep));

		vertices[numberOfValues++] = topVertexX;
		vertices[numberOfValues++] = TOP_VERTEX_Y;
		vertices[numberOfValues++] = topVertexZ;
		vertices[numberOfValues++] = baseVertexX;
		vertices[numberOfValues++] = BASE_VERTEX_Y;
		vertices[numberOfValues++] = baseVertexZ;
		vertices[numberOfValues++] = nextBaseVertexX;
		vertices[numberOfValues++] = BASE_VERTEX_Y;
		vertices[numberOfValues++] = nextBaseVertexZ;

#ifdef DEBUG
		cout << "Vertex at " << currentNumberOfDegreesTraversed << " degrees\n";
		cout << "---------------------------------------------\n";
		cout << "Top vertex X: " << topVertexX << endl;
		cout << "Top vertex Y: " << TOP_VERTEX_Y << endl;
		cout << "Top vertex Z: " << topVertexZ << endl;
		cout << "Base vertex X: " << baseVertexX << endl;
		cout << "Base vertex Y: " << BASE_VERTEX_Y << endl;
		cout << "Base vertex Z: " << baseVertexZ << endl;
		cout << "Next base vertex X: " << nextBaseVertexX << endl;
		cout << "Next base vertex Y: " << BASE_VERTEX_Y << endl;
		cout << "Next base vertex Z: " << nextBaseVertexZ << endl;
		cout << endl;

#endif

		currentNumberOfDegreesTraversed += degreesPerStep;
	}



	return vertices;
}