#ifndef OBJREADER
#define OBJREADER
#include <string>
using namespace std;

float *readOBJFile(string filename, int &nbrTriangles, float * &normalArray);

#endif