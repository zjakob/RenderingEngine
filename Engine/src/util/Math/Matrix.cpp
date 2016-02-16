#include "Matrix.h"

#include "MathUtil.h"
#include <algorithm>

using namespace math;

template <typename T, int columnCnt, int rowCnt>
int Matrix<T, columnCnt, rowCnt>::cnt = 0;

template <typename T, int columnCnt, int rowCnt>
Matrix<T, columnCnt, rowCnt>::Matrix()
{
	this->cols = columnCnt;
	this->rows = rowCnt;
	this->count = rows * cols;
	this->elements = new T[count];
	instanciationCnt = cnt++;
}

template <typename T, int columnCnt, int rowCnt>
Matrix<T, columnCnt, rowCnt>::Matrix(const Matrix& rhs)
{
	if (this != &rhs)
	{
		this->cols = rhs.cols;
		this->rows = rhs.rows;
		this->count = rhs.rows * rhs.cols;
		this->elements = new T[rhs.count];
		this->instanciationCnt = cnt++;
		std::memcpy(this->elements, rhs.elements, rhs.count * sizeof(float));
	}
}

template <typename T, int columnCnt, int rowCnt>
Matrix<T, columnCnt, rowCnt>::~Matrix()
{
	delete[] elements;
}

template <typename T, int columnCnt, int rowCnt>
T& Matrix<T, columnCnt, rowCnt>::element(int col, int row)
{
	return elements[row * columnCnt + col];
}

Matrix4x4f::Matrix4x4f()
{
	for (int i = 0; i < count; ++i)
	{
		elements[i] = 0.0f;
	}
}

void Matrix4x4f::setIdentity()
{
	for (int i = 0; i < count; ++i)
	{
		if (i == 0 || i == 5 ||
			i == 10 || i == 15)
			elements[i] = 1.0f;
		else
			elements[i] = 0.0f;
	}
}

void Matrix4x4f::translate(float x, float y, float z)
{
	this->elements[12] += x;
	this->elements[13] += y;
	this->elements[14] += z;
}

void Matrix4x4f::rotate(float x, float y, float z)
{
	Matrix4x4f* rot = getRotation(x, y, z);
	Matrix4x4f tmp = *this * *rot;/*
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			this->element(i, j) = tmp.element(i, j);
		}
	}*/
}

void Matrix4x4f::transpose()
{
	float tmp10 = this->elements[1];
	float tmp20 = this->elements[2];
	float tmp30 = this->elements[3];
	float tmp21 = this->elements[6];
	float tmp31 = this->elements[7];
	float tmp32 = this->elements[11];

	this->elements[1] = this->elements[4];
	this->elements[2] = this->elements[8];
	this->elements[3] = this->elements[9];
	this->elements[6] = this->elements[12];
	this->elements[7] = this->elements[13];
	this->elements[11] = this->elements[14];

	this->elements[4] = tmp10;
	this->elements[8] = tmp20;
	this->elements[9] = tmp30;
	this->elements[12] = tmp21;
	this->elements[13] = tmp31;
	this->elements[14] = tmp32;
}

Matrix4x4f* Matrix4x4f::getIdentity()
{
	Matrix4x4f* m = new Matrix4x4f();
	
	for (int i = 0; i < m->count; ++i)
	{
		if (i == 0 || i == 5 ||
			i == 10 || i == 15)
			m->elements[i] = 1.0f;
		else
			m->elements[i] = 0.0f;
	}

	return m;
}

Matrix4x4f* Matrix4x4f::getPerspective(float fovy, float aspect, float zNear, float zFar)
{
	Matrix4x4f* m = new Matrix4x4f();

	float f = 1.0f / std::tan(degreeToRadians(fovy * 0.5f));
	m->element(0, 0) = f / aspect;
	m->element(1, 1) = f;
	m->element(2, 2) = (zFar + zNear) / (zNear - zFar);
	m->element(2, 3) = (2 * zFar * zNear) / (zNear - zFar);
	m->element(3, 2) = -1.0f;

	return m;
}

Matrix4x4f* Matrix4x4f::getTranslation(float x, float y, float z)
{
	Matrix4x4f* m = getIdentity();
	m->elements[12] = x;
	m->elements[13] = y;
	m->elements[14] = z;
	return m;
}

Matrix4x4f* Matrix4x4f::getRotation(float x, float y, float z)
{
	float cx = std::cos(x);
	float cy = std::cos(y);
	float cz = std::cos(z);
	float sx = std::sin(x);
	float sy = std::sin(y);
	float sz = std::sin(z);

	Matrix4x4f* m = getIdentity();
	m->element(0, 0) = cz * cy;
	m->element(1, 0) = sz*cx + cz*sy*sx;
	m->element(2, 0) = sz*sx - cz*sy*cx;
	m->element(0, 0) = -sz*cy;
	m->element(1, 0) = cz*cx - sz*sy*sx;
	m->element(2, 0) = cz*sx + sz*sy*cx;
	m->element(0, 0) = sy;
	m->element(1, 0) = -cy*sx;
	m->element(2, 0) = cy*cx;

	return m;
}

Matrix4x4f* Matrix4x4f::getScale(float x, float y, float z)
{
	Matrix4x4f* m = getIdentity();
	m->element(0, 0) = x;
	m->element(1, 1) = y;
	m->element(2, 2) = z;
	return m;
}

Matrix4x4f& Matrix4x4f::operator=(const Matrix4x4f& rhs)
{
	if (this != &rhs)
	{
		std::memcpy(this->elements, rhs.elements, rhs.count * sizeof(float));
	}

	return *this;
}

Matrix4x4f Matrix4x4f::operator+(const Matrix4x4f& rhs) const
{
	Matrix4x4f m;
	for (int i = 0; i < count; ++i)
	{
		m.elements[i] = this->elements[i] + rhs.elements[i];
	}
	return m;
}

Matrix4x4f Matrix4x4f::operator-(const Matrix4x4f& rhs) const
{
	Matrix4x4f m;
	for (int i = 0; i < count; ++i)
	{
		m.elements[i] = this->elements[i] - rhs.elements[i];
	}
	return m;
}

Matrix4x4f Matrix4x4f::operator*(const Matrix4x4f& rhs) const
{
	Matrix4x4f m;
	for (int x = 0; x < rows; ++x)
	{
		for (int y = 0; y < cols; ++y)
		{
			int pos = x*rows + y;
			m.elements[pos] = 0.0f;
			for (int i = 0; i < rows; ++i)
			{
				float* colVal = this->elements + (x * rows) + i;
				float* rowVal = rhs.elements + (y * cols) + i;
				m.elements[pos] += *colVal * *rowVal;
			}
		}
	}
	return m;
}
