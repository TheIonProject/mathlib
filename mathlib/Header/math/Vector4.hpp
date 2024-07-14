/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: Vector<4, TValueType>.hpp

DESCTIPTION: 4D vector class

AUTHOR: Noah de Pischof | @torrra on GitHub

TEMPLATES:

CScalarType is a template constraint that only accepts numeric data types

*/


#ifndef __VECTOR4_H__
#define __VECTOR4_H__

#include <string>
#include <cmath>
#include <sstream>

#include "math/MathGeneric.hpp"
#include "math/VectorGeneric.hpp"

#include "math/Trigonometry.hpp"
#include "math/Arithmetic.hpp"

#include "math/Angle.hpp"

#include "math/Vector3.hpp"

namespace math
{
	template <CScalarType TValueType>
	class Vector<4, TValueType>
	{
	public:

		// Constructors / destructor

	inline			Vector(void) = default;

	inline
	explicit		Vector(TValueType _val);

	inline			Vector(TValueType _x, TValueType _y, TValueType _z, TValueType _w);

	inline			Vector(const Vector<4, TValueType>& _other);

	inline			~Vector(void) = default;

		// Get angle from this vector to another
	inline			Radian<TValueType>
					AngleFrom(const Vector<4, TValueType>& _other)					const;

		// Get angle from this vector to another unit vector
		// Should be used if this vector and the other are both
		// unit vectors
	inline			Radian<TValueType>
					AngleFromUnit(const Vector<4, TValueType>& _other)				const;

		// Get distance between 2 points
	inline	TValueType			DistanceFrom(const Vector<4, TValueType>& _other)					const;

		// Get distance squared between two points
	inline	TValueType			DistanceSquaredFrom(const Vector<4, TValueType>& _other)			const;

		// Get distance between 2 points disregarding the z and w axes
	inline	TValueType			Distance2DFrom(Vector<4, TValueType> const& _other)				const;

		// Get distance squared between two points disregarding the z and w axes
	inline	TValueType			Distance2DSquaredFrom(Vector<4, TValueType> const& _other)		const;

		// Get distance between two points disregarding the w axis
	inline	TValueType			Distance3DFrom(Vector<4, TValueType> const& _other)				const;

		// Get distance squared between two points disregarding the w axis
	inline	TValueType			Distance3DSquaredFrom(Vector<4, TValueType> const& _other)		const;


		// Compute dot product of two vectors
	inline	TValueType			Dot(const Vector<4, TValueType>& _other)							const;

		// Is this vector's magnitude longer than another ?
	inline	bool			IsLongerThan(const Vector<4, TValueType>& _other)					const;

		// Is this vector's magnitude shorter than another ?
	inline	bool			IsShorterThan(const Vector<4, TValueType>& _other)				const;

		// Is this vector's magnitude equal to 1 ?
	inline	bool			IsUnitVector(void)									const;

	inline	TValueType			Magnitude(void)										const;
	inline	TValueType			MagnitudeSquared(void)								const;

		// Adjust vector to turn into unit vector
	inline	void			Normalize(void);

		// Get copy of this vector as a unit vector
	inline	Vector<4, TValueType>			Normalized(void)									const;

		// Project this vector onto another
	inline	void			ProjectOnto(const Vector<4, TValueType>& _other);

		// Reflect this vector onto another
	inline	void			ReflectOnto(const Vector<4, TValueType>& _axis);

		// Reflect this vector onto a UNIT vector
	inline	void			ReflectOntoUnit(const Vector<4, TValueType>& _axis);

		// Rotate this vector around the all 3 axes (not w)
	inline	void			Rotate(Radian<TValueType> _angleX, Radian<TValueType> _angleY, Radian<TValueType> _angleZ);

		// Rotate this vector around an arbitrary 3D axis
	inline	void			Rotate(Radian<TValueType> _angle, const Vector3<TValueType>& _axis);

		// Multiply this vector's components by another's
	inline	void			Scale(const Vector<4, TValueType>& _other);

		// Get components as string
	inline	std::string		String(void)										const;

		// Get components as verbose string
	inline	std::string		StringLong(void)									const;

		// Add another vector's components to this one's
	inline	void			Translate(const Vector<4, TValueType>& _other);


		// Accessors

	inline	TValueType&			X(void);
	inline	TValueType&			Y(void);
	inline	TValueType&			Z(void);
	inline	TValueType&			W(void);

