#include "RigidBodySystem.h"
#include <math.h>
RigidBodySystem::RigidBodySystem(PxPhysics* gPhysics, PxScene* gScene)
{
	_gPhysics = gPhysics;
	_gScene = gScene;



	rFR = new RigidForceRegistry();

	pfR = new ParticleForceRegistry();

#pragma region Creacion de la mesa
	//Tablero principal
	PxRigidStatic* table;

	table = gPhysics->createRigidStatic(PxTransform(0, 0, 0));
	PxShape* shape = CreateShape(PxBoxGeometry(50, 0.1, 100));
	table->attachShape(*shape);
	gScene->addActor(*table);
	table->setName("table");
	RenderItem* item;
	item = new RenderItem(shape, table, { 0,0.01,0,1 });


	//Bordes


	//ARRIBA
	PxRigidStatic* side1;
	side1 = gPhysics->createRigidStatic(PxTransform(0, 1, -102.7));
	PxShape* shape1 = CreateShape(PxBoxGeometry(40, 3, 4.75));
	side1->attachShape(*shape1);
	gScene->addActor(*side1);
	side1->setName("side1");
	RenderItem* item1;
	item1 = new RenderItem(shape1, side1, { 0.5,0.25,0,1 });

	//ABAJO
	PxRigidStatic* side2;
	side2 = gPhysics->createRigidStatic(PxTransform(0, 1, 102.3));
	PxShape* shape2 = CreateShape(PxBoxGeometry(40, 3, 4.75));
	side2->attachShape(*shape2);
	gScene->addActor(*side2);
	side2->setName("side2");
	RenderItem* item2;
	item2 = new RenderItem(shape2, side2, { 0.5,0.25,0,1 });


	//DERECHA
	PxRigidStatic* side3;
	side3 = gPhysics->createRigidStatic(PxTransform(50, 1, 48.75));
	PxTransform p(52.8, 1, 48.25);
	p.q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	side3->setGlobalPose(p);
	PxShape* shape3 = CreateShape(PxBoxGeometry(41.625, 3, 4.8));
	side3->attachShape(*shape3);
	gScene->addActor(*side3);
	side3->setName("side3");
	RenderItem* item3;
	item3 = new RenderItem(shape3, side3, { 0.5,0.25,0,1 });


	PxRigidStatic* side4;
	side4 = gPhysics->createRigidStatic(PxTransform(-50, 1, 48.75));
	PxTransform p2(-52.8, 1, 48.25);
	p2.q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	side4->setGlobalPose(p2);
	PxShape* shape4 = CreateShape(PxBoxGeometry(41.625, 3, 4.8));
	side4->attachShape(*shape4);
	gScene->addActor(*side4);
	side4->setName("side4");
	RenderItem* item4;
	item4 = new RenderItem(shape4, side4, { 0.5,0.25,0,1 });



	PxRigidStatic* side5;
	side5 = gPhysics->createRigidStatic(PxTransform(-50, 1, -48.75));
	PxTransform p3(-52.8, 1, -48.25);
	p3.q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	side5->setGlobalPose(p3);
	PxShape* shape5 = CreateShape(PxBoxGeometry(41.625, 3, 4.8));
	side5->attachShape(*shape5);
	gScene->addActor(*side5);
	side5->setName("side5");
	RenderItem* item5;
	item5 = new RenderItem(shape5, side5, { 0.5,0.25,0,1 });

	PxRigidStatic* side6;
	side6 = gPhysics->createRigidStatic(PxTransform(50, 1, -48.75));
	PxTransform p4(52.8, 1, -48.25);
	p4.q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	side6->setGlobalPose(p4);
	PxShape* shape6 = CreateShape(PxBoxGeometry(41.625, 3, 4.8));
	side6->attachShape(*shape6);
	gScene->addActor(*side6);
	side6->setName("side6");
	RenderItem* item6;
	item6 = new RenderItem(shape6, side6, { 0.5,0.25,0,1 });

	//Bocas Derecha-Arriba
	PxRigidStatic* side7;
	side7 = gPhysics->createRigidStatic(PxTransform(52.9, 1, -91.96));
	PxTransform p5(52.9, 1, -91.96);
	p5.q = PxQuat(PxPi / 4, PxVec3(0, 1, 0));
	side7->setGlobalPose(p5);
	PxShape* shape7 = CreateShape(PxBoxGeometry(5, 3, 2));
	side7->attachShape(*shape7);
	gScene->addActor(*side7);
	side7->setName("side7");
	RenderItem* item7;
	item7 = new RenderItem(shape7, side7, { 0.5,0.25,0,1 });



	PxRigidStatic* side8;
	side8 = gPhysics->createRigidStatic(PxTransform(42.2, 1, -103));
	PxTransform p6(42.2, 1, -103);
	p6.q = PxQuat(PxPi / 4, PxVec3(0, 1, 0));
	side8->setGlobalPose(p6);
	PxShape* shape8 = CreateShape(PxBoxGeometry(5, 3, 2));
	side8->attachShape(*shape8);
	gScene->addActor(*side8);
	side8->setName("side8");
	RenderItem* item8;
	item8 = new RenderItem(shape8, side8, { 0.5,0.25,0,1 });

	//Bocas Izquierda Arriba
	PxRigidStatic* side9;
	side9 = gPhysics->createRigidStatic(PxTransform(-50, 1, -100));
	PxTransform p7(-42.2, 1, -103);
	p7.q = PxQuat(PxPi / 4 + PxPi / 2, PxVec3(0, 1, 0));
	side9->setGlobalPose(p7);
	PxShape* shape9 = CreateShape(PxBoxGeometry(5, 3, 2));
	side9->attachShape(*shape9);
	gScene->addActor(*side9);
	side9->setName("side9");
	RenderItem* item9;
	item9 = new RenderItem(shape9, side9, { 0.5,0.25,0,1 });

	PxRigidStatic* side10;
	side10 = gPhysics->createRigidStatic(PxTransform(52.9, 1, -91.96));
	PxTransform p8(-52.9, 1, -91.96);
	p8.q = PxQuat(PxPi / 4 + PxPi / 2, PxVec3(0, 1, 0));
	side10->setGlobalPose(p8);
	PxShape* shape10 = CreateShape(PxBoxGeometry(5, 3, 2));
	side10->attachShape(*shape10);
	gScene->addActor(*side10);
	side10->setName("side10");
	RenderItem* item10;
	item10 = new RenderItem(shape10, side10, { 0.5,0.25,0,1 });


	//Bocas Abajo Derecha
	PxRigidStatic* side11;
	side11 = gPhysics->createRigidStatic(PxTransform(52.9, 1, -91.96));
	PxTransform p9(52.9, 1, 91.96);
	p9.q = PxQuat(PxPi * 2 - PxPi / 4, PxVec3(0, 1, 0));
	side11->setGlobalPose(p9);
	PxShape* shape11 = CreateShape(PxBoxGeometry(5, 3, 2));
	side11->attachShape(*shape11);
	gScene->addActor(*side11);
	side11->setName("side11");
	RenderItem* item11;
	item11 = new RenderItem(shape11, side11, { 0.5,0.25,0,1 });



	PxRigidStatic* side12;
	side12 = gPhysics->createRigidStatic(PxTransform(42.2, 1, -103));
	PxTransform p10(42.2, 1, 103);
	p10.q = PxQuat(PxPi * 2 - PxPi / 4, PxVec3(0, 1, 0));
	side12->setGlobalPose(p10);
	PxShape* shape12 = CreateShape(PxBoxGeometry(5, 3, 2));
	side8->attachShape(*shape12);
	gScene->addActor(*side12);
	side12->setName("side8");
	RenderItem* item12;
	item12 = new RenderItem(shape12, side12, { 0.5,0.25,0,1 });



	//Bocas Abajo Izquierda

	PxRigidStatic* side13;
	side13 = gPhysics->createRigidStatic(PxTransform(-50, 1, 100));
	PxTransform p11(-42.2, 1, 103);
	p11.q = PxQuat(PxPi - (PxPi / 4 + PxPi / 2), PxVec3(0, 1, 0));
	side13->setGlobalPose(p11);
	PxShape* shape13 = CreateShape(PxBoxGeometry(5, 3, 2));
	side13->attachShape(*shape13);
	gScene->addActor(*side13);
	side13->setName("side9");
	RenderItem* item13;
	item13 = new RenderItem(shape13, side13, { 0.5,0.25,0,1 });

	PxRigidStatic* side14;
	side14 = gPhysics->createRigidStatic(PxTransform(52.9, 1, 91.96));
	PxTransform p12(-52.9, 1, 91.96);
	p12.q = PxQuat(PxPi - (PxPi / 4 + PxPi / 2), PxVec3(0, 1, 0));
	side14->setGlobalPose(p12);
	PxShape* shape14 = CreateShape(PxBoxGeometry(5, 3, 2));
	side14->attachShape(*shape14);
	gScene->addActor(*side14);
	side14->setName("side10");
	RenderItem* item14;
	item14 = new RenderItem(shape14, side14, { 0.5,0.25,0,1 });


	//Bocas Centro Izquierda
	PxRigidStatic* side15;
	side15 = gPhysics->createRigidStatic(PxTransform(52.9, 1, 91.96));
	PxTransform p13(-54, 1, 9.22);
	p13.q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	side15->setGlobalPose(p13);
	PxShape* shape15 = CreateShape(PxBoxGeometry(2.5, 3, 2));
	side15->attachShape(*shape15);
	gScene->addActor(*side15);
	side15->setName("side10");
	RenderItem* item15;
	item15 = new RenderItem(shape15, side15, { 0.5,0.25,0,1 });


	PxRigidStatic* side16;
	side16 = gPhysics->createRigidStatic(PxTransform(52.9, 1, 91.96));
	PxTransform p14(-54, 1, -9.22);
	p14.q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	side16->setGlobalPose(p14);
	PxShape* shape16 = CreateShape(PxBoxGeometry(2.5, 3, 2));
	side16->attachShape(*shape16);
	gScene->addActor(*side16);
	side16->setName("side10");
	RenderItem* item16;
	item16 = new RenderItem(shape16, side16, { 0.5,0.25,0,1 });


	//Bocas Centro Derecha
	PxRigidStatic* side17;
	side17 = gPhysics->createRigidStatic(PxTransform(52.9, 1, 91.96));
	PxTransform p15(54, 1, 9.22);
	p15.q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	side17->setGlobalPose(p15);
	PxShape* shape17 = CreateShape(PxBoxGeometry(2.5, 3, 2));
	side17->attachShape(*shape17);
	gScene->addActor(*side17);
	side17->setName("side10");
	RenderItem* item17;
	item17 = new RenderItem(shape17, side17, { 0.5,0.25,0,1 });


	PxRigidStatic* side18;
	side18 = gPhysics->createRigidStatic(PxTransform(52.9, 1, 91.96));
	PxTransform p16(54, 1, -9.22);
	p16.q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	side18->setGlobalPose(p16);
	PxShape* shape18 = CreateShape(PxBoxGeometry(2.5, 3, 2));
	side18->attachShape(*shape18);
	gScene->addActor(*side18);
	side18->setName("side10");
	RenderItem* item18;
	item18 = new RenderItem(shape18, side18, { 0.5,0.25,0,1 });




	//Filos Dorados
	PxRigidStatic* side19;
	side19 = gPhysics->createRigidStatic(PxTransform(52.9, 1, 91.96));
	PxTransform p17(60, 1, 0);
	side19->setGlobalPose(p17);
	PxShape* shape19 = CreateShape(PxBoxGeometry(2.5, 3, 110));
	side19->attachShape(*shape19);
	gScene->addActor(*side19);
	side19->setName("side10");
	RenderItem* item19;
	item19 = new RenderItem(shape19, side19, { 0.9373,0.7216,0,627 });



	PxRigidStatic* side20;
	side20 = gPhysics->createRigidStatic(PxTransform(0, 1, -100));
	PxShape* shape20 = CreateShape(PxBoxGeometry(2.5, 3, 62.5));
	PxTransform p18(0, 1, -110);
	p18.q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	side20->setGlobalPose(p18);
	side20->attachShape(*shape20);
	gScene->addActor(*side20);
	side20->setName("side1");
	RenderItem* item20;
	item20 = new RenderItem(shape20, side20, { 0.9373,0.7216,0,627 });


	PxRigidStatic* side21;
	side21 = gPhysics->createRigidStatic(PxTransform(52.9, 1, 91.96));
	PxTransform p19(-60, 1, 0);
	side21->setGlobalPose(p19);
	PxShape* shape21 = CreateShape(PxBoxGeometry(2.5, 3, 110));
	side21->attachShape(*shape21);
	gScene->addActor(*side21);
	side21->setName("side10");
	RenderItem* item21;
	item21 = new RenderItem(shape21, side21, { 0.9373,0.7216,0,627 });



	PxRigidStatic* side22;
	side22 = gPhysics->createRigidStatic(PxTransform(0, 1, -100));
	PxShape* shape22 = CreateShape(PxBoxGeometry(2.5, 3, 62.5));
	PxTransform p20(0, 1, 110);
	p20.q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	side22->setGlobalPose(p20);
	side22->attachShape(*shape22);
	gScene->addActor(*side22);
	side22->setName("side1");
	RenderItem* item22;
	item22 = new RenderItem(shape22, side22, { 0.9373,0.7216,0,627 });



	PxRigidStatic* side23;
	side23 = gPhysics->createRigidStatic(PxTransform(0, 1, 0));
	PxShape* shape23 = CreateShape(PxBoxGeometry(120, 0.1, 62.5));
	PxTransform p21(0, 5, 0);
	p21.q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	side23->setGlobalPose(p21);
	side23->attachShape(*shape23);
	gScene->addActor(*side23);
	side22->setName("side1");

	RenderItem* item23;
	item23 = new RenderItem(shape23, side23, { 0.9373,0.7216,0,627 });
	item23->release();


	PxRigidStatic* side24;
	side24 = gPhysics->createRigidStatic(PxTransform(0, 1, -105.3));
	PxShape* shape24 = CreateShape(PxBoxGeometry(45.5, 3, 2));
	side24->attachShape(*shape24);
	gScene->addActor(*side24);
	side24->setName("side1");
	RenderItem* item24;
	item24 = new RenderItem(shape24, side24, { 0.5,0.25,0,1 });

	PxRigidStatic* side25;
	side25 = gPhysics->createRigidStatic(PxTransform(0, 1, 105.3));
	PxShape* shape25 = CreateShape(PxBoxGeometry(45.5, 3, 2));
	side25->attachShape(*shape25);
	gScene->addActor(*side25);
	side25->setName("side1");
	RenderItem* item25;
	item25 = new RenderItem(shape25, side25, { 0.5,0.25,0,1 });


	PxRigidStatic* side26;
	side26 = gPhysics->createRigidStatic(PxTransform(50, 1, 48.75));
	PxTransform p22(55.3, 1, 83.45);
	p22.q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	side26->setGlobalPose(p22);
	PxShape* shape26 = CreateShape(PxBoxGeometry(10, 3, 2));
	side26->attachShape(*shape26);
	gScene->addActor(*side26);
	side26->setName("side3");
	RenderItem* item26;
	item26 = new RenderItem(shape26, side26, { 0.5,0.25,0,1 });


	PxRigidStatic* side27;
	side27 = gPhysics->createRigidStatic(PxTransform(50, 1, 48.75));
	PxTransform p23(-55.3, 1, 83.45);
	p23.q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	side27->setGlobalPose(p23);
	PxShape* shape27 = CreateShape(PxBoxGeometry(10, 3, 2));
	side27->attachShape(*shape27);
	gScene->addActor(*side27);
	side27->setName("side3");
	RenderItem* item27;
	item27 = new RenderItem(shape27, side27, { 0.5,0.25,0,1 });



	PxRigidStatic* side28;
	side28 = gPhysics->createRigidStatic(PxTransform(50, 1, 48.75));
	PxTransform p24(-55.3, 1, -83.45);
	p24.q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	side28->setGlobalPose(p24);
	PxShape* shape28 = CreateShape(PxBoxGeometry(10, 3, 2));
	side28->attachShape(*shape28);
	gScene->addActor(*side28);
	side28->setName("side3");
	RenderItem* item28;
	item28 = new RenderItem(shape28, side28, { 0.5,0.25,0,1 });


	PxRigidStatic* side29;
	side29 = gPhysics->createRigidStatic(PxTransform(50, 1, 48.75));
	PxTransform p25(55.3, 1, -83.45);
	p25.q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	side29->setGlobalPose(p25);
	PxShape* shape29 = CreateShape(PxBoxGeometry(10, 3, 2));
	side29->attachShape(*shape29);
	gScene->addActor(*side29);
	side29->setName("side3");
	RenderItem* item29;
	item29 = new RenderItem(shape29, side29, { 0.5,0.25,0,1 });

	whiteStrip = new RenderItem();
	whiteStrip->color = Vector4(1, 1, 1, 1);
	PxTransform* pWhite = new PxTransform(0, 0.1, 60);
	posicionesSaque.push_back(pWhite);
	whiteStrip->transform = pWhite;
	whiteStrip->shape = CreateShape(physx::PxBoxGeometry(50, 0.2, 0.1));
	RegisterRenderItem(whiteStrip);

#pragma endregion

#pragma region Creacion de las bolas
	bolas.push_back(new Bola("AMARILLO", Vector3(20, 0, pWhite->p.z), gPhysics, gScene));
	bolas.push_back(new Bola("MARRON", Vector3(0, 0, pWhite->p.z), gPhysics, gScene));
	bolas.push_back(new Bola("VERDE", Vector3(-20, 1, pWhite->p.z), gPhysics, gScene));


	blanca = new Bola("BLANCO", Vector3(0, 1, pWhite->p.z + 10), gPhysics, gScene);

	bolas.push_back(blanca);


	bolas.push_back(new Bola("AZUL", Vector3(0, 0, 0), gPhysics, gScene));
	bolas.push_back(new Bola("ROSA", Vector3(0, 0, -pWhite->p.z), gPhysics, gScene));


	bolas.push_back(new Bola("ROJO", Vector3(0, 0, -pWhite->p.z - 2), gPhysics, gScene));

	bolas.push_back(new Bola("ROJO", Vector3(1, 0, -pWhite->p.z - 4), gPhysics, gScene));
	bolas.push_back(new Bola("ROJO", Vector3(-1, 0, -pWhite->p.z - 4), gPhysics, gScene));

	bolas.push_back(new Bola("ROJO", Vector3(-2, 0, -pWhite->p.z - 6), gPhysics, gScene));
	bolas.push_back(new Bola("ROJO", Vector3(0, 0, -pWhite->p.z - 6), gPhysics, gScene));
	bolas.push_back(new Bola("ROJO", Vector3(2, 0, -pWhite->p.z - 6), gPhysics, gScene));

	bolas.push_back(new Bola("ROJO", Vector3(-3, 0, -pWhite->p.z - 8), gPhysics, gScene));
	bolas.push_back(new Bola("ROJO", Vector3(-1, 0, -pWhite->p.z - 8), gPhysics, gScene));
	bolas.push_back(new Bola("ROJO", Vector3(1, 0, -pWhite->p.z - 8), gPhysics, gScene));
	bolas.push_back(new Bola("ROJO", Vector3(3, 0, -pWhite->p.z - 8), gPhysics, gScene));


	bolas.push_back(new Bola("ROJO", Vector3(-4, 0, -pWhite->p.z - 10), gPhysics, gScene));
	bolas.push_back(new Bola("ROJO", Vector3(-2, 0, -pWhite->p.z - 10), gPhysics, gScene));
	bolas.push_back(new Bola("ROJO", Vector3(0, 0, -pWhite->p.z - 10), gPhysics, gScene));
	bolas.push_back(new Bola("ROJO", Vector3(2, 0, -pWhite->p.z - 10), gPhysics, gScene));
	bolas.push_back(new Bola("ROJO", Vector3(4, 0, -pWhite->p.z - 10), gPhysics, gScene));




	bolas.push_back(new Bola("NEGRO", Vector3(0, 0, -pWhite->p.z - 25), gPhysics, gScene));
#pragma endregion

#pragma region Elementos adicionales de la mesa
	RenderItem* cajaSaqueBottom = new RenderItem();
	cajaSaqueBottom->color = Vector4(1, 1, 1, 1);
	PxTransform* pBottom = new PxTransform(0, 0.1, 80);
	cajaSaqueBottom->transform = pBottom;
	cajaSaqueBottom->shape = CreateShape(physx::PxBoxGeometry(20, 0.2, 0.1));
	RegisterRenderItem(cajaSaqueBottom);
	posicionesSaque.push_back(pBottom);

	RenderItem* cajaSaqueLeft = new RenderItem();
	cajaSaqueLeft->color = Vector4(1, 1, 1, 1);
	PxTransform* pLeft = new PxTransform(-20, 0.1, 70);
	pLeft->q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	cajaSaqueLeft->transform = pLeft;
	cajaSaqueLeft->shape = CreateShape(physx::PxBoxGeometry(10, 0.2, 0.1));
	RegisterRenderItem(cajaSaqueLeft);
	posicionesSaque.push_back(pLeft);


	RenderItem* cajaSaqueRigth = new RenderItem();
	cajaSaqueRigth->color = Vector4(1, 1, 1, 1);
	PxTransform* pRight = new PxTransform(20, 0.2, 70);
	pRight->q = PxQuat(PxPi / 2, PxVec3(0, 1, 0));
	cajaSaqueRigth->transform = pRight;
	cajaSaqueRigth->shape = CreateShape(physx::PxBoxGeometry(10, 0.2, 0.1));
	RegisterRenderItem(cajaSaqueRigth);
	posicionesSaque.push_back(pRight);



	RenderItem* fondoMesa = new RenderItem();
	fondoMesa->color = Vector4(0, 0, 0, 0);
	PxTransform* fondo = new PxTransform(0, -2, 0);

	fondoMesa->transform = fondo;
	fondoMesa->shape = CreateShape(physx::PxBoxGeometry(60, 0.2, 110));
	RegisterRenderItem(fondoMesa);
#pragma endregion

#pragma region Palo
	palo = new Palo(Vector3(blanca->getPos().x, 1, blanca->getPos().z + 10), gPhysics, gScene, blanca, 8);
#pragma endregion

#pragma region Generadores de fuerza
	torbellino = new GeneradorTorbellino(Vector3(0, 1, 0), 5, Vector3(0, 0, 0), Vector3(30, 30, 30) * 3);
	explosion = new ExplosionGenerator(1000, 300, Vector3{ 0,20,0 }, 900, 100);
	aF = new AnchoredSpringFG(5, 10, Vector3(0, 70, 0));
	Particle* particle = new Particle(physx::PxTransform(-0, 100, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 10, 200, DAMPING, false);
	particle->getRenderItem()->color = Vector4(1, 0.5, 0, 1);
	particle->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(2));
	particle->getRenderItem()->transform = particle->getPos();
	RegisterRenderItem(particle->getRenderItem());

	pfR->addRegistry(aF, particle);
	particles.push_back(particle);
#pragma endregion


	cout << "Puntuacion: " << puntuacion << endl;
	cout << "Tiros restantes: " << tirosPosibles << endl;

}

