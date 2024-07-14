/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: Vector3.hpp

DESCTIPTION: 3D vector class

AUTHOR: Noah de Pischof | @torrra on GitHub

TEMPLATES:

CScalarType is a template constraint that only accepts numeric data types

*/


#ifndef __VECTOR3_H__
#define __VECTOR3_H__

#include <string>
#include <cmath>
#include <sstream>

#include "math/MathGeneric.hpp"
#include "math/VectorGeneric.hpp"

#include "math/Trigonometry.hpp"
#include "math/Arithmetic.hpp"

#include "math/Angle.hpp"

#include "math/Vector2.hpp"



namespace math
{

	template <CScalarType TValueType>
	class Vector<3, TValueType>
	{
	public:

		// Constructors / destructor
		inline				Vector(void) = default;

		inline
		explicit			Vector(TValueType _val);


		inline				Vector(TValueType _x, TValueType _y, TValueType _z);
		inline				Vector(const Vector& _other);

		inline				~Vector(void) = default;

		// Get angle from this vector to another
		inline
		Radian<TValueType>	AngleFrom(const Vector& _other)				const;

		// Get angle from this vector to another unit vector
		// Should be used if this vector and the other are both
		// unit vectors
		inline
		Radian<TValueType>	AngleFromUnit(const Vector& _other)			const;

		// Compute cross product with another
		// this x other
		inline Vector		Cross(const Vector& _other)					const;

		// Get distance between 2 points
		inline TValueType	DistanceFrom(const Vector& _other)				const;

		// Get distance squared between two points
		inline TValueType	DistanceSquaredFrom(const Vector& _other)		const;

		// Get distance between 2 points disregarding the z axis
		inline TValueType	Distance2DFrom(Vector const&)					const;

		// Get distance squared between two points disregarding the z axis
		inline TValueType	Distance2DSquaredFrom(Vector const&)			const;

		// Compute dot product of two vectors
		inline TValueType	Dot(const Vector& _other)						const;

		// Is this vector's magnitude longer than another ?
		inline bool			IsLongerThan(const Vector& _other)				const;

		// Is this vector's magnitude shorter than another ?
		inline bool			IsShorterThan(const Vector& _other)			const;

		// Is this vector's magnitude equal to 1 ?
		inline bool			IsUnitVector(void)								const;

		inline TValueType	Magnitude(void)									const;
		inline TValueType	MagnitudeSquared(void)							const;

		// Adjust vector to turn into unit vector
		inline void			Normalize(void);

		// Get copy of this vector as a unit vector
		inline Vector		Normalized(void)								const;

		// Project this vector onto another
		inline void			ProjectOnto(const Vector& _other);

		// Reflect this vector onto another
		inline void			ReflectOnto(const Vector& _axis);

		// Reflect this vector onto a UNIT vector
		inline void			ReflectOntoUnit(const Vector& _axis);

		// Rotate this vector around the all 3 axes
		inline void			Rotate
		(
			Radian<TValueType> _angleX,
			Radian<TValueType> _angleY,
			Radian<TValueType> _angleZ
		);

		// Rotate this vector around an arbitrary axis
		inline void			Rotate
		(Radian<TValueType> _angle, const Vector& _axis);

		// Multiply this vector's components by another's
		inline void			Scale(const Vector& _other);

		// Get components as string
		inline std::string	String(void)									const;

		// Get components as verbose string
		inline std::string	StringLong(void)								const;

		// Add another vector's components to this one's
		inline void			Translate(const Vector& _other);

		// Accessors

		inline TValueType&	X(void);
		inline TValueType&	Y(void);
		inline TValueType&	Z(void);

		inline TValueType	GetX(void)										const;
		inline TValueType	GetY(void)										const;
		inline TValueType	GetZ(void)										const;


		inline Vector&		operator=(const Vector& _rhs);

		inline TValueType&			operator[](int _index);
		inline TValueType			operator[](int _index)					const;

		// Boolean test operators

		inline bool			operator==(const Vector& _rhs)					const;
		inline bool			operator!=(const Vector& _rhs)					const;

		// Component-wise operations

		inline Vector			operator+(const Vector& _rhs)				const;
		inline Vector			operator-(const Vector& _rhs)				const;
		inline Vector			operator*(const Vector& _rhs)				const;
		inline Vector			operator/(const Vector& _rhs)				const;

		// Multiply all components by a single scalar
		inline Vector			operator*(TValueType _rhs)					const;

