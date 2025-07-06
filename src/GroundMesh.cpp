

#include "../header/GroundMesh.h"
#include "../header/QuadMesh.h"
#include <stdlib.h>
#include <stdio.h>
#include "../header/VECTOR3D.h"
#include "../header/Transformations.h"
#include <gl/glut.h>


void GroundMesh::init() {

	const float MESH_SIZE = 128;

	VECTOR3D origin = VECTOR3D(-16.0f, 0.0f, 16.0f);
	VECTOR3D dir1v = VECTOR3D(1.0f, 0.0f, 0.0f);
	VECTOR3D dir2v = VECTOR3D(0.0f, 0.0f, -1.0f);

	this->ground = new QuadMesh(size, MESH_SIZE);  


	ground->InitMesh(size, origin, MESH_SIZE, MESH_SIZE, dir1v, dir2v);

	VECTOR3D ambient = VECTOR3D(0.0f, 0.05f, 0.0f);
	VECTOR3D diffuse = VECTOR3D(0.4f, 0.8f, 0.4f);
	VECTOR3D specular = VECTOR3D(0.04f, 0.04f, 0.04f);
	float shininess = 0.2;
	ground->SetMaterial(ambient, diffuse, specular, shininess);

}

void GroundMesh::draw() {

	glPushMatrix();
	translateCustom(this->x,this->y, this->z);
	ground->DrawMesh(size);
	glPopMatrix();

}


GroundMesh::GroundMesh(int size, float locX, float locY, float locZ) {
	ground = NULL;
	this->size = size;
	this->init();
	this->x = locX;
	this->y = locY;
	this->z = locZ;
}

