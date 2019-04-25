/*
  Filename: Transform.h
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A06Transform
  Description: A class that represents an affine transformation.
*/

#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <iostream>

#include "Matrix3.h"
// Uncomment if you decide to write a "Matrix4" class. 
#include "Matrix4.h"
#include <glm/mat4x4.hpp>
#include "Vector3.h"

// A Transform represents a 3x4 matrix, stored in
//   column-major order as follows:
//   [ rx ux bx px ]
//   [ ry uy by py ]
//   [ rz uz bz pz ]
//   [  0  0  0  1 ] 
// 'r', 'u', 'b', and 'p' are the right, up, back,
//   and position vectors, respectively. 
// The last row is not explicitly stored since it is always
//    [  0  0  0  1 ].
class Transform
{
public:
  // Initialize to identity transform, that represents no
  //   scale, rotation, shear, or translation. 
  Transform ();
  
  // Orthonormalize the Matrix3 component.
  void
  orthonormalize ();
  
  // Reset to identity transform. 
  void
  reset ();
  
  // Return this as a 4x4 GLM matrix.
  Matrix4
  getTransform () const;
  
  // Store this transform in "array". 
  // Remember we are using column-major storage, so
  //   the order is [ rx ry rz 0 ux uy uz 0 ... px py pz 1 ].
  void
  getTransform (float array[16]) const;

  // Get the position component. 
  Vector3
  getPosition () const;
  
  // Set the position component. 
  void
  setPosition (const Vector3& position);

  // Set the position component. 
  void
  setPosition (float x, float y, float z);

  // Get the right basis vector. 
  Vector3
  getRight () const;
  
  // Get the up basis vector. 
  Vector3
  getUp () const;
  
  // Get the back basis vector. 
  Vector3
  getBack () const;

  // Get the orientation and scale matrix.
  Matrix3
  getOrientation () const;

  // Set the orientation and scale matrix. 
  void
  setOrientation (const Matrix3& orientation);

  // Set the orientation and scale matrix. 
  void
  setOrientation (const Vector3& right, const Vector3& up,
		  const Vector3& back);

  // Move "distance" units along the right vector. 
  void
  moveRight (float distance);

  // Move "distance" units along the up vector. 
  void
  moveUp (float distance);

  // Move "distance" units along the back vector. 
  void
  moveBack (float distance);

  // Move "distance" units in "localDirection", which is relative
  //   to the coordinate system defined by this transform. 
  void
  moveLocal (float distance, const Vector3& localDirection);

  // Move "distance" units in "worldDirection", which is relative
  //   to the world coodinate system. 
  void
  moveWorld (float distance, const Vector3& worldDirection);

  // Rotate about the local X axis.
  void
  pitch (float angleDegrees);

  // Rotate about the local Y axis.
  void
  yaw (float angleDegrees);

  // Rotate about the local Z axis.
  void
  roll (float angleDegrees);

  // Rotate locally about an arbitrary local unit vector "axis".
  void
  rotateLocal (float angleDegrees, const Vector3& axis);

  // Set "up" to world Y, and adjust "back" and "right"
  //   to ensure the matrix is orthogonal.
  // If "back" is pointing in the Y or -Y direction,
  //   make it [ 0 0 1 ].
  // This will override any scaling, shearing, pitching,
  //   or rolling that existed, while leaving yawing and
  //   movement.
  void
  alignWithWorldY ();

  // Rotate around the world unit vector "axis".
  void
  rotateWorld (float angleDegrees, const Vector3& axis);

  // Scale locally using a uniform scale.
  void
  scaleLocal (float scale);

  // Scale locally using a non-uniform scale.
  void
  scaleLocal (float scaleX, float scaleY, float scaleZ);
    
  // Scale wrt world using a uniform scale.
  void
  scaleWorld (float scale);

  // Scale wrt world using a non-uniform scale.
  void
  scaleWorld (float scaleX, float scaleY, float scaleZ);

  // Shear local X by Y and Z. 
  void
  shearLocalXByYz (float shearY, float shearZ);

  // Shear local Y by X and Z. 
  void
  shearLocalYByXz (float shearX, float shearZ);

  // Shear local Z by X and Y. 
  void
  shearLocalZByXy (float shearX, float shearY);

  // Invert this transform assuming it consists of a pure rotation
  //   and a translation.
  // This can be used to compute the view transform. 
  void
  invertRt ();
  
  // Combine this with "t" in the order this * t. 
  void
  combine (const Transform& t);

  //private:
  // This member stores the right, up, and back basis vectors. 
  Matrix3 m_rotScale;
  // This member stores the position/translation vector.
  Vector3 m_position;
};

// Print the complete 4x4 mtrix the Transform represents.
std::ostream&
operator<< (std::ostream& out, const Transform& t);

// Test whether or not the two Transforms have equivalent matrices and vectors.
bool
operator== (const Transform& t1, const Transform& t2);

#endif//TRANSFORM_H
