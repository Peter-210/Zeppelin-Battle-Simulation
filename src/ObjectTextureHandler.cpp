
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/ObjectTextureHandler.h"

//increase 10 to the # of images you want to load
RGBpixmap textures[10];

void loadTextures() {
	readBMPFile(&textures[0], "../assets/clover01.bmp");
	setTexture(&textures[0], 9999);


	readBMPFile(&textures[1], "../assets/balloon_blue.bmp");
	setTexture(&textures[1], 10000);


	readBMPFile(&textures[2], "../assets/brick.bmp");
	setTexture(&textures[2], 10001);


	readBMPFile(&textures[3], "../assets/balloon_red.bmp");
	setTexture(&textures[3], 10002);


	readBMPFile(&textures[4], "../assets/metal.bmp");
	setTexture(&textures[4], 10003);


	readBMPFile(&textures[5], "../assets/wood.bmp");
	setTexture(&textures[5], 10004);


	readBMPFile(&textures[5], "../assets/fire.bmp");
	setTexture(&textures[5], 10005);


	readBMPFile(&textures[5], "../assets/laser.bmp");
	setTexture(&textures[5], 10006);



}



ushort getShort(FILE* fp) //helper function
{ //BMP format uses little-endian integer types
  // get a 2-byte integer stored in little-endian form
	char ic;
	ushort ip;
	ic = fgetc(fp);
	ip = ic;  //first byte is little one 

	ic = fgetc(fp);
	ip |= ((ushort)ic << 8); // or in high order byte
	//this means ip = ip | (ushort)ic << 8, so OR all of the bytes in there.

	return ip;
}


ulong getLong(FILE* fp) //helper function
{  //BMP format uses little-endian integer types
   // get a 4-byte integer stored in little-endian form


	//since JPG uses Big endian you'd need to reverse the bits which are put here.
	//same with PNG

	ulong ip = 0;
	char ic = 0;
	unsigned char uc = ic;

	//size of unsigned long = 32 bits
	//size of unsigned char = 8 bits

	ic = fgetc(fp);   //reads 1 character from the file. Returns an unsigned char. (or int)
	uc = ic;
	ip = uc;
	//[c][][][]

	ic = fgetc(fp);
	uc = ic;     //the signed value is put onto the unsigned value for bit shifting. (shifting on signed values is bad)
	ip |= ((ulong)uc << 8);  //constructing the long. So we're ORing a given section of bits, and then continuing.
	//[x][c][][]

	ic = fgetc(fp);
	uc = ic;
	ip |= ((ulong)uc << 16);
	//[x][x][c][]

	ic = fgetc(fp);
	uc = ic;
	ip |= ((ulong)uc << 24);
	//[x][x][x][c]

	return ip;
}



void fskip(FILE* fp, int num_bytes)
{
	int i;
	for (i = 0; i < num_bytes; i++)
		fgetc(fp);
}


void readOBJ(const char* fileName, ObjData* objData)
{
	char buf[1024];
	char key[1024];
	int n;
	FILE* fin;

	int fc = 0; // face count
	int vc = 0; // vertex count
	int nc = 0; // normal count

	/* Process each line of the OBJ file, count the number of vertices, indices */
	if ((fin = fopen(fileName, "r")))
	{
		while (fgets(buf, 1024, fin))
			if (sscanf(buf, "%s%n", key, &n) >= 1)
			{
				if (!strcmp(key, "f"))
				{
					fc += 3;
				}
				else if (!strcmp(key, "v"))
				{
					vc++;
				}
				else if (!strcmp(key, "vn"))
				{
					nc++;
				}
			}
		fclose(fin);

		objData->numIndices = fc;
		objData->numVertices = vc;
	}

	/* Allocate appropriate amount of memory */
	objData->positions = (Float3D*)malloc(sizeof(Float3D) * (objData->numVertices));
	objData->normals = (Float3D*)malloc(sizeof(Float3D) * (objData->numVertices));
	objData->indices = (unsigned int*)malloc(sizeof(unsigned int) * (objData->numIndices));
	objData->textureCoords = (Float2D*)malloc(sizeof(Float2D) * (objData->numVertices));

	/* Process each line of the OBJ file again but save data this time */
	fc = 0; // face count
	vc = 0; // vertex count
	nc = 0; // normal count

	float textureX = 0;
	float textureY = 0;

	if ((fin = fopen(fileName, "r")))
	{
		while (fgets(buf, 1024, fin))
			if (sscanf(buf, "%s%n", key, &n) >= 1)
			{

				if (!strcmp(key, "f"))
				{
					sscanf(buf + 1, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &(objData->indices[fc]), &(objData->indices[fc + 1]), &(objData->indices[fc + 2]));
					fc += 3;
				}
				else if (!strcmp(key, "v"))
				{

					sscanf(buf + 1, "%f %f %f", &(objData->positions[vc].x), &(objData->positions[vc].y), &(objData->positions[vc].z));

					objData->textureCoords[vc].u = objData->positions[vc].x / 10;
					objData->textureCoords[vc].v = objData->positions[vc].y / 10;

					vc++;


				}
				else if (!strcmp(key, "vn"))
				{
					sscanf(buf + 2, "%f %f %f", &(objData->normals[nc].x), &(objData->normals[nc].y), &(objData->normals[nc].z));
					nc++;
				}
			}
		fclose(fin);
	}
}




