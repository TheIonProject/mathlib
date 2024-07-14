/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
                                __/ |
                               |___/


NAME: Arithmetic.hpppp

DESCTIPTION: Basic arithmetic function templates. Implementation below

AUTHOR: Noah de Pischof | @torrra on GitHub

TEMPLATES:

CScalarType is a template constraint that only accepts numeric data types
CIntegralType only accepts integral numeric types

*/

#ifndef __ARITHMETIC_H__
#define __ARITHMETIC_H__

#include <cmath>
#include <limits>

#include "math/MathGeneric.hpp"

namespace math
{

    // Absolute value
    template <CScalarType TValueType> inline
    TValueType       Absolute(TValueType _val)                          noexcept;


    // Epsilon test
    template <CScalarType TValueType> inline
    bool             AlmostEqual
    (
        TValueType _a, TValueType _b,
        TValueType _epsilon = static_cast<TValueType>(1e-4)
    )                                                                   noexcept;


    // Round to the nearest integral value
    template <CScalarType TValueType> inline
    TValueType       Round(TValueType _val)                             noexcept;


    // Round to the nearest integral value (greater or equal)
    template <CScalarType TValueType> inline
    TValueType       Ceil(TValueType _val)                              noexcept;



    // Round to the nearest integral value (smaller or equal)
    template <CScalarType TValueType> inline
    TValueType       Floor(TValueType _val)                             noexcept;


    // Wrap value around a set of limits
    template <CScalarType TValueType> inline
    TValueType       Wrap
    (
        TValueType _val, TValueType _low, TValueType _high
    )                                                                   noexcept;

    // Get value within a range without wrapping
    template <CScalarType TValueType> inline
    TValueType       Clamp
    (
        TValueType _val, TValueType _low, TValueType _high
    )                                                                   noexcept;


    // Raise number to an integral power
    template <CScalarType TValueType, CUnsignedType TPowerType> inline
    TValueType       Pow(TValueType _val, TPowerType _power)            noexcept;


    //TODO: Re-implement our own function
    template <CScalarType TValueType> inline
    TValueType       SquareRoot(TValueType _val)                        noexcept;

    // Get smallest value
    template <CScalarType TValueType> inline
    TValueType       Min(TValueType _a, TValueType _b)                  noexcept;

    // Get largest value
    template <CScalarType TValueType> inline
    TValueType       Max(TValueType _a, TValueType _b)                  noexcept;



    // Get factorial of an unsigned integral value
    template <CIntegralType TValueType> inline
    TValueType      Factorial(TValueType _val)                          noexcept;


    template <CScalarType TValueType> inline
    TValueType      Modulus(TValueType _toDivide, TValueType _divisor)  noexcept;





// ---- Implementation ----



    template <CScalarType TValueType> inline
    TValueType Absolute(TValueType _val) noexcept
    {
        // Unsigned types cannot be negative
        if constexpr (std::is_unsigned<TValueType>::value)
            return _val;

        else
            // Multiply by -1 if negative
            return (_val < static_cast<TValueType>(0)) ? -_val : _val;
    }


    template <CScalarType TValueType> inline
    bool  AlmostEqual(TValueType _a, TValueType _b, TValueType _epsilon) noexcept
    {
        // Cannot use negative differences with unsigned types,
        // ensure difference will be positive
        if constexpr (std::is_unsigned<TValueType>::value)
        {
            return Max(_a, _b) - Min(_a, _b) <= _epsilon;
        }

        // Check if difference is smaller than epsilon
        return Absolute(_a - _b) <= _epsilon;
    }

    template <CScalarType TValueType> inline
    TValueType Modulus(TValueType _toDivide, TValueType _divisor) noexcept
    {
        // Integral modulo, floating point types
        // are handled below
        return _toDivide % _divisor;
    }


// ---- Modulus specializations ----

    template<> inline
    double Modulus<double>(double _toDivide, double _divisor) noexcept
    {
        return fmod(_toDivide, _divisor);
    }

    template <> inline
    float Modulus<float>(float _toDivide, float _divisor) noexcept
    {
        return fmodf(_toDivide, _divisor);
    }

    template<> inline
    long double Modulus<long double>(long double _toDivide, long double _divisor) noexcept
    {
        return fmodl(_toDivide, _divisor);
    }


// !Modulus specializations


    template <CScalarType TValueType> inline
    TValueType Floor(TValueType _val) noexcept
    {
        // Integral types do not need to be manipulated.
        // Floating point cases handled below
        return _val;
    }


// ---- Floor specializations ----

    // Strip down decimal part and match size if possible

    template <> inline
    float Floor(float _val) noexcept
    {
        return static_cast<float>
        (
            static_cast<int32_t>(_val)
        );
    }


    template <> inline
    double Floor(double _val) noexcept
    {
        return static_cast<double>
        (
            static_cast<int64_t>(_val)
        );
    }


    template <> inline
    long double Floor(long double _val) noexcept
    {
        return static_cast<long double>
        (
            // No standard 128 bit integer
            // available, so resort to 64
            static_cast<int64_t>(_val)
        );
    }

// !Floor specializations


