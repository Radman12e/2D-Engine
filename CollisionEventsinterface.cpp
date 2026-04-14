#include "CollisionEventsinterface.h"
#include "Collider.h"
#include "Rigidbody.h"
void CollisionEventsinterface::TriggerCollision(Collider* Thiscollider, Collider* OtherCollider, Rigidbody* rb, CollisionPhase phase)
{
	collision col{ Thiscollider, OtherCollider, rb };

	if (Thiscollider->IsTrigger == false)
	{
		switch (phase)
		{
		case CollisionPhase::Entered:
			OnCollisionEntered(col);
			break;
		case CollisionPhase::Exit:
			OnCollisionExited(col);
			break;
		case CollisionPhase::Stay:
			OnCollisionStay(col);
			break;
		}
	}
	else
	{
		switch (phase)
		{
		case CollisionPhase::Entered:
			OnTriggerEntered(col);
			break;
		case CollisionPhase::Exit:
			OnTriggerExited(col);
			break;
		case CollisionPhase::Stay:
			OnTriggerStay(col);
			break;
		}
	}

}