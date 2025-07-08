#pragma once
#ifndef OBJECT_TEXTURE_HANDLER_H
#define OBJECT_TEXTURE_HANDLER_H

#include <gl/glut.h>
#include <cstdio>


typedef unsigned char byte;
typedef unsigned short word;
typedef unsigned long  dword;
typedef unsigned short ushort;
typedef unsigned long  ulong;

typedef struct RGB
{
	byte r, g, b;
} RGB;


typedef struct RGBpixmap
{
	int nRows, nCols;
	RGB* pixel;
} RGBpixmap;

typedef struct Float3D
{
	GLfloat x, y, z;
} Float3D;


typedef struct Float2D
{
	GLfloat u, v;
} Float2D;


typedef struct ObjData
{
	Float3D* positions;
	Float3D* normals;
	GLuint* indices;

	Float2D* textureCoords;

	unsigned int numVertices;
	unsigned int numIndices;
} ObjData;



void readOBJ(const char* fileName, ObjData* objData);
void fskip(FILE* fp, int num_bytes);
ushort getShort(FILE* fp);
ulong getLong(FILE* fp);
void readBMPFile(RGBpixmap* pm, const char* file);
void setTexture(RGBpixmap* p, GLuint textureID);
void loadTextures();

#endif