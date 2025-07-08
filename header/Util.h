#pragma once
#ifndef TIME_H
#define TIME_H

#include <chrono>
#include "../header/VECTOR3D.h"
#include "../header/BoundingBox.h"


typedef struct HitResult {
	bool hitEntity;
	VECTOR3D hitPos;
} HitResult;


//gets the current system time in milliseconds. Useful for tracking how much time has passed.
long long currentTimeMillis();
double toRadians(float angDeg);
double toDegrees(float angRads);



HitResult rayTrace(BoundingBox* box, VECTOR3D* startPosition, VECTOR3D* direction);
#endif

