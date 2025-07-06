#pragma once
#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "../header/VECTOR3D.h"

class BoundingBox {

private:
	float x1, x2, y1, y2, z1, z2;

public:
	BoundingBox(float x1, float x2, float y1, float y2, float z1, float z2);
	bool contains(VECTOR3D* vec);
	VECTOR3D getCenter();

	float getX1();
	float getX2();
	float getY1();
	float getY2();
	float getZ1();
	float getZ2();



};
#endif