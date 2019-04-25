/*
  Filename: Vector3.h
  Author: Joshua Kilhefner
  Course: CSCI 375
  Assignment: A04CameraRedux
*/

#ifndef VECTOR3_H
#define VECTOR3_H

#include <string>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "ShaderProgram.h"

class Vector3 {
  
public:

  // Initialize to zero vector
  Vector3 ();

  // Initialize each component with "xyz"
  Vector3 (float xyz);

  //Initialize with corresponding parameter
  Vector3 (float x, float y, float z);

  // Assign each data member "xyz"
  void
  set (float xyz);

  // Assign each data member from corresponding parameter
  void
  set (float x, float y, float z);

  // Negate this
  void
  negate ();

  // Compute this dot "v"
  float
  dot (const Vector3& v) const;

  // Return angle (in radians) b/w this and "v"
  float
  angleBetween (const Vector3& v) const;

  // Compute this cross "v"
  Vector3
  cross (const Vector3& v) const;

  // Compute length of this
  float length () const;

  // Normalize this
  void
  normalize ();

  Vector3&
  operator+= (const Vector3& v);

  Vector3&
  operator-= (const Vector3& v);

  Vector3&
  operator*= (float s);

  Vector3&
  operator/= (float s);
  


  float xVal;
  float yVal;
  float zVal;
  
private:
  
};
Vector3
operator+ (const Vector3& v1, const Vector3& v2);

Vector3
operator- (const Vector3& v1, const Vector3& v2);

Vector3
operator- (const Vector3& v);

Vector3
operator* (float s, const Vector3& v);

Vector3
operator* (const Vector3& v, float s);

Vector3
operator/ (const Vector3& v, float s);

// Print "v" using TWO digits of precision and a
// field width of 10 for each component
std::ostream&
operator<< (std::ostream& out, const Vector3& v);

// Vectors are equal if each of their components are
// within 0.0001f of each other
bool
operator== (const Vector3& v1, const Vector3& v2);

glm::vec3
convert(const Vector3& v);


#endif