void setTexture(RGBpixmap* p, GLuint textureID)
{
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, p->nCols, p->nRows, 0, GL_RGB,
		GL_UNSIGNED_BYTE, p->pixel);
}



void readBMPFile(RGBpixmap* pm, const char* file)
{
	FILE* fp;
	long index;
	int k, row, col, numPadBytes, nBytesInRow;
	char ch1, ch2;
	ulong fileSize;
	ushort reserved1;    // always 0
	ushort reserved2;     // always 0 
	ulong offBits; // offset to image - unreliable
	ulong headerSize;     // always 40
	ulong numCols; // number of columns in image
	ulong numRows; // number of rows in image
	ushort planes;      // always 1 
	ushort bitsPerPixel;    //8 or 24; allow 24 here
	ulong compression;      // must be 0 for uncompressed 
	ulong imageSize;       // total bytes in image 
	ulong xPels;    // always 0 
	ulong yPels;    // always 0 
	ulong numLUTentries;    // 256 for 8 bit, otherwise 0 
	ulong impColors;       // always 0 
	long count;
	char dum;

	/* open the file */
	if ((fp = fopen(file, "rb")) == NULL)
	{
		printf("Error opening file %s.\n", file);
		exit(1);
	}

	/* check to see if it is a valid bitmap file */
	//first line of BMP file is: BM6      6   (                   a  a      
	if (fgetc(fp) != 'B' || fgetc(fp) != 'M')
	{
		fclose(fp);
		printf("%s is not a bitmap file.\n", file);
		exit(1);
	}

	///so this is the header information for the file
	//we need to read this before we can get to the actual content
	fileSize = getLong(fp);   //the file size is {6  } or something in the BMP file...

	reserved1 = getShort(fp);    // always 0
	reserved2 = getShort(fp);     // always 0 
	offBits = getLong(fp); // offset to image - unreliable
	headerSize = getLong(fp);     // always 40
	numCols = getLong(fp); // number of columns in image
	numRows = getLong(fp); // number of rows in image
	planes = getShort(fp);      // always 1 
	bitsPerPixel = getShort(fp);    //8 or 24; allow 24 here
	compression = getLong(fp);      // must be 0 for uncompressed 
	imageSize = getLong(fp);       // total bytes in image 
	xPels = getLong(fp);    // always 0 
	yPels = getLong(fp);    // always 0 
	numLUTentries = getLong(fp);    // 256 for 8 bit, otherwise 0 
	impColors = getLong(fp);       // always 0 

	//if (bitsPerPixel != 24)
	//{ // error - must be a 24 bit uncompressed image
	//	printf("Error bitsperpixel not 24\n");
	//	exit(1);
	//}

	//add bytes at end of each row so total # is a multiple of 4
	// round up 3*numCols to next mult. of 4

	nBytesInRow = ((3 * numCols + 3) / 4) * 4;
	numPadBytes = nBytesInRow - 3 * numCols; //so we need to add this many padding bytes to turn it to multiple of 4

	pm->nRows = numRows; // set class's data members
	pm->nCols = numCols;
	pm->pixel = (RGB*)malloc(3 * numRows * numCols);//make space for array
	//allocate rows X columns  then X3 cause RGB

	if (!pm->pixel)
		return; // out of memory!


	count = 0;
	dum;
	for (row = 0; row < numRows; row++) // read pixel values
	{
		for (col = 0; col < numCols; col++)
		{
			int r, g, b;
			b = fgetc(fp); g = fgetc(fp); r = fgetc(fp); //read bytes
			pm->pixel[count].r = r; //place them in colors
			pm->pixel[count].g = g;
			pm->pixel[count++].b = b;
		}
		fskip(fp, numPadBytes);
	}
	fclose(fp);
}