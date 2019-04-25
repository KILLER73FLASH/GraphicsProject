/*
  Filename: Vector3.cpp
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

#include "Vector3.h"


  // Initialize to zero vector
  Vector3::Vector3 (){
    xVal = 0;
    yVal = 0;
    zVal = 0;
  }

  // Initialize each component with "xyz"
  Vector3::Vector3 (float xyz){
    xVal = xyz;
    yVal = xyz;
    zVal = xyz;
  }

  //Initialize with corresponding parameter
  Vector3::Vector3 (float x, float y, float z){
    xVal = x;
    yVal = y;
    zVal = z;
  }

  // Assign each data member "xyz"
  void
  Vector3::set (float xyz){
    xVal = xyz;
    yVal = xyz;
    zVal = xyz;
  }

  // Assign each data member from corresponding parameter
  void
  Vector3::set (float x, float y, float z){
    xVal = x;
    yVal = y;
    zVal = z;
  }

  // Negate this
  void
  Vector3::negate (){
    this->xVal = -(this->xVal);
    this->yVal = -(this->yVal);
    this->zVal = -(this->zVal);
  }

  // Compute this dot "v"
  float
  Vector3::dot (const Vector3& v) const{
    return (this->xVal*v.xVal + this->yVal*v.yVal + this->zVal*v.zVal);
  }

  // Return angle (in radians) b/w this and "v"
  float
  Vector3::angleBetween (const Vector3& v) const{
    return (acos(dot(v) / (this->length()*v.length())));
  }

  // Compute this cross "v"
  Vector3
  Vector3::cross (const Vector3& v) const{
    Vector3 product ((this->yVal * v.zVal - this->zVal * v.yVal), 
	       (this->zVal * v.xVal - this->xVal * v.zVal), 
	       (this->xVal * v.yVal - this->yVal * v.xVal));
    return product;
  }

  // Compute length of this
  float
  Vector3::length () const{
    return (sqrt(this->xVal * this->xVal + this->yVal * this->yVal +
		 this->zVal * this->zVal));
  }

  // Normalize this
  void
  Vector3::normalize (){
    float length = this->length();
    this->xVal = this->xVal / length;
    this->yVal = this->yVal / length;
    this->zVal = this->zVal / length;
  }
// Needs Work

   
  Vector3&
  Vector3::operator+= (const Vector3& v){
    set(xVal + v.xVal, yVal + v.yVal, zVal + v.zVal);
    return *this;
  }

  Vector3&
  Vector3::operator-= (const Vector3& v){
    set(xVal - v.xVal, yVal - v.yVal, zVal - v.zVal);
    return *this;
  }

  Vector3&
  Vector3::operator*= (float s){
    set(xVal * s, yVal * s, zVal * s);
    return *this;
  }

  Vector3&
  Vector3::operator/= (float s){
    set(xVal / s, yVal / s, zVal / s);
    return *this;
  }


Vector3
operator+ (const Vector3& v1, const Vector3& v2){
  Vector3 edit = v1;
  edit += v2;
  return edit;
}

Vector3
operator- (const Vector3& v1, const Vector3& v2){
  Vector3 edit = v1;
  edit -= v2;
  return edit;
}

Vector3
operator- (const Vector3& v){
  Vector3 edit = v;
  edit.negate();
  return edit;
}

Vector3
operator* (float s, const Vector3& v){
  Vector3 edit = v;
  edit *= s;
  return edit;
}

Vector3
operator* (const Vector3& v, float s){
  Vector3 edit = v;
  edit *= s;
  return edit;
}

Vector3
operator/ (const Vector3& v, float s){
  Vector3 edit = v;
  edit /= s;
  return edit;
}

// Print "v" using TWO digits of precision and a
// field width of 10 for each component
std::ostream&
operator<< (std::ostream& out, const Vector3& v){
  out << '(' << std::setw(10) << std::setprecision(2) << v.xVal <<
    ' ' << std::setw(10) << std::setprecision(2) << v.yVal << ' ' <<
    std::setw(10) << std::setprecision(2) << v.zVal << ')';
  return out;
}

// Vectors are equal if each of their components are
// within 0.0001f of each other
bool
operator== (const Vector3& v1, const Vector3& v2){
  return (abs((v1 - v2).length()) < 0.0001f);
}

glm::vec3
convert(const Vector3& v) {
  glm::vec3 converted (v.xVal, v.yVal, v.zVal);
  return converted;
}
