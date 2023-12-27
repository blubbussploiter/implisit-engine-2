#include "body.h"
#include "rbxmath.h"

int p;

void RBX::Body::updatePV() /* todo: finish this, -> requires RBX::Link, so create and implement that too. thank you! */
{
	Body* root;
	if (parent)
	{
		root = this->root;
		root->updatePV();
		if (stateIndex != root->stateIndex)
		{
			parent->updatePV();

		}
	}
}

Vector3 RBX::Body::getBranchCofmPos()
{
	Vector3 CofmInBody, p_translation;

	if (cofm)
	{
		updatePV();
		CofmInBody = cofm->getCofmInBody();
		p_translation = pv.position.pointToWorldSpace(CofmInBody);
	}
	else
	{
		updatePV();
		p_translation = pv.position.translation;
	}
	return p_translation;
}

Matrix3 RBX::Body::getIWorldAtPoint(Vector3 point)
{
	Matrix3 iBody;
	Matrix3 iWorldAtCofm;
	float mass;

	updatePV();

	mass = this->mass;
	iBody = moment;
	iWorldAtCofm = RBX::Math::momentToWorldSpace(iBody, pv.position.rotation);

	updatePV();

	return RBX::Math::getIWorldAtPoint(pv.position.translation, point, iWorldAtCofm, mass);
}

Matrix3 RBX::Body::getBranchIWorldAtPoint(Vector3 point)
{
	Cofm* cofm;
	Matrix3 Moment, iBody, iWorldAtCofm;
	Vector3 BranchCofmPos;
	float m;

	cofm = this->cofm;
	if (cofm)
		m = cofm->getMass();
	else
		m = mass;
	updatePV();
	cofm = this->cofm;
	if (cofm)
		Moment = cofm->getMoment();
	else
		Moment = moment;
	iBody = Moment;
	iWorldAtCofm = RBX::Math::momentToWorldSpace(iBody, pv.position.rotation);
	BranchCofmPos = getBranchCofmPos();
	return RBX::Math::getIWorldAtPoint(BranchCofmPos, point, iWorldAtCofm, m);
}
