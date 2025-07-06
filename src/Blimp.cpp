#include <stdio.h>
#include <math.h>
#include <gl/glut.h>
#include "../header/Blimp.h"
#include "../header/Transformations.h"
#include "../header/WindowHandler.h"
#include "../header/BoundingBox.h"
#include "../header/VECTOR3D.h"
#include "../header/ObjectTextureHandler.h"



GLfloat blimpBlue[] = { 0.0f,0.0f,1.0f,1.0f };
GLfloat blimpYellow[] = { 1.0f,0.7f,0.0f,1.0f};
GLfloat blimpGrey[] = {0.1f, 0.0f, 0.0f, 0.0f};


const float SCALE = 2;
const int RESOLUTION = 48;
const float PI = 3.14159265;

const float DIST_NEAR = 5.0;
const float DIST_FAR = 25.0;

const long long ANIM_TIME = 3000;


ObjData body;
ObjData engine;
ObjData propBlades;


Blimp::Blimp(float locX, float locY, float locZ, float rotationHorizontal, bool isPlayer) {


	readOBJ("../assets/sphere.obj", &body);
	readOBJ("../assets/engine.obj", &engine);
	readOBJ("../assets/prop_blades.obj", &propBlades);


	this->isPlayer = isPlayer;
		this->locX = locX;
		this->locY = locY;
		this->locZ = locZ;
		this->lastY = 0;
		this->lazerScale = 1;

		this->isAlive = true;

		this->health = 10;
		this->lastDamageTime = 0;
		this->respawnTime = 0;

		this->velocity = { 0, 0 ,0 }; //basically the velocity of the blimp
		this->animationOffset = 0;
		this->lastAnimationTime = 0;

		this->laserRotationTime = 0;
		this->laserHitRot = 0;



		this->rotationHorizontal = rotationHorizontal;
		this->propRotation = 0;
		this->drawLazerToggle = false;

		this->finFanHorizontal = gluNewQuadric();
		this->finFanVertical = gluNewQuadric();
		this->driveLeft = gluNewQuadric();
		this->driveRight = gluNewQuadric();
}


void Blimp::addLocation(float x, float y, float z) {

	this->lastY = y;  //displacement to determine whether it went up/down

	this->locX += x;
	this->locY += y;
	this->locZ += z;


}

void Blimp::cameraPosition(
	float* eyeX, float* eyeY, float* eyeZ,
	float* centerX, float* centerY, float* centerZ
) {
	float angle = this->getRotation();
	float angleRads = (angle * PI) / 180;
	
	*eyeX = this->locX + DIST_NEAR * cos(angleRads);
	*eyeY = this->locY;
	*eyeZ = this->locZ - DIST_NEAR * sin(angleRads);
	
	*centerX = this->locX + DIST_FAR * cos(angleRads);
	*centerY = this->locY;
	*centerZ = this->locZ - DIST_FAR * sin(angleRads);
}


void Blimp::moveForward(float x, float z) {
	float angle = this->getRotation();
	float angleRads = (angle * PI) / 180;


	double directionX = cos(angleRads);
	double directionZ = sin(angleRads);

	this->addLocation(directionX * x, 0, -directionZ * z);
}

void Blimp::moveBackward(float x, float z) {
	float angle = this->getRotation();
	float angleRads = (angle * PI) / 180;


	double directionX = cos(angleRads);
	double directionZ = sin(angleRads);

	this->addLocation(directionX * -x, 0, -directionZ * -z);
}

VECTOR3D Blimp::getDirection() {
	float angle = this->getRotation();
	float angleRads = (angle * PI) / 180;

	double directionX = cos(angleRads);
	double directionZ = sin(angleRads);
	return VECTOR3D(directionX, 0, -directionZ);
}


HitResult Blimp::rayTraceBox(BoundingBox* box, bool isAlive) {

	//the -2 for the y is to account for the fact that the lazer is below
	VECTOR3D* playerLoc = new VECTOR3D(this->getX(), this->getY() - 2, this->getZ());
	VECTOR3D playerDir = this->getDirection();
	HitResult hitEnemy = rayTrace(box, playerLoc, &playerDir);

	bool hasHitEnemy = hitEnemy.hitEntity;
	HitResult hit;

	if (hasHitEnemy && isAlive) {

		VECTOR3D hitLoc = hitEnemy.hitPos;
		float diffX = hitLoc.GetX() - playerLoc->GetX();
		float diffZ = hitLoc.GetZ() - playerLoc->GetZ();

		float distance = sqrt(diffX * diffX + diffZ * diffZ);
		this->setLazerScale(distance);
		this->setLazerScaleUpdated(true);
		hit.hitPos = hitLoc;

	}
	else {
		this->setLazerScaleUpdated(false);
		hit.hitPos = VECTOR3D(0, 0, 0);
	}
	hit.hitEntity = hasHitEnemy;

	return hit;
}



