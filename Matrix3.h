/*
  Filename: Matrix3.h
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A05Matrix
  Description: A class that represents a 3x3 matrix of floats.
*/

#ifndef MATRIX3_H
#define MATRIX3_H

#include <iostream>

#include "Vector3.h"

// Basis vectors are stored in Vector3-s and form
//   the columns of a 3x3 matrix. 
// The matrix is interpreted thus:
// [ rx ux bx ]
// [ ry uy by ]
// [ rz uz bz ]
// Operations are consistent with column vectors (v' = M * v).
class Matrix3
{
public:
  // Initialize to identity. 
  Matrix3 ();
  
  // Initial right vector to (rz, ry, rz),
  //   up to (ux, uy, uz), and
  //   back to (bx, by, bz).
  Matrix3 (float rx, float ry, float rz,
           float ux, float uy, float uz,
           float bx, float by, float bz);
  
  // Initialize corresponding basis vector.
  Matrix3 (const Vector3& right, const Vector3& up,
           const Vector3& back);
  
  // Initialize right, up, and back. Compute back via a cross product.
  // If "makeOrthonormal" is true, call "orthonormalize".
  Matrix3 (const Vector3& right, const Vector3& up,
           bool makeOrthonormal = false);

  // Set to identity matrix.
  void
  setToIdentity ();

  // Set all elements to 0.
  void
  setToZero ();

  // Return a pointer to the first element.
  float*
  data ();

  // Return a const pointer to the first element.
  const float*
  data () const;

  // Set the right vector. Do not modify others. 
  void
  setRight (const Vector3& right);

  // Get the right vector.
  Vector3
  getRight () const;

  // Set the up vector only. Do not modify others. 
  void
  setUp (const Vector3& up);

  // Get the up vector. 
  Vector3
  getUp () const;

  // Set the back vector. Do not modify others. 
  void
  setBack (const Vector3& back);

  // Get the back vector.
  Vector3
  getBack () const;

  // Set the back vector to the negation of "forward".
  void
  setForward (const Vector3& forward);

  // Get the forward vector.
  Vector3
  getForward () const;

  // Invert this matrix, assuming it's a rotation matrix.
  void
  invertRotation ();

  // Invert this matrix.
  void
  invert ();

  // Return the determinant. 
  float
  determinant () const;

  // Transpose this. 
  void
  transpose ();

  // Ensure all axes are of unit length and mutually perpendicular.
  //   Bias toward the back vector by assuming it is pointing
  //   in the correct direction. Normalize it, compute right via cross, 
  //   normalize it, and finally compute up. 
  void
  orthonormalize ();

  // For each "set" method, ensure you set ALL matrix entries!
  // Set to a uniform scale matrix. 
  void
  setToScale (float scale);

  // Set to a non-uniform scale matrix.
  void
  setToScale (float scaleX, float scaleY, float scaleZ);

  // Set to a shear matrix that shears x by y and z.
  void
  setToShearXByYz (float shearY, float shearZ);

  // Set to a shear matrix that shears y by x and z.
  void
  setToShearYByXz (float shearX, float shearZ);

  // Set to a shear matrix that shears z by x and y.
  void
  setToShearZByXy (float shearX, float shearY);

  // Set to an x-axis rotation matrix.
  void
  setToRotationX (float angleDegrees);

  // Set to a y-axis rotation matrix.
  void
  setToRotationY (float angleDegrees);

  // Set to a z-axis rotation matrix.
  void
  setToRotationZ (float angleDegrees);

  // Set to a general rotation matrix that rotates about "axis". 
  void
  setFromAngleAxis (float angleDegrees, const Vector3& axis);

  // Negate this.
  void
  negate ();

  // Return *this * v.
  Vector3
  transform (const Vector3& v) const;

  Matrix3&
  operator+= (const Matrix3& m);

  Matrix3&
  operator-= (const Matrix3& m);

  // Scalar matrix multiply.
  Matrix3&
  operator*= (float scalar);

  // Matrix multiply.
  Matrix3&
  operator*= (const Matrix3& m);

  //private:
  Vector3 m_right;
  Vector3 m_up;
  Vector3 m_back;
};

Matrix3
operator+ (const Matrix3& m1, const Matrix3& m2);

Matrix3
operator- (const Matrix3& m1, const Matrix3& m2);

// Unary negation.
Matrix3
operator- (const Matrix3& m);

Matrix3
operator* (const Matrix3& m, float scalar);

Matrix3
operator* (float scalar, const Matrix3& m);

Matrix3
operator* (const Matrix3& m1, const Matrix3& m2);

Vector3
operator* (const Matrix3& m, const Vector3& v);

// Print "m" in a neat, tabular format using TWO digits
//   of precision and a field width of 10 for each entry. 
std::ostream&
operator<< (std::ostream& out, const Matrix3& m);

bool
operator== (const Matrix3& m1, const Matrix3& m2);


#endif//MATRIX3_H
