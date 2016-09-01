#include <iostream>
#include <vector>
#include "math.h"
#define DEBUG

using namespace std;

const double DEGREES_IN_CIRCLE = 360.0;
const double DEGREES_TO_RADIANS = M_PI/180;

double cosine(double degrees) {
    return cos(degrees * DEGREES_TO_RADIANS);
}

double sine(double degrees) {
    return sin(degrees * DEGREES_TO_RADIANS);
}

float* generateCone(float baseRadius, float height, float topRadius, int numberOfSteps) {
    // TODO
    vector<float> verticies;

    // We'll go around the base of the cone. Take 360 degrees divided by the # of steps to find how many degrees we
    //    should move for each step.
    double degreesPerStep = DEGREES_IN_CIRCLE / (double) numberOfSteps;

    // Take a cross-section of each step. This way we can get the top vertex and lower vertex.
    double currentNumberOfDegreesTraversed = 0.0f;

    const float BASE_VERTEX_Z = 0.0f;
    const float TOP_VERTEX_Z = height;

    while (currentNumberOfDegreesTraversed < DEGREES_IN_CIRCLE) {
        //TODO Calculate!

        // Looking at the cone from the top down, the base is a circle. Using basic trig, we can find the needed points
        float baseVertexX = (float) (baseRadius * cosine(currentNumberOfDegreesTraversed));
        float baseVertexY = (float) (baseRadius * sine(currentNumberOfDegreesTraversed));

        float topVertexX = (float) (topRadius * cosine(currentNumberOfDegreesTraversed));
        float topVertexY = (float) (topRadius * sine(currentNumberOfDegreesTraversed));

        // The third vertex is the base vertex of the next cross-section
        float nextBaseVertexX = (float) (baseRadius * cosine(currentNumberOfDegreesTraversed + degreesPerStep));
        float nextBaseVertexY = (float) (baseRadius * sine(currentNumberOfDegreesTraversed + degreesPerStep));

        verticies.push_back(topVertexX);
        verticies.push_back(topVertexY);
        verticies.push_back(TOP_VERTEX_Z);
        verticies.push_back(baseVertexX);
        verticies.push_back(baseVertexY);
        verticies.push_back(BASE_VERTEX_Z);
        verticies.push_back(nextBaseVertexX);
        verticies.push_back(nextBaseVertexY);
        verticies.push_back(BASE_VERTEX_Z);

#ifdef DEBUG
        cout << "Vertex at " << currentNumberOfDegreesTraversed << " degrees\n";
        cout << "---------------------------------------------\n";
        cout << "Top vertex X: " << topVertexX << endl;
        cout << "Top vertex Y: " << topVertexY << endl;
        cout << "Top vertex Z: " << TOP_VERTEX_Z << endl;
        cout << "Base vertex X: " << baseVertexX << endl;
        cout << "Base vertex Y: " << baseVertexY << endl;
        cout << "Base vertex Z: " << BASE_VERTEX_Z << endl;
        cout << "Next base vertex X: " << nextBaseVertexX << endl;
        cout << "Next base vertex Y: " << nextBaseVertexY << endl;
        cout << "Next base vertex Z: " << BASE_VERTEX_Z << endl;
        cout << endl;

#endif

        currentNumberOfDegreesTraversed += degreesPerStep;
    }



    return &verticies[0];
}


int main2() {
    float baseRadius = 3.0f;
    float height = 1.0f;
    float topRadius = 0.0f;
    float numberOfSteps = 4;
    generateCone(baseRadius, height, topRadius, numberOfSteps);
    return 0;
}