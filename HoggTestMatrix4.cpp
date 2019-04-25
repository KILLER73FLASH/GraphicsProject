
/*
  Filename: CatchTestMatrix4.cpp
  Author: Chad Hogg
  Course: CSCI375
  Assignment: A07Projection
  Description: Catch2 test cases for the Matrix4 class.
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <iostream>
#include <iomanip>
#include "Vector4.h"
#include "Matrix4.h"
#include <glm/gtc/matrix_transform.hpp>

TEST_CASE ("Matrix4::Matrix4() initializes to the identity", "[Matrix4]") {
  Matrix4 m;
  CHECK (m.getRight () == Vector4 (1.0f, 0.0f, 0.0f, 0.0f));
  CHECK (m.getUp () == Vector4 (0.0f, 1.0f, 0.0f, 0.0f));
  CHECK (m.getBack () == Vector4 (0.0f, 0.0f, 1.0f, 0.0f));
  CHECK (m.getTranslation () == Vector4 (0.0f, 0.0f, 0.0f, 1.0f));
}

TEST_CASE ("Matrix4::Matrix4(const Vector4&, const Vector4&, const Vector4&, const Vector4&) copies the basis vectors", "[Matrix4]") {
  Vector4 right (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 up (-1.0f, 0.0f, 1.0f, 2.0f);
  Vector4 back (1.0f, 1.0f, 1.0f, 1.0f);
  Vector4 translation (0.0f, 1.0f, -1.0f, 0.0f);
  Matrix4 m(right, up, back, translation);
  CHECK (right == m.getRight ());
  CHECK (up == m.getUp ());
  CHECK (back == m.getBack ());
  CHECK (translation == m.getTranslation());
}

TEST_CASE ("Matrix4::setToZero() makes all elements 0", "[Matrix4]") {
  Matrix4 m;
  m.setToZero ();
  CHECK (m.getRight () == Vector4 (0.0f, 0.0f, 0.0f, 0.0f));
  CHECK (m.getUp () == Vector4 (0.0f, 0.0f, 0.0f, 0.0f));
  CHECK (m.getBack () == Vector4 (0.0f, 0.0f, 0.0f, 0.0f));
  CHECK (m.getTranslation () == Vector4 (0.0f, 0.0f, 0.0f, 0.0f));
}

TEST_CASE ("Matrix4::setToIdentity() reset to the identity matrix", "[Matrix4]") {
  Matrix4 m;
  m.setToZero ();
  m.setToIdentity ();
  CHECK (m.getRight () == Vector4 (1.0f, 0.0f, 0.0f, 0.0f));
  CHECK (m.getUp () == Vector4 (0.0f, 1.0f, 0.0f, 0.0f));
  CHECK (m.getBack () == Vector4 (0.0f, 0.0f, 1.0f, 0.0f));
  CHECK (m.getTranslation () == Vector4 (0.0f, 0.0f, 0.0f, 1.0f));  
}

TEST_CASE ("Matrix4::data() const returns pointer to x component of right", "[Matrix4]") {
  Matrix4 m;
  const float * p = m.data ();
  CHECK (Vector4 (*p, *(p+1), *(p+2), *(p+3)) == m.getRight ());
  CHECK (Vector4 (*(p+4), *(p+5), *(p+6), *(p+7)) == m.getUp ());
  CHECK (Vector4 (*(p+8), *(p+9), *(p+10), *(p+11)) == m.getBack ());
  CHECK (Vector4 (*(p+12), *(p+13), *(p+14), *(p+15)) == m.getTranslation ());
  m.setToZero ();
  CHECK (Vector4 (*p, *(p+1), *(p+2), *(p+3)) == m.getRight ());
  CHECK (Vector4 (*(p+4), *(p+5), *(p+6), *(p+7)) == m.getUp ());
  CHECK (Vector4 (*(p+8), *(p+9), *(p+10), *(p+11)) == m.getBack ());
  CHECK (Vector4 (*(p+12), *(p+13), *(p+14), *(p+15)) == m.getTranslation ());
  m.setToPerspectiveProjection (1.0f, 2.0f, 3.0f, 4.0f);
  CHECK (Vector4 (*p, *(p+1), *(p+2), *(p+3)) == m.getRight ());
  CHECK (Vector4 (*(p+4), *(p+5), *(p+6), *(p+7)) == m.getUp ());
  CHECK (Vector4 (*(p+8), *(p+9), *(p+10), *(p+11)) == m.getBack ());
  CHECK (Vector4 (*(p+12), *(p+13), *(p+14), *(p+15)) == m.getTranslation ());  
}

TEST_CASE ("Matrix4::setToPerspectiveProjection(float, float, float, float) matches slide", "[Matrix4]") {
  Matrix4 m;
  float fovYDegrees = 30.0f;
  float aspectRatio = 1.8f;
  float nearPlaneZ = -10.0f;
  float farPlaneZ = -40.0f;
  float fovYRadians = fovYDegrees * M_PI / 180.0f;
  m.setToPerspectiveProjection (fovYDegrees, aspectRatio, nearPlaneZ, farPlaneZ);

  CHECK (Vector4 (1.0f / (aspectRatio * tan (fovYRadians / 2.0f)), 0.0f, 0.0f, 0.0f) == m.getRight ());
  CHECK (Vector4 (0.0f, 1.0f / (tan (fovYRadians / 2.0f)), 0.0f, 0.0f) == m.getUp ());
  CHECK (Vector4 (0.0f, 0.0f, (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ), -1.0f) == m.getBack ());
  CHECK (Vector4 (0.0f, 0.0f, (2.0f * nearPlaneZ * farPlaneZ) / (nearPlaneZ - farPlaneZ), 0.0f) == m.getTranslation ());

  fovYDegrees = 50.0f;
  aspectRatio = 2.3f;
  nearPlaneZ = -1.0f;
  farPlaneZ = -5.0f;
  fovYRadians = fovYDegrees * M_PI / 180.0f;
  m.setToPerspectiveProjection (fovYDegrees, aspectRatio, nearPlaneZ, farPlaneZ);

  CHECK (Vector4 (1.0f / (aspectRatio * tan (fovYRadians / 2.0f)), 0.0f, 0.0f, 0.0f) == m.getRight ());
  CHECK (Vector4 (0.0f, 1.0f / (tan (fovYRadians / 2.0f)), 0.0f, 0.0f) == m.getUp ());
  CHECK (Vector4 (0.0f, 0.0f, (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ), -1.0f) == m.getBack ());
  CHECK (Vector4 (0.0f, 0.0f, (2.0f * nearPlaneZ * farPlaneZ) / (nearPlaneZ - farPlaneZ), 0.0f) == m.getTranslation ());  
}

TEST_CASE ("Matrix4::setToPerspective(float, float, float, float, float, float) matches slide", "[Matrix4]") {
  Matrix4 m;
  float left = -10.0f;
  float right = 5.0f;
  float bottom = -4.0f;
  float top = 10.0f;
  float nearPlaneZ = -10.0f;
  float farPlaneZ = -20.0f;
  m.setToPerspectiveProjection (left, right, bottom, top, nearPlaneZ, farPlaneZ);

  CHECK (Vector4 ((2.0f * nearPlaneZ) / (right - left), 0.0f, 0.0f, 0.0f) == m.getRight ());
  CHECK (Vector4 (0.0f, (2.0f * nearPlaneZ) / (top - bottom), 0.0f, 0.0f) == m.getUp ());
  CHECK (Vector4 ((right + left) / (right - left), (top + bottom) / (top - bottom), (farPlaneZ + nearPlaneZ) / (nearPlaneZ - farPlaneZ), -1.0f) == m.getBack ());
  CHECK (Vector4 (0.0f, 0.0f, (2.0f * nearPlaneZ * farPlaneZ) / (nearPlaneZ - farPlaneZ), 0.0f) == m.getTranslation ());

  left = -8.0f;
  right = 8.0f;
  bottom = -8.0f;
  top = 8.0f;
  nearPlaneZ = -8.0f;
  farPlaneZ = -16.0f;
  m.setToPerspectiveProjection (left, right, bottom, top, nearPlaneZ, farPlaneZ);

  CHECK (Vector4 ((2.0f * nearPlaneZ) / (right - left), 0.0f, 0.0f, 0.0f) == m.getRight ());
  CHECK (Vector4 (0.0f, (2.0f * nearPlaneZ) / (top - bottom), 0.0f, 0.0f) == m.getUp ());
  CHECK (Vector4 ((right + left) / (right - left), (top + bottom) / (top - bottom), (farPlaneZ + nearPlaneZ) / (nearPlaneZ - farPlaneZ), -1.0f) == m.getBack ());
  CHECK (Vector4 (0.0f, 0.0f, (2.0f * nearPlaneZ * farPlaneZ) / (nearPlaneZ - farPlaneZ), 0.0f) == m.getTranslation ());

}

TEST_CASE ("Matrix4::setToOrthographicProjection(float, float, float, float, float, float) matches slide", "[Matrix4]") {
  Matrix4 m;
  float left = -10.0f;
  float right = 5.0f;
  float bottom = -4.0f;
  float top = 10.0f;
  float nearPlaneZ = -10.0f;
  float farPlaneZ = -20.0f;
  m.setToOrthographicProjection (left, right, bottom, top, nearPlaneZ, farPlaneZ);

  CHECK (Vector4 (2.0f / (right - left), 0.0f, 0.0f, 0.0f) == m.getRight ());
  CHECK (Vector4 (0.0f, 2.0f / (top - bottom), 0.0f, 0.0f) == m.getUp ());
  CHECK (Vector4 (0.0f, 0.0f, 2.0f / (nearPlaneZ - farPlaneZ), 0.0f) == m.getBack ());
  CHECK (Vector4 (-1.0f * (right + left) / (right - left), -1.0f * (top + bottom) / (top - bottom), (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ), 1.0f) == m.getTranslation ());

  left = -8.0f;
  right = 8.0f;
  bottom = -8.0f;
  top = 8.0f;
  nearPlaneZ = -8.0f;
  farPlaneZ = -16.0f;
  m.setToOrthographicProjection (left, right, bottom, top, nearPlaneZ, farPlaneZ);

  CHECK (Vector4 (2.0f / (right - left), 0.0f, 0.0f, 0.0f) == m.getRight ());
  CHECK (Vector4 (0.0f, 2.0f / (top - bottom), 0.0f, 0.0f) == m.getUp ());
  CHECK (Vector4 (0.0f, 0.0f, 2.0f / (nearPlaneZ - farPlaneZ), 0.0f) == m.getBack ());
  CHECK (Vector4 (-1.0f * (right + left) / (right - left), -1.0f * (top + bottom) / (top - bottom), (nearPlaneZ + farPlaneZ) / (nearPlaneZ - farPlaneZ), 1.0f) == m.getTranslation ());
}

TEST_CASE ("operator== (Matrix4, Matrix4) function works", "[Matrix4]") {
  Matrix4 m1, m2, m3, m4;
  m1.setToOrthographicProjection (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
  m2.setToOrthographicProjection (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
  m3.setToPerspectiveProjection (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f);
  m4.setToPerspectiveProjection (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 0.0f);

  CHECK (m1 == m1);
  CHECK (m1 == m2);
  CHECK (!(m1 == m3));
  CHECK (!(m1 == m4));
  CHECK (m2 == m1);
  CHECK (m2 == m2);
  CHECK (!(m2 == m3));
  CHECK (!(m2 == m4));
  CHECK (!(m3 == m1));
  CHECK (!(m3 == m2));
  CHECK (m3 == m3);
  CHECK (!(m3 == m4));
  CHECK (!(m4 == m1));
  CHECK (!(m4 == m2));
  CHECK (!(m4 == m3));
  CHECK (m4 == m4);
}

/*
bool
operator== (const glm::mat4& m1, const glm::mat4& m2)
{
  const float EPSILON = 0.00001f;
  bool equal = true;
  int col = 0;
  while(col < 4 && equal) {
    int row = 0;
    while(row < 4 && equal) {
      if(fabs (m1[col][row] - m2[col][row]) > EPSILON) {
	equal = false;
      }
      row++;
    }
    col++;
  }
  return equal;
}
std::ostream&
operator<< (std::ostream& out, const glm::mat4& m)
{
  out << std::setprecision(5);
  for(int row = 0; row < 4; row++) {
    for(int col = 0; col < 4; col++) {
      out << std::setw(10) << m[col][row];
    }
    out << std::endl;
  }
  return out;
}
*/

