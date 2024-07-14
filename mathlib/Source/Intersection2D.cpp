#include "math/Intersection2D.h"


#ifndef  FLT_MAX
#include <cfloat>
#endif // ! FLT_MAX


namespace math
{


	AABBCollider2D::AABBCollider2D(const Vector2<float>& _pos, const Vector2<float>& _size)
		: m_position(_pos), m_extents(_size)
	{

	}


	Vector2<float>& AABBCollider2D::Position(void)
	{
		return m_position;
	}

	Vector2<float>& AABBCollider2D::Extents(void)
	{
		return m_extents;
	}

	Vector2<float> AABBCollider2D::GetPosition(void) const
	{
		return m_position;
	}

	Vector2<float> AABBCollider2D::GetExtents(void) const
	{
		return m_extents;
	}

	bool AABBCollider2D::CheckCollision(const AABBCollider2D& _other) const
	{
		Vector2<float>		selfMin = GetMin(),
					selfMax = GetMax();

		Vector2<float>		otherMin = _other.GetMin(),
					otherMax = _other.GetMax();


		// Check min and max vertices on each axis to look for a gap

		if (selfMax[0] < otherMin[0] || selfMin[0] > otherMax[0])
			return false;

		if (selfMax[1] < otherMin[1] || selfMin[1] > otherMax[1])
			return false;

		return true;
	}

	bool AABBCollider2D::CheckCollision(const OBBCollider2D& _other) const
	{
		// Turn this object and _other into polygon colliders
		PolygonCollider2D    selfPoly, otherPoly;

		// Get AABB vertices
		Vector2<float>				 selfVertices[4] =
		{
			GetMax(),
			GetMin(),

			{
			  m_position.GetX() + m_extents.GetX(),
			  m_position.GetY() - m_extents.GetY()
			},

			{
				m_position.GetX() - m_extents.GetX(),
				m_position.GetY() + m_extents.GetY()
			},
		};

		Vector2<float>				otherRotated =
		Rotate(_other.GetExtents(), _other.GetRotation());

		// Get OBB rotated vertices
		Vector2<float>				otherVertices[4] =
		{
			_other.GetPosition() + otherRotated,
			_other.GetPosition() - otherRotated,

			_other.GetPosition() + Rotate
			(
				{_other.GetExtents().X(), -_other.GetExtents().Y()},
				 _other.GetRotation()
			),

			_other.GetPosition() + Rotate
			(
				{-_other.GetExtents().X(), _other.GetExtents().Y()},
				 _other.GetRotation()
			),
		};

		// Use stack array to avoid heap alloc/free
		selfPoly.m_vertices = selfVertices;
		otherPoly.m_vertices = otherVertices;

		selfPoly.m_vertexCount = otherPoly.m_vertexCount = 4;

		// Run SAT algorithm on nea
		bool		intersection = selfPoly.CheckCollision(otherPoly);

		// Avoid attempt to free stack (polygon destructor) by
		// setting pointers to nullptr
		selfPoly.m_vertices = otherPoly.m_vertices = nullptr;

		return intersection;

	}

	bool AABBCollider2D::CheckCollision(const CircleCollider2D& _other) const
	{
		Vector2<float>		minVertex = GetMin(), maxVertex = GetMax();

		// Get closest point
		Vector2<float>		closestPoint
		{
			Max(minVertex.GetX(), Min(_other.GetPosition().GetX(), maxVertex.GetX())),
			Max(minVertex.GetY(), Min(_other.GetPosition().GetY(), maxVertex.GetY()))
		};

		Vector2<float>		distance = closestPoint - _other.GetPosition();

		// Point closer than end of radius = intersection
		return distance.MagnitudeSquared() <= _other.GetRadiusSquared();
	}

