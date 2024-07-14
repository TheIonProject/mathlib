/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
                                __/ |
                               |___/


NAME: MathGeneric.hpp

DESCTIPTION: Template definitions for mathematical classes

AUTHOR: Noah de Pischof | @torrra on GitHub


STYLE:

C prefix: C++20 template concept
T prefix: Template parameter

Type suffix: Generic type, goes with T prefix

*/

#ifndef __MATH_GENERICS_H__
#define __MATH_GENERICS_H__

#include <type_traits>

namespace math
{
    // Constrain type to a number:
    // int, float, etc... excluding pointers
    template <typename TEvaluatedType>
    concept CScalarType =
    std::is_arithmetic<TEvaluatedType>::value;


    // Constrain type to a built-in integral type
    // int, unsigned int, etc... excluding pointers
    template <typename TEvaluatedType>
    concept CIntegralType =
    std::is_integral<TEvaluatedType>::value;


    // Constrain template to an unsigned integral type
    template <typename TEvaluatedType>
    concept CUnsignedType =
    std::is_unsigned<TEvaluatedType>::value;


    // Constrain type to a type that can be manipulated through addition,
    // subtraction, and multiplication (between two object of this type).
    // Does NOT account for division. Use CDivisibleObject
    template <typename TEvaluatedType>
    concept CArithmeticType = requires (TEvaluatedType a, TEvaluatedType b)
    {
     // These statements are never actually ran,
     // we just check if they can compile to determine
     // if the evaluated type meets the requirements

      a + b;
      a - b;
      a * b;
    };


    // Constrain type to one that can be added, subtracted, multiplied,
    // AND divided (applies to two objects of the same type)
    template <typename TEvaluatedType>
    concept CDivisibleType = CArithmeticType<TEvaluatedType> &&
    requires (TEvaluatedType a, TEvaluatedType b)
    {
      a / b;
    };

}

#endif