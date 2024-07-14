/*

 _____                               _
|_   _|                             (_)
  | |  ___  _ __     ___ _ __   __ _ _ _ __   ___
  | | / _ \| '_ \   / _ \ '_ \ / _` | | '_ \ / _ \
 _| || (_) | | | | |  __/ | | | (_| | | | | |  __/
 \___/\___/|_| |_|  \___|_| |_|\__, |_|_| |_|\___|
								__/ |
							   |___/


NAME: Matrix4.hpp

DESCTIPTION: 4x4 matrix class

AUTHOR: Noah de Pischof | @torrra on GitHub

TEMPLATES:

CScalarType is a template constraint that only accepts numeric data types

*/

#ifndef __MATRIX4_H__
#define __MATRIX4_H__

#include "math/MathGeneric.hpp"
#include "math/MatrixGeneric.hpp"

#include "math/Matrix3.hpp"
#include "math/Vector4.hpp"

namespace math
{
	template <CScalarType TValueType>
	class Matrix<4, TValueType>
	{
	private:

		using TMatrixType = Matrix<4, TValueType>;
		using TRowType = Vector<4, TValueType>;

	public:

		// Constructors / destructor

	inline					Matrix(void) = default;
	inline					Matrix(const TValueType _diag);
	inline					Matrix(const TValueType _vals[][4]);
	inline					Matrix(const TValueType _vals[]);
	inline					Matrix(const Matrix<4, TValueType>& _other);

	inline					~Matrix(void) = default;

		// Get this matrix' determinant
	inline	TValueType           Determinant(void)                   const;

		// Turn this matrix into an identity matrix with a given diagonal
	inline	void            Identity(TValueType _diag = 1.f);

		// Get this matrix' transposed cofactor matrix
	inline	TMatrixType         Adjugate(void)                      const;

		// Get a matrix of all 3x3 submatrices' determinants within
		// this matrix
	inline	TMatrixType         Minor(void)                         const;

		// Get a matrix of this matrix' cofactors taken from all 3x3
		// matrices within it
	inline	TMatrixType         Cofactor(void)                      const;

		// Get inverse of this matrix
	inline	TMatrixType         Inverse(void)                       const;

		// Get a transposed copy of this matrix
	inline	TMatrixType         Transpose(void)                     const;

		// Get this matrix stripped of a row and a column
	inline	Matrix3<TValueType>         SubMatrix(int _row, int _column)    const;


	// Get rotation matrix from three angles (column-major)
	static inline TMatrixType			RotationMatrix(
			Radian<TValueType> _angleX,
			Radian<TValueType> _angleY,
			Radian<TValueType> _angle
	);

	inline	TMatrixType&		operator=(const TMatrixType& _rhs);
	inline	TMatrixType&		operator=(const TValueType _rhs[][4]);
	inline	TMatrixType&		operator=(const TValueType _rhs[16]);


		// Matrix / matrix operators

	inline	TMatrixType         operator+(const TMatrixType& _rhs)      const;
	inline	TMatrixType         operator-(const TMatrixType& _rhs)      const;
	inline	TMatrixType         operator*(const TMatrixType& _rhs)      const;

		// Multiply a vector 4D by this matrix
	inline	Vector4<TValueType>				operator*(const Vector4<TValueType>& _rhs)      const;


		// Multiply all numbers of a copy of this matrix by a scalar factor
	inline	TMatrixType         operator*(TValueType _factor)            const;

		// Divide all numbers of a copy of this matrix by a scalar factor
	inline	TMatrixType         operator/(TValueType _factor)            const;


		// Matrix / matrix assignment operators


	inline	TMatrixType&		operator+=(const TMatrixType& _rhs);
	inline	TMatrixType&		operator-=(const TMatrixType& _rhs);
	inline	TMatrixType&		operator*=(const TMatrixType& _rhs);

		// Multiply all numbers of a copy of this matrix by a scalar factor
	inline	TMatrixType&		operator*=(TValueType _factor);

		// Divide all numbers of a copy of this matrix by a scalar factor
	inline	TMatrixType&		operator/=(TValueType _factor);

	inline	bool				operator==(const TMatrixType& _rhs)     const;
	inline	bool				operator!=(const TMatrixType& _rhs)     const;

		// Access a row (no bound checking)
	inline	TRowType&		operator[](int _index);

		// Access a row (no bound checking)
	inline	TRowType		operator[](int _index)              const;


	private:

		TRowType       m_values[4];

	};







// ---- Implementations ----