RigidBodySystem::~RigidBodySystem()
{

	for (auto it : generators)
	{
		delete it;
	}

	for (auto it : generatorsParticles)
	{
		delete it;
	}
	for (auto it : particles)
	{
		delete it;
	}
	for (auto it : fireworks)
	{
		delete it;
	}

	for (auto it : bolas)
	{
		delete it;
	}
	delete torbellino;
}


void RigidBodySystem::addDynamicObject(float Cestatico, float Cdinamico, float Elastico, PxVec3 inertiaT, Vector3 dimension, Vector4 color, Vector3 transform, Vector3 velocity, Vector3 angularvelocity, float density, int timetoleave)
{
	RigidBody solid;
	PxRigidDynamic* new_solid;

	PxMaterial* gMaterial = _gPhysics->createMaterial(Cestatico, Cdinamico, Elastico);


	new_solid = _gPhysics->createRigidDynamic(PxTransform(transform));

	new_solid->setLinearVelocity(velocity);
	new_solid->setAngularVelocity(angularvelocity);

	solid.shape = CreateShape(PxBoxGeometry(dimension.x, dimension.y, dimension.z), gMaterial);
	new_solid->attachShape(*solid.shape);
	PxRigidBodyExt::updateMassAndInertia(*new_solid, density);

	new_solid->setMassSpaceInertiaTensor(inertiaT);
	solid.item = new RenderItem(solid.shape, new_solid, color);
	_gScene->addActor(*new_solid);

	solid._rb = new_solid;
	solid.timeUntilDeath = timetoleave;

	for (auto it : fG)
	{
		rFR->addRegistry(it, solid);
	}

	solids.push_back(solid);
}


