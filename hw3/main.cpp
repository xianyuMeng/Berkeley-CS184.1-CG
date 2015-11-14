#include <iostream>

#include "RayTracer.h"

using namespace std;

int main(int argc, char *argv[]) {
	//cout << "start ray tracing" << endl;
	RayTracer tracer(argv[1]);
	tracer.recursive();
	return 0;
};
