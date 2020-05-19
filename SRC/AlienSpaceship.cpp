#include "GameUtil.h"
#include "GameWorld.h"
#include "AlienBullet.h"
#include "AlienSpaceship.h"
#include "BoundingSphere.h"

using namespace std;

// PUBLIC INSTANCE CONSTRUCTORS ///////////////////////////////////////////////

/**  Default constructor. */
AlienSpaceship::AlienSpaceship()
	: GameObject("AlienSpaceship"), mAlienThrust(0)
{
}

/** Construct a spaceship with given position, velocity, acceleration, angle, and rotation. */
AlienSpaceship::AlienSpaceship(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r)
	: GameObject("Spaceship", p, v, a, h, r), mAlienThrust(0)
{
}

/** Copy constructor. */
AlienSpaceship::AlienSpaceship(const AlienSpaceship& s) : GameObject(s), mAlienThrust(0)
{
}

/** Destructor. */
AlienSpaceship::~AlienSpaceship(void)
{
}

// PUBLIC INSTANCE METHODS ////////////////////////////////////////////////////

/** Update this spaceship. */
void AlienSpaceship::Update(int t)
{
	// Call parent update function
	GameObject::Update(t);
}

/** Render this spaceship. */
void AlienSpaceship::Render(void)
{

	if (mAlienSpaceshipShape.get() != NULL)
	{
		mAlienSpaceshipShape->Render();
	}

	// If ship is thrusting
	if ((mAlienThrust > 0) && (mAlienThrusterShape.get() != NULL))
	{
		mAlienThrusterShape->Render();
	}


	// Enable lighting
	//glEnable(GL_LIGHTING);
	GameObject::Render();

}

/** Fire the rockets. */
void AlienSpaceship::Thrust(float t)
{
	mAlienThrust = t;
	// Increase acceleration in the direction of ship
	mAcceleration.x = mAlienThrust * cos(DEG2RAD*mAngle);
	mAcceleration.y = mAlienThrust * sin(DEG2RAD*mAngle);
}

/** Set the rotation. */
void AlienSpaceship::Rotate(float r)
{
	mRotation = r;
}

/** Shoot a bullet. */
void AlienSpaceship::Shoot(void)
{
	// Check the world exists
	if (!mWorld) return;
	// Construct a unit length vector in the direction the spaceship is headed
	GLVector3f Alienspaceship_heading(cos(DEG2RAD*mAngle), sin(DEG2RAD*mAngle), 0);
	Alienspaceship_heading.normalize();
	// Calculate the point at the node of the spaceship from position and heading
	GLVector3f bullet_position = mPosition + (Alienspaceship_heading * 4);
	// Calculate how fast the bullet should travel
	float bullet_speed = 30;
	// Construct a vector for the bullet's velocity
	GLVector3f bullet_velocity = mVelocity + Alienspaceship_heading * bullet_speed;
	// Construct a new bullet
	shared_ptr<GameObject> AlienBullet
	(new AlienBullet(bullet_position, bullet_velocity, mAcceleration, mAngle, 0, 2000));
	AlienBullet->SetBoundingShape(make_shared<BoundingSphere>(AlienBullet->GetThisPtr(), 2.0f));
	AlienBullet->SetShape(mAlienBulletShape);
	// Add the new bullet to the game world
	mWorld->AddObject(AlienBullet);

}

bool AlienSpaceship::CollisionTest(shared_ptr<GameObject> o)
{
	if (o->GetType() != GameObjectType("Asteroid") && o->GetType() != GameObjectType("Bullet")) return false;
	if (mBoundingShape.get() == NULL) return false;
	if (o->GetBoundingShape().get() == NULL) return false;
	return mBoundingShape->CollisionTest(o->GetBoundingShape());
}

void AlienSpaceship::OnCollision(const GameObjectList &objects)
{
	mWorld->FlagForRemoval(GetThisPtr());
}