void RigidBodySystem::update(double t)
{



#pragma region Actualizamos multimaps
	pfR->updateForces(t);
	rFR->updateForces(t);

#pragma endregion


#pragma region Condiciones de victoria / derrota
	if (tirosPosibles == 0 && !end)
	{
		cout << "HAS PERDIDO" << endl;
		for (auto it : bolas)
		{
			RigidBody r;
			r.item = it->getItem();
			r.shape = it->getShape();
			r.timeAlive = 0;
			r.timeUntilDeath = 10;
			r._rb = it->getBola();
			rFR->addRegistry(torbellino, r);
		}
		end = true;
	}
	else if (bolasRojas == 0 && !end)
	{
		cout << "HAS GANADO" << endl;
		cout << "Con una puntuacion de: " << puntuacion << endl;
		for (auto it : bolas)
		{
			RigidBody r;
			r.item = it->getItem();
			r.shape = it->getShape();
			r.timeAlive = 0;
			r.timeUntilDeath = 10;
			r._rb = it->getBola();
			rFR->addRegistry(torbellino, r);
		}
		end = true;
	}

#pragma endregion

#pragma region Actualizacion del tiempo tras golpeo

	if (golpeado)
		segundosTrasGolpe += t;
#pragma endregion

#pragma region Actualizacion del estado de las bolas
	auto it2 = bolas.begin();
	while (it2 != bolas.end() && !end)
	{

		if ((*it2)->getBola()->getGlobalPose().p.y < -5)
		{
			if ((*it2)->getColor() != "BLANCO")
			{
				refreshConsole();
				if (aF->getMul())puntuacion += (*it2)->getPuntuacion() * 2;
				else puntuacion += (*it2)->getPuntuacion();
				cout << "Puntuacion: " << puntuacion << endl;
				cout << "Tiros restantes: " << tirosPosibles << endl;
				refreshConsole();
				onScoring();

				if ((*it2)->getColor() != "ROJO")
				{
					(*it2)->returnToInitialPlace();
					++it2;
				}
				else
				{

					explotado = false;

					rFR->deleteForceRegistry(explosion);
			
					delete* it2;
					it2 = bolas.erase(it2);
					bolasRojas--;

				}
			}
			else
			{
				cout << "HAS PERDIDO" << endl;
			}
		}
		else
		{
			it2++;
		}


	}

#pragma endregion

#pragma region Condicion de parada de las bolas / comprobacion de existencia de falta
	if (segundosTrasGolpe > 10)
	{
		for (auto it = bolas.begin(); it != bolas.end(); it++)
		{
			(*it)->stopBola();
		}
		rotatePalo();
		puntuacionTrasGolpe = puntuacion;
		puedeDisparar = true;
		segundosTrasGolpe = 0;
		golpeado = false;

		if (puntuacionTrasGolpe == puntuacionAntesGolpe)
		{
			refreshConsole();
			tirosPosibles--;
			cout << "Puntuacion: " << puntuacion << endl;
			cout << "Tiros restantes: " << tirosPosibles << endl;

		}
	}
#pragma endregion

#pragma region Actualizacion geneadores

	for (auto it = generators.begin(); it != generators.end();)
	{
		if ((*it)->finished())
		{
			it = generators.erase(it);
		}
		else
		{
			(*it)->update(t);
			it++;
		}
	}

	if (FxCreated)
	{
		Fx->update(t);
	}

#pragma endregion




#pragma region Actualizamos solidos (P5)
	for (auto it = solids.begin(); it != solids.end(); )
	{
		it->timeAlive += t;
		if (it->timeAlive >= it->timeUntilDeath)
		{
			rFR->deleteSolidRegistry(*it);
			_gScene->removeActor(*(it->_rb));
			it->_rb->detachShape(*it->shape);
			it->item->release();
			it->shape->release();
			it = solids.erase(it);
		}
		else
		{
			++it;
		}
	}

#pragma endregion



#pragma region Actualizamos particulas
	auto it = particles.begin();

	while (it != particles.end())
	{
		auto aux = it;
		++aux;
		physx::PxTransform* trans = (*it)->getPos();

		if (trans->p.y < -100 || trans->p.y > 500 || (*it)->getTimeAlive() > (*it)->getDeathTime())
		{
			delete* it; particles.remove(*it);
		}
		else
		{
			(*it)->integrate(t);


		}
		it = aux;
	}


	auto ai = fireworks.begin();
	while (ai != fireworks.end())
	{

		auto aux = ai;
		++aux;

		physx::PxTransform* trans = (*ai)->getPos();
		if (trans->p.y < -10 || (*ai)->getTimeAlive() >(*ai)->getDeathTime())
		{
			delete* ai; fireworks.remove(*ai);
		}
		else if ((*ai)->getStatus())
		{

			physx::PxTransform p(Vector3((*ai)->getPos()->p.x, (*ai)->getPos()->p.y, (*ai)->getPos()->p.z));
			Particle* particle = new Particle(p, Vector3(0), Vector3(0, -3.0, 0), 1, 1000, DAMPING, false);
			addGenerator2(particle, 100, 0.001);
			delete* ai; fireworks.remove(*ai);
		}
		else
		{
			(*ai)->integrate(t);
		}
		ai = aux;
	}

#pragma endregion


}

