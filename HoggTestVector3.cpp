/*
  Filename: CatchTestVector3.cpp
  Author: Chad Hogg
  Course: CSCI375
  Assignment: A06Transform
  Description: Catch2 test cases for the Vector3 class.
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Vector3.h"

TEST_CASE ("Vector3 default construtor sets all components to 0", "[Vector3]") {
  Vector3 v;
  CHECK (v.xVal == Approx (0.0f));
  CHECK (v.yVal == Approx (0.0f));
  CHECK (v.zVal == Approx (0.0f));
}

TEST_CASE ("Vector3 one-argument constructor copies parameter to all components", "[Vector3]") {
  Vector3 v1(12.8f);
  Vector3 v2(-3.7f);
  CHECK (v1.xVal == Approx (12.8f));
  CHECK (v1.yVal == Approx (12.8f));
  CHECK (v1.zVal == Approx (12.8f));
  CHECK (v2.xVal == Approx (-3.7f));
  CHECK (v2.yVal == Approx (-3.7f));
  CHECK (v2.zVal == Approx (-3.7f));
}

TEST_CASE ("Vector3 three-argument constructor copies parameters appropriately", "[Vector3]") {
  Vector3 v1(1.0f, 2.0f, 3.0f);
  Vector3 v2(-0.1f, -0.2f, 0.7f);
  CHECK (v1.xVal == Approx (1.0f));
  CHECK (v1.yVal == Approx (2.0f));
  CHECK (v1.zVal == Approx (3.0f));
  CHECK (v2.xVal == Approx (-0.1f));
  CHECK (v2.yVal == Approx (-0.2f));
  CHECK (v2.zVal == Approx (0.7f));
}

TEST_CASE ("Vector3 one-argument set function copies parameter to all components", "[Vector3]") {
  Vector3 v1;
  Vector3 v2 (1.0f, 2.0f, 3.0f);
  v1.set (4.0f);
  v2.set (-2.4f);
  CHECK (v1.xVal == Approx (4.0f));
  CHECK (v1.yVal == Approx (4.0f));
  CHECK (v1.zVal == Approx (4.0f));
  CHECK (v2.xVal == Approx (-2.4f));
  CHECK (v2.yVal == Approx (-2.4f));
  CHECK (v2.zVal == Approx (-2.4f));
}

TEST_CASE ("Vector3 three-argument set function copies parameters appropriately", "[Vector3]") {
  Vector3 v1;
  Vector3 v2 (1.0f, 2.0f, 3.0f);
  v1.set (0.0f, -2.0f, 0.01f);
  v2.set (3.0f, 3.0f, 3.1f);
  CHECK (v1.xVal == Approx (0.0f));
  CHECK (v1.yVal == Approx (-2.0f));
  CHECK (v1.zVal == Approx (0.01f));
  CHECK (v2.xVal == Approx (3.0f));
  CHECK (v2.yVal == Approx (3.0f));
  CHECK (v2.zVal == Approx (3.1f));
}

TEST_CASE ("Vector3 negate function negates each component", "[Vector3]") {
  Vector3 v1 (1.0f, 2.0f, 3.0f);
  Vector3 v2 (-0.0001f, 1000.0f, 2.1f);
  v1.negate ();
  v2.negate ();
  CHECK (v1.xVal == Approx (-1.0f));
  CHECK (v1.yVal == Approx (-2.0f));
  CHECK (v1.zVal == Approx (-3.0f));
  CHECK (v2.xVal == Approx (0.0001f));
  CHECK (v2.yVal == Approx (-1000.0f));
  CHECK (v2.zVal == Approx (-2.1f));
}

TEST_CASE ("Vector3 dot function computes dot products correctly", "[Vector3]") {
  Vector3 v1 (1.0f, 2.0f, 3.0f);
  Vector3 v2 (4.0f, -5.0f, 6.0f);
  Vector3 v3 (6.0f, -1.0f, 3.0f);
  Vector3 v4 (4.0f, 18.0f, -2.0f);
  float dot12 = v1.dot (v2);
  float dot21 = v2.dot (v1);
  float dot34 = v3.dot (v4);
  float dot43 = v4.dot (v3);
  CHECK (dot12 == Approx (12.0f));
  CHECK (dot21 == Approx (12.0f));
  CHECK (dot34 == Approx (0.0f));
  CHECK (dot43 == Approx (0.0f));
}

TEST_CASE ("Vector3 angleBetween function works", "[Vector3]") {
  Vector3 v1 (1.0f, 0.0f, 0.0f);
  Vector3 v2 (0.0f, 1.0f, 0.0f);
  Vector3 v3 (1.0f, 0.0f, 0.0f);
  Vector3 v4 (2.0f, 0.0f, 0.0f);
  float angle12 = v1.angleBetween (v2);
  float angle21 = v2.angleBetween (v1);
  float angle34 = v3.angleBetween (v4);
  float angle43 = v4.angleBetween (v3);
  float angle11 = v1.angleBetween (v1);
  CHECK (angle12 == Approx (M_PI / 2.0f));
  CHECK (angle21 == Approx (M_PI / 2.0f));
  CHECK (angle34 == Approx (0.0f));
  CHECK (angle43 == Approx (0.0f));
  CHECK (angle11 == Approx (0.0f));
}

TEST_CASE ("Vector3 cross function works", "[Vector3]") {
  Vector3 v1 (1.0f, 0.0f, 0.0f);
  Vector3 v2 (0.0f, 1.0f, 0.0f);
  Vector3 v3 (3.0f, -3.0f, 1.0f);
  Vector3 v4 (4.0f, 9.0f, 2.0f);
  Vector3 cross12 = v1.cross (v2);
  Vector3 cross21 = v2.cross (v1);
  Vector3 cross34 = v3.cross (v4);
  Vector3 cross43 = v4.cross (v3);
  Vector3 cross11 = v1.cross (v1);
  CHECK (cross12.xVal == Approx (0.0f));
  CHECK (cross12.yVal == Approx (0.0f));
  CHECK (cross12.zVal == Approx (1.0f));
  CHECK (cross21.xVal == Approx (0.0f));
  CHECK (cross21.yVal == Approx (0.0f));
  CHECK (cross21.zVal == Approx (-1.0f));
  CHECK (cross34.xVal == Approx (-15.0f));
  CHECK (cross34.yVal == Approx (-2.0f));
  CHECK (cross34.zVal == Approx (39.0f));
  CHECK (cross43.xVal == Approx (15.0f));
  CHECK (cross43.yVal == Approx (2.0f));
  CHECK (cross43.zVal == Approx (-39.0f));
  CHECK (cross11.xVal == Approx (0.0f));
  CHECK (cross11.yVal == Approx (0.0f));
  CHECK (cross11.zVal == Approx (0.0f));
}

TEST_CASE ("Vector3 length function works", "[Vector3]") {
  Vector3 v1 (1.0f, 2.0f, 3.0f);
  Vector3 v2 (0.0f, 0.0f, 0.0f);
  float length1 = v1.length ();
  float length2 = v2.length ();
  CHECK (length1 == Approx (sqrt (14.0f)));
  CHECK (length2 == Approx (0.0f));
}

TEST_CASE ("Vector3 normalize function works", "[Vector3]") {
  Vector3 v1 (0.0f, 4.0f, 3.0f);
  Vector3 v2 (1.0f, 2.0f, -2.0f);
  v1.normalize ();
  v2.normalize ();
  CHECK (v1.xVal == Approx (0.0f));
  CHECK (v1.yVal == Approx (4.0f / 5.0f));
  CHECK (v1.zVal == Approx (3.0f / 5.0f));
  CHECK (v2.xVal == Approx (1.0f / 3.0f));
  CHECK (v2.yVal == Approx (2.0f / 3.0f));
  CHECK (v2.zVal == Approx (-2.0f / 3.0f));
}

TEST_CASE ("Vector3 operator+= function works", "[Vector3]") {
  Vector3 v1 (1.0f, 2.0f, 3.0f);
  Vector3 v2 (-2.1f, -8.3f, 1.0f);
  Vector3 v3 (0.0f, -1.0f, 1.0f);
  Vector3 v4 (0.0f, -1.0f, 1.0f);
  v1 += v2;
  v3 += v4;
  CHECK (v1.xVal == Approx (-1.1f));
  CHECK (v1.yVal == Approx (-6.3f));
  CHECK (v1.zVal == Approx (4.0f));
  CHECK (v3.xVal == Approx (0.0f));
  CHECK (v3.yVal == Approx (-2.0f));
  CHECK (v3.zVal == Approx (2.0f));
}

TEST_CASE ("Vector3 operator-= function works", "[Vector3]") {
  Vector3 v1 (1.0f, 2.0f, 3.0f);
  Vector3 v2 (-2.1f, -8.3f, 1.0f);
  Vector3 v3 (0.0f, -1.0f, 1.0f);
  Vector3 v4 (0.0f, -1.0f, 1.0f);
  v1 -= v2;
  v3 -= v4;
  CHECK (v1.xVal == Approx (3.1f));
  CHECK (v1.yVal == Approx (10.3f));
  CHECK (v1.zVal == Approx (2.0f));
  CHECK (v3.xVal == Approx (0.0f));
  CHECK (v3.yVal == Approx (0.0f));
  CHECK (v3.zVal == Approx (0.0f));
}

TEST_CASE ("Vector3 operator*= function works", "[Vector3]") {
  Vector3 v1 (1.0f, 2.0f, 3.0f);
  Vector3 v3 (0.0f, -1.0f, 1.0f);
  v1 *= 2.5;
  v3 *= -1.2;
  CHECK (v1.xVal == Approx (2.5f));
  CHECK (v1.yVal == Approx (5.0f));
  CHECK (v1.zVal == Approx (7.5f));
  CHECK (v3.xVal == Approx (0.0f));
  CHECK (v3.yVal == Approx (1.2f));
  CHECK (v3.zVal == Approx (-1.2f));
}

TEST_CASE ("Vector3 operator/= function works", "[Vector3]") {
  Vector3 v1 (1.0f, 2.0f, 3.0f);
  Vector3 v3 (0.0f, -1.0f, 1.0f);
  v1 /= 0.5;
  v3 /= -4.0;
  CHECK (v1.xVal == Approx (2.0f));
  CHECK (v1.yVal == Approx (4.0f));
  CHECK (v1.zVal == Approx (6.0f));
  CHECK (v3.xVal == Approx (0.0f));
  CHECK (v3.yVal == Approx (0.25f));
  CHECK (v3.zVal == Approx (-0.25f));
}

TEST_CASE ("operator+(Vector3, Vector3) function works", "[Vector3]") {
  Vector3 v1 (1.0f, 2.0f, 3.0f);
  Vector3 v2 (-1.0f, 0.0f, 1.0f);
  Vector3 v3 (1.1f, 2.2f, 3.3f);
  Vector3 v4 (-0.1f, 0.2f, -4.0f);
  Vector3 v12 = v1 + v2;
  Vector3 v21 = v2 + v1;
  Vector3 v34 = v3 + v4;
  Vector3 v43 = v4 + v3;
  CHECK (v12.xVal == Approx (0.0f));
  CHECK (v12.yVal == Approx (2.0f));
  CHECK (v12.zVal == Approx (4.0f));
  CHECK (v21.xVal == Approx (0.0f));
  CHECK (v21.yVal == Approx (2.0f));
  CHECK (v21.zVal == Approx (4.0f));
  CHECK (v34.xVal == Approx (1.0f));
  CHECK (v34.yVal == Approx (2.4f));
  CHECK (v34.zVal == Approx (-0.7f));
  CHECK (v43.xVal == Approx (1.0f));
  CHECK (v43.yVal == Approx (2.4f));
  CHECK (v43.zVal == Approx (-0.7f));
}

TEST_CASE ("operator-(Vector3, Vector3) function works", "[Vector3]") {
  Vector3 v1 (1.0f, 2.0f, 3.0f);
  Vector3 v2 (-1.0f, 0.0f, 1.0f);
  Vector3 v3 (1.1f, 2.2f, 3.3f);
  Vector3 v4 (-0.1f, 0.2f, -4.0f);
  Vector3 v12 = v1 - v2;
  Vector3 v21 = v2 - v1;
  Vector3 v34 = v3 - v4;
  Vector3 v43 = v4 - v3;
  CHECK (v12.xVal == Approx (2.0f));
  CHECK (v12.yVal == Approx (2.0f));
  CHECK (v12.zVal == Approx (2.0f));
  CHECK (v21.xVal == Approx (-2.0f));
  CHECK (v21.yVal == Approx (-2.0f));
  CHECK (v21.zVal == Approx (-2.0f));
  CHECK (v34.xVal == Approx (1.2f));
  CHECK (v34.yVal == Approx (2.0f));
  CHECK (v34.zVal == Approx (7.3f));
  CHECK (v43.xVal == Approx (-1.2f));
  CHECK (v43.yVal == Approx (-2.0f));
  CHECK (v43.zVal == Approx (-7.3f));
}

TEST_CASE ("operator-(Vector3) function works", "[Vector3]") {
  Vector3 v1 (1.0f, 2.0f, 3.0f);
  Vector3 v3 (1.1f, -2.2f, 0.0f);
  Vector3 v1m = -v1;
  Vector3 v3m = -v3;
  CHECK (v1m.xVal == Approx (-1.0f));
  CHECK (v1m.yVal == Approx (-2.0f));
  CHECK (v1m.zVal == Approx (-3.0f));
  CHECK (v3m.xVal == Approx (-1.1f));
  CHECK (v3m.yVal == Approx (2.2f));
  CHECK (v3m.zVal == Approx (0.0f));
}

TEST_CASE ("operator*(Vector3, float) and operator*(float, Vector3) functions work", "[Vector3]") {
  Vector3 v1 (1.0f, 2.0f, 3.0f);
  Vector3 v2 (0.0f, -2.0f, 4.0f);
  Vector3 v1b = v1 * 2.5f;
  Vector3 v1a = 2.5f * v1;
  Vector3 v2b = v2 * -2.0f;
  Vector3 v2a = -2.0f * v2;
  CHECK (v1b.xVal == Approx (2.5f));
  CHECK (v1b.yVal == Approx (5.0f));
  CHECK (v1b.zVal == Approx (7.5f));
  CHECK (v1a.xVal == Approx (2.5f));
  CHECK (v1a.yVal == Approx (5.0f));
  CHECK (v1a.zVal == Approx (7.5f));
  CHECK (v2b.xVal == Approx (0.0f));
  CHECK (v2b.yVal == Approx (4.0f));
  CHECK (v2b.zVal == Approx (-8.0f));
  CHECK (v2a.xVal == Approx (0.0f));
  CHECK (v2a.yVal == Approx (4.0f));
  CHECK (v2a.zVal == Approx (-8.0f));
}

TEST_CASE ("operator/(Vector3, float) function works", "[Vector3]") {
  Vector3 v1 (1.0f, 2.0f, 3.0f);
  Vector3 v2 (0.0f, -2.0f, 4.0f);
  Vector3 v1d = v1 / 2.0f;
  Vector3 v2d = v2 / -2.0f;
  CHECK (v1d.xVal == Approx (0.5f));
  CHECK (v1d.yVal == Approx (1.0f));
  CHECK (v1d.zVal == Approx (1.5f));
  CHECK (v2d.xVal == Approx (0.0f));
  CHECK (v2d.yVal == Approx (1.0f));
  CHECK (v2d.zVal == Approx (-2.0f));
}

TEST_CASE ("operator== (Vector3, Vector3) function works", "[Vector3]") {
  Vector3 v1 (1.0f, 2.0f, 3.0f);
  Vector3 v2 (1.0f, 2.0f, 3.0f);
  Vector3 v3 (0.999999f, 2.0f, 3.0f);
  Vector3 v4 (1.0f, 2.1f, 3.0f);
  CHECK (v1 == v1);
  CHECK (v1 == v2);
  CHECK (v2 == v1);
  CHECK (v1 == v3);
  CHECK (v3 == v1);
  CHECK (! (v1 == v4));
  CHECK (! (v4 == v2));
}
