/*
  Filename: Matrix4.cpp
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A07Projection
  Description: A class that represents a 4x4 matrix.
*/


#include <iostream>
#include <cmath>
#include <iomanip>

#include "Matrix4.h"
#include "Vector4.h"

// Basis vectors are stored in Vector4-s and form
//   the columns of a 4x4 matrix. 
// The matrix is interpreted thus:
// [ rx ux bx tx ]
// [ ry uy by ty ]
// [ rz uz bz tz ]
// [ rw uw bw tw ]

// If the last row contains [ 0 0 0 1 ] the transform is affine,
//   otherwise it is projective.

// Operations are consistent with column vectors (v' = M * v).

// Initialize to identity. 
Matrix4::Matrix4 () {
  m_right.set (1, 0, 0, 0);
  m_up.set(0, 1, 0, 0);
  m_back.set(0, 0, 1, 0);
  m_translation.set(0, 0, 0, 1);
}

Matrix4::Matrix4 (const Vector4& right, const Vector4& up,
		  const Vector4& back, const Vector4& translation) {
  m_right = right;
  m_up = up;
  m_back = back;
  m_translation = translation;
}

Vector4
Matrix4::getRight () const {
  return m_right;
}

Vector4
Matrix4::getUp () const {
  return m_up;
}

Vector4
Matrix4::getBack () const {
  return m_back;
}

Vector4
Matrix4::getTranslation () const {
  return m_translation;
}

// Set to identity matrix. 
void
Matrix4::setToIdentity () {
  m_right.set (1, 0, 0, 0);
  m_up.set(0, 1, 0, 0);
  m_back.set(0, 0, 1, 0);
  m_translation.set(0, 0, 0, 1);
}

// Set to zero matrix. 
void
Matrix4::setToZero () {
  m_right.set (0, 0, 0, 0);
  m_up.set(0, 0, 0, 0);
  m_back.set(0, 0, 0, 0);
  m_translation.set(0, 0, 0, 0);
}

// Return a const pointer to the first element.
const float*
Matrix4::data () const {
  return &m_right.x;
}

// For the projection methods, do all computations using
//   double-s and only cast to float when NECESSARY. 

// Set this to a perspective projection matrix. 
void
Matrix4::setToPerspectiveProjection (double fovYDegrees, double aspectRatio,
				     double nearPlaneZ, double farPlaneZ) {
  fovYDegrees *= (M_PI / 180);
  double top = tan(fovYDegrees / 2) * nearPlaneZ;
  double bottom = -1 * top;
  double right = top * aspectRatio;
  double left = bottom * aspectRatio;
  setToPerspectiveProjection(left, right,bottom, top, nearPlaneZ, farPlaneZ);
}

// Set this to a perspective projection matrix using the
//   6 clip planes specified as parameters. 
void
Matrix4::setToPerspectiveProjection (double left, double right,
			    double bottom, double top,
				     double nearPlaneZ, double farPlaneZ) {
  m_right.set ((float)( 2 * nearPlaneZ / (right - left)), 0, 0, 0);
  m_up.set(0, (float)(2 * nearPlaneZ / (top - bottom)), 0, 0);
  m_back.set((float)((left + right) / (right - left)), (float)((bottom + top) / (top - bottom)), (float)((farPlaneZ + nearPlaneZ) / (nearPlaneZ - farPlaneZ)), -1);
  m_translation.set(0, 0, (float)(2 * farPlaneZ * nearPlaneZ / (nearPlaneZ - farPlaneZ)), 0);
}

// Set this to an orthographic projection matrix using the
//   6 clip planes specified as parameters. 
void
Matrix4::setToOrthographicProjection (double left, double right,
			     double bottom, double top,
				      double nearPlaneZ, double farPlaneZ) {
  m_right.set ((float)(2 / (right - left)), 0, 0, 0);
  m_up.set(0, (float)(2 / (top - bottom)), 0, 0);
  m_back.set(0, 0, (float)(2 / (nearPlaneZ - farPlaneZ)), 0);
  m_translation.set((float)(-1 * ((right + left) / (right - left))), (float)(-1 * ((top + bottom) / (top - bottom))), (float)((nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ)), 1);
}


std::ostream&
operator<< (std::ostream& out, const Matrix4& m) {
  out << std::setprecision(2) << "(" << std::setw(10) << m.m_right << ", " << std::setw(10) << m.m_up << ", " << std::setw(10) << m.m_back << std::setw(10) << m.m_translation << ")";
  return out;
}

bool
operator== (const Matrix4& m1, const Matrix4& m2) {
  return (m1.m_right == m2.m_right && m1.m_up == m2.m_up &&
	  m1.m_back == m2.m_back && m1.m_translation == m2.m_translation);
}
