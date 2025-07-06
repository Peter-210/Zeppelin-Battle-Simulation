
#include "../header/RayTrace.h"
#include "../header/BoundingBox.h"
#include <stdio.h>
#include "../header/Util.h"

RayTrace::RayTrace(VECTOR3D* direction, VECTOR3D* origin) {
	this->addX = origin->GetX();
	this->addY = origin->GetY();
	this->addZ = origin->GetZ();

	this->multiplierX = direction->GetX();
	this->multiplierY = direction->GetY();
	this->multiplierZ = direction->GetZ();

}

HitResult RayTrace::isInBox(VECTOR3D* x1, VECTOR3D* x2,
	VECTOR3D* y1, VECTOR3D* y2,
	VECTOR3D* z1, VECTOR3D* z2, BoundingBox* box) {

	HitResult hit;

	if (box->contains(x1)) {
		hit.hitEntity = true;
		hit.hitPos = (*x1);

	}
	else if (box->contains(x2)) {
		hit.hitEntity = true;
		hit.hitPos = (*x2);

	}
	else if (box->contains(y1)) {
		hit.hitEntity = true;
		hit.hitPos = (*y1);

	}
	else if (box->contains(y2)) {
		hit.hitEntity = true;
		hit.hitPos = (*y2);

	}
	else if (box->contains(z1)) {
		hit.hitEntity = true;
		hit.hitPos = (*z1);

	}
	else if (box->contains(z2)) {
		hit.hitEntity = true;
		hit.hitPos = (*z2);
	}
	else {
		hit.hitEntity = false;
		hit.hitPos = VECTOR3D(0, 0, 0);
	}

	return hit;
}



double RayTrace::getXFactor(double xCoord) {
	return  (xCoord - this->addX) / this->multiplierX;
}




double RayTrace::getYFactor(double yCoord) {
	return  (yCoord - this->addY) / this->multiplierY;
}




double RayTrace::getZFactor(double zCoord) {
	return  (zCoord - this->addZ) / this->multiplierZ;
}



VECTOR3D RayTrace::getXPoint(double xCoord) {

	double factor = this->getXFactor(xCoord);
	double x = this->addX + multiplierX * factor;
	double y = this->addY + multiplierY * factor;
	double z = this->addZ + multiplierZ * factor;
	return VECTOR3D(x, y, z);
}

VECTOR3D RayTrace::getYPoint(double yCoord) {
	double factor = this->getYFactor(yCoord);
	double x = this->addX + multiplierX * factor;
	double y = this->addY + multiplierY * factor;
	double z = this->addZ + multiplierZ * factor;
	return VECTOR3D(x, y, z);
}


VECTOR3D RayTrace::getZPoint(double zCoord) {
	double factor = this->getZFactor(zCoord);
	double x = this->addX + multiplierX * factor;
	double y = this->addY + multiplierY * factor;
	double z = this->addZ + multiplierZ * factor;
	return VECTOR3D(x, y, z);
}

