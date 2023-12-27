#pragma once

#include <graphics3d/g3dall.h>

namespace RBX
{
	namespace Math
	{
		Matrix3 momentToWorldSpace(Matrix3 iBody, Matrix3 bodyRotation)
		{
			Matrix3 v0, v1, result;
			v0 = bodyRotation.transpose();
			v1 = iBody * bodyRotation;
			return v1 * v0;
		}
		Matrix3 momentToObjectSpace(Matrix3 iWorld, Matrix3 bodyRotation)
		{
			Matrix3 v0, v1;
			v0 = bodyRotation.transpose();
			v1 = v0 * iWorld;
			return v1 * bodyRotation;
		}
		Matrix3 getIWorldAtPoint(Vector3 cofmPos, Vector3 worldPos, Matrix3 iWorldAtCofm, float mass)
		{
			double v5; // st7
			double v6; // st6
			double v7; // st0
			double v8; // rt2
			double v9; // st2
			double v10; // st5
			double v11; // rt2
			double v12; // st2
			G3D::Matrix3 v13; // eax
			G3D::Matrix3 v14; // eax
			float fEntry00; // [esp+0h] [ebp-70h]
			float fEntry02; // [esp+8h] [ebp-68h]
			float fEntry10; // [esp+Ch] [ebp-64h]
			float fEntry11; // [esp+10h] [ebp-60h]
			float fEntry12; // [esp+14h] [ebp-5Ch]
			float fEntry20; // [esp+18h] [ebp-58h]
			float fEntry21; // [esp+1Ch] [ebp-54h]
			float fEntry22; // [esp+20h] [ebp-50h]
			G3D::Matrix3 v24; // [esp+28h] [ebp-48h] BYREF
			G3D::Matrix3 v25; // [esp+4Ch] [ebp-24h] BYREF

			v5 = worldPos.x - cofmPos.x;
			v6 = worldPos.y - cofmPos.y;
			v7 = worldPos.z - cofmPos.z;
			v8 = -(v6 * v7);
			fEntry22 = v6 * v6 + v5 * v5;
			fEntry21 = v8;
			v9 = -(v5 * v7);
			v10 = v8;
			fEntry20 = v9;
			v11 = v9;
			fEntry12 = v10;
			v12 = v7 * v7;
			fEntry11 = v5 * v5 + v12;
			fEntry10 = -(v6 * v5);
			fEntry02 = v11;
			fEntry00 = v6 * v6 + v12;
			v24 = Matrix3(fEntry00, fEntry10, fEntry02, fEntry10, fEntry11, fEntry12, fEntry20, fEntry21, fEntry22);
			v14 = v25 * v13;
			Matrix3 result = iWorldAtCofm * v14;
			return result;
		}
	}
}