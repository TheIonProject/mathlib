/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: Vector2.hpp

DESCTIPTION: 2D vector class

AUTHOR: Noah de Pischof | @torrra on GitHub

TEMPLATES:

CScalarType is a template constraint that only accepts numeric data types

*/



#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <string>
#include <sstream>

#include "math/MathGeneric.hpp"
#include "math/VectorGeneric.hpp"


#include "math/Angle.hpp"
#include "Trigonometry.hpp"


namespace math
{

	template <CScalarType TValueType>
	class Vector<2, TValueType>
	{
	public:
		// Constructors / destructor

		inline				Vector(void) = default;

		inline
		explicit			Vector(TValueType _val);

		inline				Vector(TValueType _x, TValueType _y);
		inline				Vector(const Vector& _other );

		inline				~Vector(void) = default;

		// Get angle from this vector to another
		inline
		Radian<TValueType>			AngleFrom(const Vector& _other)					const;

		// Get angle from this vector to another unit vector
		// Should be used if this vector and the other are both
		// unit vectors
		inline
		Radian<TValueType>			AngleFromUnit(const Vector& _other)				const;

		// Compute cross product with another
		// this x other
		inline TValueType			Cross(const Vector& _other)						const;

		// Get distance between 2 points
		inline TValueType			DistanceFrom(const Vector& _other)					const;

		// Get distance squared between two points
		inline TValueType			DistanceSquaredFrom(const Vector& _other)			const;

		// Compute dot product of two vectors
		inline TValueType			Dot(const Vector& _other)							const;

		// Is this vector's magnitude longer than another ?
		inline bool			IsLongerThan(const Vector& _other)					const;

		// Is this vector's magnitude shorter than another ?
		inline bool			IsShorterThan(const Vector& _other)				const;

		// Is this vector's magnitude equal to 1 ?
		inline bool			IsUnitVector(void)									const;

		inline TValueType			Magnitude(void)										const;
		inline TValueType			MagnitudeSquared(void)								const;

		// Adjust vector to turn into unit vector
		inline void			Normalize(void);

		// Get copy of this vector as a unit vector
		inline Vector			Normalized(void)									const;

		// Get vector normal to this one
		inline Vector			Normal(void)										const;

		// Project this vector onto another
		inline void			ProjectOnto(const Vector& _other);

		// Reflect this vector onto another
		inline void			ReflectOnto(const Vector& _axis);

		// Reflect this vector onto a UNIT vector
		inline void			ReflectOntoUnit(const Vector& _axis);

		// Rotate this point around the z axis
		inline void			Rotate(Radian<TValueType> _angle);

		// Multiply this vector's components by another's
		inline void			Scale(const Vector& _other);

		// Get components as string
		inline std::string		String(void)										const;

		// Get components as verbose string
		inline std::string		StringLong(void)									const;

		// Add another vector's components to this one's
		inline void			Translate(const Vector& _other);

		// Accessors

		inline TValueType&			X(void);
		inline TValueType&			Y(void);

		inline TValueType			GetX(void)											const;
		inline TValueType			GetY(void)											const;


		inline Vector&		operator=(const Vector& _rhs);

		inline TValueType&			operator[](int _index);
		inline TValueType			operator[](int _index)								const;

		// Boolean test operators

		inline bool			operator==(const Vector& _rhs)						const;
		inline bool			operator!=(const Vector& _rhs)						const;

		// Component-wise operations

		inline Vector			operator+(const Vector& _rhs)						const;
		inline Vector			operator-(const Vector& _rhs)						const;
		inline Vector			operator*(const Vector& _rhs)						const;
		inline Vector			operator/(const Vector& _rhs)						const;

		// Multiply all components by a single scalar
		inline Vector			operator*(TValueType _rhs)								const;

		// Divide all components by a single scalar
		inline Vector			operator/(TValueType _rhs)								const;

		// Flip sign of both componenents
		inline Vector			operator-(void)										const;


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


	private:

		TValueType				m_x;
		TValueType				m_y;
	};


	// Non-member functions (similar to member functions but provided for readability)

	template <CScalarType TValueType> inline
	TValueType				Dot(const Vector<2, TValueType>& _first, const Vector<2, TValueType>& _second);
	
	template <CScalarType TValueType> inline
	TValueType				Cross(const Vector<2, TValueType>& _first, const Vector<2, TValueType>& _second);


	template <CScalarType TValueType> inline
	Vector<2, TValueType>				Reflect(const Vector<2, TValueType>& _target, const Vector<2, TValueType>& _ontoNormal);
	
	template <CScalarType TValueType> inline
	Vector<2, TValueType>				ReflectUnit(const Vector<2, TValueType>& _target, const Vector<2, TValueType>& _ontoNormal);
	