void Blimp::damage() {
	const long long INVULNERABILITY_TIME = 500;

	long long damageTime = this->getLastDamageTime();
	long long currentTime = currentTimeMillis();

	if (currentTime - damageTime >= INVULNERABILITY_TIME) {
		this->setHealth(this->getHealth() - 1);
		this->setLastDamageTime(currentTime);
	}
}


void Blimp::setHealth(int health) {

	if (health <= 0) {
		this->health = 0;
		this->setIsAlive(false);
		this->respawnTime = currentTimeMillis();
	}
	else {
		this->setIsAlive(true);
		this->health = health;
	}
}

int Blimp::getHealth() {
	return health;
}

void Blimp::fireLaser() {
	this->drawLazerToggle = true;
}

void Blimp::stopLaser() {
	this->drawLazerToggle = false;
}


/*             90
               |
               |
      180----------------0
	           |
			   |
			  270

*/
void Blimp::setRotation(float angDeg) {

	if (angDeg >= 360)
		angDeg -= 360;

	if (angDeg <= 0) {
		angDeg += 360;
	}

	this->rotationHorizontal = angDeg;
}


void Blimp::setLocation(float x, float y, float z) {
	this->locX = x;
	this->locY = y;
	this->locZ = z;
}

void Blimp::setLazerScale(float scale) {
	this->lazerScale = scale;
}


float Blimp::getRotation() {
	return this->rotationHorizontal;
}


bool Blimp::getIsAlive() {
	return this->isAlive;
}

void Blimp::setIsAlive(bool isAlive) {
	this->isAlive = isAlive;
	if (isAlive) {
		this->animationOffset = 0;
	}

}

float Blimp::getX() {
	return this->locX;
}

float Blimp::getY() {
	return this->locY;
}

float Blimp::getZ() {
	return this->locZ;
}

void Blimp::setLastDamageTime(long long time) {
	this->lastDamageTime = time;
}

long long Blimp::getLastDamageTime() {
	return lastDamageTime;
}


void Blimp::setLazerScaleUpdated(bool updated) {
	this->lazerScaleUpdated = updated;
}

float Blimp::getBottomBlimpY() {
	float bodyHeight = SCALE / 2;
	float cabinHeight = SCALE / 4;
	return (bodyHeight / 2) - cabinHeight - SCALE;
}


BoundingBox Blimp::getCurrentBoundingBoxState() {
	float minX, maxX, minY, maxY, minZ, maxZ;
	const float BOX_SCALE = 2;

	minX = this->getX() - BOX_SCALE;
	maxX = this->getX() + BOX_SCALE;

	minY = this->getY() - BOX_SCALE;
	maxY = this->getY() + BOX_SCALE;

	minZ = this->getZ() - BOX_SCALE;
	maxZ = this->getZ() + BOX_SCALE;

	return BoundingBox(minX, maxX, minY, maxY, minZ, maxZ);

}







//============================================================================================================
//Drawing functions below here.


void Blimp::drawRetained(ObjData o) {

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// Set the vertex pointer
	glVertexPointer(3, GL_FLOAT, sizeof(Float3D), o.positions);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Float2D), o.textureCoords);

	// Draw the elements
	glDrawElements(GL_TRIANGLES, o.numIndices, GL_UNSIGNED_INT, o.indices);

	// Disable the client state
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}