		// Divide all components by a single scalar
		inline Vector			operator/(TValueType _rhs)					const;

		// Flip sign of both components
		inline Vector			operator-(void)								const;


		// Component-wise operations

		inline Vector&		operator+=(const Vector& _rhs);
		inline Vector&		operator-=(const Vector& _rhs);
		inline Vector&		operator*=(const Vector& _rhs);
		inline Vector&		operator/=(const Vector& _rhs);

		// Multiply all components by a single scalar
		inline Vector&		operator*=(TValueType _rhs);

		// Divide all components by a single scalar
		inline Vector&		operator/=(TValueType _rhs);


		// Constants

		inline static Vector	Zero(void);
		inline static Vector	One(void);
		inline static Vector	Up(void);
		inline static Vector	Down(void);
		inline static Vector	Left(void);
		inline static Vector	Right(void);
		inline static Vector   Back(void);
		inline static Vector   Front(void);


	private:

		TValueType				m_x;
		TValueType				m_y;
		TValueType				m_z;
	};

	// Non-member functions (similar to member functions but provided for readability)

	template <CScalarType TValueType> inline
	TValueType				Dot
	(const Vector<3, TValueType>& _first, const Vector<3, TValueType>& _second);

	template <CScalarType TValueType> inline
	Vector<3, TValueType>		Cross
	(const Vector<3, TValueType>& _first, const Vector<3, TValueType>& _second);

	template <CScalarType TValueType> inline
	Vector<3, TValueType>				Reflect
	(const Vector<3, TValueType>& _target, const Vector<3, TValueType>& _ontoNormal);

	template <CScalarType TValueType> inline
	Vector<3, TValueType>				ReflectUnit
	(const Vector<3, TValueType>& _target, const Vector<3, TValueType>& _ontoNormal);


	template <CScalarType TValueType> inline
	Vector<3, TValueType>				Project
	(const Vector<3, TValueType>& _target, const Vector<3, TValueType>& _ontoVector);

	template <CScalarType TValueType> inline
	Vector<3, TValueType>				Normalize(const Vector<3, TValueType>& _target);


	template <CScalarType TValueType> inline
	TValueType				Distance
	(const Vector<3, TValueType>& _start, const Vector<3, TValueType>& _end);


	template <CScalarType TValueType> inline
	TValueType				DistanceSquared
	(const Vector<3, TValueType>& _start, const Vector<3, TValueType>& _end);


	template <CScalarType TValueType> inline
	Vector<3, TValueType>				Rotate
	(
		const Vector<3, TValueType>& _target,
		Radian<TValueType> _angleX,
		Radian<TValueType> _angleY,
		Radian<TValueType> _angleZ
	);


	template <CScalarType TValueType> inline
	Vector<3, TValueType>				Rotate
	(
		const Vector<3, TValueType>& _target,
		Radian<TValueType> _angle, const Vector<3, TValueType>& _axis
	);

	// Send a vector's components to an output stream
	template <CScalarType TValueType> inline
	std::ostream&		operator<<
	(std::ostream& _os, Vector<3, TValueType> const& _vector);

	// Get components from an input stream
	template <CScalarType TValueType> inline
	std::istream&		operator>>
	(std::istream& _is, Vector<3, TValueType>& _vector);

















	// ---- Implementation ---


	template <CScalarType TValueType> inline
	Vector<3, TValueType>::Vector(TValueType _val)
	: m_x(_val), m_y(_val), m_z(_val) {}


	template <CScalarType TValueType> inline
	Vector<3, TValueType>::Vector(TValueType _x, TValueType _y, TValueType _z)
	: m_x(_x), m_y(_y), m_z(_z) {}


	template <CScalarType TValueType> inline
	Vector<3, TValueType>::Vector(const Vector<3, TValueType>& _other)
	: m_x(_other.m_x), m_y(_other.m_y), m_z(_other.m_z) {}


