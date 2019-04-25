/*
  Filename: Transform.cpp
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A06Transform
  Description: A class that represents an affine transformation.
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>

#include "Matrix3.h"
// Uncomment if you decide to write a "Matrix4" class. 
#include "Matrix4.h"
#include <glm/mat4x4.hpp>
#include "Vector3.h"
#include "Transform.h"

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


 // Initialize to identity transform, that represents no
 //   scale, rotation, shear, or translation. 
Transform::Transform () {
  m_rotScale.setToIdentity();
 }

// Orthonormalize the Matrix3 component.
void
Transform::orthonormalize () {
  m_rotScale.orthonormalize();
}

// Reset to identity transform. 
void
Transform::reset () {
  m_rotScale.setToIdentity();
  m_position.set(0,0,0);
}

// Return this as a 4x4 GLM matrix.
Matrix4
Transform::getTransform () const {
  Vector4 right(m_rotScale.m_right.xVal, m_rotScale.m_right.yVal, m_rotScale.m_right.zVal, 0);
  Vector4 up(m_rotScale.m_up.xVal, m_rotScale.m_up.yVal, m_rotScale.m_up.zVal, 0);
  Vector4 back(m_rotScale.m_back.xVal, m_rotScale.m_back.yVal, m_rotScale.m_back.zVal, 0);
  Vector4 translation(m_position.xVal, m_position.yVal, m_position.zVal, 1);
  return Matrix4(right, up, back, translation);
}

// Store this transform in "array". 
// Remember we are using column-major storage, so
//   the order is [ rx ry rz 0 ux uy uz 0 ... px py pz 1 ].
void
Transform::getTransform (float array[16]) const {
  array[0] = m_rotScale.m_right.xVal;
  array[1] = m_rotScale.m_right.yVal;
  array[2] = m_rotScale.m_right.zVal;
  array[3] = 0;
  array[4] = m_rotScale.m_up.xVal;
  array[5] = m_rotScale.m_up.yVal;
  array[6] = m_rotScale.m_up.zVal;
  array[7] = 0;
  array[8] = m_rotScale.m_back.xVal;
  array[9] = m_rotScale.m_back.yVal;
  array[10] = m_rotScale.m_back.zVal;
  array[11] = 0;
  array[12] = m_position.xVal;
  array[13] = m_position.yVal;
  array[14] = m_position.zVal;
  array[15] = 1;
}

// Get the position component. 
Vector3
Transform::getPosition () const {
  return m_position;
}

// Set the position component. 
void
Transform::setPosition (const Vector3& position) {
  m_position = position;
}

// Set the position component. 
void
Transform::setPosition (float x, float y, float z) {
  m_position = Vector3 (x, y, z);
}

// Get the right basis vector. 
Vector3
Transform::getRight () const {
  return m_rotScale.getRight();
}

// Get the up basis vector. 
Vector3
Transform::getUp () const {
  return m_rotScale.getUp();
}

// Get the back basis vector. 
Vector3
Transform::getBack () const {
  return m_rotScale.getBack();
}

// Get the orientation and scale matrix.
Matrix3
Transform::getOrientation () const {
  return m_rotScale;
}

// Set the orientation and scale matrix. 
void
Transform::setOrientation (const Matrix3& orientation) {
  m_rotScale = orientation;
}

// Set the orientation and scale matrix. 
void
Transform::setOrientation (const Vector3& right, const Vector3& up,
		const Vector3& back) {
  m_rotScale = Matrix3(right, up, back);
}

// Move "distance" units along the right vector. 
void
Transform::moveRight (float distance) {
  m_position += distance * m_rotScale.m_right;
}

// Move "distance" units along the up vector. 
void
Transform::moveUp (float distance) {
  m_position += distance * m_rotScale.m_up;
}

// Move "distance" units along the back vector. 
void
Transform::moveBack (float distance) {
  m_position += distance * m_rotScale.m_back;
}

// Move "distance" units in "localDirection", which is relative
//   to the coordinate system defined by this transform. 
void
Transform::moveLocal (float distance, const Vector3& localDirection) {
  m_position += distance * localDirection;
}

// Move "distance" units in "worldDirection", which is relative
//   to the world coodinate system. 
void
Transform::moveWorld (float distance, const Vector3& worldDirection) {
  Vector3 edit = worldDirection;
  edit = m_rotScale * edit;
  m_position += distance * edit;
  
}

// Rotate about the local X axis.
void
Transform::pitch (float angleDegrees) {
  //m_rotScale.setToRotationX(angleDegrees);
  Matrix3 rotate;
  rotate.setToRotationX(angleDegrees);
  m_rotScale *= rotate;
}

// Rotate about the local Y axis.
void
Transform::yaw (float angleDegrees) {
  // m_rotScale.setToRotationY(angleDegrees);
  Matrix3 rotate;
  rotate.setToRotationY(angleDegrees);
  m_rotScale *= rotate;
}

// Rotate about the local Z axis.
void
Transform::roll (float angleDegrees) {
  //m_rotScale.setToRotationZ(angleDegrees);
  Matrix3 rotate;
  rotate.setToRotationZ(angleDegrees);
  m_rotScale *= rotate;
}

// Rotate locally about an arbitrary local unit vector "axis".
void
Transform::rotateLocal (float angleDegrees, const Vector3& axis) {
  //m_rotScale.setFromAngleAxis(angleDegrees, axis);
  Matrix3 rotate;
  rotate.setFromAngleAxis(angleDegrees, axis);
  m_rotScale *= rotate;
}

// Set "up" to world Y, and adjust "back" and "right"
//   to ensure the matrix is orthogonal.
// If "back" is pointing in the Y or -Y direction,
//   make it [ 0 0 1 ].
// This will override any scaling, shearing, pitching,
//   or rolling that existed, while leaving yawing and
//   movement.
void
Transform::alignWithWorldY () {
  m_rotScale.setUp(Vector3(0, 1, 0));
  if (m_rotScale.m_back == m_rotScale.m_up || m_rotScale.m_back == -1 *m_rotScale.m_up)
    m_rotScale.setBack(Vector3(0, 0, 1));
  else
    m_rotScale.setBack(Vector3(1, 0, 0).cross(m_rotScale.m_up));
  m_rotScale.setRight(m_rotScale.m_up.cross(m_rotScale.m_back));
  m_rotScale.m_back.normalize();
  m_rotScale.m_right.normalize();
    
}

// Rotate around the world unit vector "axis".
void
Transform::rotateWorld (float angleDegrees, const Vector3& axis) {
  //Vector3 edit = axis;
  //edit = m_rotScale * edit;
  Matrix3 rotate;
  rotate.setFromAngleAxis(angleDegrees, axis);
  m_position = rotate * m_position;
  rotate *= m_rotScale;
  m_rotScale = rotate;
 

}

// Scale locally using a uniform scale.
void
Transform::scaleLocal (float scale){
  //m_rotScale.setToScale(scale);
  Matrix3 scaleMatrix;
  scaleMatrix.setToScale(scale);
  m_rotScale *= scaleMatrix;
}

// Scale locally using a non-uniform scale.
void
Transform::scaleLocal (float scaleX, float scaleY, float scaleZ) {
  //m_rotScale.setToScale(scaleX, scaleY, scaleZ);
  Matrix3 scaleMatrix;
  scaleMatrix.setToScale(scaleX, scaleY, scaleZ);
  m_rotScale *= scaleMatrix;
}

// Scale wrt world using a uniform scale.
void
Transform::scaleWorld (float scale) {
  //m_position = m_rotScale * m_position;
  Matrix3 scaleMatrix;
  scaleMatrix.setToScale(scale);
  m_position = scaleMatrix * m_position;
  scaleMatrix *= m_rotScale;
  m_rotScale = scaleMatrix;
}

// Scale wrt world using a non-uniform scale.
void
Transform::scaleWorld (float scaleX, float scaleY, float scaleZ) {
  //m_position = m_rotScale * m_position;
  Matrix3 scaleMatrix;
  scaleMatrix.setToScale(scaleX, scaleY, scaleZ);
  m_position = scaleMatrix * m_position;
  scaleMatrix *= m_rotScale;
  m_rotScale = scaleMatrix;
}

// Shear local X by Y and Z. 
void
Transform::shearLocalXByYz (float shearY, float shearZ) {
  //m_rotScale.setToShearXByYz(shearY, shearZ);
  Matrix3 shear;
  shear.setToShearXByYz(shearY, shearZ);
  m_rotScale *= shear;
}

// Shear local Y by X and Z. 
void
Transform::shearLocalYByXz (float shearX, float shearZ) {
  //m_rotScale.setToShearYByXz(shearX, shearZ);
  Matrix3 shear;
  shear.setToShearYByXz(shearX, shearZ);
  m_rotScale *= shear;
}

// Shear local Z by X and Y. 
void
Transform::shearLocalZByXy (float shearX, float shearY) {
  //m_rotScale.setToShearZByXy(shearX, shearY);
  Matrix3 shear;
  shear.setToShearZByXy(shearX, shearY);
  m_rotScale *= shear;
}

// Invert this transform assuming it consists of a pure rotation
//   and a translation.
// This can be used to compute the view transform. 
void
Transform::invertRt () {
  //Has to involve all of the matrix 
  m_rotScale.invertRotation();
  Vector3 edit = m_position;
  edit.negate();
  m_position = m_rotScale * edit;
}

// Combine this with "t" in the order this * t. 
void
Transform::combine (const Transform& t) {
  //Involves Mat4 multiplication
  Transform edit;
  edit.m_rotScale = this->m_rotScale * t.m_rotScale;
  // Got this far then remembered I had a Matrix3 method to do exactly above.
  // UGH
  edit.m_position = this->m_rotScale * t.m_position + this->m_position;
  
  edit.getTransform();
  *this = edit;
}

// Print the complete 4x4 mtrix the Transform represents.
std::ostream&
operator<< (std::ostream& out, const Transform& t) {
  out << '(' << std::setw(10) << std::setprecision(2) << t.m_rotScale.m_right.xVal << ' ' << std::setw(10) << std::setprecision(2)  <<t.m_rotScale.m_up.xVal << ' '  << std::setw(10) << std::setprecision(2)  << t.m_rotScale.m_back.xVal << ' ' << std::setw(10) << std::setprecision(2)  << t.m_position.xVal << ' ' << std::setw(10) << std::setprecision(2)  << t.m_rotScale.m_right.yVal << std::setw(10) << std::setprecision(2) << t.m_rotScale.m_up.yVal << ' ' << std::setw(10) << std::setprecision(2) << t.m_rotScale.m_back.yVal << ' ' << std::setw(10) << std::setprecision(2)  << t.m_position.yVal << ' ' << std::setw(10) << std::setprecision(2)  << t.m_rotScale.m_right.zVal << ' ' << std::setw(10) << std::setprecision(2) << t.m_rotScale.m_up.zVal << ' ' << std::setw(10) << std::setprecision(2) << t.m_rotScale.m_back.zVal << ' '<< std::setw(10) << std::setprecision(2) << t.m_position.zVal << ' ' << std::setw(10) << std::setprecision(2) << 0 << ' ' << std::setw(10) << std::setprecision(2) << 0 << ' '<< std::setw(10) << std::setprecision(2) << 0 << ' '<< std::setw(10) << std::setprecision(2)<< 1 << ' ' << ')';
  return out;
}

// Test whether or not the two Transforms have equivalent matrices and vectors.
bool
operator== (const Transform& t1, const Transform& t2) {
  return (t1.m_rotScale == t2.m_rotScale && t1.m_position == t2.m_position);
}