	bool AABBCollider2D::CheckCollision(const PolygonCollider2D& _other) const
	{
		// Turn AABB into polygon collider
		PolygonCollider2D	selfPoly;

		// Get AABB vertices
		Vector2<float>				selfVertices[4] =
		{
			GetMax(),
			GetMin(),
			{ m_position.GetX() + m_extents.GetX(), m_position.GetY() - m_extents.GetY()},
			{ m_position.GetX() - m_extents.GetX(), m_position.GetY() + m_extents.GetY()},
		};

		selfPoly.m_vertices = selfVertices;

		selfPoly.m_vertexCount = 4;

		// Run SAT algorithm
		bool		intersection = selfPoly.CheckCollision(_other);

		selfPoly.m_vertices = nullptr;

		return intersection;
	}

	bool AABBCollider2D::PointInBox(const Vector2<float>& _point) const
	{
		Vector2<float>		min = GetMin(), max = GetMax();

		// Check if point is within AABB bounds

		if (_point.GetX() < min.GetX() || _point.GetX() > max.GetX())
			return false;

		if (_point.GetY() < min.GetY() || _point.GetY() > max.GetY())
			return false;

		return true;
	}


	Ray2D::Ray2D(const Vector2<float>& _pos, const Vector2<float>& _dir)
		: m_origin(_pos)
	{
		m_direction = Normalize(_dir);

		// Pre compute direction divisor
		m_inverseDir.X() = (m_direction.GetX() != 0.f) ?
		1.f / m_direction.GetX() : 0.f;


		m_inverseDir.Y() = (m_direction.GetY() != 0.f) ?
		1.f / m_direction.GetY() : 0.f;
	}


	bool Ray2D::Intersect(const AABBCollider2D& _box, float& _distance) const
	{
		float   maxIntersect = FLT_MAX, minIntersect = -FLT_MAX;

		Vector2<float> minVertex = _box.GetMin(), maxVertex = _box.GetMax();

		// x plane = 0, y plane = 1, z plane = 2
		for (int axis = 0; axis < 2; ++axis)
		{
			// t1 for x, t3 for y, t5 for z
			float lowIntersect = (minVertex[axis] - m_origin[axis]) * m_inverseDir[axis];

			// t2 for x, t4 for y, t6 for z
			float highIntersect = (maxVertex[axis] - m_origin[axis]) * m_inverseDir[axis];

			maxIntersect = Min(Max(lowIntersect, highIntersect), maxIntersect);
			minIntersect = Max(Min(lowIntersect, highIntersect), minIntersect);
		}

		// Check if an intersection occurred
		bool	intersection = maxIntersect > Max(minIntersect, 0.f);

		// Write distance into reference argument if intersection is successful
		if (intersection)
			_distance = minIntersect;

		// Return intersection status
		return intersection;
	}

    Vector2<float> &Ray2D::Origin(void)
    {
       return m_origin;
    }

    Vector2<float> &Ray2D::Direction(void)
    {
        return m_direction;
    }

    Vector2<float> Ray2D::GetOrigin(void) const
    {
        return m_origin;
    }

    Vector2<float> Ray2D::GetDirection(void) const
    {
        return m_direction;
    }

    Vector2<float> Ray2D::GetInverseDir(void) const
    {
        return m_inverseDir;
    }

    PolygonCollider2D::PolygonCollider2D(Vector2<float> _vertices[], int _count)
        : m_vertexCount(_count)
    {
		// Allocate space for vertices
		if (!m_vertices)
			m_vertices = new Vector2<float>[_count];


		for (int vertex = 0; vertex < _count; ++vertex)
		{
			// Copy vertices into heap array
			m_vertices[vertex] = _vertices[vertex];
		}
	}

	PolygonCollider2D::PolygonCollider2D(const PolygonCollider2D& _other)
		: m_vertexCount(_other.m_vertexCount)
	{
		// Allocate vertices for deep copy
		if (_other.m_vertexCount)
			m_vertices = new Vector2<float>[_other.m_vertexCount];

		// Copy vertices into new array
		for (unsigned int vert = 0; vert < _other.m_vertexCount; ++vert)
			m_vertices[vert] = _other.m_vertices[vert];

	}


