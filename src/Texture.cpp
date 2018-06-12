#include "Texture.h"
using namespace std;

Texture::Texture(){
	cout << "constructing texture" << endl;
	cout << "empty" << endl;
	cout << "completed" << endl;
}

Texture::~Texture(){
	cout << "deconstructing texture" << endl;
	cout << "empty" << endl;
	cout << "completed" << endl;
}

tuple < int, int, unsigned char* > loadTextureBMP(string filename){
	unsigned char *res;
	int height, width;
	height = width = 0;

	FILE *f = fopen(filename.c_str(), "rb");
	if(!f){
		cerr << "File not opened" << endl;
		return { height, width, res };
	}
	cout << "start reading file" << endl;

	unsigned char header[54];

	if(fread(header, 1, 54, f) != 54){
		cout << "File is not valid" << endl;
		return { height, width, res };
	}

	cout << "header is ready" << endl;

	int fileSize = 0, imageOffset = 0, imageSize = 0, compressionMethod = 0, numberOfBitPerPixel = 0;

	for(int i = 3;i >= 0;i--)
		fileSize <<= 8, fileSize += header[2 + i];
	for(int i = 3;i >= 0;i--)
		imageOffset <<= 8, imageOffset += header[10 + i];
	for(int i = 3;i >= 0;i--)
		width <<= 8, width += header[18 + i];
	for(int i = 3;i >= 0;i--)
		height <<= 8, height += header[22 + i];
	for(int i = 3;i >= 0;i--)
		imageSize <<= 8, imageSize += header[34 + i];
	for(int i = 3;i >= 0;i--)
		compressionMethod <<= 8, compressionMethod += header[30 + i];
	for(int i = 1;i >= 0;i--)
		numberOfBitPerPixel <<= 8, numberOfBitPerPixel += header[28 + i];

	cout << "fileSize: " << fileSize << " bytes" << endl;
	cout << "Image offset: " << imageOffset << endl;
	cout << "width: " << width << endl;
	cout << "height: " << height << endl;
	cout << "image size: " << imageSize << endl;
	cout << "compression method: " << compressionMethod << endl;
	cout << "number of bit per pixel: " << numberOfBitPerPixel << endl;

	unsigned char *buffer = new unsigned char[imageSize];
	int checkLengthErr = fread(buffer, 1, imageSize, f);
	if(checkLengthErr != imageSize){
		cerr << "Error while reading data" << endl;
		cout << imageSize << ' ' << checkLengthErr << endl;
	}

	fclose(f);
	
	res = new unsigned char[width * height * 3];

	int rowSize = (numberOfBitPerPixel * width + 31) / 32 * 4;
	cout << "row size: " << rowSize << endl;

	for(int i = 0;i < height;i++){
		for(int j = 0;j < width;j++){
			res[(i * width + j) * 3] = buffer[i * rowSize + j * 3];
			res[(i * width + j) * 3 + 1] = buffer[i * rowSize + j * 3 + 1];
			res[(i * width + j) * 3 + 2] = buffer[i * rowSize + j * 3 + 2];
		}
	}
	
	cout << "Ready" << endl;

	return { height, width, res };
}

void Texture::loadFromBMP(string filename){
    auto textureData = loadTextureBMP(filename);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, get < 1 > (textureData), get < 0 > (textureData), 0, GL_RGB, GL_UNSIGNED_BYTE, get < 2 > (textureData));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Texture::activeTexture0(){
    glBindTexture(GL_TEXTURE_2D, id);
    glActiveTexture(GL_TEXTURE0);
}

void Texture::activeTexture1(){
    glBindTexture(GL_TEXTURE_2D, id);
    glActiveTexture(GL_TEXTURE1);
}

void Texture::activeTexture2(){
    glBindTexture(GL_TEXTURE_2D, id);
    glActiveTexture(GL_TEXTURE2);
}

void Texture::activeTexture3(){
    glBindTexture(GL_TEXTURE_2D, id);
    glActiveTexture(GL_TEXTURE3);
}