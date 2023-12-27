#pragma once

#include <graphics3d/G3DAll.h>

static int p;

namespace RBX
{
	class PV;
	class SimBody;
	class Velocity;
	class Cofm;
	class Link;

	class Body
	{
	public: /* members */
		int kernelIndex;
		int leafBodyIndex;
		int connectorUseCount;
		bool leafBody;
		Body* root;
		Body* parent;
		int index;
		G3D::Array<Body*> children;
		Cofm* cofm;
		SimBody* simBody;
		bool canThrottle;
		Link* link;
		float mass;
		int stateIndex;
		CoordinateFrame meInParent;
		Matrix3 moment;
		PV pv;
	public: /* methods */

		void updatePV();

		Vector3 getBranchCofmPos();

		Matrix3 getIWorldAtPoint(Vector3 point);
		Matrix3 getBranchIWorldAtPoint(Vector3 point);

		Body()
		{
			index = -1;
			mass = 0.0f;
			stateIndex = p++;
			root = this;
			simBody = new SimBody(this);
		}
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

		float getMass() 
		{
			updateIfDirty();
			return mass; 
		}

		Vector3 getCofmInBody()
		{
			updateIfDirty();
			return cofmInBody; 
		}

		Matrix3 getMoment()
		{
			updateIfDirty();
			return moment; 
		}

		Cofm(Body* body);
	};

	class PV
	{
	public:
		CoordinateFrame position;
		Velocity velocity;

		Velocity velocityAtPoint(Vector3 worldPos)
		{
			Velocity result;
			Vector3 l, r;
			float rx, ry, rz;
			l = worldPos - position.translation;
			rx = velocity.rotational.x * l.y - l.x * velocity.rotational.y;
			ry = velocity.rotational.y * l.z - l.y * velocity.rotational.z;
			rz = velocity.rotational.z * l.x - l.z * velocity.rotational.x;
			result.linear.x = ry + velocity.linear.x;
			result.linear.y = rz + velocity.linear.y;
			result.linear.z = rx + velocity.linear.z;
			result.rotational = velocity.rotational;
			return result;
		}

		void pvAtLocalOffset(Vector3 localOffset)
		{
			CoordinateFrame coord;
			coord.translation = localOffset;
			pvAtLocalCoord(coord);
		}

		void pvAtLocalCoord(CoordinateFrame localCoord)
		{
			pvAtLocalCoord(*this, localCoord, *this);
		}

		static void pvAtLocalCoord(RBX::PV& base, CoordinateFrame localCoord, RBX::PV& answer)
		{
			answer.position = base.position * localCoord;
			answer.velocity = base.velocityAtPoint(answer.position.translation);
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

	class Link
	{

	};

}