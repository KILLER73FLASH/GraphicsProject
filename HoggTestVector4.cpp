/*
  Filename: CatchTestVector4.cpp
  Author: Chad Hogg
  Course: CSCI375
  Assignment: A07Projection
  Description: Catch2 test cases for the Vector4 class.
*/

#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include "Vector4.h"

TEST_CASE ("Vector4() sets all components to 0", "[Vector4]") {
  Vector4 v;
  CHECK (v.x == Approx (0.0f));
  CHECK (v.y == Approx (0.0f));
  CHECK (v.z == Approx (0.0f));
  CHECK (v.w == Approx (0.0f));
}

TEST_CASE ("Vector4(float) copies parameter to all components", "[Vector4]") {
  Vector4 v1(12.8f);
  Vector4 v2(-3.7f);
  CHECK (v1.x == Approx (12.8f));
  CHECK (v1.y == Approx (12.8f));
  CHECK (v1.z == Approx (12.8f));
  CHECK (v1.w == Approx (12.8f));
  CHECK (v2.x == Approx (-3.7f));
  CHECK (v2.y == Approx (-3.7f));
  CHECK (v2.z == Approx (-3.7f));
  CHECK (v2.w == Approx (-3.7f));
}

TEST_CASE ("Vector4(float, float, float, float) copies parameters appropriately", "[Vector4]") {
  Vector4 v1(1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v2(-0.1f, -0.2f, 0.7f, -2.0f);
  CHECK (v1.x == Approx (1.0f));
  CHECK (v1.y == Approx (2.0f));
  CHECK (v1.z == Approx (3.0f));
  CHECK (v1.w == Approx (4.0f));
  CHECK (v2.x == Approx (-0.1f));
  CHECK (v2.y == Approx (-0.2f));
  CHECK (v2.z == Approx (0.7f));
  CHECK (v2.w == Approx (-2.0f));
}

TEST_CASE ("Vector4::data() const returns pointer to x component", "[Vector4]") {
  Vector4 v1(1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v2(-0.1f, -0.2f, 0.7f, -2.0f);
  CHECK (1.0f == Approx (*v1.data ()));
  CHECK (&v1.x == v1.data());
  CHECK (-0.1f == Approx (*v2.data ()));
  CHECK (&v2.x == v2.data());
}

TEST_CASE ("Vector4::set(float) copies parameter to all components", "[Vector4]") {
  Vector4 v1;
  Vector4 v2 (1.0f, 2.0f, 3.0f, 4.0f);
  v1.set (5.0f);
  v2.set (-2.4f);
  CHECK (v1.x == Approx (5.0f));
  CHECK (v1.y == Approx (5.0f));
  CHECK (v1.z == Approx (5.0f));
  CHECK (v1.w == Approx (5.0f));
  CHECK (v2.x == Approx (-2.4f));
  CHECK (v2.y == Approx (-2.4f));
  CHECK (v2.z == Approx (-2.4f));
  CHECK (v2.w == Approx (-2.4f));
}

TEST_CASE ("Vector4::set(float, float, float, float) copies parameters appropriately", "[Vector4]") {
  Vector4 v1;
  Vector4 v2 (1.0f, 2.0f, 3.0f, 4.0f);
  v1.set (0.0f, -2.0f, 0.01f, 0.0f);
  v2.set (3.0f, 3.0f, 3.1f, 1.0f);
  CHECK (v1.x == Approx (0.0f));
  CHECK (v1.y == Approx (-2.0f));
  CHECK (v1.z == Approx (0.01f));
  CHECK (v1.w == Approx (0.0f));
  CHECK (v2.x == Approx (3.0f));
  CHECK (v2.y == Approx (3.0f));
  CHECK (v2.z == Approx (3.1f));
  CHECK (v2.w == Approx (1.0f));
}

TEST_CASE ("Vector4::dot() const computes dot products correctly", "[Vector4]") {
  Vector4 v1 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v2 (4.0f, -5.0f, 6.0f, -7.0f);
  Vector4 v3 (6.0f, -1.0f, 3.0f, -0.5f);
  Vector4 v4 (4.0f, 18.0f, -2.0f, 0.0f);
  float dot12 = v1.dot (v2);
  float dot21 = v2.dot (v1);
  float dot34 = v3.dot (v4);
  float dot43 = v4.dot (v3);
  CHECK (dot12 == Approx (-16.0f));
  CHECK (dot21 == Approx (-16.0f));
  CHECK (dot34 == Approx (0.0f));
  CHECK (dot43 == Approx (0.0f));
}

TEST_CASE ("Vector4::length() works", "[Vector4]") {
  Vector4 v1 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v2 (0.0f, 0.0f, 0.0f, 0.0f);
  float length1 = v1.length ();
  float length2 = v2.length ();
  CHECK (length1 == Approx (sqrt (30.0f)));
  CHECK (length2 == Approx (0.0f));
}

TEST_CASE ("Vector4::normalize() works", "[Vector4]") {
  Vector4 v1 (0.0f, 0.0f, 3.0f, 4.0f);
  Vector4 v2 (1.0f, 2.0f, 0.0f, -2.0f);
  v1.normalize ();
  v2.normalize ();
  CHECK (v1.x == Approx (0.0f));
  CHECK (v1.y == Approx (0.0f));
  CHECK (v1.z == Approx (3.0f / 5.0f));
  CHECK (v1.w == Approx (4.0f / 5.0f));
  CHECK (v2.x == Approx (1.0f / 3.0f));
  CHECK (v2.y == Approx (2.0f / 3.0f));
  CHECK (v2.z == Approx (0.0f));
  CHECK (v2.w == Approx (-2.0f / 3.0f));
}

TEST_CASE ("Vector4::negate() negates each component", "[Vector4]") {
  Vector4 v1 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v2 (-0.0001f, 1000.0f, 2.1f, 0.0f);
  v1.negate ();
  v2.negate ();
  CHECK (v1.x == Approx (-1.0f));
  CHECK (v1.y == Approx (-2.0f));
  CHECK (v1.z == Approx (-3.0f));
  CHECK (v1.w == Approx (-4.0f));
  CHECK (v2.x == Approx (0.0001f));
  CHECK (v2.y == Approx (-1000.0f));
  CHECK (v2.z == Approx (-2.1f));
  CHECK (v2.w == Approx (-0.0f));
}

TEST_CASE ("Vector4::operator+=(const Vector4&) works", "[Vector4]") {
  Vector4 v1 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v2 (-2.1f, -8.3f, 1.0f, 0.0f);
  Vector4 v3 (0.0f, -1.0f, 1.0f, 2.0f);
  Vector4 v4 (0.0f, -1.0f, 1.0f, 2.0f);
  v1 += v2;
  v3 += v4;
  CHECK (v1.x == Approx (-1.1f));
  CHECK (v1.y == Approx (-6.3f));
  CHECK (v1.z == Approx (4.0f));
  CHECK (v1.w == Approx (4.0f));
  CHECK (v3.x == Approx (0.0f));
  CHECK (v3.y == Approx (-2.0f));
  CHECK (v3.z == Approx (2.0f));
  CHECK (v3.w == Approx (4.0f));
}

TEST_CASE ("Vector4::operator-=(const Vector4&) works", "[Vector4]") {
  Vector4 v1 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v2 (-2.1f, -8.3f, 1.0f, 0.0f);
  Vector4 v3 (0.0f, -1.0f, 1.0f, 2.0f);
  Vector4 v4 (0.0f, -1.0f, 1.0f, 2.0f);
  v1 -= v2;
  v3 -= v4;
  CHECK (v1.x == Approx (3.1f));
  CHECK (v1.y == Approx (10.3f));
  CHECK (v1.z == Approx (2.0f));
  CHECK (v1.w == Approx (4.0f));
  CHECK (v3.x == Approx (0.0f));
  CHECK (v3.y == Approx (0.0f));
  CHECK (v3.z == Approx (0.0f));
  CHECK (v3.w == Approx (0.0f));
}

TEST_CASE ("Vector4::operator*=(const Vector4&) works", "[Vector4]") {
  Vector4 v1 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v2 (-2.1f, -8.3f, 1.0f, 0.0f);
  Vector4 v3 (0.0f, -1.0f, 1.0f, 2.0f);
  Vector4 v4 (0.0f, -1.0f, 1.0f, 2.0f);
  v1 *= v2;
  v3 *= v4;
  CHECK (v1.x == Approx (-2.1f));
  CHECK (v1.y == Approx (-16.6f));
  CHECK (v1.z == Approx (3.0f));
  CHECK (v1.w == Approx (0.0f));
  CHECK (v3.x == Approx (0.0f));
  CHECK (v3.y == Approx (1.0f));
  CHECK (v3.z == Approx (1.0f));
  CHECK (v3.w == Approx (4.0f));
}

TEST_CASE ("Vector4::operator*=(float) works", "[Vector4]") {
  Vector4 v1 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v3 (0.0f, -1.0f, 1.0f, 2.0f);
  v1 *= 2.5;
  v3 *= -1.2;
  CHECK (v1.x == Approx (2.5f));
  CHECK (v1.y == Approx (5.0f));
  CHECK (v1.z == Approx (7.5f));
  CHECK (v1.w == Approx (10.0f));
  CHECK (v3.x == Approx (0.0f));
  CHECK (v3.y == Approx (1.2f));
  CHECK (v3.z == Approx (-1.2f));
  CHECK (v3.w == Approx (-2.4f));
}

TEST_CASE ("Vector4::operator/=(float) works", "[Vector4]") {
  Vector4 v1 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v3 (0.0f, -1.0f, 1.0f, 2.0f);
  v1 /= 0.5;
  v3 /= -4.0;
  CHECK (v1.x == Approx (2.0f));
  CHECK (v1.y == Approx (4.0f));
  CHECK (v1.z == Approx (6.0f));
  CHECK (v1.w == Approx (8.0f));
  CHECK (v3.x == Approx (0.0f));
  CHECK (v3.y == Approx (0.25f));
  CHECK (v3.z == Approx (-0.25f));
  CHECK (v3.w == Approx (-0.5f));
}

TEST_CASE ("operator+(const Vector4&, const Vector4&) works", "[Vector4]") {
  Vector4 v1 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v2 (-1.0f, 0.0f, 1.0f, 2.0f);
  Vector4 v3 (1.1f, 2.2f, 3.3f, 4.4f);
  Vector4 v4 (-0.1f, 0.2f, -4.0f, 3.3f);
  Vector4 v12 = v1 + v2;
  Vector4 v21 = v2 + v1;
  Vector4 v34 = v3 + v4;
  Vector4 v43 = v4 + v3;
  CHECK (v12.x == Approx (0.0f));
  CHECK (v12.y == Approx (2.0f));
  CHECK (v12.z == Approx (4.0f));
  CHECK (v12.w == Approx (6.0f));
  CHECK (v21.x == Approx (0.0f));
  CHECK (v21.y == Approx (2.0f));
  CHECK (v21.z == Approx (4.0f));
  CHECK (v21.w == Approx (6.0f));
  CHECK (v34.x == Approx (1.0f));
  CHECK (v34.y == Approx (2.4f));
  CHECK (v34.z == Approx (-0.7f));
  CHECK (v34.w == Approx (7.7f));
  CHECK (v43.x == Approx (1.0f));
  CHECK (v43.y == Approx (2.4f));
  CHECK (v43.z == Approx (-0.7f));
  CHECK (v43.w == Approx (7.7f));
}

TEST_CASE ("operator-(const Vector4&, const Vector4&) works", "[Vector4]") {
  Vector4 v1 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v2 (-1.0f, 0.0f, 1.0f, 2.0f);
  Vector4 v3 (1.1f, 2.2f, 3.3f, 4.4f);
  Vector4 v4 (-0.1f, 0.2f, -4.0f, 3.3f);
  Vector4 v12 = v1 - v2;
  Vector4 v21 = v2 - v1;
  Vector4 v34 = v3 - v4;
  Vector4 v43 = v4 - v3;
  CHECK (v12.x == Approx (2.0f));
  CHECK (v12.y == Approx (2.0f));
  CHECK (v12.z == Approx (2.0f));
  CHECK (v12.w == Approx (2.0f));
  CHECK (v21.x == Approx (-2.0f));
  CHECK (v21.y == Approx (-2.0f));
  CHECK (v21.z == Approx (-2.0f));
  CHECK (v21.w == Approx (-2.0f));
  CHECK (v34.x == Approx (1.2f));
  CHECK (v34.y == Approx (2.0f));
  CHECK (v34.z == Approx (7.3f));
  CHECK (v34.w == Approx (1.1f));
  CHECK (v43.x == Approx (-1.2f));
  CHECK (v43.y == Approx (-2.0f));
  CHECK (v43.z == Approx (-7.3f));
  CHECK (v43.w == Approx (-1.1f));
}

TEST_CASE ("operator-(const Vector4&) works", "[Vector4]") {
  Vector4 v1 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v3 (1.1f, -2.2f, 0.0f, 1.0f);
  Vector4 v1m = -v1;
  Vector4 v3m = -v3;
  CHECK (v1m.x == Approx (-1.0f));
  CHECK (v1m.y == Approx (-2.0f));
  CHECK (v1m.z == Approx (-3.0f));
  CHECK (v1m.w == Approx (-4.0f));
  CHECK (v3m.x == Approx (-1.1f));
  CHECK (v3m.y == Approx (2.2f));
  CHECK (v3m.z == Approx (0.0f));
  CHECK (v3m.w == Approx (-1.0f));
}

TEST_CASE ("operator*(const Vector4&, const Vector4&) works", "[Vector4]") {
  Vector4 v1 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v2 (-1.0f, 0.0f, 1.0f, 2.0f);
  Vector4 v3 (1.1f, 2.2f, 3.3f, 4.4f);
  Vector4 v4 (-0.1f, 0.2f, -4.0f, 3.3f);
  Vector4 v12 = v1 * v2;
  Vector4 v21 = v2 * v1;
  Vector4 v34 = v3 * v4;
  Vector4 v43 = v4 * v3;
  CHECK (v12.x == Approx (-1.0f));
  CHECK (v12.y == Approx (0.0f));
  CHECK (v12.z == Approx (3.0f));
  CHECK (v12.w == Approx (8.0f));
  CHECK (v21.x == Approx (-1.0f));
  CHECK (v21.y == Approx (0.0f));
  CHECK (v21.z == Approx (3.0f));
  CHECK (v21.w == Approx (8.0f));
  CHECK (v34.x == Approx (-0.11f));
  CHECK (v34.y == Approx (0.44f));
  CHECK (v34.z == Approx (-13.2f));
  CHECK (v34.w == Approx (14.52f));
  CHECK (v43.x == Approx (-0.11f));
  CHECK (v43.y == Approx (0.44f));
  CHECK (v43.z == Approx (-13.2f));
  CHECK (v43.w == Approx (14.52f));
}

TEST_CASE ("operator*(const Vector4&, float) and operator*(float, const Vector4&) functions work", "[Vector4]") {
  Vector4 v1 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v2 (0.0f, -2.0f, 4.0f, 2.0f);
  Vector4 v1b = v1 * 2.5f;
  Vector4 v1a = 2.5f * v1;
  Vector4 v2b = v2 * -2.0f;
  Vector4 v2a = -2.0f * v2;
  CHECK (v1b.x == Approx (2.5f));
  CHECK (v1b.y == Approx (5.0f));
  CHECK (v1b.z == Approx (7.5f));
  CHECK (v1b.w == Approx (10.0f));
  CHECK (v1a.x == Approx (2.5f));
  CHECK (v1a.y == Approx (5.0f));
  CHECK (v1a.z == Approx (7.5f));
  CHECK (v1a.w == Approx (10.0f));
  CHECK (v2b.x == Approx (0.0f));
  CHECK (v2b.y == Approx (4.0f));
  CHECK (v2b.z == Approx (-8.0f));
  CHECK (v2b.w == Approx (-4.0f));
  CHECK (v2a.x == Approx (0.0f));
  CHECK (v2a.y == Approx (4.0f));
  CHECK (v2a.z == Approx (-8.0f));
  CHECK (v2a.w == Approx (-4.0f));
}

TEST_CASE ("operator/(const Vector4, float) function works", "[Vector4]") {
  Vector4 v1 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v2 (0.0f, -2.0f, 4.0f, 2.0f);
  Vector4 v1d = v1 / 2.0f;
  Vector4 v2d = v2 / -2.0f;
  CHECK (v1d.x == Approx (0.5f));
  CHECK (v1d.y == Approx (1.0f));
  CHECK (v1d.z == Approx (1.5f));
  CHECK (v1d.w == Approx (2.0f));
  CHECK (v2d.x == Approx (0.0f));
  CHECK (v2d.y == Approx (1.0f));
  CHECK (v2d.z == Approx (-2.0f));
  CHECK (v2d.w == Approx (-1.0f));
}

TEST_CASE ("operator== (Vector4, Vector4) function works", "[Vector4]") {
  Vector4 v1 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v2 (1.0f, 2.0f, 3.0f, 4.0f);
  Vector4 v3 (0.999999f, 2.0f, 3.0f, 4.0f);
  Vector4 v4 (1.0f, 2.1f, 3.0f, 4.0f);
  CHECK (v1 == v1);
  CHECK (v1 == v2);
  CHECK (v2 == v1);
  CHECK (v1 == v3);
  CHECK (v3 == v1);
  CHECK (! (v1 == v4));
  CHECK (! (v4 == v2));
}