    template <CScalarType TValueType> inline
    TValueType Round(TValueType _val) noexcept
    {
        return _val;
    }


// ---- Round specializations ----

    template <> inline
    float Round(float _val) noexcept
    {

        float      floored = Floor<float>(_val);

        // Round up if decimal part >= .5
        if (_val - floored >= 0.5f)
            return floored + 1.f;

        // Round down if not
        else
            return floored;

    }


    template <> inline
    double Round(double _val) noexcept
    {

        double      floored = Floor<double>(_val);

        // Round up if decimal part >= .5
        if (_val - floored >= 0.5)
            return floored + 1.0;

        // Round down if not
        else
            return floored;

    }

    template <> inline
    long double Round(long double _val) noexcept
    {

        long double      floored = Floor<long double>(_val);

        // Round up if decimal part >= .5
        if (_val - floored >= 0.5l)
            return floored + 1.0l;

        // Round down if not
        else
            return floored;

    }


// !Round specializations

    template <CScalarType TValueType> inline
    TValueType Ceil(TValueType _val) noexcept
    {
        // No need to round integral values.
        // Floating point types handled below
        return _val;
    }

// ---- Ceil specializations ----

    template <> inline
    float Ceil(float _val) noexcept
    {
        float      floored = Floor<float>(_val);

        if (AlmostEqual<float>(_val, floored))
            return floored;


        // Round up if any decimal part > 0 is found
        else
            return floored + static_cast<float>(1);
    }


    template <> inline
    double Ceil(double _val) noexcept
    {
        double      floored = Floor<double>(_val);

        if (AlmostEqual<double>(_val, floored))
            return floored;


        // Round up if any decimal part > 0 is found
        else
            return floored + static_cast<double>(1);
    }


    template <> inline
    long double Ceil(long double _val) noexcept
    {
        long double      floored = Floor<long double>(_val);

        if (AlmostEqual<long double>(_val, floored))
            return floored;


        // Round up if any decimal part > 0 is found
        else
            return floored + static_cast<long double>(1);
    }


// !Ceil specializations


   // Get value within a range without wrapping
   template <CScalarType TValueType> inline
   TValueType Clamp(TValueType _val, TValueType _low, TValueType _high) noexcept
   {
       // Return highest of low values
       if (_val < _low)
           return _low;

       // Return lowest of high values
       if (_val > _high)
           return _high;

       return _val;
   }



   template <CScalarType TValueType> inline
   TValueType Wrap(TValueType _val, TValueType _low, TValueType _high) noexcept
   {
       if (-_val > _high)
           _val = _high + Modulus(_val - _high, _low - _high);

       else
           _val = _low + Modulus(_val - _low, _high - _low);

       if (_val < _low)
           _val += _high;

       return _val;
   }



   template <CScalarType TValueType, CUnsignedType TPowerType> inline
   TValueType Pow(TValueType _val, TPowerType _power) noexcept
   {
       if (static_cast<TPowerType>(0) == _power)
           return static_cast<TValueType>(1);

       if (static_cast<TPowerType>(1) == _power)
           return _val;


       TValueType       valCopy = _val;

       // Multiply value by itself _power times
       for (TPowerType iteration = static_cast<TPowerType>(1); iteration < _power; ++iteration)
           _val *= valCopy;

       return _val;
   }



   template <CScalarType TValueType> inline
   TValueType SquareRoot(TValueType _val) noexcept
   {
       return static_cast<TValueType>
       (
           sqrt(static_cast<double>(_val))
       );
   }



   // ---- SquareRoot specializations ----

   template<> inline
   float SquareRoot<float>(float _val) noexcept
   {
       return sqrtf(_val);
   }


   template<> inline
   long double SquareRoot<long double>(long double _val) noexcept
   {
       return sqrtl(_val);
   }



   // !SquareRoot specializations



   template <CScalarType TValueType> inline
   TValueType Min(TValueType _a, TValueType _b) noexcept
   {
       // Return smallest
       return (_a < _b) ? _a : _b;
   }


   template <CScalarType TValueType> inline
   TValueType Max(TValueType _a, TValueType _b) noexcept
   {
       // Return largest
       return (_a > _b) ? _a : _b;
   }


   template <CIntegralType TValueType> inline
   TValueType Factorial(TValueType _val) noexcept
   {
       TValueType       zero = static_cast<TValueType>(0),
                        one = static_cast<TValueType>(1);


       if (zero == _val || one == _val)
           return one;

       if (static_cast<TValueType>(2) == _val)
           return _val;

       TValueType     result = Absolute(_val),
           valCopy = result - one;


       // Multiply _val by numbers smaller than itself going all the way down to 1
       while (valCopy > zero)
           result *= valCopy--;

       // Restore negative sign if type permits it and value is < 0
       if constexpr (!std::is_unsigned<TValueType>::value)
           result *= (_val < static_cast<TValueType>(0)) ? -one : one;

       return result;
   }

// !Implementation
}

namespace LibMath = math;
namespace lm = LibMath;

#endif

