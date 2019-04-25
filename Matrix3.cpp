/*
  Filename: Matrix3.cpp
  Author: Joshua Kilhefner
  Course: CSCI 375
  Assignment: A04CameraRedux
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <memory>
#include <vector>
#include <iomanip>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "Matrix3.h"
#include "Vector3.h"

// Initialize to identity. 
Matrix3::Matrix3 (){
  m_right.xVal = 1.0f;
  m_right.yVal = 0.0f;
  m_right.zVal = 0.0f;
  m_up.xVal = 0.0f;
  m_up.yVal = 1.0f;
  m_up.zVal = 0.0f;
  m_back.xVal = 0.0f;
  m_back.yVal = 0.0f;
  m_back.zVal = 1.0f;
}

// Initial right vector to (rx, ry, rz),
//   up to (ux, uy, uz), and
//   back to (bx, by, bz).
Matrix3::Matrix3 (float rx, float ry, float rz,
		  float ux, float uy, float uz,
		  float bx, float by, float bz){
  m_right.xVal = rx;
  m_right.yVal = ry;
  m_right.zVal = rz;
  m_up.xVal = ux;
  m_up.yVal = uy;
  m_up.zVal = uz;
  m_back.xVal = bx;
  m_back.yVal = by;
  m_back.zVal = bz;
}

// Initialize corresponding basis vector.
Matrix3::Matrix3 (const Vector3& right, const Vector3& up,
		  const Vector3& back){
  m_right.xVal = right.xVal;
  m_right.yVal =right.yVal;
  m_right.zVal = right.zVal;
  m_up.xVal = up.xVal;
  m_up.yVal = up.yVal;
  m_up.zVal = up.zVal;
  m_back.xVal = back.xVal;
  m_back.yVal = back.yVal;
  m_back.zVal = back.zVal;
}

// Initialize right, up, and back. Compute back via a cross product.
// If "makeOrthonormal" is true, call "orthonormalize".
Matrix3::Matrix3 (const Vector3& right, const Vector3& up,
		  bool makeOrthonormal){
  m_right.xVal = right.xVal;
  m_right.yVal =right.yVal;
  m_right.zVal = right.zVal;
  m_up.xVal = up.xVal;
  m_up.yVal = up.yVal;
  m_up.zVal = up.zVal;
  m_back = m_right.cross(m_up);
  if (makeOrthonormal)
    orthonormalize();
}

// Set to identity matrix.
void
Matrix3::setToIdentity(){
  m_right.xVal = 1.0f;
  m_right.yVal = 0.0f;
  m_right.zVal = 0.0f;
  m_up.xVal = 0.0f;
  m_up.yVal = 1.0f;
  m_up.zVal = 0.0f;
  m_back.xVal = 0.0f;
  m_back.yVal = 0.0f;
  m_back.zVal = 1.0f;
}

// Set all elements to 0.
void
Matrix3::setToZero (){
  m_right.xVal = 0.0f;
  m_right.yVal = 0.0f;
  m_right.zVal = 0.0f;
  m_up.xVal = 0.0f;
  m_up.yVal = 0.0f;
  m_up.zVal = 0.0f;
  m_back.xVal = 0.0f;
  m_back.yVal = 0.0f;
  m_back.zVal = 0.0f;
}

// Return a pointer to the first element.
float*
Matrix3::data (){
  return &m_right.xVal;
}

// Return a const pointer to the first element.
const float*
Matrix3::data () const{
  return &m_right.xVal;
}

// Set the right vector. Do not modify others. 
void
Matrix3::setRight (const Vector3& right){
  m_right.xVal = right.xVal;
  m_right.yVal =right.yVal;
  m_right.zVal = right.zVal;
}

// Get the right vector.
Vector3
Matrix3::getRight () const{
  return m_right;
}

// Set the up vector only. Do not modify others. 
void
Matrix3::setUp (const Vector3& up){
  m_up.xVal = up.xVal;
  m_up.yVal = up.yVal;
  m_up.zVal = up.zVal;
}

// Get the up vector. 
Vector3
Matrix3::getUp () const{
  return m_up;
}

// Set the back vector. Do not modify others. 
void
Matrix3::setBack (const Vector3& back){
  m_back.xVal = back.xVal;
  m_back.yVal = back.yVal;
  m_back.zVal = back.zVal;
}

// Get the back vector.
Vector3
Matrix3::getBack () const{
  return m_back;
}

// Set the back vector to the negation of "forward".
void
Matrix3::setForward (const Vector3& forward){
  m_back = forward * -1;
}

// Get the forward vector.
Vector3
Matrix3::getForward () const{
  return (m_back * -1);
}

// Invert this matrix, assuming it's a rotation matrix.
void
Matrix3::invertRotation (){
  transpose();
}

// Invert this matrix.
void
  Matrix3::invert (){
  Matrix3 temp;
  temp.m_right.xVal = (this->m_up.yVal * this->m_back.zVal - this->m_back.yVal * this->m_up.zVal);
  temp.m_right.yVal = (this->m_back.yVal * this->m_right.zVal - this->m_right.yVal * this->m_back.zVal);
  temp.m_right.zVal = (this->m_right.yVal * this->m_up.zVal - this->m_up.yVal * this->m_right.zVal);
  temp.m_up.xVal = (this->m_back.xVal * this->m_up.zVal - this->m_up.xVal * this->m_back.zVal);
  temp.m_up.yVal = (this->m_right.xVal * this->m_back.zVal - this->m_back.xVal * this->m_right.zVal);
  temp.m_up.zVal = (this->m_up.xVal * this->m_right.zVal - this->m_right.xVal * this->m_up.zVal);
  temp.m_back.xVal = (this->m_up.xVal * this->m_back.yVal - this->m_back.xVal * this->m_up.yVal);
  temp.m_back.yVal = (this->m_back.xVal * this->m_right.yVal - this->m_right.xVal * this->m_back.yVal);
  temp.m_back.zVal = (this->m_right.xVal * this->m_up.yVal - this->m_up.xVal * this->m_right.yVal);
  temp = (this->determinant() * temp);
  this->m_right = temp.m_right;
  this->m_up = temp.m_up;
  this->m_back = temp.m_back;
}

// Return the determinant. 
float
Matrix3::determinant () const{
  float det =
    m_right.xVal * (m_up.yVal * m_back.zVal - m_back.yVal * m_up.zVal) -
    m_right.yVal * (m_up.xVal * m_back.zVal - m_back.xVal * m_up.zVal) +
    m_right.zVal * (m_up.xVal * m_back.yVal - m_back.xVal * m_up.yVal);
  
  return det;
}

// Transpose this. 
void
Matrix3::transpose (){
  Vector3 tempRight = this->m_right;
  Vector3 tempUp = this->m_up;
  Vector3 tempBack = this->m_back;
  m_right.xVal = tempRight.xVal;
  m_right.yVal = tempUp.xVal;
  m_right.zVal = tempBack.xVal;
  m_up.xVal = tempRight.yVal;
  m_up.yVal = tempUp.yVal;
  m_up.zVal = tempBack.yVal;
  m_back.xVal = tempRight.zVal;
  m_back.yVal = tempUp.zVal;
  m_back.zVal = tempBack.zVal;
  
}

// Ensure all axes are of unit length and mutually perpendicular.
//   Bias toward the back vector by assuming it is pointing
//   in the correct direction. Normalize it, compute right via cross, 
//   normalize it, and finally compute up. 
void
Matrix3::orthonormalize (){
  m_back.normalize();
  m_right = m_up.cross(m_back);
  m_right.normalize();
  m_up = m_back.cross(m_right);
}

// For each "set" method, ensure you set ALL matrix entries!
// Set to a uniform scale matrix. 
void
Matrix3::setToScale (float scale){
  m_right.xVal = scale;
  m_right.yVal = 0;
  m_right.zVal = 0;
  m_up.xVal = 0;
  m_up.yVal = scale;
  m_up.zVal = 0;
  m_back.xVal = 0;
  m_back.yVal = 0;
  m_back.zVal = scale;
  
}

// Set to a non-uniform scale matrix.
void
Matrix3::setToScale (float scaleX, float scaleY, float scaleZ){
  m_right.xVal = scaleX;
  m_right.yVal = 0;
  m_right.zVal = 0;
  m_up.xVal = 0;
  m_up.yVal = scaleY;
  m_up.zVal = 0;
  m_back.xVal = 0;
  m_back.yVal = 0;
  m_back.zVal = scaleZ;
  
}

// Set to a shear matrix that shears x by y and z.
void
Matrix3::setToShearXByYz (float shearY, float shearZ){
  m_right.xVal = 1.0f;
  m_right.yVal = 0.0f;
  m_right.zVal = 0.0f;
  m_up.xVal = shearY;
  m_up.yVal = 1.0f;
  m_up.zVal = 0.0f;
  m_back.xVal = shearZ;
  m_back.yVal = 0.0f;
  m_back.zVal = 1.0f;
}

// Set to a shear matrix that shears y by x and z.
void
Matrix3::setToShearYByXz (float shearX, float shearZ){
  m_right.xVal = 1.0f;
  m_right.yVal = shearX;
  m_right.zVal = 0.0f;
  m_up.xVal = 0.0f;
  m_up.yVal = 1.0f;
  m_up.zVal = 0.0f;
  m_back.xVal = 0.0f;
  m_back.yVal = shearZ;
  m_back.zVal = 1.0f;
}

// Set to a shear matrix that shears z by x and y.
void
Matrix3::setToShearZByXy (float shearX, float shearY){
  m_right.xVal = 1.0f;
  m_right.yVal = 0.0f;
  m_right.zVal = shearX;
  m_up.xVal = 0.0f;
  m_up.yVal = 1.0f;
  m_up.zVal = shearY;
  m_back.xVal = 0.0f;
  m_back.yVal = 0.0f;
  m_back.zVal = 1.0f;
}

// Set to an x-axis rotation matrix.
void
Matrix3::setToRotationX (float angleDegrees){
  angleDegrees *= (M_PI / 180);
  m_right.xVal = 1.0f;
  m_right.yVal = 0.0f;
  m_right.zVal = 0.0f;
  m_up.xVal = 0.0f;
  m_up.yVal = cos(angleDegrees);
  m_up.zVal = sin(angleDegrees);;
  m_back.xVal = 0.0f;
  m_back.yVal = -(sin(angleDegrees));
  m_back.zVal = cos(angleDegrees);;
  
}

// Set to a y-axis rotation matrix.
void
Matrix3::setToRotationY (float angleDegrees){
  angleDegrees *= (M_PI / 180);
  m_right.xVal = cos(angleDegrees);
  m_right.yVal = 0.0f;
  m_right.zVal = -(sin(angleDegrees));
  m_up.xVal = 0.0f;
  m_up.yVal = 1.0f;
  m_up.zVal = 0.0f;
  m_back.xVal = sin(angleDegrees);
  m_back.yVal = 0.0f;
  m_back.zVal = cos(angleDegrees);
  
}

// Set to a z-axis rotation matrix.
void
Matrix3::setToRotationZ (float angleDegrees){
  angleDegrees *= (M_PI / 180);
  m_right.xVal = cos(angleDegrees);
  m_right.yVal = sin(angleDegrees);
  m_right.zVal = 0.0f;
  m_up.xVal = -(sin(angleDegrees));
  m_up.yVal = cos(angleDegrees);
  m_up.zVal = 0.0f;
  m_back.xVal = 0.0f;
  m_back.yVal = 0.0f;
  m_back.zVal = 1.0f;
}

// Set to a general rotation matrix that rotates about "axis". 
void
Matrix3::setFromAngleAxis (float angleDegrees, const Vector3& axis){
  Vector3 tilt = axis;
  tilt.normalize();
  angleDegrees *= (M_PI / 180);
  float c = cos(angleDegrees);
  float s = sin(angleDegrees);
  
  m_right.xVal = tilt.xVal * tilt.xVal + c * (1 - tilt.xVal * tilt.xVal);
  m_right.yVal = tilt.xVal * tilt.yVal * (1 - c) + tilt.zVal * s;
  m_right.zVal = tilt.xVal * tilt.zVal * (1 - c) - tilt.yVal * s;
  m_up.xVal = tilt.xVal * tilt.yVal * (1 - c) - tilt.zVal * s;
  m_up.yVal = tilt.yVal * tilt.yVal + c * (1 - tilt.yVal * tilt.yVal);
  m_up.zVal = tilt.yVal * tilt.zVal * (1 - c) + tilt.xVal * s;
  m_back.xVal = tilt.xVal * tilt.zVal * (1 - c) + tilt.yVal * s;
  m_back.yVal = tilt.yVal * tilt.zVal * (1-c) - tilt.xVal * s;
  m_back.zVal = tilt.zVal * tilt.zVal + c * (1 - tilt.zVal * tilt.zVal);
}

// Negate this.
void
Matrix3::negate (){
  m_right.xVal *= -1.0f;
  m_right.yVal *= -1.0f;
  m_right.zVal *= -1.0f;
  m_up.xVal *= -1.0f;
  m_up.yVal *= -1.0f;
  m_up.zVal *= -1.0f;
  m_back.xVal *= -1.0f;
  m_back.yVal *= -1.0f;
  m_back.zVal *= -1.0f;
  
}

// Return *this * v.
Vector3
Matrix3::transform (const Vector3& v) const{
  return (*this * v);
}

Matrix3&
Matrix3::operator+= (const Matrix3& m){
  Matrix3 edit;
  edit.m_right = m_right + m.m_right;
  edit.m_up = m_up + m.m_up;
  edit.m_back = m_back + m.m_back;
  *this = edit;
  return *this;
  }

Matrix3&
Matrix3::operator-= (const Matrix3& m){
   Matrix3 edit;
   edit.m_right = m_right - m.m_right;
   edit.m_up = m_up - m.m_up;
   edit.m_back = m_back - m.m_back;
   *this = edit;
   return *this;
}

  // Scalar matrix multiply.
Matrix3&
Matrix3::operator*= (float scalar){
  Matrix3 edit;
  edit.m_right = m_right * scalar;
  edit.m_up = m_up * scalar;
  edit.m_back = m_back * scalar;
  *this = edit;
  return *this;
}

// Matrix multiply.
Matrix3&
Matrix3::operator*= (const Matrix3& m){
     Matrix3 edit;
     edit.m_right.xVal = m_right.xVal * m.m_right.xVal +
       m_up.xVal *  m.m_right.yVal + m.m_right.zVal * m_back.xVal;
     edit.m_right.yVal = m.m_right.xVal * m_right.yVal +
       m.m_right.yVal *  m_up.yVal + m.m_right.zVal * m_back.yVal;
     edit.m_right.zVal = m.m_right.xVal * m_right.zVal +
       m.m_right.yVal *  m_up.zVal + m.m_right.zVal * m_back.zVal;
     edit.m_up.xVal = m.m_up.xVal * m_right.xVal +
       m.m_up.yVal *  m_up.xVal + m.m_up.zVal * m_back.xVal;
     edit.m_up.yVal = m.m_up.xVal * m_right.yVal +
       m.m_up.yVal *  m_up.yVal + m.m_up.zVal * m_back.yVal;
     edit.m_up.zVal = m.m_up.xVal * m_right.zVal +
       m.m_up.yVal *  m_up.zVal + m.m_up.zVal * m_back.zVal;
     edit.m_back.xVal = m.m_back.xVal * m_right.xVal +
       m.m_back.yVal *  m_up.xVal + m.m_back.zVal * m_back.xVal;
     edit.m_back.yVal = m.m_back.xVal * m_right.yVal +
       m.m_back.yVal *  m_up.yVal + m.m_back.zVal * m_back.yVal;
     edit.m_back.zVal = m.m_back.xVal * m_right.zVal +
       m.m_back.yVal *  m_up.zVal + m.m_back.zVal * m_back.zVal;
     *this = edit;
     return *this;
}

Matrix3
operator+ (const Matrix3& m1, const Matrix3& m2){
  Matrix3 edit = m1;
  edit += m2;
  return edit;
}

Matrix3
operator- (const Matrix3& m1, const Matrix3& m2){
  Matrix3 edit = m1;
  edit -= m2;
  return edit;
}

// Unary negation.
Matrix3
operator- (const Matrix3& m){
  Matrix3 edit = m;
  edit.negate();
  return edit;
}

Matrix3
operator* (const Matrix3& m, float scalar){
  Matrix3 edit = m;
  edit *= scalar;
  return edit;
}

Matrix3
operator* (float scalar, const Matrix3& m){
  Matrix3 edit = m;
  edit *= scalar;
  return edit;
}

Matrix3
operator* (const Matrix3& m1, const Matrix3& m2){
  Matrix3 edit = m1;
  edit *= m2;
  return edit;
}
Vector3
operator* (const Matrix3& m, const Vector3& v){
  Vector3 edit;
  edit.xVal = m.m_right.xVal * v.xVal + m.m_up.xVal * v.yVal + m.m_back.xVal * v.zVal;
  edit.yVal = m.m_right.yVal * v.xVal + m.m_up.yVal * v.yVal + m.m_back.yVal * v.zVal;
  edit.zVal = m.m_right.zVal * v.xVal + m.m_up.zVal * v.yVal + m.m_back.zVal * v.zVal;
  return edit;
}

// Print "m" in a neat, tabular format using TWO digits
//   of precision and a field width of 10 for each entry. 
std::ostream&
operator<< (std::ostream& out, const Matrix3& m){
  out << '(' << std::setw(10) << std::setprecision(2) << m.m_right <<
    ' ' << std::setw(10) << std::setprecision(2) << m.m_up << ' ' <<
    std::setw(10) << std::setprecision(2) << m.m_back << ')';
  return out;
} 


bool
operator== (const Matrix3& m1, const Matrix3& m2){
  return (m1.m_right == m2.m_right && m1.m_up == m2.m_up && m1.m_back == m2.m_back);
}

