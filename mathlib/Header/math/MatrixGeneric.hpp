#ifndef __MATRIX_GENERIC_H__
#define __MATRIX_GENERIX_H__

#include <inttypes.h>

#include "math/MathGeneric.hpp"
#include "math/Vector2.hpp"
#include "math/Vector3.hpp"
#include "math/Vector4.hpp"


namespace math
{
    template <uint8_t TDimensions, CScalarType TValueType>
    class Matrix;


    template <CScalarType TValueType>
    using Matrix2 = Matrix<2, TValueType>;

    using Matrix2f = Matrix2<float>;
    using Matrix2d = Matrix2<double>;
    using Matrix2i = Matrix2<int32_t>;


    template <CScalarType TValueType>
    using Matrix3 = Matrix<3, TValueType>;

    using Matrix3f = Matrix3<float>;
    using Matrix3d = Matrix3<double>;
    using Matrix3i = Matrix3<int32_t>;



    template <CScalarType TValueType>
    using Matrix4 = Matrix<4, TValueType>;

    using Matrix4f = Matrix4<float>;
    using Matrix4d = Matrix4<double>;
    using Matrix4i = Matrix4<int32_t>;

}

#endif