	inline	TValueType			GetX(void)											const;
	inline	TValueType			GetY(void)											const;
	inline	TValueType			GetZ(void)											const;
	inline	TValueType			GetW(void)											const;


	inline	Vector<4, TValueType>&		operator=(const Vector<4, TValueType>& _rhs);

	inline	TValueType&			operator[](int _index);
	inline	TValueType			operator[](int _index)								const;


		// Boolean test operators

	inline	bool			operator==(const Vector<4, TValueType>& _rhs)						const;
	inline	bool			operator!=(const Vector<4, TValueType>& _rhs)						const;


		// Component-wise operations

	inline	Vector<4, TValueType>			operator+(const Vector<4, TValueType>& _rhs)						const;
	inline	Vector<4, TValueType>			operator-(const Vector<4, TValueType>& _rhs)						const;
	inline	Vector<4, TValueType>			operator*(const Vector<4, TValueType>& _rhs)						const;
	inline	Vector<4, TValueType>			operator/(const Vector<4, TValueType>& _rhs)						const;


		// Multiply all components by a single scalar
	inline	Vector<4, TValueType>			operator*(TValueType _rhs)								const;

		// Divide all components by a single scalar
	inline	Vector<4, TValueType>			operator/(TValueType _rhs)								const;

		// Flip sign of both components
	inline	Vector<4, TValueType>			operator-(void)										const;


		// Component-wise operations

	inline	Vector<4, TValueType>&		operator+=(const Vector<4, TValueType>& _rhs);
	inline	Vector<4, TValueType>&		operator-=(const Vector<4, TValueType>& _rhs);
	inline	Vector<4, TValueType>&		operator*=(const Vector<4, TValueType>& _rhs);
	inline	Vector<4, TValueType>&		operator/=(const Vector<4, TValueType>& _rhs);

		// Multiply all components by a single scalar
	inline	Vector<4, TValueType>&		operator*=(TValueType _rhs);

		// Divide all components by a single scalar
	inline	Vector<4, TValueType>&		operator/=(TValueType _rhs);


		// Constants

	inline	static Vector<4, TValueType>	Zero(void);
	inline	static Vector<4, TValueType>	One(void);
	inline	static Vector<4, TValueType>	Up(void);
	inline	static Vector<4, TValueType>	Down(void);
	inline	static Vector<4, TValueType>	Left(void);
	inline	static Vector<4, TValueType>	Right(void);
	inline	static Vector<4, TValueType>  Back(void);
	inline	static Vector<4, TValueType>  Front(void);


	private:

		TValueType				m_x = 0.f;
		TValueType				m_y = 0.f;
		TValueType				m_z = 0.f;
		TValueType				m_w = 0.f;
	};

	// Non-member functions (similar to member functions but provided for readability)
	template <CScalarType TValueType> inline
	TValueType				Dot(const Vector<4, TValueType>& _first, const Vector<4, TValueType>& _second);

	template <CScalarType TValueType> inline
	Vector<4, TValueType>				Reflect(const Vector<4, TValueType>& _target, const Vector<4, TValueType>& _ontoNormal);

	template <CScalarType TValueType> inline
	Vector<4, TValueType>				ReflectUnit(const Vector<4, TValueType>& _target, const Vector<4, TValueType>& _ontoNormal);

	template <CScalarType TValueType> inline
	Vector<4, TValueType>				Project(const Vector<4, TValueType>& _target, const Vector<4, TValueType>& _ontoVector);


	template <CScalarType TValueType> inline
	Vector<4, TValueType>				Normalize(const Vector<4, TValueType>& _target);


	template <CScalarType TValueType> inline
	TValueType				Distance(const Vector<4, TValueType>& _start, const Vector<4, TValueType>& _end);

	template <CScalarType TValueType> inline
	TValueType				DistanceSquared(const Vector<4, TValueType>& _start, const Vector<4, TValueType>& _end);

	template <CScalarType TValueType> inline
	Vector<4, TValueType>				Rotate
	(
		const Vector<4, TValueType>& _target, Radian<TValueType> _angleX, Radian<TValueType> _angleY, Radian<TValueType> _angleZ
	);


	template <CScalarType TValueType> inline
	Vector<4, TValueType>				Rotate
	(
		const Vector<4, TValueType>& _target, Radian<TValueType> _angle, const Vector3<TValueType>& _axis
	);


	// Send a vector's components to an output stream
	template <CScalarType TValueType> inline
	std::ostream& operator<<(std::ostream& _os, Vector<4, TValueType> const& _vector);