TEST_CASE ("Matrix4::setToPerspectiveProjection (float, float, float, float) agrees with GLM", "[Matrix4]") {
  Matrix4 m;
  float fovYDegrees = 30.0f;
  float aspectRatio = 1.8f;
  float nearPlaneZ = -10.0f;
  float farPlaneZ = -40.0f;
  float fovYRadians = fovYDegrees * M_PI / 180.0f;
  m.setToPerspectiveProjection (fovYDegrees, aspectRatio, nearPlaneZ, farPlaneZ);
  const float* d = m.data ();
  glm::mat4 mine (*d, *(d+1), *(d+2), *(d+3), *(d+4), *(d+5), *(d+6), *(d+7), *(d+8), *(d+9), *(d+10), *(d+11), *(d+12), *(d+13), *(d+14), *(d+15));
  glm::mat4 real = glm::perspective(fovYRadians, aspectRatio, nearPlaneZ, farPlaneZ);
  CHECK (real == mine);
}

TEST_CASE ("Matrix4::setToPerspectiveProjection (float, float, float, float, float, float) agrees with GLM", "[Matrix4]") {
  Matrix4 m;
  float left = -10.0f;
  float right = 5.0f;
  float bottom = -4.0f;
  float top = 10.0f;
  float nearPlaneZ = -10.0f;
  float farPlaneZ = -20.0f;
  m.setToPerspectiveProjection (left, right, bottom, top, nearPlaneZ, farPlaneZ);

  const float* d = m.data ();
  glm::mat4 mine (*d, *(d+1), *(d+2), *(d+3), *(d+4), *(d+5), *(d+6), *(d+7), *(d+8), *(d+9), *(d+10), *(d+11), *(d+12), *(d+13), *(d+14), *(d+15));
  glm::mat4 real = glm::frustum(left, right, bottom, top, nearPlaneZ, farPlaneZ);
  CHECK (real == mine);
}

TEST_CASE ("Matrix4::setToOrthographicProjection (float, float, float, float, float, float) agrees with GLM", "[Matrix4]") {
  Matrix4 m;
  float left = -10.0f;
  float right = 5.0f;
  float bottom = -4.0f;
  float top = 10.0f;
  float nearPlaneZ = -10.0f;
  float farPlaneZ = -20.0f;
  m.setToOrthographicProjection (left, right, bottom, top, nearPlaneZ, farPlaneZ);

  const float* d = m.data ();
  glm::mat4 mine (*d, *(d+1), *(d+2), *(d+3), *(d+4), *(d+5), *(d+6), *(d+7), *(d+8), *(d+9), *(d+10), *(d+11), *(d+12), *(d+13), *(d+14), *(d+15));
  glm::mat4 real = glm::ortho(left, right, bottom, top, nearPlaneZ, farPlaneZ);
  CHECK (real == mine);
}
