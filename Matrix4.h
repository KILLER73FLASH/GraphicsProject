/*
  Filename: Matrix4.h
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A07Projection
  Description: A class that represents a 4x4 matrix.
*/

#ifndef MATRIX4_H
#define MATRIX4_H

#include <iostream>

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
class Matrix4
{
public:
  // Initialize to identity. 
  Matrix4 ();

  Matrix4 (const Vector4& right, const Vector4& up,
	   const Vector4& back, const Vector4& translation);

  Vector4
  getRight () const;

  Vector4
  getUp () const;

  Vector4
  getBack () const;

  Vector4
  getTranslation () const;

  // Set to identity matrix. 
  void
  setToIdentity ();

  // Set to zero matrix. 
  void
  setToZero ();
    
  // Return a const pointer to the first element.
  const float*
  data () const;

  // For the projection methods, do all computations using
  //   double-s and only cast to float when NECESSARY. 

  // Set this to a perspective projection matrix. 
  void
  setToPerspectiveProjection (double fovYDegrees, double aspectRatio,
			      double nearPlaneZ, double farPlaneZ);

  // Set this to a perspective projection matrix using the
  //   6 clip planes specified as parameters. 
  void
  setToPerspectiveProjection (double left, double right,
			      double bottom, double top,
			      double nearPlaneZ, double farPlaneZ);

  // Set this to an orthographic projection matrix using the
  //   6 clip planes specified as parameters. 
  void
  setToOrthographicProjection (double left, double right,
			       double bottom, double top,
			       double nearPlaneZ, double farPlaneZ);
  
  //private:
  Vector4 m_right;
  Vector4 m_up;
  Vector4 m_back;
  Vector4 m_translation;
};

std::ostream&
operator<< (std::ostream& out, const Matrix4& m);

bool
operator== (const Matrix4& m1, const Matrix4& m2);

#endif
