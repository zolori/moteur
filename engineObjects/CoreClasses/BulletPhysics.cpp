#include "BulletPhysics.h"

BulletPhysics::BulletPhysics()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	overlappingPairCache = new btDbvtBroadphase();
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -100, 0));
}

BulletPhysics::~BulletPhysics()
{
	for (int i = dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[i];
		btRigidBody* body = btRigidBody::upcast(obj);
		if (body && body->getMotionState())
		{
			delete body->getMotionState();
		}
		dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	//delete collision shapes
	for (int j = 0; j < collisionShapes.size(); j++)
	{
		btCollisionShape* shape = collisionShapes[j];
		collisionShapes[j] = 0;
		delete shape;
	}

	//delete dynamics world
	delete dynamicsWorld;

	//delete solver
	delete solver;

	//delete broadphase
	delete overlappingPairCache;

	//delete dispatcher
	delete dispatcher;

	delete collisionConfiguration;

	collisionShapes.clear();
}

void BulletPhysics::Update(float dt)
{
	dynamicsWorld->stepSimulation(dt, 10);

	//print positions of all objects
	/*for (int j = dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
	{
		btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
		btRigidBody* body = btRigidBody::upcast(obj);
		btTransform trans;
		if (body && body->getMotionState())
		{
			body->getMotionState()->getWorldTransform(trans);
		}
		else
		{
			trans = obj->getWorldTransform();
		}
		printf("world pos object %d = %f,%f,%f\n", j, float(trans.getOrigin().getX()), float(trans.getOrigin().getY()), float(trans.getOrigin().getZ()));
	}*/
}

void BulletPhysics::CreateBox(float xHalfSize, float yHalfSize, float zHalfSize, float xPos, float yPos, float zPos, float Mass)
{
	btCollisionShape* groundShape = new btBoxShape(btVector3(xHalfSize, yHalfSize, zHalfSize));

	collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(xPos, yPos, zPos));

	btScalar mass(Mass);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		groundShape->calculateLocalInertia(mass, localInertia);

	//using motionstate is optional, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, groundShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	//add the body to the dynamics world
	dynamicsWorld->addRigidBody(body);
	rigidbodies.push_back(body);
}

void BulletPhysics::CreateSphere(float radius, float xPos, float yPos, float zPos, float Mass)
{
	btCollisionShape* colShape = new btSphereShape(radius);
	collisionShapes.push_back(colShape);

	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(xPos, yPos, zPos));

	btScalar mass(Mass);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic)
		colShape->calculateLocalInertia(mass, localInertia);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, colShape, localInertia);
	btRigidBody* body = new btRigidBody(rbInfo);

	dynamicsWorld->addRigidBody(body);
	rigidbodies.push_back(body);
}

void BulletPhysics::CreatePlane()
{
	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setOrigin(btVector3(0, -1, 0));
	btStaticPlaneShape* plane = new btStaticPlaneShape(btVector3(0, -1, 0), 0);
	btMotionState* motion = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo info(0.0, motion, plane);
	btRigidBody* body = new btRigidBody(info);
	body->setCollisionFlags(btCollisionObject::CF_STATIC_OBJECT);
	dynamicsWorld->addRigidBody(body);
	rigidbodies.push_back(body);
}
