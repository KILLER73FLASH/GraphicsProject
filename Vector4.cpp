/*
  Filename: Vector4.cpp
  Author: Chad Hogg
  Course: CSCI375
  Assignment: A07Projection
  Description: A class that represents a vector with four float components.
*/

// For trigonometric functions 
#include <cmath>
// For output control
#include <iomanip>

// Local includes
#include "Vector4.h"

Vector4::Vector4 ()
{
  set(0.0f);
}

Vector4::Vector4 (float xyzw)
{
  set(xyzw);
}

Vector4::Vector4 (float x, float y, float z, float w)
{
  set(x, y, z, w);
}

const float*
Vector4::data () const
{
  return &x;
}

void
Vector4::set (float xyzw)
{
  x = y = z = w = xyzw;
}

void
Vector4::set (float x, float y, float z, float w)
{
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

float
Vector4::dot (const Vector4& v) const
{
  return x * v.x + y * v.y + z * v.z + w * v.w;
}

float
Vector4::length () const
{
  return sqrt(x * x + y * y + z * z + w * w);
}

void
Vector4::normalize ()
{
  float len = length ();
  x /= len;
  y /= len;
  z /= len;
  w /= len;
}

void
Vector4::negate ()
{
  x *= -1.0f;
  y *= -1.0f;
  z *= -1.0f;
  w *= -1.0f;
}

Vector4&
Vector4::operator+= (const Vector4& v)
{
  x += v.x;
  y += v.y;
  z += v.z;
  w += v.w;
  return *this;
}

Vector4&
Vector4::operator-= (const Vector4& v)
{
  x -= v.x;
  y -= v.y;
  z -= v.z;
  w -= v.w;
  return *this;
}

Vector4&
Vector4::operator*= (float s)
{
  x *= s;
  y *= s;
  z *= s;
  w *= s;
  return *this;
}

Vector4&
Vector4::operator*= (const Vector4& v)
{
  //TODO Is element-wise multiplication what is desired here?
  x *= v.x;
  y *= v.y;
  z *= v.z;
  w *= v.w;
  return *this;
}

Vector4&
Vector4::operator/= (float s)
{
  x /= s;
  y /= s;
  z /= s;
  w /= s;
  return *this;
}

Vector4
operator+ (const Vector4& v1, const Vector4& v2)
{
  return Vector4 (v1) += v2;
}

Vector4
operator- (const Vector4& v1, const Vector4& v2)
{
  return Vector4 (v1) -= v2;
}

Vector4
operator- (const Vector4& v)
{
  Vector4 result (v);
  result.negate ();
  return result;
}

Vector4
operator* (const Vector4& v1, const Vector4& v2)
{
  return Vector4 (v1) *= v2;
}

Vector4
operator* (float s, const Vector4& v)
{
  return Vector4 (v) *= s;
}

Vector4
operator* (const Vector4& v, float s)
{
  return Vector4 (v) *= s;
}

Vector4
operator/ (const Vector4& v, float s)
{
  return Vector4 (v) /= s;
}

std::ostream&
operator<< (std::ostream& out, const Vector4& v)
{
  out << std::setprecision(2) << "(" << std::setw(10) << v.x << ", " << std::setw(10) << v.y << ", " << std::setw(10) << v.z << std::setw(10) << v.w << ")";
  return out;
}

bool
operator== (const Vector4& v1, const Vector4& v2)
{
  const float EPSILON = 0.00001f;
  return (fabs(v1.x - v2.x) < EPSILON) &&
    (fabs(v1.y - v2.y) < EPSILON) &&
    (fabs(v1.z - v2.z) < EPSILON) &&
    (fabs(v1.w - v2.w) < EPSILON);
}
