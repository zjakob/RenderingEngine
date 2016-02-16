#ifndef ENGINE_MATRIX_H
#define ENGINE_MATRIX_H

namespace math
{

template <typename T, int columnCnt, int rowCnt>
class Matrix
{
protected:
	T* elements;
	int count;
	int cols;
	int rows;
	
public:
	Matrix();
	Matrix(const Matrix& rhs);
	~Matrix();
	// TODO move, copy, assignm

	static int cnt;
	int instanciationCnt;
	inline operator T*() { return &elements[0]; }
	T& element(int col, int row);
};

/*
 * Row major matrix:
 * [  m0,  m1,  m2,  m3 ]
 * [  m4,  m5,  m6,  m7 ]
 * [  m8,  m9, m10, m11 ]
 * [ m12, m13, m14, m15 ]
 */
class Matrix4x4f : public Matrix<float, 4, 4>
{
public:
	Matrix4x4f();

	void setIdentity();
	void translate(float x, float y, float z);
	void rotate(float x, float y, float z);
	void transpose();
	
	Matrix4x4f& operator= (const Matrix4x4f& rhs);
	Matrix4x4f operator+(const Matrix4x4f& rhs) const;
	Matrix4x4f operator-(const Matrix4x4f& rhs) const;
	Matrix4x4f operator*(const Matrix4x4f& rhs) const;

	static Matrix4x4f* getIdentity();
	/**
	* @brief	returns a perspective matrix
	*
	* @param	fovy the field of view in degree
	*/
	static Matrix4x4f* getPerspective(float fovy, float aspect, float zNear, float zFar);
	static Matrix4x4f* getTranslation(float x, float y, float z);
	static Matrix4x4f* getRotation(float x, float y, float z);
	static Matrix4x4f* getScale(float x, float y, float z);
};

}

#endif