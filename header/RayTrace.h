#pragma once
#ifndef RAYTRACE_H
#define RAYTRACE_H

#include "../header/VECTOR3D.h"
#include "../header/BoundingBox.h"
#include "../header/Util.h"

class RayTrace {

private:
	double addX, multiplierX;
	double addY, multiplierY;
	double addZ, multiplierZ;

public:

	RayTrace(VECTOR3D* dir, VECTOR3D* origin);
	double getXFactor(double xCoord);
	double getYFactor(double yCoord);
	double getZFactor(double zCoord);

	VECTOR3D getXPoint(double xCoord);
	VECTOR3D getYPoint(double yCoord);
	VECTOR3D getZPoint(double zCoord);
	HitResult isInBox(VECTOR3D* x1, VECTOR3D* x2,
		VECTOR3D* y1, VECTOR3D* y2,
		VECTOR3D* z1, VECTOR3D* z2, BoundingBox* box);



};

#endif