#pragma once
#include <string>
#include "RenderUtils.hpp"
#include <PxScene.h>
#include <PxPhysics.h>
#include "PxShape.h"
#include <iostream>
#include "PxPhysics.h"
#include "PxRigidDynamic.h"

const float CESTATICO = 0.2;
const float CDINAMICO = 0.5;
const float CELASTICO = 0.5;

const float RADIUS = 1;

using namespace physx;
using namespace std;
class Bola
{
private:
	string color;
	PxRigidDynamic* bola;
	Vector3 position;
	PxTransform* transform;
	PxPhysics* _gPhysics;
	PxScene* _gScene;
	RenderItem* item; 
	PxShape* shape;
	Vector3 initialPos;
	float segundosTrasGolpe = 0;
	float delay = 1;
	bool disparada = false;
	bool canStop = false;
	float puntuacion;

	
	//int points;
public:
	Bola(string color, Vector3 position,PxPhysics* _gPhysics, PxScene* _gScene);
	~Bola();
	inline PxVec3 getPos() { return bola->getGlobalPose().p; }
	void setPos(PxVec3 newPos);
	RenderItem* getItem() { return item; }
	PxRigidDynamic* getBola() { return bola; }

	void update(double t);
	inline void setDisparada() { disparada = !disparada; }
	void stopBola();
	string getColor() { return color; }
	float getPuntuacion() { return puntuacion; }

	PxShape* getShape() { return shape; }
	void returnToInitialPlace();
};

