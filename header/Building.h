#pragma once

#include <gl/glut.h>
#include <vector>
#include "../header/BoundingBox.h"
#include "VECTOR3D.h"
#include "Util.h"

#ifndef BUILDING_H
#define BUILDING_H

class Building {

public:
	Building(float locX, float locY, float locZ, float sizeXZ, float sizeY);
	BoundingBox getCurrentBoundingBoxState();
	void draw();

protected:
	float locX, locY, locZ;
	float sizeXZ, sizeY;
};

#endif