	PolygonCollider2D::~PolygonCollider2D(void)
	{
		if (m_vertices)
			delete[] m_vertices;
	}


	Vector2<float>& PolygonCollider2D::operator[](int _index)
	{
		return m_vertices[_index];
	}


	Vector2<float> PolygonCollider2D::operator[](int _index) const
	{
		return m_vertices[_index];
	}



	bool PolygonCollider2D::CheckCollision(const PolygonCollider2D& _other) const
	{
		return SeparatingAxisTheorem(_other);
	}

	void PolygonCollider2D::MinMaxProjection
	(const Vector2<float>& _normal, float& _min, float& _max) const
	{
		// Find min and max projections by testing each vertex against normal
		for (unsigned int vertex = 0; vertex < m_vertexCount; ++vertex)
		{
			float	projection = Round(_normal.Dot(m_vertices[vertex]));

			if (projection < _min)
				_min = projection;

			else if (projection > _max)
				_max = projection;
		}
	}

	bool PolygonCollider2D::
		SeparatingAxisTheorem(const PolygonCollider2D& _other) const
	{
		// Check all of this polygon's axes for a gap
		if (!InternalSAT(_other))
			return false;

		// Check all the other polygon's axes if no gap was previously found
		if (!_other.InternalSAT(*this))
			return false;

		return true;
	}


	bool PolygonCollider2D::InternalSAT(const PolygonCollider2D& _other) const
	{
		float	min1, max1;
		float   min2, max2;

		// Get every normal
		for (unsigned int side = 0; side < m_vertexCount; ++side)
		{
			min1 = FLT_MAX, max1 = -FLT_MAX;
			min2 = FLT_MAX, max2 = -FLT_MAX;

			Vector2<float>		normal;

			if (0 == side)
				normal = (m_vertices[side] - m_vertices[m_vertexCount - 1])
						  .Normal();

			else
				normal = (m_vertices[side] - m_vertices[side - 1]).Normal();

			// Find min and max projections onot normal for both polygons
			MinMaxProjection(normal, min1, max1);
			_other.MinMaxProjection(normal, min2, max2);

			if (min2 > max1 || min1 > max2)
				return false;
		}

		return true;
	}

	bool PolygonCollider2D::CheckCollision(const AABBCollider2D& _other) const
	{
		// Use already defined AABB vs polygon check
		return _other.CheckCollision(*this);
	}

	bool PolygonCollider2D::CheckCollision(const OBBCollider2D& _other) const
	{
		// Use already define OBB vs polygon check
		return _other.CheckCollision(*this);
	}



	Vector2<float> AABBCollider2D::GetMin(void) const
	{
		return m_position - m_extents;
	}


	Vector2<float> AABBCollider2D::GetMax(void) const
	{
		return m_position + m_extents;
	}


	Vector2<float> OBBCollider2D::GetMin(void) const
	{
		// Rotate BEFORE translating
		Vector2<float>		rotated = Rotate(m_extents, m_rotation);

		return m_position - rotated;
	}

	Vector2<float> OBBCollider2D::GetMax(void) const
	{
		// Rotate BEFORE translating
		Vector2<float>		rotated = Rotate(m_extents, m_rotation);

		return rotated + m_position;
	}


	OBBCollider2D::OBBCollider2D
	(const Vector2<float>& _pos, const Vector2<float>& _extents, Radian<float> _angle)
		: m_position(_pos), m_extents(_extents), m_rotation(_angle)
	{
	}

	bool OBBCollider2D::CheckCollision(const AABBCollider2D& _other) const
	{
		// Use already defined AABB vs OBB check
		return _other.CheckCollision(*this);
	}


	Vector2<float>& OBBCollider2D::Position(void)
	{
		return m_position;
	}

