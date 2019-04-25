
/*
  Filename: CatchTestVector3.cpp
  Author: Chad Hogg
  Course: CSCI375
  Assignment: A04CameraRedux
  Description: Catch2 test cases for the Vector3 class.
*/

#include <catch.hpp>
#include "Vector3.h"

TEST_CASE ("Vector3 default construtor sets all components to 0", "[Vector3]") {
  Vector3 v;
  CHECK (v.x == Approx (0.0f));
  CHECK (v.y == Approx (0.0f));
  CHECK (v.z == Approx (0.0f));
}

TEST_CASE ("Vector3 one-argument constructor copies parameter to all components", "[Vector3]") {
  Vector3 v1(12.8f);
  Vector3 v2(-3.7f);
  CHECK (v1.x == Approx (12.8f));
  CHECK (v1.y == Approx (12.8f));
  CHECK (v1.z == Approx (12.8f));
  CHECK (v2.x == Approx (-3.7f));
  CHECK (v2.y == Approx (-3.7f));
  CHECK (v2.y == Approx (-3.7f));
}

TEST_CASE ("Vector3 three-argument constructor copies parameters appropriately", "[Vector3]") {
  Vector3 v1(1.0f, 2.0f, 3.0f);
  Vector3 v2(-0.1f, -0.2f, 0.7f);
  CHECK (v1.x == Approx (1.0f));
  CHECK (v1.y == Approx (2.0f));
  CHECK (v1.z == Approx (3.0f));
  CHECK (v2.x == Approx (-0.1f));
  CHECK (v2.y == Approx (-0.2f));
  CHECK (v2.z == Approx (0.7f));
}
