/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: Trigonometry.hpp

DESCTIPTION: Trigonometry functions (sin, cos, acos...)

AUTHOR: Noah de Pischof | @torrra on GitHub


*/

#ifndef __TRIGONOMETRY_H__
#define __TRIGONOMETRY_H__

#include <cmath>

#include "math/Angle.hpp"

// Number of times cos should run its loop
#define COS_IT		6u

#define MIN_COS		-1.f
#define MAX_COS		1.f


namespace math
{
	// Compute cosine of an angle in radians using
	// 6 iterations of Taylor's series
	template <CScalarType TValueType> inline
	TValueType		Cos(const Radian<TValueType>& _rad);

	// Compute sine using Cos with a pi / 2 offset
	template <CScalarType TValueType> inline
	TValueType		Sin(const Radian<TValueType>& _rad);

	// Compute tan using sin / cos
	template <CScalarType TValueType> inline
	TValueType		Tan(const Radian<TValueType>& _rad);

	// Inverse trigonometry

	template <CScalarType TValueType> inline
	Radian<TValueType>		Acos(TValueType _cosine);

	template <CScalarType TValueType> inline
	Radian<TValueType>		Asin(TValueType _sine);

	template <CScalarType TValueType> inline
	Radian<TValueType>		Atan(TValueType _tangent);

	// Compute arctangent by dividing y by x
	// Note: can handle x being equal to 0
	template <CScalarType TValueType> inline
	Radian<TValueType>		Atan2(TValueType _y, TValueType _x);


	// Class made to hold factorials for cos
	template <CScalarType TValueType>
	class Factorials
	{
	public:

				Factorials(void) = default;


		static const TValueType		m_evenFacts[6];
	};









	// Cos specifically made for sin to avoid constructing another Radian object
	template <CScalarType TValueType> inline
	static TValueType InternalCos(TValueType _val)
	{
		TValueType	  powResult, cosResult = 0.f, itResult;

		// Wrap angle between -pi and pi as 6 iterations of
		// Taylor's series get less accurate as the angle approaches
		// -2 pi or +2pi
		TValueType	  radians = Wrap(_val, -MTH_PI, MTH_PI);


		for (unsigned int it = 1; it <= COS_IT; ++it)
		{
			// Get numerator, angle raised to the power of
			// an even number
			powResult = Pow(radians, it * 2);

			// Divide result by factorial of said power * sign
			itResult = powResult * math::Factorials<TValueType>::m_evenFacts[it - 1];

			cosResult += itResult;

		}

		cosResult = 1.f - cosResult;

		return cosResult;
	}

	template <CScalarType TValueType> inline
	static TValueType AtanZeroX(TValueType _y)
	{
		// Return 90 degrees * sign of _y

		if (_y > 0.f)
			return PI_OVER_TWO;

		else if (_y < 0.f)
			return -PI_OVER_TWO;

		return 0.f;
	}


	template <CScalarType TValueType> inline
	TValueType Cos(const Radian<TValueType>& _rad)
	{
		// Wrap angle between -pi and pi as 6 iterations of
		// Taylor's series get less accurate as the angle approaches
		// -2 pi or +2pi
		TValueType	radians = _rad.Rad(true);
		TValueType	powResult, cosResult = 0.f, itResult;

		for (unsigned int it = 1; it <= COS_IT; ++it)
		{
			// Get numerator, angle raised to the power of
			// an even number
			powResult = Pow(radians, it * 2);

			// Divide result by factorial of said power * sign
			itResult = powResult * math::Factorials<TValueType>::m_evenFacts[it - 1];

			cosResult += itResult;

		}

		cosResult = 1.f - cosResult;

		return cosResult;

		// TODO: use local vars instead of static (cache locality)
		// TODO: implement a more standard algorithm, maybe degree 14 instead of 6 ?
	}


	template <CScalarType TValueType> inline
	TValueType Sin(const Radian<TValueType>& _rad)
	{
		// Apply 90 degree offset
		// See: https://upload.wikimedia.org/wikipedia/commons/thumb/7/71/Sine_cosine_one_period.svg/1920px-Sine_cosine_one_period.svg.png
		constexpr TValueType		piOverTwo = 1.570796326794896619231f;

		// cos x == cos -x so get absolute value of angle to apply offset easily
		TValueType				cosine = InternalCos(Absolute(_rad.Raw()) - piOverTwo);


		// Restore sign of angle as sine is an odd function,
		// which means sin -x == -sinx
		if (_rad.Raw() < 0.f)
			return -cosine;

		else return cosine;

		// TODO: optimize
	}


	template <CScalarType TValueType> inline
	TValueType Tan(const Radian<TValueType>& _rad)
	{
		// tan x = sin x / cos x
		return Sin(_rad) / Cos(_rad);

		// TODO: needs to be faster
	}

	// TODO: re-implement my own inverse trig functions

	template <CScalarType TValueType> inline
	Radian<TValueType> Acos(TValueType _cosine)
	{
		return Radian(acosf(_cosine));
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Asin(TValueType _sine)
	{
		return Radian(asinf(_sine));
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Atan(TValueType _tangent)
	{
		return Radian(atanf(_tangent));
	}


	template <CScalarType TValueType> inline
	Radian<TValueType> Atan2(TValueType _y, TValueType _x)
	{
		// Handle x == 0 case
		if (AlmostEqual(_x, 0.0f))
			return Radian(AtanZeroX(_y));


		Radian		angle = Atan(_y / _x);

		// Find quadrant of point within trigonometric circle
		// and add offset to get correct angle

		if (_x >= 0.f && _y <= 0.f)
			angle += RAD_CIRCLE;

		else if (_x < 0.f && _y <= 0.f)
			angle += MTH_PI;

		else if (_x < 0.f && _y > 0.f)
			angle += MTH_PI;

		return angle;
	}


	template <CScalarType TValueType> inline
	const TValueType math::Factorials<TValueType>::m_evenFacts[] =
	{
		// Pre-compute even factorials and divisions
		// for faster cosine execution
		1.f / static_cast<TValueType>(Factorial(2)),
		-1.f / static_cast<TValueType>(Factorial(4)),
		1.f / static_cast<TValueType>(Factorial(6)),
		-1.f / static_cast<TValueType>(Factorial(8)),
		1.f / static_cast<TValueType>(Factorial(10)),
		-1.f / static_cast<TValueType>(Factorial(12))
	};




}

namespace LibMath = math;
namespace lm = math;

#endif