#include <ctype.h>

#include <PxPhysicsAPI.h>

#include <vector>

#include "core.hpp"
#include "RenderUtils.hpp"
#include "callbacks.hpp"
#include "Particle.h"
#include <iostream>
#include <list>

std::string display_text = "This is a test";


using namespace physx;

const double DAMPING = 0.998;
PxDefaultAllocator		gAllocator;
PxDefaultErrorCallback	gErrorCallback;

PxFoundation*			gFoundation = NULL;
PxPhysics*				gPhysics	= NULL;


PxMaterial*				gMaterial	= NULL;

PxPvd*                  gPvd        = NULL;

std::list<Particle*>v;
PxDefaultCpuDispatcher*	gDispatcher = NULL;
PxScene*				gScene      = NULL;
ContactReportCallback gContactReportCallback;


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

	// For Solid Rigids +++++++++++++++++++++++++++++++++++++
	PxSceneDesc sceneDesc(gPhysics->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	gDispatcher = PxDefaultCpuDispatcherCreate(2);
	sceneDesc.cpuDispatcher = gDispatcher;
	sceneDesc.filterShader = contactReportFilterShader;
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	gScene = gPhysics->createScene(sceneDesc);



	
	
}


// Function to configure what happens in each step of physics
// interactive: true if the game is rendering, false if it offline
// t: time passed since last call in milliseconds
void stepPhysics(bool interactive, double t)
{
	PX_UNUSED(interactive);


	//for (auto it = v.begin(); it != v.end(); ++it)
	//{
	//	if (v.empty())return;

	//	
	//	physx::PxTransform* trans = (*it)->getPos();

	//	std::cout << trans->p.y<<std::endl;
	//	(*it)->verticalShoot(t);
	//	if (trans->p.y < 50)
	//	{
	//		(*it)->setDestroy();
	//	}
	//	
	///*	auto e = rewards.begin();
	//	while (e != rewards.end())
	//	{
	//		auto c = e;
	//		++e;
	//		deleteReward(*c);

	//		delete (rewardToDelete);
	//rewards.remove(rewardToDelete);
	//	}*/



	//	/*
	//auto e = rewards.begin();
	//while (!nextLevelBool && e != rewards.end())
	//{
	//	auto c = e;
	//	++e;
	//	(*c)->update();

	//}*/
	//	if ((*it)->getDestroy())
	//	{
	//		auto c = it;
	//		if(it!=v.end())
	//		{
	//			++it;
	//		}
	//		
	//		delete *c;
	//		v.remove(*c);	
	//	}

	//
	//}
	//
	auto it = v.begin();
	while (it != v.end())
	{
		auto aux = it;
		++aux;
		physx::PxTransform* trans = (*it)->getPos();
		if (trans->p.y < 20)
		{
			delete* it; v.remove(*it);
		}
		else
		{
			(*it)->integrate(t);
		}
		it = aux;
	}
	gScene->simulate(t);
	gScene->fetchResults(true);
}

// Function to clean data
// Add custom code to the begining of the function
void cleanupPhysics(bool interactive)
{
	PX_UNUSED(interactive);

	// Rigid Body ++++++++++++++++++++++++++++++++++++++++++
	gScene->release();
	gDispatcher->release();
	// -----------------------------------------------------
	gPhysics->release();	
	PxPvdTransport* transport = gPvd->getTransport();
	gPvd->release();
	transport->release();
	auto it = v.begin();
	while (it != v.end())
	{
		auto aux = it;
		++aux;	
		delete* it; v.remove(*it);
		it = aux;
	}
	
	gFoundation->release();
}

// Function called when a key is pressed
void keyPress(unsigned char key, const PxTransform& camera)
{
	PX_UNUSED(camera);

	switch(toupper(key))
	{
	case 'R':
	{	Camera* cam = GetCamera();
		Particle* particle;
		float masa = 1;
		particle = new Particle(cam->getTransform(), cam->getDir() * 100, Vector3(0,-9.8,0),masa, DAMPING);
		particle->getRenderItem()->color = Vector4(1, 0.5, 0, 1);
		particle->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(0.3));
		particle->getRenderItem()->transform = particle->getPos();
		RegisterRenderItem(particle->getRenderItem());
		v.push_back(particle);
	}
		
		break;
	case ' ':
	{
		break;
	}
	default:
		break;
	}
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