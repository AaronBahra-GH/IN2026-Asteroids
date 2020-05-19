#ifndef __DEMOBULLET_H__
#define __DEMOBULLET_H__

#include "GameUtil.h"
#include "GameObject.h"

class DemoBullet : public GameObject
{
public:
	DemoBullet();
	DemoBullet(GLVector3f p, GLVector3f v, GLVector3f a, GLfloat h, GLfloat r, int ttl);
	DemoBullet(const DemoBullet& b);
	virtual ~DemoBullet(void);

	virtual void Update(int t);

	void SetTimeToLive(int ttl) { mTimeToLive = ttl; }
	int GetTimeToLive(void) { return mTimeToLive; }

	bool CollisionTest(shared_ptr<GameObject> o);
	void OnCollision(const GameObjectList& objects);

protected:
	int mTimeToLive;
};

#endif
