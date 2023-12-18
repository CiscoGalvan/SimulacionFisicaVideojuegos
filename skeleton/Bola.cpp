#include "Bola.h"
Bola::Bola(string color, Vector3 pos, PxPhysics* _gPhysics, PxScene* _gScene)
{
	this->color = color;
	this->position = pos;
	this->_gPhysics = _gPhysics;
	this->_gScene= _gScene;
	this->initialPos = pos;

	

	PxMaterial* gMaterial = _gPhysics->createMaterial(CESTATICO,CDINAMICO,CELASTICO);

	shape = CreateShape(PxSphereGeometry(RADIUS), gMaterial);
	PxFilterData filterData;
	if(color=="BLANCO") filterData.word0 = 3;
	shape->setSimulationFilterData(filterData);
	bola = _gPhysics->createRigidDynamic(PxTransform(this->position));
	bola->setMass(0.180);
	
	/*PxRigidBodyExt::updateMassAndInertia(*new_solid, density);
	new_solid->setMassSpaceInertiaTensor(inertiaT);*/

	_gScene->addActor(*bola);
	
	
	if (color == "ROJO")
	{
		bola->setName("R");
		puntuacion = 1;
		item = new RenderItem(shape, bola, Vector4(1, 0, 0, 1));
	}
	else if (color == "AMARILLO")
	{
		bola->setName("Y");
		puntuacion = 2;
		item = new RenderItem(shape, bola, Vector4(1, 1, 0, 1));		
	}
	else if (color == "MARRON")
	{
		bola->setName("B");
		puntuacion = 4;
		item = new RenderItem(shape, bola, Vector4(0.36, 0.25, 0.04, 1));
	}
	else if (color == "VERDE")
	{
		puntuacion = 3;
		bola->setName("G");
		
		item = new RenderItem(shape, bola, Vector4(0.17, 0.40, 0.15, 1));
	}
	else if (color == "AZUL")
	{
		bola->setName("C");
		puntuacion = 5;
		item = new RenderItem(shape, bola, Vector4(0, 0, 0.85, 1));
	}
	else if (color == "ROSA")
	{
		bola->setName("P");
		puntuacion = 6;
		item = new RenderItem(shape, bola, Vector4(0.96, 0.31, 0.3, 1));		
	}
	else if (color == "NEGRO")
	{
		bola->setName("N");
		puntuacion = 7;
		item = new RenderItem(shape, bola, Vector4(0, 0, 0, 1));
	}
	else if(color =="BLANCO")
	{
		bola->setName("W");
		item = new RenderItem(shape, bola, Vector4(1, 1, 1, 1));
		
		
	}



	transform = new PxTransform(position);
	bola->setGlobalPose(*transform);
	bola->attachShape(*shape);
}

Bola::~Bola()
{
	_gScene->removeActor(*bola);
}
void Bola::setPos(PxVec3 newPos)
{
	 position = newPos;
	 transform->p = position; 
	 bola->setGlobalPose(*transform);
}


void Bola::update(double t)
{
}

void Bola::stopBola()
{


	bola->setLinearVelocity(Vector3(0, 0, 0));
	bola->setAngularVelocity(Vector3(0, 0, 0));
	//bola->setLinearVelocity(bola->getLinearVelocity()*0.999);
	//bola->setAngularVelocity(bola->getAngularVelocity() * 0.999);
	//if(color == "BLANCO")
	//{
	//	delay = 1;
	//	disparada = false;
	//	canStop = false;
	//}
}
void Bola::returnToInitialPlace()
{
	transform->p = this->initialPos;
	bola->setLinearVelocity(Vector3(0, 0, 0));
	bola->setAngularVelocity(Vector3(0, 0, 0));
	bola->setGlobalPose(*transform);
}