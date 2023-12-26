#include "body.h"



#pragma region cofm

void RBX::Cofm::updateIfDirty()
{
}

RBX::Cofm::Cofm(Body* body) : body(body)
{
	dirty = 1;
	cofmInBody = Vector3::zero();
}

#pragma endregion