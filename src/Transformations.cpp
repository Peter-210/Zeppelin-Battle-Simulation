
#include <gl/glut.h>
#include <math.h>
#include "../header/Transformations.h"


const float PI = 3.14159265;

void loadIdentityCustom() {
	float matrix[16] = {1,0,0,0 ,0,1,0,0 ,0,0,1,0 ,0,0,0,1};
	glLoadMatrixf(matrix);
}


void translateCustom(float x, float y, float z) {
	float matrix[16] = {1,0,0,0,  0,1,0,0,  0,0,1,0,  x,y,z,1};
	glMultMatrixf(matrix);
}

void scaleCustom(float x, float y, float z) {
	float matrix[16] = {x,0,0,0,  0,y,0,0,  0,0,z,0,  0,0,0,1};
	glMultMatrixf(matrix);
}

void rotateCustom(float angleDeg, float vX, float vY, float vZ) {
	float angRads = angleDeg * (PI / 180);

	if (vX != 0) {
		rotateX(angRads);
	}

	if (vY != 0) {
		rotateY(angRads);
	}

	if (vZ != 0) {
		rotateZ(angRads);
	}


}

void rotateX(float angRads) {
	float matrix[16] = {1,0,0,0,  0,cos(angRads),sin(angRads),0,  0,-sin(angRads),cos(angRads),0,  0,0,0,1};
	glMultMatrixf(matrix);
}

void rotateY(float angRads) {
	float matrix[16] = {cos(angRads),0,-sin(angRads),0,  0,1,0,0,  sin(angRads),0,cos(angRads),0,  0,0,0,1};
	glMultMatrixf(matrix);
}


void rotateZ(float angRads) {
	float matrix[16] = { cos(angRads), sin(angRads),0,0,  -sin(angRads), cos(angRads), 0,0,  0,0,1,0,  0,0,0,1 };
	glMultMatrixf(matrix);
}

