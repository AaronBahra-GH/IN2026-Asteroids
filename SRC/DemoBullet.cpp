#include "GameWorld.h"
#include "DemoBullet.h"
#include "BoundingSphere.h"

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/** Constructor. Bullets live for 2s by default. */
DemoBullet::DemoBullet() : GameObject("DemoBullet"), mTimeToLive(2000)
{
}

/** Construct a new bullet with given position, velocity, acceleration, angle, rotation and lifespan. */
DemoBullet::DemoBullet(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r, int ttl) : GameObject("DemoBullet", p, v, a, h, r), mTimeToLive(ttl)
{
}

/** Copy constructor. */
DemoBullet::DemoBullet(const DemoBullet& b) : GameObject(b), mTimeToLive(b.mTimeToLive)
{
}

/** Destructor. */
DemoBullet::~DemoBullet(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update bullet, removing it from game world if necessary. */
void DemoBullet::Update(int t)
{
	// Update position/velocity
	GameObject::Update(t);
	// Reduce time to live
	mTimeToLive = mTimeToLive - t;
	// Ensure time to live isn't negative
	if (mTimeToLive < 0) { mTimeToLive = 0; }
	// If time to live is zero then remove bullet from world
	if (mTimeToLive == 0) {
		if (mWorld) mWorld->FlagForRemoval(GetThisPtr());
	}

}

bool DemoBullet::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() != GameObjectType("Asteroid") && o->GetType() != GameObjectType("Spaceship")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void DemoBullet::OnCollision(const GameObjectList& objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}