	template <CScalarType TValueType> inline
	Matrix<4, TValueType>::Matrix(const TValueType _diag)
	{
		Identity(_diag);
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>::Matrix(const TValueType _vals[][4])
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] = _vals[row][column];
			}
		}
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>::Matrix(const TValueType _vals[])
	{
		int		arrayIndex = 0;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column, ++arrayIndex)
			{
				m_values[row][column] = _vals[arrayIndex];
			}
		}
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>::Matrix(const Matrix<4, TValueType>& _other)
	{
		int		maxSize = 4;

		for (int row = 0; row < maxSize; ++row)
		{
			for (int column = 0; column < maxSize; ++column)
			{
				m_values[row][column] = _other[row][column];
			}
		}
	}


	template <CScalarType TValueType> inline
	TValueType Matrix<4, TValueType>::Determinant(void) const
	{
		Matrix3<TValueType>     minor;

		TValueType		result = 0.f, minusOne = -1.f;
		int			stripedRow = 0;

		for (unsigned int cofactor = 0; cofactor < 4; ++cofactor)
		{
			minor = SubMatrix(stripedRow, cofactor);
			result += m_values[stripedRow][cofactor] * minor.Determinant() * Pow(minusOne, cofactor);

		}

		return result;

	}


	template <CScalarType TValueType> inline
	void Matrix<4, TValueType>::Identity(TValueType _diag)
	{
		int		maxSize = 4;

		for (int row = 0; row < maxSize; ++row)
		{
			for (int column = 0; column < maxSize; ++column)
			{
				m_values[row][column] = (row == column) ? _diag : 0.f;
			}
		}
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::Adjugate(void) const
	{
		Matrix<4, TValueType>			result;

		TValueType			minusOne = -1;

		for (unsigned int row = 0; row < 4; ++row)
		{
			for (unsigned int column = 0; column < 4; ++column)
			{
				result[column][row] = SubMatrix(row, column).Determinant();

				result[column][row] *= Pow(minusOne, row + column);
			}
		}

		return result;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::Minor(void) const
	{
		Matrix<4, TValueType>		result;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result[row][column] = SubMatrix(row, column).Determinant();
			}
		}

		return result;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::Cofactor(void) const
	{
		Matrix<4, TValueType>			result;

		TValueType			minusOne = -1;

		for (unsigned int row = 0; row < 4; ++row)
		{
			for (unsigned int column = 0; column < 4; ++column)
			{
				result[row][column] = SubMatrix(row, column).Determinant();

				result[row][column] *= Pow(minusOne, row + column);
			}
		}

		return result;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::Inverse(void) const
	{
		TValueType			invDeterminant = 1.f / Determinant();
		Matrix<4, TValueType>			result;
		TValueType			minusOne = -1;

		for (unsigned int row = 0; row < 4; ++row)
		{
			for (unsigned int column = 0; column < 4; ++column)
			{
				result[column][row] = SubMatrix(row, column).Determinant();

				result[column][row] *= Pow(minusOne, row + column);
				result[column][row] *= invDeterminant;

			}
		}

		return result;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::Transpose(void) const
	{
		Matrix<4, TValueType> result;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result[row][column] = m_values[column][row];
			}
		}

		return result;

	}


	template <CScalarType TValueType> inline
	Matrix3<TValueType> Matrix<4, TValueType>::SubMatrix(int _row, int _column) const
	{
		Matrix3<TValueType> minor;

		for (int thisRow = 0, mat2Row = 0; thisRow < 4; ++thisRow)
		{
			if (_row == thisRow)
				continue;

			for (int thisColumn = 0, mat2Column = 0; thisColumn < 4; ++thisColumn)
			{
				if (_column == thisColumn)
					continue;

				minor[mat2Row][mat2Column++] = m_values[thisRow][thisColumn];
			}

			++mat2Row;
		}

		return minor;
	}

	template<CScalarType TValueType>
	inline Matrix<4, TValueType> Matrix<4, TValueType>::RotationMatrix(
		Radian<TValueType> _angleX,
		Radian<TValueType> _angleY,
		Radian<TValueType> _angleZ
	)
	{
		TValueType				cosYaw = Cos(_angleZ), sinYaw = Sin(_angleZ);
		TValueType				cosPitch = Cos(_angleX), sinPitch = Sin(_angleX);
		TValueType				cosRoll = Cos(_angleY), sinRoll = Sin(_angleY);

		TMatrixType				rotationMatrix;

		// Assign COLUMN-MAJOR rotation matrix

		rotationMatrix[0][0] = cosYaw * cosRoll + sinYaw * sinPitch * sinRoll;
		rotationMatrix[1][0] = -cosYaw * sinRoll + sinYaw * sinPitch * cosRoll;
		rotationMatrix[2][0] = sinYaw * cosPitch;
		rotationMatrix[3][0] = static_cast<TValueType>(0);

		rotationMatrix[0][1] = sinRoll * cosPitch;
		rotationMatrix[1][1] = cosRoll * cosPitch;
		rotationMatrix[2][1] = -sinPitch;
		rotationMatrix[3][1] = static_cast<TValueType>(0);

		rotationMatrix[0][2] = -sinYaw * cosRoll + cosYaw * sinPitch * sinRoll;
		rotationMatrix[1][2] = sinRoll * sinYaw + cosYaw * sinPitch * cosRoll;
		rotationMatrix[2][2] = cosYaw * cosPitch;
		rotationMatrix[3][2] = static_cast<TValueType>(0);

		rotationMatrix[0][3] = static_cast<TValueType>(0);
		rotationMatrix[1][3] = static_cast<TValueType>(0);
		rotationMatrix[2][3] = static_cast<TValueType>(0);
		rotationMatrix[3][3] = static_cast<TValueType>(1);

		return rotationMatrix;

	}



	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& Matrix<4, TValueType>::operator=(const Matrix<4, TValueType>& _rhs)
	{
		for (uint8_t row = 0; row < 4; ++row)
			this->m_values[row] = _rhs.m_values[row];

		return *this;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& Matrix<4, TValueType>::operator=(const TValueType _rhs[][4])
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] = _rhs[row][column];
			}
		}

		return *this;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& Matrix<4, TValueType>::operator=(const TValueType _rhs[16])
	{
		int		arrayIndex = 0;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column, ++arrayIndex)
			{
				m_values[row][column] = _rhs[arrayIndex];
			}
		}

		return *this;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::operator+(const Matrix<4, TValueType>& _rhs) const
	{
		Matrix<4, TValueType>		result;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result.m_values[row][column] = m_values[row][column] + _rhs[row][column];
			}
		}

		return result;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::operator-(const Matrix<4, TValueType>& _rhs) const
	{
		Matrix<4, TValueType> result;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result.m_values[row][column] = m_values[row][column] - _rhs[row][column];
			}
		}

		return result;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::operator*(const Matrix<4, TValueType>& _rhs) const
	{
		Matrix<4, TValueType>		result;

		for (int thisRow = 0; thisRow < 4; thisRow++)
		{
			for (int rightColumn = 0; rightColumn < 4; rightColumn++)
			{
				TValueType	currentNum = 0.f;

				for (int rightRow = 0; rightRow < 4; rightRow++)
				{
					currentNum += m_values[thisRow][rightRow] * _rhs[rightRow][rightColumn];
				}

				result.m_values[thisRow][rightColumn] = currentNum;
			}
		}

		return result;
	}


	template <CScalarType TValueType> inline
	Vector4<TValueType> Matrix<4, TValueType>::operator*(const Vector4<TValueType>& _rhs) const
	{
		Vector4<TValueType>		result;
		TValueType				num;

		for (int row = 0; row < 4; ++row)
		{
			num = 0.f;

			for (int column = 0; column < 4; ++column)
			{
				num += m_values[row][column] * _rhs[column];
			}

			result[row] = num;
		}

		return result;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::operator*(TValueType _rhs) const
	{
		Matrix<4, TValueType>		result;

		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				result[row][column] = m_values[row][column] * _rhs;
			}
		}

		return result;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType> Matrix<4, TValueType>::operator/(TValueType _rhs) const
	{
		return *this * (1.f / _rhs);
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& math::Matrix<4, TValueType>::operator+=(const Matrix<4, TValueType>& _rhs)
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] += _rhs[row][column];
			}
		}

		return *this;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& math::Matrix<4, TValueType>::operator-=(const Matrix<4, TValueType>& _rhs)
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] -= _rhs[row][column];
			}
		}

		return *this;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& Matrix<4, TValueType>::operator*=(const Matrix<4, TValueType>& _rhs)
	{
		Matrix<4, TValueType>		result;

		for (int thisRow = 0; thisRow < 4; thisRow++)
		{
			for (int rightColumn = 0; rightColumn < 4; rightColumn++)
			{
				TValueType	currentNum = 0.f;

				for (int rightRow = 0; rightRow < 4; rightRow++)
				{
					currentNum += m_values[thisRow][rightRow] * _rhs[rightRow][rightColumn];
				}

				result.m_values[thisRow][rightColumn] = currentNum;
			}
		}

		*this = result;

		return *this;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& Matrix<4, TValueType>::operator*=(TValueType _rhs)
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				m_values[row][column] *= _rhs;
			}
		}

		return *this;
	}


	template <CScalarType TValueType> inline
	Matrix<4, TValueType>& Matrix<4, TValueType>::operator/=(TValueType _rhs)
	{
		*this *= (1.f / _rhs);

		return *this;
	}


	template <CScalarType TValueType> inline
	bool Matrix<4, TValueType>::operator==(const Matrix<4, TValueType>& _rhs) const
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int column = 0; column < 4; ++column)
			{
				if (!math::AlmostEqual(m_values[row][column],
					_rhs.m_values[row][column]))
					return false;
			}
		}

		return true;
	}

	template <CScalarType TValueType> inline
	bool Matrix<4, TValueType>::operator!=(const Matrix<4, TValueType>& _rhs) const
	{
		return !(*this == _rhs);
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType>& Matrix<4, TValueType>::operator[](int _index)
	{
		return m_values[_index];
	}


	template <CScalarType TValueType> inline
	Vector<4, TValueType> Matrix<4, TValueType>::operator[](int _index) const
	{
		return m_values[_index];
	}
}

namespace lm = math;
namespace LibMath = lm;

#endif