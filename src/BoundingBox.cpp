
#include <stdio.h>;
#include "../header/BoundingBox.h"
#include "../header/VECTOR3D.h"

BoundingBox::BoundingBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) {
	this->x1 = xMin;
	this->x2 = xMax;
	
	this->y1 = yMin;
	this->y2 = yMax;

	this->z1 = zMin;
	this->z2 = zMax;
}


bool BoundingBox::contains(VECTOR3D* vec) {
	bool containsX = (this->x1 <= vec->GetX()) && (vec->GetX() <= this->x2);
	bool containsY = (this->y1 <= vec->GetY()) && (vec->GetY() <= this->y2);
	bool containsZ = (this->z1 <= vec->GetZ()) && (vec->GetZ() <= this->z2);

	return containsX && containsY && containsZ;
}

VECTOR3D BoundingBox::getCenter() {
	float x = (this->getX2() + this->getX1()) / 2 + this->getX1();
	float y  = (this->getY2() + this->getY1()) / 2 + this->getY1();
	float z = (this->getZ2() + this->getZ1()) / 2 + this->getZ1();

	//printf("hey%f", (this->getX2() + this->getX1()) / 2 + this->getX1());


	return VECTOR3D(x, y, z);
}


float BoundingBox::getX1() {
	return this->x1;
}

float BoundingBox::getX2() {
	return this->x2;
}


float BoundingBox::getY1() {
	return this->y1;
}


float BoundingBox::getY2() {
	return this->y2;
}


float BoundingBox::getZ1() {
	return this->z1;

}

float BoundingBox::getZ2() {
	return this->z2;
}
