#pragma once

#include "GroundMesh.h"
#include "QuadMesh.h"


class GroundMesh {

public:
	void init();
	GroundMesh(int size, float locX, float locY, float locZ);
	void draw();


private:
	QuadMesh* ground; 
	int size;
	float x;
	float y;
	float z;



};