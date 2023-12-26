#pragma once

#include <graphics3d/G3DAll.h>

namespace RBX
{
	class PV;
	class SimBody;
	class Velocity;
	class Cofm;

	class Body
	{
	private:

	};

	class Cofm
	{
	private:

		Body* body;
		Vector3 cofmInBody;
		Matrix3 moment;

		bool dirty;
		float mass;

	public:

		void updateIfDirty();

		float getMass() { return mass; }

		Vector3 getCofmInBody(){ return cofmInBody; }

		Matrix3 getMoment(){ return moment; }

		Cofm(Body* body);
	};

	class PV
	{
	public:
		CoordinateFrame position;
		Velocity velocity;

		void velocityAtPoint(Vector3 point)
		{

		}

		void pvAtLocalCoord()
		{

		}

		static void pvAtLocalCoord(RBX::PV* pv, CoordinateFrame localCoord)
		{

		}
	};

	class Velocity
	{
	public:

		Vector3 linear, rotational;

		static Velocity zero()
		{
			return Velocity();
		}

		Velocity()
		{
			linear = Vector3::zero();
			rotational = Vector3::zero();
		}
	};

}