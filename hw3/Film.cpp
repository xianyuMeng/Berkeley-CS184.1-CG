#include "Film.h"

Film::Film(int width, int height) :width(width), height(height){
	colorbuffer = new unsigned char[width * height * 3];
	memset((void *)colorbuffer, 0, width * height * 3);
	//3 channels.
}

Film::~Film(){
	delete colorbuffer;
}

void Film::commit(const vec3 &color, int i, int j){
	int step = j * width * 3 + i * 3;
	auto r = unsigned char(color.x * 255.0f);
	auto g = unsigned char(color.y * 255.0f);
	auto b = unsigned char(color.z * 255.0f);
	colorbuffer[step] = b;
	colorbuffer[step + 1] = g;
	colorbuffer[step + 2] = r;
}

void Film::WriteImage(std::string fname){
	/*Before you use FreeImage, call FreeImage_Initialise(). 
	To record the colors for each pixel, use an array of one byte elements. 
	Then convert this array to a FIBITMAP object as follows, assuming the bytes are in RGB order:*/
	FreeImage_Initialise();
	int pix = width * height;
	BYTE *pixels = new BYTE[3 * pix];
	memcpy((void *)pixels, (void *)colorbuffer, width * height * 3);

	FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);

	std::cout << "Saving screenshot: " << fname << "\n";

	FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
	
	delete pixels;
	FreeImage_DeInitialise();
}