void RigidBodySystem::addGenerator(Particle* p, int nParticles, float frecuency)
{
	SolidGenerator* gen = new SolidGenerator(p, nParticles, frecuency, this, true, 0);
	generators.push_back(gen);
}

void RigidBodySystem::addGenerator2(Particle* p, int nParticles, float frecuency)
{
	SolidGenerator* gen = new SolidGenerator(p, nParticles, frecuency, this, false, 1);
	generators.push_back(gen);
}


void RigidBodySystem::addGeneratorCharge(int nParticles, float frecuency)
{

	if (FxCreated)
	{
		Fx->moreParticles(nParticles);
	}
	else
	{
		Particle* particle;

		float masa = 0.1;
		float liveTime = 10000;
		particle = new Particle(*palo->getPos(), Vector3(0, 0, 0), Vector3(0, 0, 0), masa, liveTime, DAMPING, false);


		SolidGenerator* gen = new SolidGenerator(particle, nParticles, frecuency, this, false, 0);
		Fx = gen;
		FxCreated = true;
	}

}
void RigidBodySystem::allowTorbellino()
{
	fG.push_back(torbellino);
	for (auto it : solids)
	{
		rFR->addRegistry(torbellino, it);
	}
}

void RigidBodySystem::ExplotaTodo()
{
	if (!explotado)
	{
		explotado = true;
		for (auto it : bolas)
		{
			RigidBody r;
			r.item = it->getItem();
			r.shape = it->getShape();
			r.timeAlive = 0;
			r.timeUntilDeath = 10;
			r._rb = it->getBola();

			rFR->addRegistry(explosion, r);
		}
	}
	else
	{
		explotado = false;

		rFR->deleteForceRegistry(explosion);

	}


}
void RigidBodySystem::denyTorbellino()
{
	fG.remove(torbellino);
	rFR->deleteForceRegistry(torbellino);
}
void RigidBodySystem::switch2()
{
	if (active)
	{
		denyTorbellino();
	}
	else
		allowTorbellino();

	active = !active;
}