void Blimp::draw() {



	
	if (this->getIsAlive()) {
		this->animationOffset = 0;
	   }
	else {
		const long long ANIM_PERIOD = 50;
		long long time = currentTimeMillis();
		if (time - lastAnimationTime >= ANIM_PERIOD) {
			this->lastAnimationTime = time;
			this->animationOffset += 0.2;
		}

		const long long TIME_TO_RESPAWN = 3000;
		if (time - respawnTime > TIME_TO_RESPAWN) {
			respawnTime = time;
			setIsAlive(true);
			setHealth(10);

			setLocation(rand() % 10, rand() % 10, rand() % 10);
		}
	}



		glPushMatrix();  //the matrix stack is still there after you exit the function. If you do this and don't pop
		                     //it'll break

		
     	translateCustom(locX, locY, locZ);
		//glTranslatef(locX, locY, locZ);

		rotateCustom(rotationHorizontal, 0, 1, 0);
		//glRotatef(rotationHorizontal, 0, 1, 0);

		glPushMatrix();


		drawBody();
		drawCarriage();
		drawFins();
		drawEngine();

		propRotation += 10;
		if (propRotation > 360) {
			propRotation -= 360;
		}

		glPopMatrix();
}



void Blimp::drawBody() {
	glPushMatrix();


	if (this->isPlayer) {
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, 10000);
	}
	else {
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBindTexture(GL_TEXTURE_2D, 10002);
	}
	///glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blimpBlue);
	glMatrixMode(GL_MODELVIEW);

	//glScalef(SCALE, SCALE / 2, SCALE / 2);

	translateCustom(animationOffset, -animationOffset, animationOffset);
	scaleCustom(SCALE / 2, SCALE / 5, SCALE / 5);


	this->drawRetained(body);
	//glutSolidSphere(SCALE, RESOLUTION, RESOLUTION);
	glPopMatrix();
}




void Blimp::drawCarriage() {

	///glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blimpYellow);


	glPushMatrix();
	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blimpYellow);
	

	translateCustom(animationOffset * 2, -animationOffset*2, animationOffset);
	translateCustom(0, -SCALE, 0);
	//glTranslatef(0, -SCALE, 0);
	
	scaleCustom(SCALE / 3, SCALE / 4, SCALE / 6);
	//glScalef(SCALE/3, SCALE/4, SCALE/6);

	glutSolidCube(SCALE);

	// Draw Laser
	if (this->drawLazerToggle) {
		glPushMatrix();
		///glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blimpYellow);

		const float DEFAULT_DIST_SCALE = 8 * SCALE;

		float distanceLazerScale;

		if (this->lazerScaleUpdated) {
			distanceLazerScale = this->lazerScale * 0.25;
		}
		else {
			distanceLazerScale = DEFAULT_DIST_SCALE;
		}

		translateCustom(distanceLazerScale * 2, 0.0, 0.0);
		scaleCustom(distanceLazerScale, SCALE / 20, SCALE / 20);
	
		glBindTexture(GL_TEXTURE_2D, 10006);
		glutSolidSphere(SCALE, RESOLUTION, RESOLUTION);
		glPopMatrix();


		// Draw Laser Collision Effect
		if (this->lazerScaleUpdated) {
			glPushMatrix();
		///	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blimpBlue);
			translateCustom(distanceLazerScale * 4, 0.0, 0.0);
			scaleCustom(1.0, 1.0, 1.0);

			const long long LAZER_ROT_TIME = 50;
			long long time = currentTimeMillis();
			if (time - laserRotationTime >= LAZER_ROT_TIME) {
				laserRotationTime = time;
				this->laserHitRot += 5;
			}

			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
			glBindTexture(GL_TEXTURE_2D, 10005);

			glRotatef(laserHitRot, 0, 0, 1); 
			glutSolidCube(SCALE);
			
			glPushMatrix();
			glRotatef(laserHitRot * 2, 1, 1, 0);
			glutSolidCube(SCALE);
			glPopMatrix();



			glPopMatrix();
		}
	}

	glPopMatrix();

}


void Blimp::drawFins() {

	///glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blimpBlue);
	glPushMatrix();


	translateCustom(animationOffset*2, -animationOffset, -animationOffset);
	translateCustom(-SCALE * 2, 0, 0);
	//glTranslatef(-SCALE * 2, 0, 0);

	glPushMatrix();
	
    //glRotatef(90, 1, 0, 0);
	rotateCustom(90, 1, 0, 0);


	gluPartialDisk(this->finFanHorizontal, 0, SCALE, 10, 3, 0, 180);
	glPopMatrix();
	gluPartialDisk(this->finFanVertical, 0, SCALE, 10, 3, 0, 180);


	glPopMatrix();
	glPopMatrix();

}


