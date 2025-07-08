#pragma once

#include <gl/glut.h>
#include <vector>
#include "../header/BoundingBox.h"
#include "VECTOR3D.h"
#include "Util.h"
#include "ObjectTextureHandler.h"

#ifndef BLIMP_H
#define BLIMP_H


class Blimp {


public:
	Blimp(float locX, float locY, float locZ, float rotationHorizontal, bool isPlayer);
	
	void setRotation(float newRotation);
	float getRotation();
	void draw();
	void setLocation(float x, float y, float z);
	void addLocation(float x, float y, float z);
	float getX();
	float getY();
	float getZ();
	float getBottomBlimpY();
	void fireLaser(); ////
	void stopLaser();
	BoundingBox getCurrentBoundingBoxState();
	VECTOR3D getDirection();


	void moveForward(float x, float z);
	void moveBackward(float x, float z);
	void cameraPosition(
		float* eyeX, float* eyeY, float* eyeZ,
		float* centerX, float* centerY, float* centerZ
	);
	bool getIsAlive();
	void setIsAlive(bool isAlive);

	void setLazerScale(float scale);
	void setLazerScaleUpdated(bool updated);
	HitResult rayTraceBox(BoundingBox* box, bool alive);
	void setHealth(int health);
	int getHealth();

	void setLastDamageTime(long long lastTime);
	long long getLastDamageTime();
	void damage();
	
	
protected:
	float locX;
	float locY;
	float locZ;
	bool isPlayer;
	long long lastDamageTime;

	float lastY;

	float propRotation;

	bool drawLazerToggle;
	float lazerScale;
	bool lazerScaleUpdated;

	bool isAlive;
	int health;

	float animationOffset;
	long long lastAnimationTime;
	long long respawnTime;


	long long laserRotationTime;
	float laserHitRot;



	
	std::vector<float> velocity;

	float rotationHorizontal;
	GLUquadricObj *finFanHorizontal, *finFanVertical, *driveLeft, *driveRight;


	void drawBody();
	void drawFins();
	void drawCarriage();
	void drawEngine();
	void drawRetained(ObjData o);


};

#endif