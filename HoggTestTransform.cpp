
/*
  Filename: HoggTestTransform.cpp
  Author: Chad Hogg
  Assignment: A07Projection
  Description: Catch2 test cases for the Transform class.
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Vector3.h"
#include "Matrix3.h"
#include "Transform.h"
#include "Matrix4.h"

class MyMatrix4
{
public:

  // column-major order
  float elements[4][4];

  MyMatrix4 ()
  {
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
	elements[i][j] = 0.0f;
      }
    }
  }
  
  MyMatrix4 (const Matrix3& m, const Vector3& v)
  {
    elements[0][0] = m.getRight ().xVal;
    elements[0][1] = m.getRight ().yVal;
    elements[0][2] = m.getRight ().zVal;
    elements[0][3] = 0.0f;
    elements[1][0] = m.getUp ().xVal;
    elements[1][1] = m.getUp ().yVal;
    elements[1][2] = m.getUp ().zVal;
    elements[1][3] = 0.0f;
    elements[2][0] = m.getBack ().xVal;
    elements[2][1] = m.getBack ().yVal;
    elements[2][2] = m.getBack ().zVal;
    elements[2][3] = 0.0f;
    elements[3][0] = v.xVal;
    elements[3][1] = v.yVal;
    elements[3][2] = v.zVal;
    elements[3][3] = 1.0f;
  }
};

MyMatrix4 operator* (const MyMatrix4& m1, const MyMatrix4& m2)
{
  MyMatrix4 r;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      float total = 0.0;
      for (int k = 0; k < 4; k++) {
	total += m1.elements[k][j] * m2.elements[i][k];
      }
      r.elements[i][j] = total;
    }
  }
  return r;
}

bool operator== (const MyMatrix4& m1, const MyMatrix4& m2)
{
  const float EPSILON = 0.0001f;
  bool result = true;
  for (int i = 0; i < 4 && result; i++) {
    for (int j = 0; j < 4 && result; j++) {
      if (fabs (m1.elements[i][j] - m2.elements[i][j]) > EPSILON) {
	result = false;
      }
    }
  }
  return result;
}

std::ostream& operator<<(std::ostream& out, const MyMatrix4& m)
{
  for (int j = 0; j < 4; j++) {
    for (int i = 0; i < 4; i++) {
      out << std::setprecision(2) << std::setw(10) << m.elements[i][j];
    }
    out << std::endl;
  }
  return out;
}

const Matrix3 IDENTITY_MATRIX
(1.0f, 0.0f, 0.0f,
 0.0f, 1.0f, 0.0f,
 0.0f, 0.0f, 1.0f);

const Matrix3 ZERO_MATRIX
(0.0f, 0.0f, 0.0f,
 0.0f, 0.0f, 0.0f,
 0.0f, 0.0f, 0.0f);

const Matrix3 ARBITRARY_MATRIX
(1.0f, 0.0f, -1.0f,
 4.0f, 0.5f, 12.2f,
 0.0f, 9.9f, -2.0f);

const Matrix3 ANOTHER_MATRIX
(-7.0f, 2.3f, 1.0f,
 2.0f, 3.0f, 4.0f,
 0.0f, -1.0f, 0.1f);

const Vector3 ZERO_VECTOR (0.0f, 0.0f, 0.0f);
const Vector3 BASIS_I (1.0f, 0.0f, 0.0f);
const Vector3 BASIS_J (0.0f, 1.0f, 0.0f);
const Vector3 BASIS_K (0.0f, 0.0f, 1.0f);
const Vector3 ARBITRARY_VECTOR (-3.0f, 7.5f, 2.4f);
const Vector3 ANOTHER_VECTOR (0.2f, 1.5f, -2.0f);

TEST_CASE ("MyMatrix4 constructors", "[Transform]")
{
  MyMatrix4 t1;
  CHECK (t1.elements[0][0] == Approx (0.0f));
  CHECK (t1.elements[0][1] == Approx (0.0f));
  CHECK (t1.elements[0][2] == Approx (0.0f));
  CHECK (t1.elements[0][3] == Approx (0.0f));
  CHECK (t1.elements[1][0] == Approx (0.0f));
  CHECK (t1.elements[1][1] == Approx (0.0f));
  CHECK (t1.elements[1][2] == Approx (0.0f));
  CHECK (t1.elements[1][3] == Approx (0.0f));
  CHECK (t1.elements[2][0] == Approx (0.0f));
  CHECK (t1.elements[2][1] == Approx (0.0f));
  CHECK (t1.elements[2][2] == Approx (0.0f));
  CHECK (t1.elements[2][3] == Approx (0.0f));
  CHECK (t1.elements[3][0] == Approx (0.0f));
  CHECK (t1.elements[3][1] == Approx (0.0f));
  CHECK (t1.elements[3][2] == Approx (0.0f));
  CHECK (t1.elements[3][3] == Approx (0.0f));
  MyMatrix4 t2(ARBITRARY_MATRIX, ARBITRARY_VECTOR);
  CHECK (t2.elements[0][0] == Approx (ARBITRARY_MATRIX.getRight ().xVal));
  CHECK (t2.elements[0][1] == Approx (ARBITRARY_MATRIX.getRight ().yVal));
  CHECK (t2.elements[0][2] == Approx (ARBITRARY_MATRIX.getRight ().zVal));
  CHECK (t2.elements[0][3] == Approx (0.0f));
  CHECK (t2.elements[1][0] == Approx (ARBITRARY_MATRIX.getUp ().xVal));
  CHECK (t2.elements[1][1] == Approx (ARBITRARY_MATRIX.getUp ().yVal));
  CHECK (t2.elements[1][2] == Approx (ARBITRARY_MATRIX.getUp ().zVal));
  CHECK (t2.elements[1][3] == Approx (0.0f));
  CHECK (t2.elements[2][0] == Approx (ARBITRARY_MATRIX.getBack ().xVal));
  CHECK (t2.elements[2][1] == Approx (ARBITRARY_MATRIX.getBack ().yVal));
  CHECK (t2.elements[2][2] == Approx (ARBITRARY_MATRIX.getBack ().zVal));
  CHECK (t2.elements[2][3] == Approx (0.0f));
  CHECK (t2.elements[3][0] == Approx (ARBITRARY_VECTOR.xVal));
  CHECK (t2.elements[3][1] == Approx (ARBITRARY_VECTOR.yVal));
  CHECK (t2.elements[3][2] == Approx (ARBITRARY_VECTOR.zVal));
  CHECK (t2.elements[3][3] == Approx (1.0f));
  MyMatrix4 t3(t2);
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      CHECK (t2.elements[i][j] == t3.elements[i][j]);
    }
  }
}

TEST_CASE ("MyMatrix4 multiplication", "[Transform]")
{
  MyMatrix4 first;
  MyMatrix4 second;
  MyMatrix4 expected;
  first.elements[0][0] = 5.0f;
  first.elements[0][1] = 0.0f;
  first.elements[0][2] = 3.0f;
  first.elements[0][3] = 1.0f;
  first.elements[1][0] = 2.0f;
  first.elements[1][1] = 6.0f;
  first.elements[1][2] = 8.0f;
  first.elements[1][3] = 8.0;
  first.elements[2][0] = 6.0f;
  first.elements[2][1] = 2.0f;
  first.elements[2][2] = 1.0f;
  first.elements[2][3] = 5.0f;
  first.elements[3][0] = 1.0f;
  first.elements[3][1] = 0.0f;
  first.elements[3][2] = 4.0f;
  first.elements[3][3] = 6.0f;
  second.elements[0][0] = 7.0f;
  second.elements[0][1] = 1.0f;
  second.elements[0][2] = 9.0f;
  second.elements[0][3] = 5.0f;
  second.elements[1][0] = 5.0f;
  second.elements[1][1] = 8.0f;
  second.elements[1][2] = 4.0f;
  second.elements[1][3] = 3.0f;
  second.elements[2][0] = 8.0f;
  second.elements[2][1] = 2.0f;
  second.elements[2][2] = 3.0f;
  second.elements[2][3] = 7.0f;
  second.elements[3][0] = 0.0f;
  second.elements[3][1] = 6.0f;
  second.elements[3][2] = 8.0f;
  second.elements[3][3] = 9.0f;
  expected.elements[0][0] = 96.0f;
  expected.elements[0][1] = 24.0f;
  expected.elements[0][2] = 58.0f;
  expected.elements[0][3] = 90.0f;
  expected.elements[1][0] = 68.0f;
  expected.elements[1][1] = 56.0f;
  expected.elements[1][2] = 95.0f;
  expected.elements[1][3] = 107.0f;
  expected.elements[2][0] = 69.0f;
  expected.elements[2][1] = 18.0f;
  expected.elements[2][2] = 71.0f;
  expected.elements[2][3] = 81.0f;
  expected.elements[3][0] = 69.0f;
  expected.elements[3][1] = 52.0f;
  expected.elements[3][2] = 92.0f;
  expected.elements[3][3] = 142.0f;
  CHECK (expected == first * second);
}

TEST_CASE ("Transform::Transform() creates identity transform", "[Transform]") {
  Transform t;
  CHECK (t.getOrientation () == IDENTITY_MATRIX);
  CHECK (t.getPosition () == ZERO_VECTOR);
}

TEST_CASE ("Transform functions for getting and setting components work", "[Transform]") {
  Transform t;
  CHECK (t.getOrientation () == IDENTITY_MATRIX);
  CHECK (t.getRight () == BASIS_I);
  CHECK (t.getUp () == BASIS_J);
  CHECK (t.getBack () == BASIS_K);
  CHECK (t.getPosition () == ZERO_VECTOR);

  t.setOrientation (ARBITRARY_MATRIX);
  CHECK (t.getOrientation () == ARBITRARY_MATRIX);
  CHECK (t.getRight () == ARBITRARY_MATRIX.getRight ());
  CHECK (t.getUp () == ARBITRARY_MATRIX.getUp ());
  CHECK (t.getBack () == ARBITRARY_MATRIX.getBack ());
  CHECK (t.getPosition () == ZERO_VECTOR);

  t.setPosition (ARBITRARY_VECTOR);
  CHECK (t.getOrientation () == ARBITRARY_MATRIX);
  CHECK (t.getRight () == ARBITRARY_MATRIX.getRight ());
  CHECK (t.getUp () == ARBITRARY_MATRIX.getUp ());
  CHECK (t.getBack () == ARBITRARY_MATRIX.getBack ());
  CHECK (t.getPosition () == ARBITRARY_VECTOR);

  t.setOrientation (ANOTHER_MATRIX.getRight (),
		    ANOTHER_MATRIX.getUp (),
		    ANOTHER_MATRIX.getBack ());
  CHECK (t.getOrientation () == ANOTHER_MATRIX);
  CHECK (t.getRight () == ANOTHER_MATRIX.getRight ());
  CHECK (t.getUp () == ANOTHER_MATRIX.getUp ());
  CHECK (t.getBack () == ANOTHER_MATRIX.getBack ());
  CHECK (t.getPosition () == ARBITRARY_VECTOR);

  t.setPosition (ANOTHER_VECTOR.xVal, ANOTHER_VECTOR.yVal, ANOTHER_VECTOR.zVal);
  CHECK (t.getOrientation () == ANOTHER_MATRIX);
  CHECK (t.getRight () == ANOTHER_MATRIX.getRight ());
  CHECK (t.getUp () == ANOTHER_MATRIX.getUp ());
  CHECK (t.getBack () == ANOTHER_MATRIX.getBack ());
  CHECK (t.getPosition () == ANOTHER_VECTOR);  
}


TEST_CASE ("Transform::reset() works", "[Transform]") {
  Transform t;
  t.setOrientation (ARBITRARY_MATRIX);
  t.setPosition (ARBITRARY_VECTOR);
  t.reset ();
  CHECK (t.getOrientation () == IDENTITY_MATRIX);
  CHECK (t.getPosition () == ZERO_VECTOR);
}

TEST_CASE ("Transform::getTransform() and getTransform(float[16]) work", "[Transform]") {
  Transform t;
  t.setOrientation (ARBITRARY_MATRIX);
  t.setPosition (ARBITRARY_VECTOR);
  float expectedArray[16] =
    { ARBITRARY_MATRIX.getRight ().xVal, ARBITRARY_MATRIX.getRight ().yVal, ARBITRARY_MATRIX.getRight ().zVal, 0.0f,
      ARBITRARY_MATRIX.getUp ().xVal, ARBITRARY_MATRIX.getUp ().yVal, ARBITRARY_MATRIX.getUp ().zVal, 0.0f,
      ARBITRARY_MATRIX.getBack ().xVal, ARBITRARY_MATRIX.getBack ().yVal, ARBITRARY_MATRIX.getBack ().zVal, 0.0f,
      ARBITRARY_VECTOR.xVal, ARBITRARY_VECTOR.yVal, ARBITRARY_VECTOR.zVal, 1.0f};
  float receivedArray[16];
  t.getTransform (receivedArray);
  Matrix4 expectedMatrix4 (Vector4 (expectedArray[0], expectedArray[1], expectedArray[2], expectedArray[3]), Vector4 (expectedArray[4], expectedArray[5], expectedArray[6], expectedArray[7]), Vector4 (expectedArray[8], expectedArray[9], expectedArray[10], expectedArray[11]), Vector4 (expectedArray[12], expectedArray[13], expectedArray[14], expectedArray[15]));
  Matrix4 receivedMatrix4 (t.getTransform ());
  for(unsigned int i = 0; i < 16; i++) {
    CHECK (expectedArray[i] == receivedArray[i]);
  }
  CHECK (expectedMatrix4 == receivedMatrix4);
}

TEST_CASE ("Transform::orthonormalize() works", "[Transform]") {
  Transform t;
  t.setOrientation (ARBITRARY_MATRIX);
  t.setPosition (ARBITRARY_VECTOR);
  t.orthonormalize();
  Vector3 back(ARBITRARY_MATRIX.getBack ());
  back.normalize ();
  CHECK (t.getBack () == back);
  CHECK (t.getBack ().length () == Approx (1.0f));
  CHECK (t.getBack ().angleBetween (t.getRight ()) == Approx (M_PI / 2.0f));
  CHECK (t.getRight ().angleBetween (t.getUp ()) == Approx (M_PI / 2.0f));
  CHECK (t.getRight ().length () == Approx (1.0f));
  CHECK (t.getUp ().angleBetween (t.getBack ()) == Approx (M_PI / 2.0f));
  CHECK (t.getRight ().angleBetween (t.getUp ()) == Approx (M_PI / 2.0f));
  CHECK (t.getUp ().length () == Approx (1.0f));
  CHECK (t.getPosition () == ARBITRARY_VECTOR);
}

TEST_CASE ("Transform movement functions work", "[Transform]") {
  Transform t;
  t.setOrientation (ARBITRARY_MATRIX);
  t.setPosition (ARBITRARY_VECTOR);

  SECTION ("Moving Right") {
    t.moveRight (5.0f);
    CHECK (t.getOrientation () == ARBITRARY_MATRIX);
    CHECK (t.getPosition () == ARBITRARY_VECTOR + (5.0f * ARBITRARY_MATRIX.getRight ()));
    MyMatrix4 original(ARBITRARY_MATRIX, ARBITRARY_VECTOR);
    MyMatrix4 translate(IDENTITY_MATRIX, Vector3(5.0f, 0.0f, 0.0f));
    MyMatrix4 expected = original * translate;
    MyMatrix4 actual(t.getOrientation (), t.getPosition ());
    CHECK (expected == actual);
  }

  SECTION ("Moving Up") {
    t.moveUp (5.0f);
    CHECK (t.getOrientation () == ARBITRARY_MATRIX);
    CHECK (t.getPosition () == ARBITRARY_VECTOR + (5.0f * ARBITRARY_MATRIX.getUp ()));
    MyMatrix4 original(ARBITRARY_MATRIX, ARBITRARY_VECTOR);
    MyMatrix4 translate(IDENTITY_MATRIX, Vector3(0.0f, 5.0f, 0.0f));
    MyMatrix4 expected = original * translate;
    MyMatrix4 actual(t.getOrientation (), t.getPosition ());
    CHECK (expected == actual);
  }

  SECTION ("Moving Right") {
    t.moveBack (5.0f);
    CHECK (t.getOrientation () == ARBITRARY_MATRIX);
    CHECK (t.getPosition () == ARBITRARY_VECTOR + (5.0f * ARBITRARY_MATRIX.getBack ()));
    MyMatrix4 original(ARBITRARY_MATRIX, ARBITRARY_VECTOR);
    MyMatrix4 translate(IDENTITY_MATRIX, Vector3(0.0f, 0.0f, 5.0f));
    MyMatrix4 expected = original * translate;
    MyMatrix4 actual(t.getOrientation (), t.getPosition ());
    CHECK (expected == actual);
  }

  
}

TEST_CASE ("Transform rotation functions work", "[Transform]") {
  Transform t;
  t.setOrientation (ARBITRARY_MATRIX);
  t.setPosition (ARBITRARY_VECTOR);
  Matrix3 m;
  MyMatrix4 original (ARBITRARY_MATRIX, ARBITRARY_VECTOR);

  SECTION ("Pitch") {
    t.pitch (30);
    m.setToRotationX (30);
    MyMatrix4 pitch (m, ZERO_VECTOR);
    MyMatrix4 actual(t.getOrientation (), t.getPosition ());
    CHECK (original * pitch == actual);
  }

  SECTION ("Yaw") {
    t.yaw (60);
    m.setToRotationY (60);
    CHECK (original * MyMatrix4 (m, ZERO_VECTOR) == MyMatrix4 (t.getOrientation (), t.getPosition ()));
  }

  SECTION ("Roll") {
    t.roll (90);
    m.setToRotationZ (90);
    CHECK (original * MyMatrix4 (m, ZERO_VECTOR) == MyMatrix4 (t.getOrientation (), t.getPosition ()));
  }

  SECTION ("Arbitrary Local") {
    t.rotateLocal (45, Vector3(1.0f, 2.0f, 3.0f));
    m.setFromAngleAxis (45, Vector3(1.0f, 2.0f, 3.0f));
    CHECK (original * MyMatrix4 (m, ZERO_VECTOR) == MyMatrix4 (t.getOrientation (), t.getPosition ()));
  }

  SECTION ("Arbitrary World") {
    t.rotateWorld (45, Vector3(1.0f, 2.0f, 3.0f));
    m.setFromAngleAxis (45, Vector3(1.0f, 2.0f, 3.0f));
    CHECK (MyMatrix4 (m, ZERO_VECTOR) * original == MyMatrix4 (t.getOrientation (), t.getPosition ()));
  }
}

TEST_CASE ("Transform::alignWithWorldY() works", "[Transform]") {
  Transform t;
  t.setOrientation (ARBITRARY_MATRIX);
  t.setPosition (ARBITRARY_VECTOR);
  t.alignWithWorldY ();
  CHECK (t.getOrientation ().getUp () == BASIS_J);
  CHECK (t.getOrientation ().getRight ().length () == Approx (1.0f));
  CHECK (t.getOrientation ().getBack ().length () == Approx (1.0f));
  CHECK (t.getOrientation ().getRight ().angleBetween (t.getOrientation ().getUp ()) == Approx (M_PI / 2.0f));
  CHECK (t.getOrientation ().getUp ().angleBetween (t.getOrientation ().getBack ()) == Approx (M_PI / 2.0f));
  CHECK (t.getOrientation ().getBack ().angleBetween (t.getOrientation ().getRight ()) == Approx (M_PI / 2.0f));
}

TEST_CASE ("Transform scale functions work", "[Transform]") {
  Transform t;
  t.setOrientation (ARBITRARY_MATRIX);
  t.setPosition (ARBITRARY_VECTOR);
  Matrix3 m;
  MyMatrix4 original (ARBITRARY_MATRIX, ARBITRARY_VECTOR);

  SECTION ("Local Uniform") {
    t.scaleLocal (2.0f);
    m.setToScale (2.0f);
    CHECK (original * MyMatrix4 (m, ZERO_VECTOR) == MyMatrix4 (t.getOrientation (), t.getPosition ()));
  }

  SECTION ("Local Non-Uniform") {
    t.scaleLocal (1.0f, 2.0f, 3.0f);
    m.setToScale (1.0f, 2.0f, 3.0f);
    CHECK (original * MyMatrix4 (m, ZERO_VECTOR) == MyMatrix4 (t.getOrientation (), t.getPosition ()));
  }

  SECTION ("World Uniform") {
    t.scaleWorld (-3.0f);
    m.setToScale (-3.0f);
    CHECK (MyMatrix4 (m, ZERO_VECTOR) * original == MyMatrix4 (t.getOrientation (), t.getPosition ()));
  }

  SECTION ("World Non-Uniform") {
    t.scaleWorld (-2.0f, 4.0f, 0.0f);
    m.setToScale (-2.0f, 4.0f, 0.0f);
    CHECK (MyMatrix4 (m, ZERO_VECTOR) * original == MyMatrix4 (t.getOrientation (), t.getPosition ()));
  }
}

TEST_CASE ("Transform shear functions work", "[Transform]") {
  Transform t;
  t.setOrientation (ARBITRARY_MATRIX);
  t.setPosition (ARBITRARY_VECTOR);
  Matrix3 m;
  MyMatrix4 original (ARBITRARY_MATRIX, ARBITRARY_VECTOR);

  SECTION ("X By YZ") {
    t.shearLocalXByYz (2.0f, 3.0f);
    m.setToShearXByYz (2.0f, 3.0f);
    CHECK (original * MyMatrix4 (m, ZERO_VECTOR) == MyMatrix4 (t.getOrientation (), t.getPosition ()));
  }

  SECTION ("Y By XZ") {
    t.shearLocalYByXz (1.5f, -1.0f);
    m.setToShearYByXz (1.5f, -1.0f);
    CHECK (original * MyMatrix4 (m, ZERO_VECTOR) == MyMatrix4 (t.getOrientation (), t.getPosition ()));
  }

  SECTION ("Z By XY") {
    t.shearLocalZByXy (0.5f, 0.0f);
    m.setToShearZByXy (0.5f, 0.0f);
    CHECK (original * MyMatrix4 (m, ZERO_VECTOR) == MyMatrix4 (t.getOrientation (), t.getPosition ()));
  }
}

TEST_CASE ("Transform inversions work", "[Transform]") {
  Transform t;
  t.setOrientation (ARBITRARY_MATRIX);
  t.setPosition (ARBITRARY_VECTOR);

  t.invertRt ();
  Matrix3 m(ARBITRARY_MATRIX);
  m.transpose ();
  CHECK (t.getOrientation () == m);
  CHECK (t.getPosition () == t.getOrientation () * (-1.0f * ARBITRARY_VECTOR));
}

TEST_CASE ("Transform combine works", "[Transform]") {
  Transform t1, t2;
  t1.setOrientation (ARBITRARY_MATRIX);
  t1.setPosition (ARBITRARY_VECTOR);
  t2.setOrientation (ANOTHER_MATRIX);
  t2.setPosition (ANOTHER_VECTOR);
  Matrix3 m = t1.getOrientation () * t2.getOrientation ();
  Vector3 v = t1.getPosition () + t1.getOrientation () * t2.getPosition ();
  t1.combine (t2);
  CHECK (t1.getOrientation () == m);
  CHECK (t1.getPosition () == v);
}

TEST_CASE ("Transform operator== works", "[Transform]") {
  Transform t1, t2, t3, t4;
  t1.setOrientation (ARBITRARY_MATRIX);
  t1.setPosition (ARBITRARY_VECTOR);
  t2.setOrientation (ARBITRARY_MATRIX);
  t2.setPosition (ARBITRARY_VECTOR);
  t3.setOrientation (ANOTHER_MATRIX);
  t3.setPosition (ANOTHER_VECTOR);
  t4.setOrientation (ARBITRARY_MATRIX);
  t4.setPosition (ANOTHER_VECTOR);

  CHECK (t1 == t2);
  CHECK (! (t1 == t3));
  CHECK (! (t1 == t4));
  CHECK (t2 == t1);
  CHECK (! (t2 == t3));
  CHECK (! (t2 == t4));
  CHECK (! (t3 == t1));
  CHECK (! (t3 == t2));
  CHECK (! (t3 == t4));
  CHECK (! (t4 == t1));
  CHECK (! (t4 == t2));
  CHECK (! (t4 == t3));
}
