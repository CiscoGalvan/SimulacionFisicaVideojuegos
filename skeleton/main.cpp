#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "ParticleSystem.h"
#include "RigidBodySystem.h"
#include <iostream>
#include <list>
#include "Bola.h"

std::string display_text = "This is a test";


using namespace physx;


PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

RigidBodySystem* rS = NULL;
PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;

bool pulsed = false;
bool shot = false;
int cont = 0;
// Initialize physics engine
void initPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	gFoundation = PxCreateFoundation(PX_FOUNDATION_VERSION, gAllocator, gErrorCallback);

	gPvd = PxCreatePvd(*gFoundation);
	PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
	gPvd->connect(*transport,PxPvdInstrumentationFlag::eALL);

	gPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale(),true,gPvd);

	gMaterial = gPhysics->createMaterial(0.5f, 0.5f, 0.6f);

	
	GetCamera()->setDir(&PxTransform(-0.00002, -1, -0.002222));
	GetCamera()->setTransform(&PxTransform(0, 200,0));

	
	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);

	rS = new RigidBodySystem(gPhysics, gScene);

}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);
	gScene->simulate(t);
	rS->update(t);
	gScene->fetchResults(true);

	if (pulsed && rS->poderDisparar())
	{
		cont++;
		rS->setHoldValue(cont);
	}
	else
	{
		rS->revientaPelota();
		cont = 0;	
		rS->setHoldValue(0);
	}


	
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);
	delete rS;
	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	//pS->cleanupPhysics();
	
	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case '1':
	{
		rS->configuraCamara();
		break;
	}
	case '6':
	{
		if(rS->firstMoved())rS->moveBlanca(Direcciones::RIGHT);
		break;
	}
	case '4':
	{
		if (rS->firstMoved())rS->moveBlanca(Direcciones::LEFT);
		break;
	}
	case '8':
	{
		if (rS->firstMoved())rS->moveBlanca(Direcciones::UP);
		break;
	}
	case '2':
	{
		if (rS->firstMoved())rS->moveBlanca(Direcciones::DOWN);
		break;
	}
	case ' ':
	{
		if(rS->poderDisparar())rS->rotatePalo();
		break;
	}
	case'F':
	{
		rS->ExplotaTodo();
		break;
	}

	//case 'T':	//BOLA DE MASA PEQUEÑA
	//{	
	//	pS->shootParticle(25, 0.2, 20,0.1,Vector3(0, -9.8, 0));
	//	break;
	//}	

	//case 'Y':	//FIREWORK 1
	//{
	//	pS->shootFirework(250, 0.2, 2, 1,Vector3(0, -9.8, 0),false);
	//	break;
	//}
	//case 'U':	//FIREWORK 2
	//{
	//	pS->shootFirework(250, 0.2, 2,1, Vector3(0, -9.8, 0), true);
	//	break;
	//}
	//case 'Q':	//SHOW RED SQUARE
	//{
	//	pS->showSquareFunction();
	//	break;
	//}
	//case 'Z':	//SHOW BLUE SQUARE
	//{
	//	pS->showSquareFunction2();
	//	break;
	//}
	//case 'I':   //SPAWN PARTICLES ABOVE RED SQUARE
	//{
	//	physx::PxTransform pT(20.1391, 89.0057 ,19.4672);
	//	Particle* particle;
	//	float masa = 0.1;
	//	float liveTime = 10000;
	//	particle = new Particle(pT, Vector3(0,0,0), Vector3(0,0,0 ), masa, liveTime, DAMPING, false);
	//	pS->addGenerator("fuente", particle, 1, 0.01,2);
	//	break;
	//}

	//case 'L':   //SPAWN TWO PARTICLES WITH DIFFERENT MASS
	//{
	//	pS->generaParticula(physx::PxTransform(-34, 200, -47), Vector3(0, 0, 0), Vector3(0, 0, 0), 10, Vector3(0, -9.8, 0));
	//	pS->generaParticula(physx::PxTransform(-34, 200, -27), Vector3(0, 0, 0), Vector3(0, 0, 0), 0.001, Vector3(0, -9.8, 0));
	//}
	//case'K':	//ACTIVATE WIND IN RED SQUARE
	//{
	//	pS->allowWind();
	//	break;
	//}
	//case 'J':	//DENY WIND IN RED SQUARE
	//{
	//	pS->denyWind();
	//	break;
	//}
	//case 'N':	//ACTIVATE WHIRLWIND
	//{
	//	pS->allowTorbellino();
	//	break;
	//}
	//case 'M':   //DEACTIVATE WHIRLWIND
	//{
	//	pS->denyTorbellino();
	//	break;
	//}
	//case 'B':	//ACTIVATE EXPLOSION
	//{
	//	pS->explode();
	//	break;
	//}
	//case 'V':	//RANDOM GEN
	//{
	//	pS->setGeneration();
	//	break;
	//}

	//case '1':	//TWO PARTICLES JOINT BY A SPRING
	//{
	//	pS->generateSpringDemo();
	//	break;
	//}
	//case '2':	//TO TES GRAVITY IN JOINTS
	//{
	//	pS->temporalGravity(Vector3(40, 0, 0));
	//	break;
	//}
	//case '3':	//TO MAKE THE CONSTANT K BIGGER
	//{
	//	pS->biggerK();
	//	break;
	//}
	//case '4':	//AND SMALLER
	//{
	//	pS->smallerK();
	//	break;
	//}
	//case'5':	//GENERATES A SLINKY
	//{
	//	pS->generateSlinky();
	//	break;
	//}
	//case'6':	//GENERATES WATER
	//{
	//	pS->generateWater();
	//	break;
	//}
	/*case '7' : 
	{	
		
		Camera* cam = GetCamera();	
		rS->addDynamicObject(0.2f, 0.1f, 0.3f, Vector3(1, 1, 1), Vector3(4, 4, 4), Vector4(1, 0.5, 0, 1), cam->getTransform().p,cam->getDir() * 50, Vector3(0, 80, 80),0.15, 10000);
		break;
	}
	case '8':
	{
		physx::PxTransform pT(20.1391, 89.0057, 19.4672);
		Particle* particle;
		float masa = 0.1;
		float liveTime = 10000;
		particle = new Particle(pT, Vector3(0, 0, 0) , Vector3(0, 0, 0), masa, liveTime, DAMPING, false);
		rS->addGenerator(particle, 100, 0.1);
		break;
		
		break;
	}
	case'9':
	{
		rS->switch2();
		break;
	}*/
	default:
		break;
	}
}

void mousePressed(int button, int state)
{
	if (state == 0 && button == 0) pulsed = true;
	else pulsed = false;
}

void onCollision(physx::PxActor* actor1, physx::PxActor* actor2)
{
	PX_UNUSED(actor1);
	PX_UNUSED(actor2);
}



int main(int, const char*const*)
{
#ifndef OFFLINE_EXECUTION 
	extern void renderLoop();
	renderLoop();
#else
	static const PxU32 frameCount = 100;
	initPhysics(false);
	for(PxU32 i=0; i<frameCount; i++)
		stepPhysics(false);
	cleanupPhysics(false);
#endif

	return 0;
}