	Vector2<float>& OBBCollider2D::Extents(void)
	{
		return m_extents;
	}

	Radian<float>& OBBCollider2D::Rotation(void)
	{
		return m_rotation;
	}

	Vector2<float> OBBCollider2D::GetPosition(void) const
	{
		return m_position;
	}

	Vector2<float> OBBCollider2D::GetExtents(void) const
	{
		return m_extents;
	}

	Radian<float> OBBCollider2D::GetRotation(void) const
	{
		return m_rotation;
	}


	bool OBBCollider2D::CheckCollision(const OBBCollider2D& _other) const
	{
		// Turn both OBBs into polygons
		PolygonCollider2D	selfPoly, otherPoly;

		Vector2<float>				selfRotated = Rotate(m_extents, m_rotation);
		Vector2<float>				otherRotated = Rotate(_other.m_extents,
												  _other.m_rotation);

		// Rotate vertices
		Vector2<float>				selfVertices[4] =
		{
			m_position + selfRotated,
			m_position - selfRotated,
			m_position + Rotate
			(
				{ m_extents.GetX(), -m_extents.GetY() },
				  m_rotation
			),
			m_position + Rotate
			(
				{ -m_extents.GetX(), m_extents.GetY() },
				  m_rotation
			),
		};

		// Rotate vertices
		Vector2<float>				otherVertices[4] =
		{
			_other.GetPosition() + otherRotated,
			_other.GetPosition() - otherRotated,

			_other.GetPosition() + Rotate
			(
				{_other.GetExtents().X(), -_other.GetExtents().Y()},
				 _other.GetRotation()
			),

			_other.GetPosition() + Rotate
			(
				{-_other.GetExtents().X(), _other.GetExtents().Y()},
				 _other.GetRotation()
			),
		};

		// Use stack instead of heap
		selfPoly.m_vertices = selfVertices;
		otherPoly.m_vertices = otherVertices;

		selfPoly.m_vertexCount = otherPoly.m_vertexCount = 4;

		// Run SAT
		bool		intersection = selfPoly.CheckCollision(otherPoly);

		// Avoid attempt to free stack
		selfPoly.m_vertices = otherPoly.m_vertices = nullptr;

		return intersection;
	}

	bool OBBCollider2D::CheckCollision(const CircleCollider2D& _other) const
	{
		Vector2<float>		 minVertex = GetMin(), maxVertex = GetMax();

		Vector2<float>		closestPoint
		{
			Max(minVertex.GetX(), Min(_other.GetPosition().GetX(), maxVertex.GetX())),
			Max(minVertex.GetY(), Min(_other.GetPosition().GetY(), maxVertex.GetY()))
		};

		// Check if closest point is within the circle's range

		Vector2<float>		distance = closestPoint - _other.GetPosition();


		return distance.MagnitudeSquared() <= _other.GetRadiusSquared();
	}

	bool OBBCollider2D::CheckCollision(const PolygonCollider2D& _other) const
	{
		// Turn OBB into polygon collider
		PolygonCollider2D	selfPoly;

		Vector2<float>				selfRotated = Rotate(m_extents, m_rotation);

		Vector2<float>				selfVertices[4] =
		{
			m_position + selfRotated,
			m_position - selfRotated,
			m_position + Rotate
			(
				{ m_extents.GetX(), -m_extents.GetY() },
				  m_rotation
			),
			m_position + Rotate
			(
				{ -m_extents.GetX(), m_extents.GetY() },
				  m_rotation
			),
		};

		// Use stack array instead of heap
		selfPoly.m_vertices = selfVertices;

		selfPoly.m_vertexCount = 4;

		// Run SAT
		bool	intersection = selfPoly.CheckCollision(_other);

		// Avoid attempt to free stack in destructor
		selfPoly.m_vertices = nullptr;

		return intersection;
	}

