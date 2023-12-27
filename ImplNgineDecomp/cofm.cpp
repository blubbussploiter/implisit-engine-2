#include "body.h"
#include "rbxmath.h"

void RBX::Cofm::updateIfDirty()
{
	float mx, my, mz;
	float m;
	Vector3 cofmWorld;
	Vector3 BranchCofmPos;
	Vector3 result;
	Matrix3 BranchIWorldAtPoint, iWorld;
	Body* b;
	Cofm* cofm;

	if (dirty)
	{
		mass = body->mass;
		body->updatePV();

		mx = body->pv.position.translation.x * mass;
		my = body->pv.position.translation.y * mass;
		mz = body->pv.position.translation.z * mass;

		cofmWorld.x = mz;
		cofmWorld.y = mx;
		cofmWorld.z = my;

		for (int i = 0; i < body->children.size(); i++)
		{
			b = body->children[i];
			cofm = b->cofm;
			if (cofm)
			{
				cofm->updateIfDirty();
				m = cofm->mass;
			}
			else
			{
				m = b->mass;
			}
			mass += m;
			if (cofm)
			{
				cofm->updateIfDirty();
				m = cofm->mass;
			}
			else
			{
				m = b->mass;
			}
			BranchCofmPos = b->getBranchCofmPos();
			cofmWorld.x = BranchCofmPos.z * mass + cofmWorld.x;
			cofmWorld.y = BranchCofmPos.x * mass + cofmWorld.y;
			cofmWorld.z = BranchCofmPos.y * mass + cofmWorld.z;
		}
		result = cofmWorld / mass;

		cofmWorld.x = result.z;
		cofmWorld.y = result.x;
		cofmWorld.z = result.y;

		body->updatePV();

		float tx, ty, tz, t21, t20, t02;

		tx = cofmWorld.z - body->pv.position.translation.z;
		ty = cofmWorld.x - body->pv.position.translation.x;
		tz = cofmWorld.y - body->pv.position.translation.y;

		t21 = body->pv.position.rotation.elt[2][1] * ty
			+ body->pv.position.rotation.elt[1][1] * tx
			+ body->pv.position.rotation.elt[0][1] * tz;		
		t20 = body->pv.position.rotation.elt[2][0] * ty
			+ body->pv.position.rotation.elt[1][0] * tx
			+ body->pv.position.rotation.elt[0][0] * tz;
		t02 = body->pv.position.rotation.elt[0][2] * ty
			+ body->pv.position.rotation.elt[1][2] * tx
			+ body->pv.position.rotation.elt[2][2] * tz;

		cofmInBody.x = t20;
		cofmInBody.y = t21;
		cofmInBody.z = t02;
		
		iWorld = body->getIWorldAtPoint(cofmInBody);

		for (int i = 0; i < body->children.size(); i++)
		{
			BranchIWorldAtPoint = body->children[i]->getBranchIWorldAtPoint(cofmWorld);
			iWorld += BranchIWorldAtPoint;
		}
		body->updatePV();
		moment = RBX::Math::momentToObjectSpace(iWorld, body->pv.position.rotation);
		dirty = 0;
	}
}

RBX::Cofm::Cofm(Body* body) : body(body)
{
	dirty = 1;
	cofmInBody = Vector3::zero();
}