void Blimp::drawEngine() {

	///glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blimpYellow);
	float engineScale = SCALE / 3;



	float offset = 0;

	if (lastY > 0) {
		offset = 90;
	}
	else if (lastY < 0) {
		offset = -90;
	}


	//right engine
	glPushMatrix();
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, 10003);


	translateCustom(animationOffset, -animationOffset*0.5, -animationOffset);

	//glTranslatef(0, 0, SCALE + engineScale);
	translateCustom(0, 0, SCALE + engineScale);

	glPushMatrix();

	//glRotatef(90, 0, 1, 0);   //positioning of the engine
	//rotateCustom(90, 0, 1, 0);

	glRotatef(-90, 0, 0, 1);
	glRotatef(offset, 0, 0, 1);

	glScalef(SCALE / 6, SCALE / 6, SCALE / 6);

	//glRotatef(-offset, 1, 0, 0);  //tilting the things up or down
	//rotateCustom(-offset, 1, 0, 0);


	this->drawRetained(engine);

	//glutSolidCone(engineScale, engineScale * 1.5, 24, 24);   //engine body
	glPopMatrix();


	   glPushMatrix();




	//glRotatef(90, 0, 1, 0);
	   rotateCustom(90, 0, 1, 0);
	 
	
	//glRotatef(180 - offset, 1, 0, 0);
	   rotateCustom(180 - offset, 1, 0, 0);

	gluCylinder(driveRight, engineScale/4, engineScale/4, engineScale, 12, 12);  //driveshaft
	   glPopMatrix();


	  glPushMatrix(); //prop blades

	  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	  glBindTexture(GL_TEXTURE_2D, 10004);

	//  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blimpGrey);
	  //glRotatef(90, 0, 1, 0);
	  rotateCustom(90, 0, 1, 0);
	  //glRotatef(180 - offset, 1, 0, 0);
	  rotateCustom(180 - offset, 1, 0, 0);
	  //glTranslatef(0, 0, engineScale);
	  translateCustom(0, 0, engineScale);

	  //glRotatef(propRotation, 0, 0, 1);
	  rotateCustom(propRotation, 0, 0, 1);
	
	  glScalef(engineScale / 6, engineScale / 4, engineScale / 2);

	  this->drawRetained(propBlades);

	//glutSolidCube(1);

	   glPopMatrix();  //prop blades
	   glPopMatrix();




	//   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blimpYellow);

	//left engine
	glPushMatrix();

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, 10003);

	translateCustom(animationOffset*0.5, -animationOffset, 2*animationOffset);



	//glTranslatef(0, 0, -(SCALE + engineScale));
	translateCustom(0, 0, -(SCALE + engineScale));
	glPushMatrix(); 

	//glRotatef(90, 0, 1, 0);   //positioning of the engine
	rotateCustom(-90, 0, 0, -1);
	
	glScalef(SCALE / 6, SCALE / 6, SCALE / 6);


	rotateCustom(offset, 0, 0, 1);

	this->drawRetained(engine);

	///glutSolidCone(engineScale, engineScale * 1.5, 24, 24);   //engine body
	glPopMatrix();


	glPushMatrix();
	//glRotatef(90, 0, 1, 0);
	rotateCustom(90, 0, 1, 0);
	
	//glRotatef(180 - offset, 1, 0, 0);
	rotateCustom(180 - offset, 1, 0, 0);

	gluCylinder(driveRight, engineScale / 4, engineScale / 4, engineScale, 12, 12);  //driveshaft
	glPopMatrix();


	glPushMatrix(); //prop blades

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, 10004);

	//glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, blimpGrey);
	//glRotatef(90, 0, 1, 0);
	rotateCustom(90, 0, 1, 0);
	
	//glRotatef(180 - offset, 1, 0, 0);
	rotateCustom(180 - offset, 1, 0, 0);
	//glTranslatef(0, 0, engineScale);
	translateCustom(0, 0, engineScale);
	
	//glRotatef(-propRotation, 0, 0, 1);
	rotateCustom(-propRotation, 0, 0, 1);
	//glScalef(engineScale * 2, engineScale / 4, engineScale / 8);

	scaleCustom(engineScale / 6, engineScale / 4, engineScale / 2);
	
	this->drawRetained(propBlades);

	///glutSolidCube(1);

	glPopMatrix();  //prop blades
	glPopMatrix();
	
 
}