	Vector2<float>& CircleCollider2D::Position(void)
	{
		return m_position;
	}

	float& CircleCollider2D::Radius(void)
	{
		return m_radius;
	}

	Vector2<float> CircleCollider2D::GetPosition(void) const
	{
		return m_position;
	}

	float CircleCollider2D::GetRadius(void) const
	{
		return m_radius;
	}

	float CircleCollider2D::GetRadiusSquared(void) const
	{
		return m_radius * m_radius;
	}

	CircleCollider2D::CircleCollider2D(const Vector2<float>& _pos, float _radius)
		: m_position(_pos), m_radius(_radius)
	{
	}


	bool CircleCollider2D::CheckCollision(const AABBCollider2D& _other) const
	{
		// Use already defined AABB vs circle check
		return _other.CheckCollision(*this);
	}

	bool CircleCollider2D::CheckCollision(const OBBCollider2D& _other) const
	{
		// Use already defined OBB vs circle cleck
		return _other.CheckCollision(*this);
	}

	bool CircleCollider2D::CheckCollision(const CircleCollider2D& _other) const
	{
		// Check if distance between two circles is shorter than their radii
		float		distance = DistanceSquared(m_position, _other.m_position);

		// Use square instead of square root for speed
		return distance <= GetRadiusSquared() + _other.GetRadiusSquared();
	}

	bool CircleCollider2D::PointInCircle(const Vector2<float>& _point) const
	{
		Vector2<float>		distance = _point - m_position;

		// Check if distance is shorter than circle radius
		return distance.MagnitudeSquared() <= m_radius * m_radius;
	}

	Line2D::Line2D(const Vector2<float>& _start, const Vector2<float>& _end)
		: m_start(_start), m_end(_end)
	{
	}

    Vector2<float> &Line2D::Start(void)
    {
       return m_start;
    }

    Vector2<float> &Line2D::End(void)
    {
        return m_end;
    }

    Vector2<float> Line2D::GetStart(void) const
    {
        return m_start;
    }

    Vector2<float> Line2D::GetEnd(void) const
    {
        return m_end;
    }

    bool Line2D::Intersect(const AABBCollider2D &_box) const
    {
		// Use huge value (likely smaller than line length)
		// that can be safely squared without causing
		// 32-bit overflow
		float 		distanceToBox = 1e10f;


		Vector2<float>		direction = m_end - m_start;

		// Turn segment into ray to use already defined raycast algorithm
		Ray2D		lineRay(m_start, direction);

		// If no intersection or intersection is further than line length,
		// no line intsersection occurs
		if(!lineRay.Intersect(_box, distanceToBox) ||
			distanceToBox * distanceToBox > direction.MagnitudeSquared())
		{
			return false;
		}

		return true;
    }

    bool Line2D::Intersect(const CircleCollider2D &_circle) const
    {
		// Apply quadratic formula to find whether there is an intersection

		Vector2<float>		circleToLineStart = m_start - _circle.GetPosition();
		Vector2<float>		lineDirection = m_end - m_start;

		// Compute b^2
		float		quadraticDelta =
		(2.f * lineDirection.Dot(circleToLineStart));

		quadraticDelta *= quadraticDelta;

		// Find 4ac
		float		tmpQuadratic = 4.f * lineDirection.MagnitudeSquared() *
					(circleToLineStart.MagnitudeSquared() -
					_circle.GetRadiusSquared());

		// delta = b^2 - 4ac
		quadraticDelta -= tmpQuadratic;

		// No intersection if unable to compute square root of delta
		// (delta is negative)
		if (quadraticDelta < 0.f)
			return false;


        return true;
    }

    float Line2D::Length(void) const
    {
		// Distance from start to end
        return (m_end - m_start).Magnitude();
    }

    float Line2D::LengthSquared(void) const
    {
		// Distance from start to end squared
       return (m_end - m_start).MagnitudeSquared();
    }
}