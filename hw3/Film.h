#ifndef _INCLUDEFILMHEADER
#define _INCLUDEFILMHEADER
#include "Variable.h"
#include "FreeImage.h"
#include <string>
#include <iostream>
class Film{
public:
	Film(int width, int height);
	~Film();
	//write color on the image
	void commit(const vec3 &color, int i, int j);
	//output image to a file
	void WriteImage(std::string fname);

private:
	int width, height;
	unsigned char *colorbuffer;
};

#endif