	template <CScalarType TValueType> inline
	Vector<2, TValueType>				Project(const Vector<2, TValueType>& _target, const Vector<2, TValueType>& _ontoVector);

	
	template <CScalarType TValueType> inline
	Vector<2, TValueType>				Normalize(const Vector<2, TValueType>& _target);


	template <CScalarType TValueType> inline
	TValueType				Distance(const Vector<2, TValueType>& _start, const Vector<2, TValueType>& _end);
	
	
	template <CScalarType TValueType> inline
	TValueType				DistanceSquared(const Vector<2, TValueType>& _start, const Vector<2, TValueType>& _end);


	template <CScalarType TValueType> inline
	Vector<2, TValueType>				Rotate(const Vector<2, TValueType>& _target, Radian<TValueType> _angle);

	
	// Send a Vector<2, TValueType>'s components to an output stream
	template <CScalarType TValueType> inline
	std::ostream&		operator<<(std::ostream& _os, Vector<2, TValueType> const& _vector);

	// Get components from an input stream
	template <CScalarType TValueType> inline
	std::istream&		operator>>(std::istream& _is, Vector<2, TValueType>& _vector);





// ---- Implementation ----


	template <CScalarType TValueType> inline
	Vector<2, TValueType>::Vector(TValueType _val)
		: m_x(_val), m_y(_val) {}

	template <CScalarType TValueType> inline
	Vector<2, TValueType>::Vector(TValueType _x, TValueType _y)
		: m_x(_x), m_y(_y) {}


	template <CScalarType TValueType> inline
	Vector<2, TValueType>::Vector(const Vector<2, TValueType>& _other)
		: m_x(_other.m_x), m_y(_other.m_y) {}


