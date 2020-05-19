#include "GameUtil.h"
#include "GameWorld.h"
#include "DemoBullet.h"
#include "DemoSpaceship.h"
#include "BoundingSphere.h"

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/**  Default constructor. */
DemoSpaceship::DemoSpaceship()
	: GameObject("DemoSpaceship"), mDemoThrust(0)
{
}

/** Construct a spaceship with given position, velocity, acceleration, angle, and rotation. */
DemoSpaceship::DemoSpaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("Spaceship", p, v, a, h, r), mDemoThrust(0)
{
}

/** Copy constructor. */
DemoSpaceship::DemoSpaceship(const DemoSpaceship& s) : GameObject(s), mDemoThrust(0)
{
}

/** Destructor. */
DemoSpaceship::~DemoSpaceship(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update this spaceship. */
void DemoSpaceship::Update(int t)
{
	// Call parent update function
	GameObject::Update(t);
}

/** Render this spaceship. */
void DemoSpaceship::Render(void)
{

	if (mDemoSpaceshipShape.get() != NULL)
	{
		mDemoSpaceshipShape->Render();
	}

	// If ship is thrusting
	if ((mDemoThrust > 0) && (mDemoThrusterShape.get() != NULL))
	{
		mDemoThrusterShape->Render();
	}


	// Enable lighting
	//glEnable(GL_LIGHTING);
	GameObject::Render();

}

/** Fire the rockets. */
void DemoSpaceship::Thrust(float t)
{
	mDemoThrust = t;
	// Increase acceleration in the direction of ship
	mAcceleration.x = mDemoThrust * cos(DEG2RAD*mAngle);
	mAcceleration.y = mDemoThrust * sin(DEG2RAD*mAngle);
}

/** Set the rotation. */
void DemoSpaceship::Rotate(float r)
{
	mRotation = r;
}

/** Shoot a bullet. */
void DemoSpaceship::Shoot(void)
{
	// Check the world exists
	if (!mWorld) return;
	// Construct a unit length vector in the direction the spaceship is headed
	GLVector3f Demospaceship_heading(cos(DEG2RAD*mAngle), sin(DEG2RAD*mAngle), 0);
	Demospaceship_heading.normalize();
	// Calculate the point at the node of the spaceship from position and heading
	GLVector3f bullet_position = mPosition + (Demospaceship_heading * 4);
	// Calculate how fast the bullet should travel
	float bullet_speed = 30;
	// Construct a vector for the bullet's velocity
	GLVector3f bullet_velocity = mVelocity + Demospaceship_heading * bullet_speed;
	// Construct a new bullet
	shared_ptr<GameObject> DemoBullet
	(new DemoBullet(bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 2000));
	DemoBullet->SetBoundingShape(make_shared<BoundingSphere>(DemoBullet->GetThisPtr(), 2.0f));
	DemoBullet->SetShape(mDemoBulletShape);
	// Add the new bullet to the game world
	mWorld->AddObject(DemoBullet);

}

bool DemoSpaceship::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() != GameObjectType("Asteroid") && o->GetType() != GameObjectType("Bullet")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void DemoSpaceship::OnCollision(const GameObjectList &objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}