void RigidBodySystem::configuraCamara()
{
	switch (posicion)
	{
	case 1:
		GetCamera()->setTransform(&PxTransform(0.316627, 21.8175, 112.645));
		GetCamera()->setDir(&PxTransform(0.02, -0.154267, -0.987827));
		break;
	case 2:
		GetCamera()->setTransform(&PxTransform(-89.6938, 35.2356, 2.84123));
		GetCamera()->setDir(&PxTransform(0.944456, -0.328637, 0.00029408));
		break;
	case 3:
		GetCamera()->setDir(&PxTransform(-0.00002, -1, -0.002222));
		GetCamera()->setTransform(&PxTransform(0, 200, 0));
		break;
	case 4:
		GetCamera()->setDir(&PxTransform(-0.998871, -0.0464056, -0.0101474));
		GetCamera()->setTransform(&PxTransform(97.6517, 26.6167, -1.18714));
		break;
	case 5:
		GetCamera()->setDir(&PxTransform(-0.01898, -0.125275, 0.99194));
		GetCamera()->setTransform(&PxTransform(-0.759642, 12.7665, -111.752));
		break;


	default:
		break;
	}
	posicion = posicion % 5 + 1;
}

void RigidBodySystem::moveBlanca(const Direcciones& dir)
{
	switch (dir)
	{
	case Direcciones::UP:
	{
		if (blanca->getPos().z > posicionesSaque[0]->p.z)
		{
			blanca->setPos(blanca->getPos() + Vector3(0, 0, -1));
			rotatePalo();
		}

		break;
	}
	case Direcciones::DOWN:
	{
		if (blanca->getPos().z < posicionesSaque[1]->p.z)
		{
			blanca->setPos(blanca->getPos() + Vector3(0, 0, 1));
			rotatePalo();
		}
		break;
	}

	case Direcciones::LEFT:
	{
		if (blanca->getPos().x > posicionesSaque[2]->p.x)
		{
			blanca->setPos(blanca->getPos() + Vector3(-1, 0, 0));
			rotatePalo();
		}
		break;
	}

	case Direcciones::RIGHT:
	{
		if (blanca->getPos().x < posicionesSaque[3]->p.x)
		{
			blanca->setPos(blanca->getPos() + Vector3(1, 0, 0));
			rotatePalo();
		}
		break;
	}
	default:
		break;
	}
}