	template <CScalarType TValueType> inline
	Radian<TValueType> Vector<2, TValueType>::AngleFrom(const Vector<2, TValueType>& _other) const
	{
		TValueType		magnitudes = MagnitudeSquared() * _other.MagnitudeSquared();

		// Only run square root once
		magnitudes = SquareRoot(magnitudes);

		// Transform dot product equation to get cos angle,
		// then run acos
		return Acos(Dot(_other) / magnitudes);
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Vector<2, TValueType>::AngleFromUnit(const Vector<2, TValueType>& _other) const
	{
		// Clamp dot to avoid acos domain error (NaN result)
		// and call acos as both vectors are assumed to be
		// unit vectors
		return Acos(Clamp(Dot(_other), MIN_COS, MAX_COS));
	}


	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::Cross(const Vector<2, TValueType>& _other) const
	{
		// Only compute result for result's  z component as
		// both x and y will be zero for vec2 cross product
		return (m_x * _other.m_y) - (m_y * _other.m_x);
	}


	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::DistanceFrom(const Vector<2, TValueType>& _other) const
	{
		return SquareRoot(DistanceSquaredFrom(_other));
	}


	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::DistanceSquaredFrom(const Vector<2, TValueType>& _other) const
	{
		// Find distance vector and get magnitude
		return (_other - *this).MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::Dot(const Vector<2, TValueType>& _other) const
	{
		// Multiply components
		return (m_x * _other.m_x) + (m_y * _other.m_y);
	}


	template <CScalarType TValueType> inline
	bool Vector<2, TValueType>::IsLongerThan(const Vector<2, TValueType>& _other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() > _other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	bool Vector<2, TValueType>::IsShorterThan(const Vector<2, TValueType>& _other) const
	{
		// Compare squared magnitudes to avoid two sqrt calls
		return MagnitudeSquared() < _other.MagnitudeSquared();
	}


	template <CScalarType TValueType> inline
	bool Vector<2, TValueType>::IsUnitVector() const
	{
		// 1 squared == 1 so avoiding sqrt call is possible
		return AlmostEqual(MagnitudeSquared(), 1.f);
	}


	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::Magnitude() const
	{
		return SquareRoot(MagnitudeSquared());
	}

	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::MagnitudeSquared() const
	{
		// Square components
		return Dot(*this);
	}


	template <CScalarType TValueType> inline
	void Vector<2, TValueType>::Normalize()
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
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::Normalized(void) const
	{
		Vector<2, TValueType>		result = *this;

		result.Normalize();

		// Return normalized copy
		return result;
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::Normal(void) const
	{
		// Swap x and y and flip one sign (y here)
		return Vector<2, TValueType>(-m_y, m_x);
	}



	template <CScalarType TValueType> inline
	void Vector<2, TValueType>::ProjectOnto(const Vector<2, TValueType>& _other)
	{
		// Apply projection formula
		TValueType		squareMagnitude = _other.MagnitudeSquared();
		TValueType		projFactor = Dot(_other) / squareMagnitude;

		m_x = _other.m_x * projFactor;
		m_y = _other.m_y * projFactor;

	}



	template <CScalarType TValueType> inline
	void Vector<2, TValueType>::ReflectOnto(const Vector<2, TValueType>& _axis)
	{
		// Only reflect onto unit vector
		Vector<2, TValueType>		normal = math::Normalize(_axis);

		// Apply reflection formula
		*this -= normal * (Dot(normal) * 2.f);
	}


	template <CScalarType TValueType> inline
	void Vector<2, TValueType>::ReflectOntoUnit(const Vector<2, TValueType>& _axis)
	{
		// Assume normal is already unit vector and skip normalize call
		*this -= _axis * (Dot(_axis) * 2.f);
	}



	template <CScalarType TValueType> inline
	void Vector<2, TValueType>::Rotate(Radian<TValueType> _angle)
	{
		TValueType		cosAngle = Cos(_angle),
					sinAngle = Sin(_angle);

		// Copy x as base x value is needed for
		// both x and y results
		TValueType		xCopy = m_x;

		// Manually multiply by 2x2 rotation matrix
		m_x = cosAngle * xCopy - m_y * sinAngle;
		m_y = sinAngle * xCopy + m_y * cosAngle;
	}



	template <CScalarType TValueType> inline
	void Vector<2, TValueType>::Scale(const Vector<2, TValueType>& _other)
	{
		*this *= _other;
	}


	template <CScalarType TValueType> inline
	std::string Vector<2, TValueType>::String() const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream
		stream << '{' << m_x << ',' << m_y << '}';

		return stream.str();
	}


	template <CScalarType TValueType> inline
	std::string Vector<2, TValueType>::StringLong() const
	{
		// Use stream for easy conversion
		std::stringstream		stream;

		// Pass components to stream with some extra
		stream << "Vector2{ x:" << m_x << ", y:" << m_y << " }";

		return stream.str();
	}


	template <CScalarType TValueType> inline
	void Vector<2, TValueType>::Translate(const Vector<2, TValueType>& _other)
	{
		*this += _other;
	}



	template <CScalarType TValueType> inline
	TValueType& Vector<2, TValueType>::X()
	{
		return m_x;
	}



	template <CScalarType TValueType> inline
	TValueType& Vector<2, TValueType>::Y()
	{
		return m_y;
	}



	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::GetX() const
	{
		return m_x;
	}


	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::GetY() const
	{
		return m_y;
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType>& Vector<2, TValueType>::operator=(const Vector<2, TValueType>& _rhs)
	{
		// Copy assign
		m_x = _rhs.m_x;
		m_y = _rhs.m_y;

		return *this;
	}


	template <CScalarType TValueType> inline
	TValueType& Vector<2, TValueType>::operator[](int _index)
	{
		switch (_index)
		{
		case 0:
			return m_x;

		case 1:
			return m_y;

		default:
			throw std::logic_error("Index out of range");
		}
	}


	template <CScalarType TValueType> inline
	TValueType Vector<2, TValueType>::operator[](int _index) const
	{
		switch (_index)
		{
		case 0:
			return m_x;

		case 1:
			return m_y;

		default:
			throw std::logic_error("Index out of range");
		}
	}


	template <CScalarType TValueType> inline
	bool Vector<2, TValueType>::operator==(const Vector<2, TValueType>& _rhs) const
	{
		// Compare both components
		return
		(
			AlmostEqual(m_x, _rhs.m_x) &&
			AlmostEqual(m_y, _rhs.m_y)
		);
	}



	template <CScalarType TValueType> inline
	bool Vector<2, TValueType>::operator!=(const Vector<2, TValueType>& _rhs) const
	{
		return !(*this == _rhs);
	}


	template <CScalarType TValueType> inline
	TValueType Dot(const Vector<2, TValueType>& _first, const Vector<2, TValueType>& _second)
	{
		return _first.Dot(_second);
	}


	template <CScalarType TValueType> inline
	TValueType Cross(const Vector<2, TValueType>& _first, const Vector<2, TValueType>& _second)
	{
		return _first.Cross(_second);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Reflect(const Vector<2, TValueType>& _target, const Vector<2, TValueType>& _ontoNormal)
	{
		Vector<2, TValueType>		result = _target;

		// Return reflected copy
		result.ReflectOnto(_ontoNormal);

		return result;
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> ReflectUnit(const Vector<2, TValueType>& _target, const Vector<2, TValueType>& _ontoNormal)
	{
		Vector<2, TValueType>		result = _target;

		// Return reflected copy
		result.ReflectOntoUnit(_ontoNormal);

		return result;
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Project(const Vector<2, TValueType>& _target, const Vector<2, TValueType>& _ontoVector)
	{
		Vector<2, TValueType>		result = _target;

		// Return projected copy
		result.ProjectOnto(_ontoVector);

		return result;
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType> Normalize(const Vector<2, TValueType>& _target)
	{
		Vector<2, TValueType>		result = _target;

		// Return normalized copy
		result.Normalize();

		return result;
	}


	template <CScalarType TValueType> inline
	TValueType Distance(const Vector<2, TValueType>& _start, const Vector<2, TValueType>& _end)
	{
		return _start.DistanceFrom(_end);
	}


	template <CScalarType TValueType> inline
	TValueType DistanceSquared(const Vector<2, TValueType>& _start, const Vector<2, TValueType>& _end)
	{
		return _start.DistanceSquaredFrom(_end);
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType> Rotate(const Vector<2, TValueType>& _target, Radian<TValueType> _angle)
	{
		Vector<2, TValueType>		result = _target;

		// Return rotated copy
		result.Rotate(_angle);

		return result;
	}


	// Component-wise operators


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::operator+(const Vector<2, TValueType>& _rhs) const
	{
		return Vector<2, TValueType>(m_x + _rhs.m_x, m_y + _rhs.m_y);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::operator-(const Vector<2, TValueType>& _rhs) const
	{
		return Vector<2, TValueType>(m_x - _rhs.m_x, m_y - _rhs.m_y);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::operator*(const Vector<2, TValueType>& _rhs) const
	{
		return Vector<2, TValueType>(m_x * _rhs.m_x, m_y * _rhs.m_y);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::operator/(const Vector<2, TValueType>& _rhs) const
	{
		return Vector<2, TValueType>(m_x /_rhs.m_x, m_y / _rhs.m_y);
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::operator*(TValueType _rhs) const
	{
		return Vector<2, TValueType>(m_x * _rhs, m_y * _rhs);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::operator/(TValueType _rhs) const
	{
		_rhs = 1.f / _rhs;

		return Vector<2, TValueType>(m_x * _rhs, m_y * _rhs);
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::operator-(void) const
	{
		return Vector<2, TValueType>(-m_x, -m_y);
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType>& Vector<2, TValueType>::operator+=(const Vector<2, TValueType>& _rhs)
	{
		m_x += _rhs.m_x;
		m_y += _rhs.m_y;

		return *this;
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType>& Vector<2, TValueType>::operator-=(const Vector<2, TValueType>& _rhs)
	{
		m_x -= _rhs.m_x;
		m_y -= _rhs.m_y;

		return *this;
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType>& Vector<2, TValueType>::operator*=(const Vector<2, TValueType>& _rhs)
	{
		m_x *= _rhs.m_x;
		m_y *= _rhs.m_y;

		return *this;
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType>& Vector<2, TValueType>::operator/=(const Vector<2, TValueType>& _rhs)
	{
		m_x /= _rhs.m_x;
		m_y /= _rhs.m_y;

		return* this;
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType>& Vector<2, TValueType>::operator*=(TValueType _rhs)
	{
		m_x *= _rhs;
		m_y *= _rhs;

		return *this;
	}



	template <CScalarType TValueType> inline
	Vector<2, TValueType>& Vector<2, TValueType>::operator/=(TValueType _rhs)
	{
		_rhs = 1.f / _rhs;

		m_x *= _rhs;
		m_y *= _rhs;

		return *this;
	}

	// !Component-wise operators


	// Constants


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::Zero(void)
	{
		return Vector<2, TValueType>();
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::One(void)
	{
		return Vector<2, TValueType>(1.f, 1.f);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::Up(void)
	{
		return Vector<2, TValueType>(0.f, 1.f);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::Down(void)
	{
		return Vector<2, TValueType>(0.f, -1.f);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::Left(void)
	{
		return Vector<2, TValueType>(-1.f, 0.f);
	}


	template <CScalarType TValueType> inline
	Vector<2, TValueType> Vector<2, TValueType>::Right(void)
	{
		return Vector<2, TValueType>(1.f, 0.f);
	}

	// !Constants


	template <CScalarType TValueType> inline
	std::ostream& operator<<(std::ostream& _os, Vector<2, TValueType> const& _vector)
	{
		// Pass components to stream
		_os << '{' << _vector.GetX() << ',' << _vector.GetY() << '}';

		return _os;
	}


	template <CScalarType TValueType> inline
	std::istream& operator>>(std::istream& _is, Vector<2, TValueType>& _vector)
	{
		char	discard;

		// Get input from stream
		_is >> discard >> _vector.X() >> discard >> _vector.Y() >> discard;

		return _is;
	}

}

namespace LibMath = math;
namespace lm = LibMath;

#endif