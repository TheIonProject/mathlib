#pragma once

#include "math/Vector3.hpp"
#include "math/Matrix3.hpp"
#include "math/Arithmetic.hpp"

namespace math
{
	class OBBCollider3D;
	class SphereCollider3D;

	// Axis aligned bounding box
	class AABBCollider3D
	{

	public:

			// Constructors

						AABBCollider3D(void) = default;

						AABBCollider3D(const Vector3<float>& _pos, const Vector3<float>& _size);
						AABBCollider3D(const AABBCollider3D& _other) = default;

						~AABBCollider3D(void) = default;


			// AABB collision checks

			bool		CheckCollision(const AABBCollider3D& _other)	const;
			bool		CheckCollision (const SphereCollider3D& _other)	const;

			bool		PointInBox(const Vector3<float>& _point)				const;

			// Accessors

			Vector3<float>&	Position(void);
			Vector3<float>&	Extents(void);

			Vector3<float>		GetPosition(void)								const;
			Vector3<float>		GetExtents(void)								const;

			// Calculate min and max vertex coords.

			Vector3<float>		GetMin(void)									const;
			Vector3<float>		GetMax(void)									const;


	private:

		Vector3<float>		m_position;
		Vector3<float>		m_extents;

	};

	// Bounding sphere
	class SphereCollider3D
	{
	public:

		// Constructors / destructor

					SphereCollider3D(void) = default;
					SphereCollider3D(const Vector3<float>& _pos, float _radius);

					SphereCollider3D
					(const SphereCollider3D& _other) = default;

					~SphereCollider3D(void) = default;

		// Collision checks

		bool		CheckCollision(const AABBCollider3D& _other)	const;
		bool		CheckCollision(const SphereCollider3D& _other)	const;

		// Point vs sphere
		bool		PointInSphere(const Vector3<float>& _point)			const;


		// Accessors

		Vector3<float>&	Position(void);
		float&		Radius(void);

		Vector3<float>		GetPosition(void)								const;
		float		GetRadius(void)									const;
		float		GetRadiusSquared(void)							const;

	private:

		Vector3<float> m_position{};
		float	m_radius = 0.f;
	};

	class Ray3D
	{
	public:

		// Constructors / destructor

					Ray3D(void) = delete;
					Ray3D(const Vector3<float>& _pos, const Vector3<float>& _dir);
					Ray3D(const Ray3D& _other) = default;

					~Ray3D(void) = default;

		// Intersection with 3D vounding volumes

		bool		Intersect
		(const AABBCollider3D& _box, float& _distance)				const;

		bool		Intersect
		(const SphereCollider3D& _sphere, float& _distance)			const;

		// Accessors

		Vector3<float>&	Origin(void);
		Vector3<float>&	Direction(void);

		Vector3<float>		GetOrigin(void)									 const;
		Vector3<float>		GetDirection(void)								 const;
		Vector3<float>		GetInverseDir(void)								 const;


	private:
		// Origin of ray
		Vector3<float>    m_origin;

		// Direction unit vector
		Vector3<float>    m_direction;

		// 1 / direction
		Vector3<float>    m_inverseDir;
	};


	// Oriented bounding box
	class OBBCollider3D
	{
	public:

		// Constructors / destructor

					OBBCollider3D(void) = default;

					OBBCollider3D
					(const Vector3<float>& _pos, const Vector3<float>& _extents,
					 Radian<float> _angleX, Radian<float> _angleY, Radian<float> _angleZ);

					OBBCollider3D(const OBBCollider3D& _other) = default;
					~OBBCollider3D(void) = default;

		// Accessors

		Radian<float>&		RotationX(void);
		Radian<float>&		RotationY(void);
		Radian<float>&		RotationZ(void);

		Radian<float>		GetRotationX(void) const;
		Radian<float>		GetRotationY(void) const;
		Radian<float>		GetRotationZ(void) const;

		Vector3<float>&	Position(void);
		Vector3<float>&	Extents(void);

		// Calculate rotation matrix from 3 object's 3 angles
		Matrix3f 	RotationMatrix(void)							const;

		Vector3<float>		GetPosition(void)								const;
		Vector3<float>		GetExtents(void)								const;

		// Calculate rotated min and max vertices

		Vector3<float>		GetMin(void)									const;
		Vector3<float>		GetMax(void)									const;


	private:

		Vector3<float>		m_position;
		Vector3<float>		m_extents;
		Radian<float>		m_rotation[3];
	};

	// 3D line segment
	class Line3D
	{
	public:
		// Constructors / destructor

					Line3D(void) = default;
					Line3D(const Vector3<float>& _start, const Vector3<float>& _end);
					Line3D(const Line3D& _other) = default;

		// Accessors

		Vector3<float>&	Start(void);
		Vector3<float>&	End(void);

		Vector3<float>		GetStart(void)												const;
		Vector3<float>		GetEnd(void)												const;

		// Intersection checks

		bool		Intersect(const AABBCollider3D& _box)						const;
		bool		Intersect(const SphereCollider3D& _circle)					const;

		// Calculate segment length

		float		Length(void)												const;
		float		LengthSquared(void)											const;

	private:

		Vector3<float>		m_start;
		Vector3<float>		m_end;
	};


	using Box = AABBCollider3D;
	using OrientedBox = OBBCollider3D;

	using Point3D = Vector3<float>;
	using Sphere = SphereCollider3D;

}