void RigidBodySystem::revientaPelota()
{
	if (FxCreated)
	{
		delete Fx; lastHoldValue = 0;
		FxCreated = false;
	}
	if (holdValue != 0)
	{
		puntuacionAntesGolpe = puntuacion;
		golpeado = true;
		FuerzaInstantanea(blanca, Vector3(cos(palo->getAngles()), 0, sin(palo->getAngles())) * holdValue * -30);
		blanca->setDisparada();
		puedeDisparar = false;
		firstMove = false;
	}
}

void RigidBodySystem::rotatePalo()
{
	palo->updateBlanca();
	palo->rotateAroundBola();
}

void RigidBodySystem::setHoldValue(float newValue)
{
	if (lastHoldValue + 10 < holdValue)
	{

		addGeneratorCharge(1000, 0);
		lastHoldValue = holdValue;
	}
	holdValue = newValue;
}

void RigidBodySystem::onScoring()
{
	Firework* firework;
	firework = new Firework(PxTransform(0, 0, 0), Vector3(0, 1, 0) * 250, Vector3(0, -9.8, 0), 1, 2, DAMPING, 100, 1000, false);
	firework->getRenderItem()->color = Vector4(1, 0.5, 0, 1);
	firework->getRenderItem()->shape = CreateShape(physx::PxSphereGeometry(0.2));
	firework->getRenderItem()->transform = firework->getPos();
	RegisterRenderItem(firework->getRenderItem());
	fireworks.push_back(firework);

}

bool RigidBodySystem::poderDisparar() { return puedeDisparar; }