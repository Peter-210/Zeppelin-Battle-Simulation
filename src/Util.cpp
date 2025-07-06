

#include "../header/Util.h"
#include "../header/VECTOR3D.h"
#include "../header/RayTrace.h"
#include <chrono>

const float PI = 3.14159265;

long long currentTimeMillis() {
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch()).count();
}

double toRadians(float angDeg) {
	return (angDeg * PI) / 180;
}


double toDegrees(float angRads) {
	return (180 * angRads) / PI;
}

HitResult rayTrace(BoundingBox* box, VECTOR3D* startPosition, VECTOR3D* direction) {



	VECTOR3D objectLocation = box->getCenter();
	

	const float MULTIPLIER = 10;
	float destX = direction->GetX() * MULTIPLIER;
	float destY = direction->GetY() * MULTIPLIER;
	float destZ = direction->GetZ() * MULTIPLIER;


	VECTOR3D* difference;
	float diffX, diffY, diffZ;
	diffX = objectLocation.GetX() - startPosition->GetX();
	diffY = objectLocation.GetY() - startPosition->GetY();
	diffZ = objectLocation.GetZ() - startPosition->GetZ();

	difference = new VECTOR3D(diffX, diffY, diffZ);

	//printf("%f, %f %f", diffX, diffY, diffZ);
	//printf("%f, %f %f", startPosition->GetX(), startPosition->GetY(), startPosition->GetZ());


	double dotProduct = difference->DotProduct(*direction);

	//printf("dotProduct: %f\n", dotProduct);

	if (dotProduct < 0) {
		HitResult noHit;
		noHit.hitEntity = false;
		noHit.hitPos = VECTOR3D(0, 0, 0);
		return noHit;
	}


	RayTrace* trace = new RayTrace(direction, startPosition);

	
	VECTOR3D pointXMin = trace->getXPoint(box->getX1());
	VECTOR3D pointYMin = trace->getYPoint(box->getY1());
	VECTOR3D pointZMin = trace->getZPoint(box->getZ1());
	VECTOR3D pointXMax = trace->getXPoint(box->getX2());
	VECTOR3D pointYMax = trace->getYPoint(box->getY2());
	VECTOR3D pointZMax = trace->getZPoint(box->getZ2());
	

	return trace->isInBox( &pointXMin, &pointXMax, &pointYMin, &pointYMax, &pointZMin, &pointZMax, box);
}