	// Get components from an input stream
	template <CScalarType TValueType> inline
	std::istream& operator>>(std::istream& _is, Vector<4, TValueType>& _vector);







/// ---- Implementation ----


	template <CScalarType TValueType> inline
	Vector<4, TValueType>::Vector(TValueType _val)
		: m_x(_val), m_y(_val), m_z(_val), m_w(_val)
	{}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>::Vector(TValueType _x, TValueType _y, TValueType _z, TValueType _w)
		: m_x(_x), m_y(_y), m_z(_z), m_w(_w)
	{}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>::Vector(const Vector<4, TValueType>& _other)
		: m_x(_other.m_x), m_y(_other.m_y), m_z(_other.m_z), m_w(_other.m_w)
	{}


	template <CScalarType TValueType> inline
	Radian<TValueType> Vector<4, TValueType>::AngleFrom(const Vector<4, TValueType>& _other) const
	{
		TValueType		magnitudes = MagnitudeSquared() * _other.MagnitudeSquared();

		// Only run square root once
		magnitudes = SquareRoot(magnitudes);

		// Transform dot product equation to get cos angle,
		// then run acos
		return Acos(Dot(_other) / magnitudes);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Vector<4, TValueType>::AngleFromUnit(const Vector<4, TValueType>& _other) const
	{
		// Clamp dot to avoid acos domain error (NaN result)
		// and call acos as both vectors are assumed to be
		// unit vectors
		return Acos(Clamp(Dot(_other), MIN_COS, MAX_COS));
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::DistanceFrom(const Vector<4, TValueType>& _other) const
	{
		return SquareRoot(DistanceSquaredFrom(_other));
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::DistanceSquaredFrom(const Vector<4, TValueType>& _other) const
	{
		// Find distance vector and get magnitude
		return (_other - *this).MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::Distance2DFrom(Vector<4, TValueType> const& _other) const
	{
		// Ignore z and w axes
		Vector2<TValueType>		self2D = { m_x, m_y };
		Vector2<TValueType>		other2D = { _other.m_x, _other.m_y };


		return self2D.DistanceFrom(other2D);
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::Distance2DSquaredFrom(Vector<4, TValueType> const& _other) const
	{
		// Ignore z and w axes
		Vector2<TValueType>		self2D = { m_x, m_y };
		Vector2<TValueType>		other2D = { _other.m_x, _other.m_y };


		return self2D.DistanceSquaredFrom(other2D);
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::Distance3DFrom(Vector<4, TValueType> const& _other) const
	{
		// Ignore w axis
		Vector3<TValueType>		self3D = { m_x, m_y, m_z };
		Vector3<TValueType>		other3D = { _other.m_x, _other.m_y, _other.m_z };


		return self3D.DistanceFrom(other3D);
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::Distance3DSquaredFrom(Vector<4, TValueType> const& _other) const
	{
		// Ignore w axis
		Vector3<TValueType>		self3D = { m_x, m_y, m_z };
		Vector3<TValueType>		other3D = { _other.m_x, _other.m_y, _other.m_z };


		return self3D.DistanceSquaredFrom(other3D);
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::Dot(const Vector<4, TValueType>& _other) const
	{
		// Multiply components
		return (m_x * _other.m_x) + (m_y * _other.m_y) +
			(m_z * _other.m_z) + (m_w * _other.m_w);
	}


	template <CScalarType TValueType> inline
	bool Vector<4, TValueType>::IsLongerThan(const Vector<4, TValueType>& _other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() > _other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	bool Vector<4, TValueType>::IsShorterThan(const Vector<4, TValueType>& _other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() < _other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	bool Vector<4, TValueType>::IsUnitVector(void) const
	{
		// 1 squared == 1 so avoiding sqrt call is possible
		return AlmostEqual(MagnitudeSquared(), 1.f);
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::Magnitude(void) const
	{
		return SquareRoot(MagnitudeSquared());
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::MagnitudeSquared(void) const
	{
		// Square components
		return Dot(*this);
	}


	template <CScalarType TValueType> inline
	void Vector<4, TValueType>::Normalize(void)
	{
		// Only divide once
		TValueType		invMagnitude = Magnitude();

		if (AlmostEqual(invMagnitude, 0.f, std::numeric_limits<TValueType>::epsilon()))
		{
			throw std::logic_error("Cannot divide by zero magnitude");
		}

		else
			invMagnitude = 1.f / invMagnitude;


		m_x *= invMagnitude;
		m_y *= invMagnitude;
		m_z *= invMagnitude;
		m_w *= invMagnitude;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Normalized(void) const
	{
		Vector<4, TValueType>		result = *this;

		result.Normalize();

		// Return normalized copy
		return result;
	}


	template <CScalarType TValueType> inline
	void Vector<4, TValueType>::ProjectOnto(const Vector<4, TValueType>& _other)
	{
		// Apply projection formula
		TValueType		squareMagnitude = _other.MagnitudeSquared();
		TValueType		projFactor = Dot(_other) / squareMagnitude;

		m_x = _other.m_x * projFactor;
		m_y = _other.m_y * projFactor;
		m_z = _other.m_z * projFactor;
		m_w = _other.m_w * projFactor;
	}


	template <CScalarType TValueType> inline
	void Vector<4, TValueType>::ReflectOnto(const Vector<4, TValueType>& _axis)
	{
		// Only reflect onto unit vector
		Vector<4, TValueType>		normal = math::Normalize(_axis);

		*this -= normal * (Dot(normal) * 2.f);
	}


	template <CScalarType TValueType> inline
	void Vector<4, TValueType>::ReflectOntoUnit(const Vector<4, TValueType>& _axis)
	{
		// Assume normal is already unit vector and skip normalize call
		*this -= _axis * (Dot(_axis) * 2.f);
	}



	template <CScalarType TValueType> inline
	void Vector<4, TValueType>::Rotate(Radian<TValueType> _angleX, Radian<TValueType> _angleY, Radian<TValueType> _angleZ)
	{
		Vector<4, TValueType>		copy = *this;

		TValueType		cosYaw = Cos(_angleZ), sinYaw = Sin(_angleZ);
		TValueType		cosPitch = Cos(_angleX), sinPitch = Sin(_angleX);
		TValueType		cosRoll = Cos(_angleY), sinRoll = Sin(_angleY);
		TValueType		rowResult;

		// Create rotation matrix
		TValueType		rotation[][4] =
		{
			{
				cosYaw * cosRoll + sinYaw * sinPitch * sinRoll,
				-cosYaw * sinRoll + sinYaw * sinPitch * cosRoll,
				sinYaw * cosPitch,
				0.f
			},


			{
				sinRoll * cosPitch,
				cosRoll * cosPitch,
				-sinPitch,
				0.f
			},


			{
				-sinYaw * cosRoll + cosYaw * sinPitch * sinRoll,
				sinRoll * sinYaw + cosYaw * sinPitch * cosRoll,
				cosYaw * cosPitch,
				0.f
			},

			{ 0.f, 0.f, 0.f, 1.f}
		};


		for (int row = 0; row < 4; ++row)
		{
			rowResult = 0.f;

			for (int column = 0; column < 4; ++column)
			{
				rowResult += rotation[row][column] * copy[column];
			}

			(*this)[row] = rowResult;
		}


	}



	template <CScalarType TValueType> inline
	void Vector<4, TValueType>::Rotate(Radian<TValueType> _angle, const Vector3<TValueType>& _axis)
	{
		// Ignore w axis
		Vector3<TValueType>		self3D = { m_x, m_y, m_z };

		// Rotate without w
		self3D.Rotate(_angle, _axis);

		m_x = self3D.GetX();
		m_y = self3D.GetY();
		m_z = self3D.GetZ();
	}


	template <CScalarType TValueType> inline
	void Vector<4, TValueType>::Scale(const Vector<4, TValueType>& _other)
	{
		*this *= _other;
	}



	template <CScalarType TValueType> inline
	std::string Vector<4, TValueType>::String(void) const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << '{' << m_x << ',' << m_y << ',' << m_z << ',' << m_w << '}';

		return stream.str();
	}


	template <CScalarType TValueType> inline
	std::string Vector<4, TValueType>::StringLong(void) const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << "Vector4{ x:" << m_x << ", y:" << m_y << ", z:"
			<< m_z << ", w:" << m_w << " }";

		return stream.str();
	}



	template <CScalarType TValueType> inline
	void Vector<4, TValueType>::Translate(const Vector<4, TValueType>& _other)
	{
		*this += _other;
	}


	template <CScalarType TValueType> inline
	TValueType& Vector<4, TValueType>::X(void)
	{
		return m_x;
	}



	template <CScalarType TValueType> inline
	TValueType& Vector<4, TValueType>::Y(void)
	{
		return m_y;
	}



	template <CScalarType TValueType> inline
	TValueType& Vector<4, TValueType>::Z(void)
	{
		return m_z;
	}


	template <CScalarType TValueType> inline
	TValueType& Vector<4, TValueType>::W(void)
	{
		return m_w;
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::GetX(void) const
	{
		return m_x;
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::GetY(void) const
	{
		return m_y;
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::GetZ(void) const
	{
		return m_z;
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::GetW(void) const
	{
		return m_w;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Vector<4, TValueType>::operator=(const Vector<4, TValueType>& _rhs)
	{
		// Copy assign
		m_x = _rhs.m_x;
		m_y = _rhs.m_y;
		m_z = _rhs.m_z;
		m_w = _rhs.m_w;

		return *this;
	}


	template <CScalarType TValueType> inline
	TValueType& Vector<4, TValueType>::operator[](int _index)
	{
		switch (_index)
		{
		case 0:
			return m_x;
		case 1:
			return m_y;
		case 2:
			return m_z;
		case 3:
			return m_w;
		default:
			throw std::logic_error("Vector index out of range");
		}
	}


	template <CScalarType TValueType> inline
	TValueType Vector<4, TValueType>::operator[](int _index) const
	{
		switch (_index)
		{
		case 0:
			return m_x;
		case 1:
			return m_y;
		case 2:
			return m_z;
		case 3:
			return m_w;
		default:
			throw std::logic_error("Vector index out of range");
		}
	}



	template <CScalarType TValueType> inline
	bool Vector<4, TValueType>::operator==(const Vector<4, TValueType>& _rhs) const
	{
		// Compare all components
		return
			(
				AlmostEqual(m_x, _rhs.m_x) &&
				AlmostEqual(m_y, _rhs.m_y) &&
				AlmostEqual(m_z, _rhs.m_z) &&
				AlmostEqual(m_w, _rhs.m_w)

				);
	}



	template <CScalarType TValueType> inline
	bool Vector<4, TValueType>::operator!=(const Vector<4, TValueType>& _rhs) const
	{
		return !(*this == _rhs);
	}


	// Component-wise operators


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::operator+(const Vector<4, TValueType>& _rhs) const
	{
		return Vector<4, TValueType>(m_x + _rhs.m_x, m_y + _rhs.m_y,
			m_z + _rhs.m_z, m_w + _rhs.m_w);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::operator-(const Vector<4, TValueType>& _rhs) const
	{
		return Vector<4, TValueType>(m_x - _rhs.m_x, m_y - _rhs.m_y,
			m_z - _rhs.m_z, m_w - _rhs.m_w);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::operator*(const Vector<4, TValueType>& _rhs) const
	{
		return Vector<4, TValueType>(m_x * _rhs.m_x, m_y * _rhs.m_y,
			m_z * _rhs.m_z, m_w * _rhs.m_w);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::operator/(const Vector<4, TValueType>& _rhs) const
	{
		return Vector<4, TValueType>(m_x / _rhs.m_x, m_y / _rhs.m_y,
			m_z / _rhs.m_z, m_w / _rhs.m_w);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::operator*(TValueType _rhs) const
	{
		return Vector<4, TValueType>(m_x * _rhs, m_y * _rhs,
			m_z * _rhs, m_w * _rhs);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::operator/(TValueType _rhs) const
	{
		_rhs = 1.f / _rhs;

		return Vector<4, TValueType>(m_x * _rhs, m_y * _rhs, m_z * _rhs, m_w * _rhs);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::operator-(void) const
	{
		return Vector<4, TValueType>(-m_x, -m_y, -m_z, -m_w);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Vector<4, TValueType>::operator+=(const Vector<4, TValueType>& _rhs)
	{
		m_x += _rhs.m_x;
		m_y += _rhs.m_y;
		m_z += _rhs.m_z;
		m_w += _rhs.m_w;

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Vector<4, TValueType>::operator-=(const Vector<4, TValueType>& _rhs)
	{
		m_x -= _rhs.m_x;
		m_y -= _rhs.m_y;
		m_z -= _rhs.m_z;
		m_w -= _rhs.m_w;

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Vector<4, TValueType>::operator*=(const Vector<4, TValueType>& _rhs)
	{
		m_x *= _rhs.m_x;
		m_y *= _rhs.m_y;
		m_z *= _rhs.m_z;
		m_w *= _rhs.m_w;

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Vector<4, TValueType>::operator/=(const Vector<4, TValueType>& _rhs)
	{
		m_x /= _rhs.m_x;
		m_y /= _rhs.m_y;
		m_z /= _rhs.m_z;
		m_w /= _rhs.m_w;

		return*this;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Vector<4, TValueType>::operator*=(TValueType _rhs)
	{
		m_x *= _rhs;
		m_y *= _rhs;
		m_z *= _rhs;
		m_w *= _rhs;

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Vector<4, TValueType>::operator/=(TValueType _rhs)
	{
		_rhs = 1.f / _rhs;

		m_x *= _rhs;
		m_y *= _rhs;
		m_z *= _rhs;
		m_w *= _rhs;

		return *this;
	}


	// !Component-wise operators


	// Constants


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Zero(void)
	{
		return Vector<4, TValueType>();
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::One(void)
	{
		return Vector<4, TValueType>(1.f, 1.f, 1.f, 1.f);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Up(void)
	{
		return Vector<4, TValueType>(0.f, 1.f, 0.f, 0.f);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Down(void)
	{
		return Vector<4, TValueType>(0.f, -1.f, 0.f, 0.f);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Left(void)
	{
		return Vector<4, TValueType>(-1.f, 0.f, 0.f, 0.f);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Right(void)
	{
		return Vector<4, TValueType>(1.f, 0.f, 0.f, 0.f);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Back(void)
	{
		return Vector<4, TValueType>(0.f, 0.f, -1.f, 0.f);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Vector<4, TValueType>::Front(void)
	{
		return Vector<4, TValueType>(0.f, 0.f, 1.f, 0.f);
	}


	// !Constants


	template <CScalarType TValueType> inline
	TValueType Dot(const Vector<4, TValueType>& _first, const Vector<4, TValueType>& _second)
	{
		return _first.Dot(_second);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Reflect(const Vector<4, TValueType>& _target, const Vector<4, TValueType>& _ontoNormal)
	{
		Vector<4, TValueType>		copy = _target;

		// Return reflected copy
		copy.ReflectOnto(_ontoNormal);

		return copy;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> ReflectUnit(const Vector<4, TValueType>& _target, const Vector<4, TValueType>& _ontoNormal)
	{
		Vector<4, TValueType>		copy = _target;

		// Return reflected copy
		copy.ReflectOntoUnit(_ontoNormal);

		return copy;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Project(const Vector<4, TValueType>& _target, const Vector<4, TValueType>& _ontoVector)
	{
		Vector<4, TValueType>		copy = _target;

		// Return projected copy
		copy.ProjectOnto(_ontoVector);

		return copy;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Normalize(const Vector<4, TValueType>& _target)
	{
		// Return normalized copy
		return _target.Normalized();
	}


	template <CScalarType TValueType> inline
	TValueType Distance(const Vector<4, TValueType>& _start, const Vector<4, TValueType>& _end)
	{
		return _start.DistanceFrom(_end);
	}


	template <CScalarType TValueType> inline
	TValueType DistanceSquared(const Vector<4, TValueType>& _start, const Vector<4, TValueType>& _end)
	{
		return _start.DistanceSquaredFrom(_end);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Rotate(const Vector<4, TValueType>& _target, Radian<TValueType> _angleX, Radian<TValueType> _angleY, Radian<TValueType> _angleZ)
	{
		Vector<4, TValueType>		copy = _target;

		// Return rotated copy
		copy.Rotate(_angleX, _angleY, _angleZ);

		return copy;
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Rotate(const Vector<4, TValueType>& _target, Radian<TValueType> _angle, const Vector3<TValueType>& _axis)
	{
		Vector<4, TValueType>		copy = _target;

		// Return rotated copy
		copy.Rotate(_angle, _axis);

		return copy;
	}


	template <CScalarType TValueType> inline
	std::ostream& operator<<(std::ostream& _os, Vector<4, TValueType> const& _vector)
	{
		// Pass components to stream
		_os << '{' << _vector.GetX() << ',' << _vector.GetY()
			<< ',' << _vector.GetZ() << ',' << _vector.GetW() << '}';

		return _os;
	}

	template <CScalarType TValueType> inline
	std::istream& operator>>(std::istream& _is, Vector<4, TValueType>& _vector)
	{
		char	discard;

		// Get input from stream
		_is >> discard >> _vector.X() >> discard >> _vector.Y()
			>> discard >> _vector.Z() >> discard >> _vector.W() >> discard;

		return _is;
	}


}

namespace LibMath = math;
namespace lm = LibMath;


#endif