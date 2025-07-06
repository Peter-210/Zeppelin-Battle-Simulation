#include <stdio.h>
#include <math.h>
#include <vector>
#include <gl/glut.h>
#include "../header/Building.h"
#include "../header/Transformations.h"
#include "../header/WindowHandler.h"
#include "../header/BoundingBox.h"
#include "../header/VECTOR3D.h"


const float SCALE = 2;
const int RESOLUTION = 48;
const float PI = 3.14159265;
const int TEXTURE_ID = 10001;



Building::Building(float locX, float locY, float locZ, float sizeXZ, float sizeY) {
	this->locX = locX;
	this->locY = locY;
	this->locZ = locZ;
	this->sizeXZ = sizeXZ;
	this->sizeY = sizeY;
}

BoundingBox Building::getCurrentBoundingBoxState() {
	float minX, maxX, minY, maxY, minZ, maxZ;

	minX = this->locX - this->sizeXZ;
	maxX = this->locX + this->sizeXZ;

	minY = this->locY - this->sizeY;
	maxY = this->locY + this->sizeY;

	minZ = this->locZ- this->sizeXZ;
	maxZ = this->locZ + this->sizeXZ;

	return BoundingBox(minX, maxX, minY, maxY, minZ, maxZ);
}



//============================================================================================================
//Drawing functions below here.


void Building::draw() {
	// Set up texture mapping assuming no lighting/shading 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glPushMatrix();

	glTranslated(this->locX, this->locY + this->sizeY, this->locZ);
	glScaled(this->sizeXZ, this->sizeY, this->sizeXZ);

	glBindTexture(GL_TEXTURE_2D, TEXTURE_ID); // top face of cube
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, TEXTURE_ID); // right face of cube
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, TEXTURE_ID); // left face of cube
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glEnd();

	/*
	glBindTexture(GL_TEXTURE_2D, TEXTURE_ID); // bottom face of cube
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();
	*/

	glBindTexture(GL_TEXTURE_2D, TEXTURE_ID); // back face of cube
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, TEXTURE_ID); // front face of cube
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glEnd();

	glFlush();
	glPopMatrix();
}
