#include <iostream>
#include <vector>
#include "math.h"

using namespace std;

float* generateCone(float baseRadius, float height, float topRadius, int numberOfSteps) {
    // TODO
    vector<float> verticies;

    // Calculate the circumference of the base radius to find the step delta
    double baseCircumference = 2 * M_PI * baseRadius;
    double topCircumference = 2 * M_PI * topRadius;

    // Divide the circumference by the number of steps so we know how far to go for each step
    double baseDelta = baseCircumference / numberOfSteps;
    double topDelta = topCircumference / numberOfSteps;

    // Take a cross-section of each step. This way we can get the top vertex and lower vertex.
    float currentBaseStep = 0.0f;
    float currentTopStep = 0.0f;

    const float BASE_VERTEX_Z = 0.0f;
    const float TOP_VERTEX_Z = height;
    while (currentBaseStep < baseCircumference) {
        //TODO Calculate!
        float topVertexX = 0.0f;
        float topVertexY = 0.0f;
        float baseVertexX = 0.0f;
        float baseVertexY = 0.0f;

        // The third vertex is the base vertex of the next cross-section
        float nextBaseVertexX = 0.0f;
        float nextBaseVertexY = 0.0f;

        verticies.push_back(topVertexX);
        verticies.push_back(topVertexY);
        verticies.push_back(TOP_VERTEX_Z);
        verticies.push_back(baseVertexX);
        verticies.push_back(baseVertexY);
        verticies.push_back(BASE_VERTEX_Z);
        verticies.push_back(nextBaseVertexX);
        verticies.push_back(nextBaseVertexY);
        verticies.push_back(BASE_VERTEX_Z);

        currentBaseStep += baseDelta;
        currentTopStep += topDelta;
    }


    return &verticies[0];
}

int main() {
    generateCone(1.27f, 1.0f, 1.0f, 4);
    return 0;
}