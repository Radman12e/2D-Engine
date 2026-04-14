#pragma once


class Rigidbody;
class Collider;

enum CollisionPhase
{
	Stay, Entered, Exit
};

struct collision
{
	Collider* ThisCollider;
	Collider* OtherCollider;
	Rigidbody* rb;
};

class CollisionEventsinterface
{
protected:
	virtual void OnCollisionStay(collision& CollisionObject) = 0;

	virtual void OnCollisionEntered(collision& CollisionObject) = 0;
	virtual void OnCollisionExited(collision& CollisionObject) = 0;

	virtual void OnTriggerEntered(collision& CollisionObject) = 0;

	virtual void OnTriggerStay(collision& CollisionObject) = 0;
	virtual void OnTriggerExited(collision& CollisionObject) = 0;


public:
	void TriggerCollision(Collider* Thiscollider, Collider* OtherCollider, Rigidbody* rb, CollisionPhase phase);

};

