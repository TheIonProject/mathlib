/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: Matrix2.hpp

DESCTIPTION: 2x2 matrix class

AUTHOR: Noah de Pischof | @torrra on GitHub

TEMPLATES:

CScalarType is a template constraint that only accepts numeric data types

*/



#ifndef __MATRIX2_H__
#define __MATRIX2_H__

#include "math/MathGeneric.hpp"
#include "math/MatrixGeneric.hpp"

#include "math/Vector2.hpp"

#include "math/Angle.hpp"

#include "math/Arithmetic.hpp"
#include "math/Trigonometry.hpp"

namespace math
{
    template <CScalarType TValueType>
    class Matrix<2, TValueType>
     {
     private:

         using TMatrixType = Matrix<2, TValueType>;
         using TRowType = Vector<2, TValueType>;

     public:

          // Constructor / destructor

        inline          Matrix(void) = default;
        inline          Matrix(const TValueType _diag);

        inline          Matrix(TValueType _a, TValueType _b, TValueType _c, TValueType _d);

        inline          Matrix(const TValueType _vals[]);
        inline          Matrix(const Matrix& _other);

                        ~Matrix(void) = default;

        // Calculate matrix determinant
        inline TValueType      Determinant(void)                   const;

        // Turn this matrix into an identity matrix of a given diagonal
        inline void            Identity(TValueType _diag = static_cast<TValueType>(1));

        // Get transposed matrix of cofactors
        inline TMatrixType         Adjugate(void)                      const;

        // Get inverse of this matrix
        inline TMatrixType         Inverse(void)                       const;

        // Get transposed copy of this matrix
        inline TMatrixType         Transpose(void)                     const;

        inline TMatrixType&        operator=(const TMatrixType& _rhs);

        // TMatrixType / matrix operators

        inline TMatrixType         operator+(const TMatrixType& _rhs)      const;
        inline TMatrixType         operator-(const TMatrixType& _rhs)      const;
        inline TMatrixType         operator*(const TMatrixType& _rhs)      const;

        // Multiply all numbers of a copy of this matrix by a scalar factor
        inline TMatrixType         operator*(TValueType _factor)            const;

        // TMatrixType / matrix assignment operators

        inline TMatrixType&        operator+=(const TMatrixType& _rhs);
        inline TMatrixType&        operator-=(const TMatrixType& _rhs);
        inline TMatrixType&        operator*=(const TMatrixType& _rhs);

        inline bool            operator==(const TMatrixType& _rhs)     const;
        inline bool            operator!=(const TMatrixType& _rhs)     const;

        // Access a row (no bound checking)
        inline TRowType&    operator[](int _index);

        // Access a row (no bound checking)
        inline TRowType    operator[](int _index)              const;

        // Get a 2x2 rotation matrix from an angle in radians
        inline static TMatrixType  Rotate(Radian<TValueType> _angle);



    private:

        TRowType     m_values[2];
     };







    // ---- Implementations ----


