/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: Interpolation.hpp

DESCTIPTION: Interpolation functions

AUTHOR: Noah de Pischof | @torrra on GitHub


*/

#ifndef __INTERPOLATION_H__
#define __INTERPOLATION_H__

#include "math/MathGeneric.hpp"

#include "math/Vector3.hpp"
#include "math/Vector2.hpp"

namespace math
{
	// Linear interpolation between a start, an end and a ratio
	// between 0 and 1
	template <CScalarType TValueType> inline
	TValueType		Lerp(TValueType _low, TValueType _high, TValueType _ratio) noexcept;


	// Get the Lerp ratio from a lerp'd value and its bounds
	template <CScalarType TValueType> inline
	TValueType		InverseLerp(TValueType _val, TValueType _low, TValueType _high) noexcept;







// ---- Implementation ----

	template <CScalarType TValueType> inline
	TValueType Lerp(TValueType _low, TValueType _high, TValueType _ratio) noexcept
	{
		if (_ratio == 0.f)
			return _low;

		else if (_ratio == 1.f)
			return _high;

		// Use naive lerp formula
		return (static_cast<TValueType>(1) - _ratio) * _low + _ratio * _high;
	}


	template <CScalarType TValueType> inline
	TValueType InverseLerp(TValueType _val, TValueType _low, TValueType _high) noexcept
	{
		// Reverse lerp formula to get ratio (commonly referred to as t)
		return (_val - _low) / (_high - _low);
	}

}


#endif