	template <CScalarType TValueType> inline
	Radian<TValueType> Vector<3, TValueType>::AngleFrom
	(const Vector<3, TValueType>& _other) const
	{
		TValueType    magnitudes = MagnitudeSquared() * _other.MagnitudeSquared();

		// Only run square root once
		magnitudes = SquareRoot(magnitudes);

		// Transform dot product equation to get cos angle,
		// then run acos
		return Acos(Dot(_other) / magnitudes);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Vector<3, TValueType>::AngleFromUnit
	(const Vector<3, TValueType>& _other) const
	{
		// Clamp dot to avoid acos domain error (NaN result)
		// and call acos as both vectors are assumed to be
		// unit vectors
		return Acos(Clamp(Dot(_other), MIN_COS, MAX_COS));
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Cross
	(const Vector<3, TValueType>& _other) const
	{
		// Compute cross product
		return Vector<3, TValueType>
			(
				(m_y * _other.m_z) - (m_z * _other.m_y),
				(m_z * _other.m_x) - (m_x * _other.m_z),
				(m_x * _other.m_y) - (m_y * _other.m_x)
			);

	}


	template <CScalarType TValueType> inline
	TValueType Vector<3, TValueType>::DistanceFrom
	(const Vector<3, TValueType>& _other) const
	{
		return SquareRoot(DistanceSquaredFrom(_other));
	}


	template <CScalarType TValueType> inline
	TValueType Vector<3, TValueType>::DistanceSquaredFrom
	(const Vector<3, TValueType>& _other) const
	{
		// Find distance vector and get magnitude
		return (_other - *this).MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	TValueType Vector<3, TValueType>::Distance2DFrom
	(const Vector<3, TValueType>& _other) const
	{
		return SquareRoot(Distance2DSquaredFrom(_other));
	}


	template <CScalarType TValueType> inline
	TValueType Vector<3, TValueType>::Distance2DSquaredFrom(const Vector<3, TValueType>& _other) const
	{
		// Ignore z axis
		Vector2<TValueType>		dist2D =
		{
			_other.m_x - m_x,
			_other.m_y - m_y
		};

		// Find distance vector and get magnitude
		return dist2D.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	TValueType Vector<3, TValueType>::Dot
	(const Vector<3, TValueType>& _other) const
	{
		// Multiply components
		return (m_x * _other.m_x) + (m_y * _other.m_y) + (m_z * _other.m_z);
	}



	template <CScalarType TValueType> inline
	bool Vector<3, TValueType>::IsLongerThan
	(const Vector<3, TValueType>& _other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() > _other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	bool Vector<3, TValueType>::IsShorterThan
	(const Vector<3, TValueType>& _other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() < _other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	bool Vector<3, TValueType>::IsUnitVector() const
	{
		// 1 squared == 1 so avoiding sqrt call is possible
		return AlmostEqual(MagnitudeSquared(), 1.f);
	}


	template <CScalarType TValueType> inline
	TValueType Vector<3, TValueType>::Magnitude() const
	{
		return SquareRoot(MagnitudeSquared());
	}



	template <CScalarType TValueType> inline
	TValueType Vector<3, TValueType>::MagnitudeSquared() const
	{
		// Square components
		return Dot(*this);
	}



	template <CScalarType TValueType> inline
	void Vector<3, TValueType>::Normalize()
	{
		TValueType		invMagnitude = Magnitude();

		if (AlmostEqual(invMagnitude, 0.f, std::numeric_limits<float>::epsilon()))
		{
			throw std::logic_error("Cannot divide by zero magnitude");
		}

		// Only divide once
		else
			invMagnitude = 1.f / invMagnitude;


		m_x *= invMagnitude;
		m_y *= invMagnitude;
		m_z *= invMagnitude;
	}



	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Normalized(void) const
	{
		Vector<3, TValueType>		result = *this;

		result.Normalize();

		// Return normalized copy
		return result;
	}



	template <CScalarType TValueType> inline
	void Vector<3, TValueType>::ProjectOnto(const Vector<3, TValueType>& _other)
	{
		// Apply projection formula
		TValueType		squareMagnitude = _other.MagnitudeSquared();
		TValueType		projFactor = Dot(_other) / squareMagnitude;

		m_x = _other.m_x * projFactor;
		m_y = _other.m_y * projFactor;
		m_z = _other.m_z * projFactor;

	}



	template <CScalarType TValueType> inline
	void Vector<3, TValueType>::ReflectOnto(const Vector<3, TValueType>& _axis)
	{
		// Only reflect onto unit vector
		Vector<3, TValueType>		normal = math::Normalize(_axis);

		// Apply reflection formula
		*this -= normal * (Dot(normal) * 2.f);
	}


	template <CScalarType TValueType> inline
		void Vector<3, TValueType>::ReflectOntoUnit(const Vector<3, TValueType>& _axis)
	{
		// Assume normal is already unit vector and skip normalize call
		*this -= _axis * (Dot(_axis) * 2.f);
	}


	template <CScalarType TValueType> inline
	void Vector<3, TValueType>::Rotate
	(Radian<TValueType> _angleX, Radian<TValueType> _angleY, Radian<TValueType> _angleZ)
	{
		Vector<3, TValueType>		copy = *this;

		TValueType				cosYaw = Cos(_angleZ), sinYaw = Sin(_angleZ);
		TValueType				cosPitch = Cos(_angleX), sinPitch = Sin(_angleX);
		TValueType				cosRoll = Cos(_angleY), sinRoll = Sin(_angleY);
		TValueType				rowResult;


		// Create rotation matrix.
		// Not an actual matrix3 object to avoid circular includes
		TValueType		rotation[][3] =
		{
			{
				cosYaw * cosRoll + sinYaw * sinPitch * sinRoll,
				-cosYaw * sinRoll + sinYaw * sinPitch * cosRoll,
				sinYaw * cosPitch
			},


			{
				sinRoll * cosPitch,
				cosRoll * cosPitch,
				-sinPitch
			},


			{
				-sinYaw * cosRoll + cosYaw * sinPitch * sinRoll,
				sinRoll * sinYaw + cosYaw * sinPitch * cosRoll,
				cosYaw * cosPitch
			}
		};


		// Multiply vector by matrix
		for (int row = 0; row < 3; ++row)
		{
			// Accumulator
			rowResult = static_cast<TValueType>(0);

			for (int column = 0; column < 3; ++column)
			{
				rowResult += rotation[row][column] * copy[column];
			}

			(*this)[row] = rowResult;
		}


	}


	template <CScalarType TValueType> inline
	void Vector<3, TValueType>::Rotate
	(Radian<TValueType> _angle, const Vector<3, TValueType>& _axis)
	{
		const Vector<3, TValueType>		norm = math::Normalize(_axis);
		const TValueType				xCpy = m_x, yCpy = m_y, zCpy = m_z;

		// lib math trig functions are not precise enough,
		// use the standard ones instead :(
		const TValueType			cosAngle = std::cos(_angle.Raw());
		const TValueType			sinAngle = std::sin(_angle.Raw());

		const TValueType			oneMinCos = 1.f - cosAngle;
		const Vector<3, TValueType>		oneMinAxis = norm * oneMinCos;

		// Create multiplication matrix and multiply manually
		// TODO: Clean up
		TValueType				factorX = cosAngle + norm.m_x *
			norm.m_x * oneMinCos;

		TValueType				factorY = norm.m_x * norm.m_y *
			oneMinCos - norm.m_z * sinAngle;
		TValueType				factorZ = norm.m_x * norm.m_z *
			oneMinCos + norm.m_y * sinAngle;

		m_x = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

		factorX = norm.m_y * norm.m_x *
			oneMinCos + norm.m_z * sinAngle;

		factorY = cosAngle + norm.m_y *
			norm.m_y * oneMinCos;

		factorZ = norm.m_y * norm.m_z *
			oneMinCos - norm.m_x * sinAngle;

		m_y = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

		factorX = norm.m_z * norm.m_x *
			oneMinCos - norm.m_y * sinAngle;

		factorY = norm.m_z * norm.m_y *
			oneMinCos + norm.m_x * sinAngle;

		factorZ = cosAngle + norm.m_z *
			norm.m_z * oneMinCos;

		m_z = xCpy * factorX + yCpy * factorY + factorZ * zCpy;

	}


	template <CScalarType TValueType> inline
	void Vector<3, TValueType>::Scale(const Vector<3, TValueType>& _other)
	{
		*this *= _other;
	}


	template <CScalarType TValueType> inline
	std::string Vector<3, TValueType>::String() const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << '{' << m_x << ',' << m_y << ',' << m_z << '}';

		return stream.str();
	}



	template <CScalarType TValueType> inline
	std::string Vector<3, TValueType>::StringLong() const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << "Vector3{ x:" << m_x << ", y:" << m_y << ", z:" << m_z << " }";

		return stream.str();
	}


	template <CScalarType TValueType> inline
	void Vector<3, TValueType>::Translate(const Vector<3, TValueType>& _other)
	{
		*this += _other;
	}



	template <CScalarType TValueType> inline
	TValueType& Vector<3, TValueType>::X()
	{
		return m_x;
	}


	template <CScalarType TValueType> inline
	TValueType& Vector<3, TValueType>::Y()
	{
		return m_y;
	}


	template <CScalarType TValueType> inline
	TValueType& Vector<3, TValueType>::Z()
	{
		return m_z;
	}


	template <CScalarType TValueType> inline
	TValueType Vector<3, TValueType>::GetX() const
	{
		return m_x;
	}


	template <CScalarType TValueType> inline
	TValueType Vector<3, TValueType>::GetY() const
	{
		return m_y;
	}


	template <CScalarType TValueType> inline
	TValueType Vector<3, TValueType>::GetZ() const
	{
		return m_z;
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType>& Vector<3, TValueType>::operator=
	(const Vector<3, TValueType>& _rhs)
	{
		// Copy assign
		m_x = _rhs.m_x;
		m_y = _rhs.m_y;
		m_z = _rhs.m_z;

		return *this;
	}


	template <CScalarType TValueType> inline
	TValueType& Vector<3, TValueType>::operator[](int _index)
	{
		switch (_index)
		{
		case 0:
			return m_x;
		case 1:
			return m_y;
		case 2:
			return m_z;
		default:
			throw std::logic_error("Vector index out of range");
		}
	}


	template <CScalarType TValueType> inline
	TValueType Vector<3, TValueType>::operator[](int _index) const
	{
		switch (_index)
		{
		case 0:
			return m_x;

		case 1:
			return m_y;

		case 2:
			return m_z;

		default:
			throw std::logic_error("Vector index out of range");
		}
	}


	template <CScalarType TValueType> inline
	bool Vector<3, TValueType>::operator==(const Vector<3, TValueType>& _rhs) const
	{
		// Compare all components
		return
			(
				AlmostEqual(m_x, _rhs.m_x) &&
				AlmostEqual(m_y, _rhs.m_y) &&
				AlmostEqual(m_z, _rhs.m_z)
				);
	}



	template <CScalarType TValueType> inline
	bool Vector<3, TValueType>::operator!=
	(const Vector<3, TValueType>& _rhs) const
	{
		return !(*this == _rhs);
	}


	template <CScalarType TValueType> inline
	TValueType Dot
	(const Vector<3, TValueType>& _first, const Vector<3, TValueType>& _second)
	{
		return _first.Dot(_second);
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Cross
	(const Vector<3, TValueType>& _first, const Vector<3, TValueType>& _second)
	{
		return _first.Cross(_second);
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Reflect
	(const Vector<3, TValueType>& _target, const Vector<3, TValueType>& _ontoNormal)
	{
		Vector<3, TValueType>		result = _target;

		// Return reflected copy
		result.ReflectOnto(_ontoNormal);

		return result;
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> ReflectUnit
	(const Vector<3, TValueType>& _target, const Vector<3, TValueType>& _ontoNormal)
	{
		Vector<3, TValueType>		result = _target;

		// Return reflected copy
		result.ReflectOntoUnit(_ontoNormal);

		return result;
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Project
	(const Vector<3, TValueType>& _target, const Vector<3, TValueType>& _ontoVector)
	{
		Vector<3, TValueType>		result = _target;

		// Return projected copy
		result.ProjectOnto(_ontoVector);

		return result;
	}



	template <CScalarType TValueType> inline
	Vector<3, TValueType> Normalize(const Vector<3, TValueType>& _target)
	{
		Vector<3, TValueType>		result = _target;

		// Return normalized copy
		result.Normalize();

		return result;
	}


	template <CScalarType TValueType> inline
	TValueType Distance
	(const Vector<3, TValueType>& _start, const Vector<3, TValueType>& _end)
	{
		return _start.DistanceFrom(_end);
	}


	template <CScalarType TValueType> inline
	TValueType DistanceSquared
	(const Vector<3, TValueType>& _start, const Vector<3, TValueType>& _end)
	{
		return _start.DistanceSquaredFrom(_end);
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Rotate
	(
		const Vector<3, TValueType>& _target,
		Radian<TValueType> _x, Radian<TValueType> _y, Radian<TValueType> _z
	)
	{
		Vector<3, TValueType>		result = _target;

		// Return rotated copy
		result.Rotate(_x, _y, _z);

		return result;
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Rotate
	(
		const Vector<3, TValueType>& _target,
		Radian<TValueType> _angle, const Vector<3, TValueType>& _axis
	)
	{
		Vector<3, TValueType>		result = _target;

		// Return rotated copy
		result.Rotate(_angle, _axis);

		return result;
	}


	// Component-wise operators


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::operator+
	(const Vector<3, TValueType>& _rhs) const
	{
		return Vector<3, TValueType>(m_x + _rhs.m_x, m_y + _rhs.m_y, m_z + _rhs.m_z);
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::operator-
	(const Vector<3, TValueType>& _rhs) const
	{
		return Vector<3, TValueType>(m_x - _rhs.m_x, m_y - _rhs.m_y, m_z - _rhs.m_z);
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::operator*
	(const Vector<3, TValueType>& _rhs) const
	{
		return Vector<3, TValueType>(m_x * _rhs.m_x, m_y * _rhs.m_y, m_z * _rhs.m_z);
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::operator/
	(const Vector<3, TValueType>& _rhs) const
	{
		return Vector<3, TValueType>(m_x / _rhs.m_x, m_y / _rhs.m_y, m_z / _rhs.m_z);
	}



	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::operator*(TValueType _rhs) const
	{
		return Vector<3, TValueType>(m_x * _rhs, m_y * _rhs, m_z * _rhs);
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::operator/(TValueType _rhs) const
	{
		_rhs = 1.f / _rhs;

		return Vector<3, TValueType>(m_x * _rhs, m_y * _rhs, m_z * _rhs);
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::operator-(void) const
	{
		return Vector<3, TValueType>(-m_x, -m_y, -m_z);
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType>& Vector<3, TValueType>::operator+=
	(const Vector<3, TValueType>& _rhs)
	{
		m_x += _rhs.m_x;
		m_y += _rhs.m_y;
		m_z += _rhs.m_z;

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType>& Vector<3, TValueType>::operator-=
	(const Vector<3, TValueType>& _rhs)
	{
		m_x -= _rhs.m_x;
		m_y -= _rhs.m_y;
		m_z -= _rhs.m_z;

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType>& Vector<3, TValueType>::operator*=
	(const Vector<3, TValueType>& _rhs)
	{
		m_x *= _rhs.m_x;
		m_y *= _rhs.m_y;
		m_z *= _rhs.m_z;

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType>& Vector<3, TValueType>::operator/=
	(const Vector<3, TValueType>& _rhs)
	{
		m_x /= _rhs.m_x;
		m_y /= _rhs.m_y;
		m_z /= _rhs.m_z;

		return*this;
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType>& Vector<3, TValueType>::operator*=(TValueType _rhs)
	{
		m_x *= _rhs;
		m_y *= _rhs;
		m_z *= _rhs;

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType>& Vector<3, TValueType>::operator/=(TValueType _rhs)
	{
		_rhs = 1.f / _rhs;

		m_x *= _rhs;
		m_y *= _rhs;
		m_z *= _rhs;

		return *this;
	}


	// !Component-wise operators


	// Constants


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Zero(void)
	{
		return Vector<3, TValueType>();
	}



	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::One(void)
	{
		return Vector<3, TValueType>(1.f, 1.f, 1.f);
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Up(void)
	{
		return Vector<3, TValueType>(0.f, 1.f, 0.f);
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Down(void)
	{
		return Vector<3, TValueType>(0.f, -1.f, 0.f);
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Left(void)
	{
		return Vector<3, TValueType>(-1.f, 0.f, 0.f);
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Right(void)
	{
		return Vector<3, TValueType>(1.f, 0.f, 0.f);
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Back(void)
	{
		return Vector<3, TValueType>(0.f, 0.f, -1.f);
	}


	template <CScalarType TValueType> inline
	Vector<3, TValueType> Vector<3, TValueType>::Front(void)
	{
		return Vector<3, TValueType>(0.f, 0.f, 1.f);
	}

	// !Constants


	template <CScalarType TValueType> inline
	std::ostream& operator<<(std::ostream& _os, Vector<3, TValueType> const& _vector)
	{
		// Pass components to stream
		_os << '{' << _vector.GetX() << ',' << _vector.GetY() << ',' <<
			_vector.GetZ() << '}';

		return _os;
	}


	template <CScalarType TValueType> inline
	std::istream& operator>>(std::istream& _is, Vector<3, TValueType>& _vector)
	{
		char	discard;

		// Get input from stream
		_is >> discard >> _vector.X() >> discard >> _vector.Y()
			>> discard >> _vector.Z() >> discard;

		return _is;
	}
}

namespace LibMath = math;
namespace lm = LibMath;

#endif