    template <CScalarType TValueType> inline
    Matrix<2, TValueType>::Matrix(TValueType _a, TValueType _b, TValueType _c, TValueType _d)
    {
        m_values[0][0] = _a;
        m_values[0][1] = _b;
        m_values[1][0] = _c;
        m_values[1][1] = _d;
    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType>::Matrix(const TValueType _diag)
    {
        m_values[0][0] = _diag;
        m_values[1][1] = _diag;

        m_values[0][1] = static_cast<TValueType>(0);
        m_values[1][0] = static_cast<TValueType>(0);
    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType>::Matrix(const TValueType _vals[])
    {
        m_values[0][0] = _vals[0];
        m_values[0][1] = _vals[1];
        m_values[1][0] = _vals[2];
        m_values[1][1] = _vals[3];
    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType>::Matrix(const Matrix<2, TValueType>& _other)
    {
        m_values[0][0] = _other.m_values[0][0];
        m_values[0][1] = _other.m_values[0][1];
        m_values[1][0] = _other.m_values[1][0];
        m_values[1][1] = _other.m_values[1][1];
    }


    template <CScalarType TValueType> inline
    TValueType Matrix<2, TValueType>::Determinant(void)    const
    {
        return (m_values[0][0] * m_values[1][1]) -
	           (m_values[0][1] * m_values[1][0]);
    }


    template <CScalarType TValueType> inline
    void Matrix<2, TValueType>::Identity(TValueType _diag)
    {
        m_values[0][0] = _diag;
	    m_values[0][1] = 0.f;
	    m_values[1][0] = 0.f;
	    m_values[1][1] = _diag;
    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::Adjugate(void) const
    {
        // Transpose cofactors
        return Matrix<2, TValueType>(m_values[1][1], -m_values[0][1],
                       -m_values[1][0], m_values[0][0]);
    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::Inverse(void) const
    {
        TValueType       det = Determinant();

        // Divide adjugate by determinant
        if (det != 0.f)
            return Adjugate() * (1 / det);

        // Do not devide by zero
        return Matrix<2, TValueType>();
    }



    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::Transpose(void) const
    {
        // Switch non-diagonal values
        return Matrix<2, TValueType>
        (
            m_values[0][0], m_values[1][0],
            m_values[0][1], m_values[1][1]
        );
    }



    template <CScalarType TValueType> inline
    Matrix<2, TValueType>& Matrix<2, TValueType>::operator=(const Matrix<2, TValueType>& _rhs)
    {
        m_values[0][0] = _rhs[0][0];
        m_values[0][1] = _rhs[0][1];
        m_values[1][0] = _rhs[1][0];
        m_values[1][1] = _rhs[1][1];

        return *this;

    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::operator+(const Matrix<2, TValueType>& _rhs) const
    {
        // Add components
        return Matrix<2, TValueType>
        (
            m_values[0][0] + _rhs[0][0], m_values[0][1] + _rhs[0][1],
            m_values[1][0] + _rhs[1][0], m_values[1][1] + _rhs[1][1]
        );
    }



    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::operator-(const Matrix<2, TValueType>& _rhs) const
    {
        // Subtract components
        return Matrix<2, TValueType>
        (
            m_values[0][0] - _rhs.m_values[0][0], m_values[0][1] - _rhs.m_values[0][1],
            m_values[1][0] - _rhs.m_values[1][0], m_values[1][1] - _rhs.m_values[1][1]
        );
    }



    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::operator*(const Matrix<2, TValueType>& _rhs) const
    {
        // Multiply components
        return Matrix<2, TValueType>
        (
            m_values[0][0] * _rhs.m_values[0][0] + m_values[1][0] * _rhs.m_values[0][1],
            m_values[0][1] * _rhs.m_values[0][0] + m_values[1][1] * _rhs.m_values[0][1],
            m_values[0][0] * _rhs.m_values[1][0] + m_values[1][0] * _rhs.m_values[1][1],
            m_values[0][1] * _rhs.m_values[1][0] + m_values[1][1] * _rhs.m_values[1][1]
        );
    }



    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::operator*(TValueType _factor) const
    {
        // Multiply by a scalar
        return Matrix<2, TValueType>(
                        m_values[0][0] * _factor,
                        m_values[0][1] * _factor,
                        m_values[1][0] * _factor,
                        m_values[1][1] * _factor
                      );
    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType>& Matrix<2, TValueType>::operator+=(const Matrix<2, TValueType>& _rhs)
    {
        *this = *this + _rhs;

        return *this;
    }



    template <CScalarType TValueType> inline
    Matrix<2, TValueType>& Matrix<2, TValueType>::operator-=(const Matrix<2, TValueType>& _rhs)
    {
        *this = *this - _rhs;

        return *this;
    }



    template <CScalarType TValueType> inline
    Matrix<2, TValueType>& Matrix<2, TValueType>::operator*=(const Matrix<2, TValueType>& _rhs)
    {
        *this = *this * _rhs;

        return *this;
    }



    template <CScalarType TValueType> inline
    bool  Matrix<2, TValueType>::operator==(const Matrix<2, TValueType>& _rhs) const
    {
        // Check if all componenents are almost equal
        return math::AlmostEqual(m_values[0][0], _rhs[0][0]) &&
               math::AlmostEqual(m_values[0][1], _rhs[0][1]) &&
               math::AlmostEqual(m_values[1][0], _rhs[1][0]) &&
               math::AlmostEqual(m_values[1][1], _rhs[1][1]);
    }


    template <CScalarType TValueType> inline
    bool Matrix<2, TValueType>::operator!=(const Matrix<2, TValueType>& _rhs) const
    {
        return !(*this == _rhs);
    }



    template <CScalarType TValueType> inline
    Vector2<TValueType>&
    Matrix<2, TValueType>::operator[](int _index)
    {
        return m_values[_index];
    }


    template <CScalarType TValueType> inline
    Vector2<TValueType>
    Matrix<2, TValueType>::operator[](int _index) const
    {
        return m_values[_index];
    }


    template <CScalarType TValueType> inline
    Matrix<2, TValueType> Matrix<2, TValueType>::Rotate(Radian<TValueType> _angle)
    {
        TValueType   cosAngle = Cos(_angle), sinAngle = Sin(_angle);

        // Create z axis rotation matrix (non-homogenized)
        return Matrix<2, TValueType>
        (
            cosAngle, -sinAngle,
            sinAngle, cosAngle
        );
    }


// !Implementation


}


namespace LibMath = math;
namespace lm = math;

#endif