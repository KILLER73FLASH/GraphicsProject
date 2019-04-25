
/*
  Filename: CatchTestMatrix3.cpp
  Author: Chad Hogg
  Assignment: A06Transform
  Description: Catch2 test cases for the Matrix3 class.
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Vector3.h"
#include "Matrix3.h"

const Matrix3 IDENTITY_MATRIX
(1.0f, 0.0f, 0.0f,
 0.0f, 1.0f, 0.0f,
 0.0f, 0.0f, 1.0f);

const Matrix3 ZERO_MATRIX
(0.0f, 0.0f, 0.0f,
 0.0f, 0.0f, 0.0f,
 0.0f, 0.0f, 0.0f);

const Matrix3 A_START_MATRIX
(6.0f, 4.0f, 2.0f,
 1.0f, -2.0f, 8.0f,
 1.0f, 5.0f, 7.0f);

const Vector3 ZERO_VECTOR (0.0f, 0.0f, 0.0f);
const Vector3 A_VECTOR (1.0f, 2.0f, 3.0f);
const Vector3 BASIS_I (1.0f, 0.0f, 0.0f);
const Vector3 BASIS_J (0.0f, 1.0f, 0.0f);
const Vector3 BASIS_K (0.0f, 0.0f, 1.0f);


TEST_CASE ("Matrix3 default constructor creates identity matrix", "[Matrix3]") {
  Matrix3 m;
  CHECK (m.getRight ().xVal == Approx (1.0f));
  CHECK (m.getRight ().yVal == Approx (0.0f));
  CHECK (m.getRight ().zVal == Approx (0.0f));
  CHECK (m.getUp ().xVal == Approx (0.0f));
  CHECK (m.getUp ().yVal == Approx (1.0f));
  CHECK (m.getUp ().zVal == Approx (0.0f));
  CHECK (m.getBack ().xVal == Approx (0.0f));
  CHECK (m.getBack ().yVal == Approx (0.0f));
  CHECK (m.getBack ().zVal == Approx (1.0f));
}

TEST_CASE ("Matrix3 9-parameter construtor copies correctly", "[Matrix3]") {
  Matrix3 m1 (1.0f, 2.0f, 3.0f,
	      4.0f, 5.0f, 6.0f,
	      7.0f, 8.0f, 9.0f);
  Matrix3 m2 (0.0f, 1.0f, -1.0f,
	      0.1f, 0.2f, 0.3f,
	      -1.0f, 0.5f, 0.0f);
  CHECK (m1.getRight ().xVal == Approx (1.0f));
  CHECK (m1.getRight ().yVal == Approx (2.0f));
  CHECK (m1.getRight ().zVal == Approx (3.0f));
  CHECK (m1.getUp ().xVal == Approx (4.0f));
  CHECK (m1.getUp ().yVal == Approx (5.0f));
  CHECK (m1.getUp ().zVal == Approx (6.0f));
  CHECK (m1.getBack ().xVal == Approx (7.0f));
  CHECK (m1.getBack ().yVal == Approx (8.0f));
  CHECK (m1.getBack ().zVal == Approx (9.0f));
  CHECK (m2.getRight ().xVal == Approx (0.0f));
  CHECK (m2.getRight ().yVal == Approx (1.0f));
  CHECK (m2.getRight ().zVal == Approx (-1.0f));
  CHECK (m2.getUp ().xVal == Approx (0.1f));
  CHECK (m2.getUp ().yVal == Approx (0.2f));
  CHECK (m2.getUp ().zVal == Approx (0.3f));
  CHECK (m2.getBack ().xVal == Approx (-1.0f));
  CHECK (m2.getBack ().yVal == Approx (0.5f));
  CHECK (m2.getBack ().zVal == Approx (0.0f));
}

TEST_CASE ("Matrix3 3-parameter construtor copies correctly", "[Matrix3]") {
  Vector3 r1 (1.0f, 2.0f, 3.0f);
  Vector3 u1 (4.0f, 5.0f, 6.0f);
  Vector3 b1 (7.0f, 8.0f, 9.0f);
  Matrix3 m1 (r1, u1, b1);
  Vector3 r2 (0.0f, 1.0f, -1.0f);
  Vector3 u2 (0.1f, 0.2f, 0.3f);
  Vector3 b2 (-1.0f, 0.5f, 0.0f);
  Matrix3 m2 (r2, u2, b2);
  CHECK (m1.getRight ().xVal == Approx (r1.xVal));
  CHECK (m1.getRight ().yVal == Approx (r1.yVal));
  CHECK (m1.getRight ().zVal == Approx (r1.zVal));
  CHECK (m1.getUp ().xVal == Approx (u1.xVal));
  CHECK (m1.getUp ().yVal == Approx (u1.yVal));
  CHECK (m1.getUp ().zVal == Approx (u1.zVal));
  CHECK (m1.getBack ().xVal == Approx (b1.xVal));
  CHECK (m1.getBack ().yVal == Approx (b1.yVal));
  CHECK (m1.getBack ().zVal == Approx (b1.zVal));
  CHECK (m2.getRight ().xVal == Approx (r2.xVal));
  CHECK (m2.getRight ().yVal == Approx (r2.yVal));
  CHECK (m2.getRight ().zVal == Approx (r2.zVal));
  CHECK (m2.getUp ().xVal == Approx (u2.xVal));
  CHECK (m2.getUp ().yVal == Approx (u2.yVal));
  CHECK (m2.getUp ().zVal == Approx (u2.zVal));
  CHECK (m2.getBack ().xVal == Approx (b2.xVal));
  CHECK (m2.getBack ().yVal == Approx (b2.yVal));
  CHECK (m2.getBack ().zVal == Approx (b2.zVal));
}

TEST_CASE ("Matrix3 2-parameter + bool construtor builds correct axis without normalization", "[Matrix3]") {
  Vector3 r1 (1.0f, 0.0f, 0.0f);
  Vector3 u1 (0.0f, 1.0f, 0.0f);
  Vector3 b1 (0.0f, 0.0f, 1.0f);
  Matrix3 m1 (r1, u1, false);
  Vector3 r2 (-2.0f, 0.0f, 0.0f);
  Vector3 u2 (0.0f, 2.0f, 0.0f);
  Vector3 b2 (0.0f, 0.0f, -4.0f);
  Matrix3 m2 (r2, u2, false);
  Vector3 r3 (1.0f, 2.0f, 3.0f);
  Vector3 u3 (4.0f, 5.0f, 6.0f);
  Vector3 b3 = r3.cross (u3);
  Matrix3 m3 (r3, u3, false);
  CHECK (m1.getRight ().xVal == Approx (r1.xVal));
  CHECK (m1.getRight ().yVal == Approx (r1.yVal));
  CHECK (m1.getRight ().zVal == Approx (r1.zVal));
  CHECK (m1.getUp ().xVal == Approx (u1.xVal));
  CHECK (m1.getUp ().yVal == Approx (u1.yVal));
  CHECK (m1.getUp ().zVal == Approx (u1.zVal));
  CHECK (m1.getBack ().xVal == Approx (b1.xVal));
  CHECK (m1.getBack ().yVal == Approx (b1.yVal));
  CHECK (m1.getBack ().zVal == Approx (b1.zVal));
  CHECK (m2.getRight ().xVal == Approx (r2.xVal));
  CHECK (m2.getRight ().yVal == Approx (r2.yVal));
  CHECK (m2.getRight ().zVal == Approx (r2.zVal));
  CHECK (m2.getUp ().xVal == Approx (u2.xVal));
  CHECK (m2.getUp ().yVal == Approx (u2.yVal));
  CHECK (m2.getUp ().zVal == Approx (u2.zVal));
  CHECK (m2.getBack ().xVal == Approx (b2.xVal));
  CHECK (m2.getBack ().yVal == Approx (b2.yVal));
  CHECK (m2.getBack ().zVal == Approx (b2.zVal));
  CHECK (m3.getRight ().xVal == Approx (r3.xVal));
  CHECK (m3.getRight ().yVal == Approx (r3.yVal));
  CHECK (m3.getRight ().zVal == Approx (r3.zVal));
  CHECK (m3.getUp ().xVal == Approx (u3.xVal));
  CHECK (m3.getUp ().yVal == Approx (u3.yVal));
  CHECK (m3.getUp ().zVal == Approx (u3.zVal));
  CHECK (m3.getBack ().xVal == Approx (b3.xVal));
  CHECK (m3.getBack ().yVal == Approx (b3.yVal));
  CHECK (m3.getBack ().zVal == Approx (b3.zVal));
}

TEST_CASE ("Matrix3 2-parameter + bool construtor builds correct axis with normalization", "[Matrix3]") {
  Vector3 r1 (1.0f, 0.0f, 0.0f);
  Vector3 u1 (0.0f, 1.0f, 0.0f);
  Vector3 b1 (0.0f, 0.0f, 1.0f);
  Matrix3 m1 (r1, u1, true);
  b1.normalize ();
  Vector3 r2 (-2.0f, 0.0f, 0.0f);
  Vector3 u2 (0.0f, 2.0f, 0.0f);
  Vector3 b2 (0.0f, 0.0f, -4.0f);
  Matrix3 m2 (r2, u2, true);
  b2.normalize ();
  Vector3 r3 (1.0f, 2.0f, 3.0f);
  Vector3 u3 (4.0f, 5.0f, 6.0f);
  Vector3 b3 = r3.cross (u3);
  Matrix3 m3 (r3, u3, true);
  b3.normalize ();

  // I originally tested that all vectors were normalized versions of the originals, since they were already orthogonal, but was surprised to find that the tests failed.  I guess there are an infinite number of orthogonalizations, so I need to instead just test that I have found one of them.

  CHECK (m1.getBack () == b1);
  CHECK (m1.getRight ().dot (m1.getUp ()) == Approx (0.0f));
  CHECK (m1.getRight ().dot (m1.getBack ()) == Approx (0.0f));
  CHECK (m1.getUp ().dot (m1.getBack ()) == Approx (0.0f));
  CHECK (m1.getRight ().length () == Approx (1.0f));
  CHECK (m1.getUp ().length () == Approx (1.0f));
  CHECK (m1.getBack ().length () == Approx (1.0f));

  CHECK (m2.getBack () == b2);
  CHECK (m2.getRight ().dot (m2.getUp ()) == Approx (0.0f));
  CHECK (m2.getRight ().dot (m2.getBack ()) == Approx (0.0f));
  CHECK (m2.getUp ().dot (m2.getBack ()) == Approx (0.0f));
  CHECK (m2.getRight ().length () == Approx (1.0f));
  CHECK (m2.getUp ().length () == Approx (1.0f));
  CHECK (m2.getBack ().length () == Approx (1.0f));

  CHECK (m3.getBack () == b3);
  CHECK (m3.getRight ().dot (m3.getUp ()) == Approx (0.0f));
  CHECK (m3.getRight ().dot (m3.getBack ()) == Approx (0.0f));
  CHECK (m3.getUp ().dot (m3.getBack ()) == Approx (0.0f));
  CHECK (m3.getRight ().length () == Approx (1.0f));
  CHECK (m3.getUp ().length () == Approx (1.0f));
  CHECK (m3.getBack ().length () == Approx (1.0f));
}

TEST_CASE ("Matrix3 setToIdentity function works", "[Matrix3]") {
  Matrix3 m (1.0f, 2.0f, 3.0f,
	     4.0f, 5.0f, 6.0f,
	     7.0f, 8.0f, 9.0f);
  m.setToIdentity ();
  CHECK (m == IDENTITY_MATRIX);
}

TEST_CASE ("Matrix3 setToZero function works", "[Matrix3]") {
  Matrix3 m;
  m.setToZero ();
  CHECK (m == ZERO_MATRIX);
}

TEST_CASE ("Matrix3 data function (non-const) works", "[Matrix3]") {
  Matrix3 m (1.0f, 2.0f, 3.0f,
	     4.0f, 5.0f, 6.0f,
	     7.0f, 8.0f, 9.0f);
  float * d = m.data ();
  CHECK (*d == Approx (1.0f));
  CHECK (*(d+1) == Approx (2.0f));
  CHECK (*(d+2) == Approx (3.0f));
  CHECK (*(d+3) == Approx (4.0f));
  CHECK (*(d+4) == Approx (5.0f));
  CHECK (*(d+5) == Approx (6.0f));
  CHECK (*(d+6) == Approx (7.0f));
  CHECK (*(d+7) == Approx (8.0f));
  CHECK (*(d+8) == Approx (9.0f));
  *d = 10.0f;
  CHECK (m.getRight ().xVal == Approx (10.0f));
}

TEST_CASE ("Matrix3 data function (const) works", "[Matrix3]") {
  Matrix3 m (1.0f, 2.0f, 3.0f,
	     4.0f, 5.0f, 6.0f,
	     7.0f, 8.0f, 9.0f);
  const Matrix3& c = m;
  const float * d = c.data ();
  CHECK (*d == Approx (1.0f));
  CHECK (*(d+1) == Approx (2.0f));
  CHECK (*(d+2) == Approx (3.0f));
  CHECK (*(d+3) == Approx (4.0f));
  CHECK (*(d+4) == Approx (5.0f));
  CHECK (*(d+5) == Approx (6.0f));
  CHECK (*(d+6) == Approx (7.0f));
  CHECK (*(d+7) == Approx (8.0f));
  CHECK (*(d+8) == Approx (9.0f));
  CHECK (c.data() == m.data());
}

TEST_CASE ("Matrix3 setRight function works", "[Matrix3]") {
  Matrix3 m;
  m.setToZero ();
  Vector3 v (1.0f, 2.0f, 3.0f);
  m.setRight (v);
  CHECK (m.getRight () == v);
  CHECK (m.getUp () == ZERO_VECTOR);
  CHECK (m.getBack () == ZERO_VECTOR);
}

TEST_CASE ("Matrix3 getRight function works", "[Matrix3]") {
  Matrix3 m (1.0f, 2.0f, 3.0f,
	     4.0f, 5.0f, 6.0f,
	     7.0f, 8.0f, 9.0f);
  Vector3 v = m.getRight ();
  CHECK (v.xVal == Approx (1.0f));
  CHECK (v.yVal == Approx (2.0f));
  CHECK (v.zVal == Approx (3.0f));
}

TEST_CASE ("Matrix3 setUp function works", "[Matrix3]") {
  Matrix3 m;
  m.setToZero ();
  Vector3 v (1.0f, 2.0f, 3.0f);
  m.setUp (v);
  CHECK (m.getRight () == ZERO_VECTOR);
  CHECK (m.getUp () == v);
  CHECK (m.getBack () == ZERO_VECTOR);
}

TEST_CASE ("Matrix3 getUp function works", "[Matrix3]") {
  Matrix3 m (1.0f, 2.0f, 3.0f,
	     4.0f, 5.0f, 6.0f,
	     7.0f, 8.0f, 9.0f);
  Vector3 v = m.getUp ();
  CHECK (v.xVal == Approx (4.0f));
  CHECK (v.yVal == Approx (5.0f));
  CHECK (v.zVal == Approx (6.0f));
}

TEST_CASE ("Matrix3 setBack function works", "[Matrix3]") {
  Matrix3 m;
  m.setToZero ();
  Vector3 v (1.0f, 2.0f, 3.0f);
  m.setBack (v);
  CHECK (m.getRight () == ZERO_VECTOR);
  CHECK (m.getUp () == ZERO_VECTOR);
  CHECK (m.getBack () == v);
}

TEST_CASE ("Matrix3 getBack function works", "[Matrix3]") {
  Matrix3 m (1.0f, 2.0f, 3.0f,
	     4.0f, 5.0f, 6.0f,
	     7.0f, 8.0f, 9.0f);
  Vector3 v = m.getBack ();
  CHECK (v.xVal == Approx (7.0f));
  CHECK (v.yVal == Approx (8.0f));
  CHECK (v.zVal == Approx (9.0f));
}

TEST_CASE ("Matrix3 setForward function works", "[Matrix3]") {
  Matrix3 m;
  m.setToZero ();
  Vector3 v (1.0f, 2.0f, 3.0f);
  m.setForward (v);
  CHECK (m.getRight () == ZERO_VECTOR);
  CHECK (m.getUp () == ZERO_VECTOR);
  CHECK (m.getBack () == -v);
}

TEST_CASE ("Matrix3 getForward function works", "[Matrix3]") {
  Matrix3 m (1.0f, 2.0f, 3.0f,
	     4.0f, 5.0f, 6.0f,
	     7.0f, 8.0f, 9.0f);
  Vector3 v = m.getForward ();
  CHECK (v.xVal == Approx (-7.0f));
  CHECK (v.yVal == Approx (-8.0f));
  CHECK (v.zVal == Approx (-9.0f));
}

TEST_CASE ("Matrix3 invertRotation function works", "[Matrix3]") {
  Matrix3 m (1.0f, 2.0f, 3.0f,
	     4.0f, 5.0f, 6.0f,
	     7.0f, 8.0f, 9.0f);
  Matrix3 t (m);
  m.invertRotation ();
  t.transpose ();
  CHECK (m == t);
}

TEST_CASE ("Matrix3 invert function works", "[Matrix3]") {
  Matrix3 m (7.0f, 0.0f, -3.0f,
	     2.0f, 3.0f, 4.0f,
	     1.0f, -1.0f, -2.0f);
  Matrix3 i (-2.0f, 3.0f, 9.0f,
	     8.0f, -11.0f, -34.0f,
	     -5.0f, 7.0f, 21.0f);
  Matrix3 o (m);
  m.invert ();
  CHECK (m == i);
  CHECK (o * i == IDENTITY_MATRIX);
}

TEST_CASE ("Matrix3 determinant function works", "[Matrix3]") {
  Matrix3 m (6.0f, 4.0f, 2.0f, 1.0f, -2.0f, 8.0f, 1.0f, 5.0f, 7.0f);
  float d = m.determinant ();
  CHECK (d == Approx (-306.0f));
}

TEST_CASE ("Matrix3 transpose function works", "[Matrix3]") {
  Matrix3 m (6.0f, 4.0f, 2.0f,
	     1.0f, -2.0f, 8.0f,
	     1.0f, 5.0f, 7.0f);
  Matrix3 t (6.0f, 1.0f, 1.0f,
	     4.0f, -2.0f, 5.0f,
	     2.0f, 8.0f, 7.0f);
  m.transpose ();
  CHECK (m == t);
}

TEST_CASE ("Matrix3 orthonormalize function works", "[Matrix3]") {
  Matrix3 m (A_START_MATRIX);
  Matrix3 o (m);
  m.orthonormalize ();
  Vector3 b (o.getBack ());
  b.normalize ();
  CHECK (m.getBack () == b);
  CHECK (m.getRight ().length () == Approx (1.0f));
  CHECK (m.getUp ().length () == Approx (1.0f));
  CHECK (m.getRight ().dot (m.getUp ()) == Approx (0.0f));
  CHECK (m.getUp ().dot (m.getBack ()) == Approx (0.0f));
  CHECK (m.getBack ().dot (m.getRight ()) == Approx (0.0f));
}

TEST_CASE ("Matrix3 setToScale(float) works", "[Matrix3]") {
  Matrix3 m (A_START_MATRIX);
  m.setToScale (-3.0f);
  Matrix3 s (-3.0f, 0.0f, 0.0f,
	     0.0f, -3.0f, 0.0f,
	     0.0f, 0.0f, -3.0f);
  Vector3 v (1.0f, 2.0f, -3.0f);
  CHECK (m == s);
  CHECK (m * v == Vector3 (-3.0f, -6.0f, 9.0f));
}

TEST_CASE ("Matrix3 setToScale(float, float, float) function works", "[Matrix3]") {
  Matrix3 m (A_START_MATRIX);
  m.setToScale (3.0f, -4.0f, 0.1f);
  Matrix3 s (3.0f, 0.0f, 0.0f,
	     0.0f, -4.0f, 0.0f,
	     0.0f, 0.0f, 0.1f);
  Vector3 v (1.0f, 2.0f, -3.0f);
  CHECK (m == s);
  CHECK (m * v == Vector3 (3.0f, -8.0f, -0.3f));
}

TEST_CASE ("Matrix3 setToShearXByYz function works", "[Matrix3]") {
  Matrix3 onlyByY (A_START_MATRIX);
  onlyByY.setToShearXByYz (3.0f, 0.0f);
  Matrix3 onlyByYExpected (1.0f, 0.0f, 0.0f,
			   3.0f, 1.0f, 0.0f,
			   0.0f, 0.0f, 1.0f);
  Matrix3 onlyByZ (A_START_MATRIX);
  onlyByZ.setToShearXByYz (0.0f, 2.0f);
  Matrix3 onlyByZExpected (1.0f, 0.0f, 0.0f,
			   0.0f, 1.0f, 0.0f,
			   2.0f, 0.0f, 1.0f);
  Matrix3 byBoth (A_START_MATRIX);
  byBoth.setToShearXByYz (3.0f, 2.0f);
  Matrix3 byBothExpected (1.0f, 0.0f, 0.0f,
			  3.0f, 1.0f, 0.0f,
			  2.0f, 0.0f, 1.0f);
  Vector3 start (3.0f, 4.0f, 5.0f);
  CHECK (onlyByY == onlyByYExpected);
  CHECK (onlyByY * start == Vector3 (3.0f + (3.0f * 4.0f), 4.0f, 5.0f));
  CHECK (onlyByZ == onlyByZExpected);
  CHECK (onlyByZ * start == Vector3 (3.0f + (2.0f * 5.0f), 4.0f, 5.0f));
  CHECK (byBoth == byBothExpected);
  CHECK (byBoth * start == Vector3 (3.0f + (3.0f * 4.0f) + (2.0f * 5.0f), 4.0f, 5.0f));
}

TEST_CASE ("Matrix3 setToShearYByXz function works", "[Matrix3]") {
  Matrix3 onlyByX (A_START_MATRIX);
  onlyByX.setToShearYByXz (1.5f, 0.0f);
  Matrix3 onlyByXExpected (1.0f, 1.5f, 0.0f,
			   0.0f, 1.0f, 0.0f,
			   0.0f, 0.0f, 1.0f);
  Matrix3 onlyByZ (A_START_MATRIX);
  onlyByZ.setToShearYByXz (0.0f, -1.0f);
  Matrix3 onlyByZExpected (1.0f, 0.0f, 0.0f,
			   0.0f, 1.0f, 0.0f,
			   0.0f, -1.0f, 1.0f);
  Matrix3 byBoth (A_START_MATRIX);
  byBoth.setToShearYByXz (1.5f, -1.0f);
  Matrix3 byBothExpected (1.0f, 1.5f, 0.0f,
			  0.0f, 1.0f, 0.0f,
			  0.0f, -1.0f, 1.0f);
  Vector3 start (3.0f, 4.0f, 5.0f);
  CHECK (onlyByX == onlyByXExpected);
  CHECK (onlyByX * start == Vector3 (3.0f, 4.0f + (1.5f * 3.0f), 5.0f));
  CHECK (onlyByZ == onlyByZExpected);
  CHECK (onlyByZ * start == Vector3 (3.0f, 4.0f + (-1.0f * 5.0f), 5.0f));
  CHECK (byBoth == byBothExpected);
  CHECK (byBoth * start == Vector3 (3.0f, 4.0f + (1.5f * 3.0f) + (-1.0f * 5.0f), 5.0f));
}

TEST_CASE ("Matrix3 setToShearZByXy function works", "[Matrix3]") {
  Matrix3 onlyByX (A_START_MATRIX);
  onlyByX.setToShearZByXy (8.0f, 0.0f);
  Matrix3 onlyByXExpected (1.0f, 0.0f, 8.0f,
			   0.0f, 1.0f, 0.0f,
			   0.0f, 0.0f, 1.0f);
  Matrix3 onlyByY (A_START_MATRIX);
  onlyByY.setToShearZByXy (0.0f, 0.1f);
  Matrix3 onlyByYExpected (1.0f, 0.0f, 0.0f,
			   0.0f, 1.0f, 0.1f,
			   0.0f, 0.0f, 1.0f);
  Matrix3 byBoth (A_START_MATRIX);
  byBoth.setToShearZByXy (8.0f, 0.1f);
  Matrix3 byBothExpected (1.0f, 0.0f, 8.0f,
			  0.0f, 1.0f, 0.1f,
			  0.0f, 0.0f, 1.0f);
  Vector3 start (3.0f, 4.0f, 5.0f);
  CHECK (onlyByX == onlyByXExpected);
  CHECK (onlyByX * start == Vector3 (3.0f, 4.0f, 5.0f + (8.0f * 3.0f)));
  CHECK (onlyByY == onlyByYExpected);
  CHECK (onlyByY * start == Vector3 (3.0f, 4.0f, 5.0f + (0.1f * 4.0f)));
  CHECK (byBoth == byBothExpected);
  CHECK (byBoth * start == Vector3 (3.0f, 4.0f, 5.0f + (8.0f * 3.0f) + (0.1f * 4.0f)));
}

TEST_CASE ("Matrix3 setToRotationX function works", "[Matrix3]") {
  Matrix3 m (A_START_MATRIX);
  m.setToRotationX (90.0f);
  Matrix3 r (1.0f, 0.0f, 0.0f,
	     0.0f, cos (M_PI / 2.0f), sin (M_PI / 2.0f),
	     0.0f, -sin (M_PI / 2.0f), cos (M_PI / 2.0f));
  Vector3 start (3.0f, 4.0f, 5.0f);
  CHECK (m == r);
  // Interpretation -- with right hand, point thumb in positive axis direction, rotation follows curvature of fingers
  CHECK (m * BASIS_I == BASIS_I);
  CHECK (m * BASIS_J == Vector3 (0.0f, 0.0f, 1.0f));
  CHECK (m * BASIS_K == Vector3 (0.0f, -1.0f, 0.0f));
  CHECK (m * start == Vector3 (3.0f, -5.0f, 4.0f));
}

TEST_CASE ("Matrix3 setToRotationY function works", "[Matrix3]") {
  Matrix3 m (A_START_MATRIX);
  m.setToRotationY (90.0f);
  Matrix3 r (cos (M_PI / 2.0f), 0.0f, -sin (M_PI / 2.0f),
	     0.0f, 1.0f, 0.0f,
	     sin (M_PI / 2.0f), 0.0f, cos (M_PI / 2.0f));
  Vector3 start (3.0f, 4.0f, 5.0f);
  CHECK (m == r);
  CHECK (m * BASIS_I == Vector3 (0.0f, 0.0f, -1.0f));
  CHECK (m * BASIS_J == BASIS_J);
  CHECK (m * BASIS_K == Vector3 (1.0f, 0.0f, 0.0f));
  CHECK (m * start == Vector3 (5.0f, 4.0f, -3.0f));
}

TEST_CASE ("Matrix3 setToRotationZ function works", "[Matrix3]") {
  Matrix3 m (A_START_MATRIX);
  m.setToRotationZ (90.0f);
  Matrix3 r (cos (M_PI / 2.0f), sin (M_PI / 2.0f), 0.0f,
	     -sin (M_PI / 2.0f), cos (M_PI / 2.0f), 0.0f,
	     0.0f, 0.0f, 1.0f);
  Vector3 start (3.0f, 4.0f, 5.0f);
  CHECK (m == r);
  CHECK (m * BASIS_I == Vector3 (0.0f, 1.0f, 0.0f));
  CHECK (m * BASIS_J == Vector3 (-1.0f, 0.0f, 0.0f));
  CHECK (m * BASIS_K == BASIS_K);
  CHECK (m * start == Vector3 (-4.0f, 3.0f, 5.0f));
}

TEST_CASE ("Matrix3 setFromAngleAxis function simulates others", "[Matrix3]") {
  Matrix3 m (A_START_MATRIX);
  Matrix3 o (A_START_MATRIX);
  m.setFromAngleAxis (90.0f, BASIS_I);
  o.setToRotationX (90.0f);
  CHECK (m == o);
  m.setFromAngleAxis (90.0f, BASIS_J);
  o.setToRotationY (90.0f);
  CHECK (m == o);
  m.setFromAngleAxis (90.0f, BASIS_K);
  o.setToRotationZ (90.0f);
  CHECK (m == o);
}

TEST_CASE ("Matrix3 setFromAngleAxis function works", "[Matrix3]") {
  // This idea comes from https://en.wikipedia.org/wiki/Rotation_matrix#Determining_the_axis
  Matrix3 m (A_START_MATRIX);
  Vector3 axis (1.5f, -2.7f, 0.4f);
  float angle (43.7f);
  m.setFromAngleAxis (angle, axis);
  Vector3 recoveredAxis(m.getUp ().zVal - m.getBack ().yVal,
			m.getBack ().xVal - m.getRight ().zVal,
			m.getRight ().yVal - m.getUp ().xVal);
  axis.normalize ();
  recoveredAxis.normalize ();
  CHECK (recoveredAxis == axis);
  float trace = m.getRight ().xVal + m.getUp ().yVal + m.getBack ().zVal;
  float recoveredAngle = acos ( (trace - 1.0f) / 2.0f);
  CHECK (recoveredAngle == Approx (fabs (angle * M_PI / 180.0)));
}

TEST_CASE ("Matrix3 negate function works", "[Matrix3]") {
  Matrix3 m (A_START_MATRIX);
  m.negate ();
  CHECK (m.getRight () == -A_START_MATRIX.getRight ());
  CHECK (m.getUp () == -A_START_MATRIX.getUp ());
  CHECK (m.getBack () == -A_START_MATRIX.getBack ());
}

TEST_CASE ("Matrix3 transform function works", "[Matrix3]") {
  Matrix3 m (A_START_MATRIX);
  Vector3 v (1.0f, 2.0f, 3.0f);
  Vector3 r = m.transform (v);
  Vector3 firstRow = Vector3 (m.getRight ().xVal, m.getUp ().xVal, m.getBack ().xVal);
  Vector3 secondRow = Vector3 (m.getRight ().yVal, m.getUp ().yVal, m.getBack ().yVal);
  Vector3 thirdRow = Vector3 (m.getRight ().zVal, m.getUp ().zVal, m.getBack ().zVal);
  CHECK (r.xVal == Approx (firstRow.dot (v)));
  CHECK (r.yVal == Approx (secondRow.dot (v)));
  CHECK (r.zVal == Approx (thirdRow.dot (v)));
}

TEST_CASE ("Matrix3 operator+= function works", "[Matrix3]") {
  Matrix3 m (A_START_MATRIX);
  m += A_START_MATRIX;
  Matrix3 r (A_START_MATRIX.getRight () * 2.0f,
	     A_START_MATRIX.getUp () * 2.0f,
	     A_START_MATRIX.getBack () * 2.0f);
  CHECK (m == r);
  m += IDENTITY_MATRIX;
  r = Matrix3 (A_START_MATRIX.getRight () * 2.0f + BASIS_I,
	       A_START_MATRIX.getUp () * 2.0f + BASIS_J,
	       A_START_MATRIX.getBack () * 2.0f + BASIS_K);
  CHECK (m == r);
}

TEST_CASE ("Matrix3 operator-= function works", "[Matrix3]") {
  Matrix3 m (A_START_MATRIX);
  m -= A_START_MATRIX;
  CHECK (m == ZERO_MATRIX);
  m -= IDENTITY_MATRIX;
  Matrix3 r (-BASIS_I, -BASIS_J, -BASIS_K);
  CHECK (m == r);
}

TEST_CASE ("Matrix3 operator*=(float) function works", "[Matrix3]") {
  Matrix3 m (A_START_MATRIX);
  m *= 3.5f;
  Matrix3 r (A_START_MATRIX.getRight () * 3.5f,
	     A_START_MATRIX.getUp () * 3.5f,
	     A_START_MATRIX.getBack () * 3.5f);
  CHECK (m == r);
  m *= 0.0f;
  CHECK (m == ZERO_MATRIX);
}

TEST_CASE ("Matrix3 operator*=(Matrix3) function works", "[Matrix3]") {
  Matrix3 m (A_START_MATRIX);
  m *= IDENTITY_MATRIX;
  CHECK (m == A_START_MATRIX);
  m *= ZERO_MATRIX;
  CHECK (m == ZERO_MATRIX);
}

TEST_CASE ("operator+(Matrix3, Matrix3) function works", "[Matrix3]") {
  CHECK (A_START_MATRIX + A_START_MATRIX == Matrix3 (A_START_MATRIX.getRight () * 2.0f,
						     A_START_MATRIX.getUp () * 2.0f,
						     A_START_MATRIX.getBack () * 2.0f));
  CHECK (A_START_MATRIX + ZERO_MATRIX == A_START_MATRIX);
  CHECK (A_START_MATRIX + IDENTITY_MATRIX == Matrix3 (A_START_MATRIX.getRight () + BASIS_I,
						      A_START_MATRIX.getUp () + BASIS_J,
						      A_START_MATRIX.getBack () + BASIS_K));
}

TEST_CASE ("operator-(Matrix3, Matrix3) function works", "[Matrix3]") {
  CHECK (A_START_MATRIX - A_START_MATRIX == ZERO_MATRIX);
  CHECK (A_START_MATRIX - IDENTITY_MATRIX == Matrix3 (A_START_MATRIX.getRight () - BASIS_I,
						      A_START_MATRIX.getUp () - BASIS_J,
						      A_START_MATRIX.getBack () - BASIS_K));
  CHECK (A_START_MATRIX - ZERO_MATRIX == A_START_MATRIX);
}

TEST_CASE ("operator-(Matrix3) function works", "[Matrix3]") {
  CHECK (-A_START_MATRIX == Matrix3 (-A_START_MATRIX.getRight (),
				     -A_START_MATRIX.getUp (),
				     -A_START_MATRIX.getBack ()));
  CHECK (-IDENTITY_MATRIX == Matrix3 (-BASIS_I, -BASIS_J, -BASIS_K));
  CHECK (-ZERO_MATRIX == ZERO_MATRIX);
}

TEST_CASE ("operator*(Matrix3, float) function works", "[Matrix3]") {
  CHECK (A_START_MATRIX * 2.5f == Matrix3 (A_START_MATRIX.getRight () * 2.5f,
					   A_START_MATRIX.getUp () * 2.5f,
					   A_START_MATRIX.getBack () * 2.5f));
  CHECK (IDENTITY_MATRIX * -0.1f == Matrix3 (BASIS_I * -0.1f,
					     BASIS_J * -0.1f,
					     BASIS_K * -0.1f));
  CHECK (ZERO_MATRIX * 15.0f == ZERO_MATRIX);
}

TEST_CASE ("operator*(float, Matrix3) function works", "[Matrix3]") {
  CHECK (2.5f * A_START_MATRIX == Matrix3 (2.5f * A_START_MATRIX.getRight (),
					   2.5f * A_START_MATRIX.getUp (),
					   2.5f * A_START_MATRIX.getBack ()));
  CHECK (-0.1f * IDENTITY_MATRIX == Matrix3 (-0.1f * BASIS_I,
					     -0.1f * BASIS_J,
					     -0.1f * BASIS_K));
  CHECK (15.0f * ZERO_MATRIX == ZERO_MATRIX);
}

TEST_CASE ("operator*(Matrix3, Matrix3) function works", "[Matrix3]") {
  CHECK (A_START_MATRIX * IDENTITY_MATRIX == A_START_MATRIX);
  CHECK (IDENTITY_MATRIX * A_START_MATRIX == A_START_MATRIX);
  CHECK (A_START_MATRIX * ZERO_MATRIX == ZERO_MATRIX);
  CHECK (ZERO_MATRIX * A_START_MATRIX == ZERO_MATRIX);
  Matrix3 m1 (4.0f, 2.0f, 6.0f,
	      6.0f, 1.0f, 9.0f,
	      8.0f, 4.0f, 3.0f);
  Matrix3 m2 (1.0f, 4.0f, 7.0f,
	      5.0f, 3.0f, 6.0f,
	      8.0f, 2.0f, 5.0f);
  Matrix3 p (84.0f, 34.0f, 63.0f,
	     86.0f, 37.0f, 75.0f,
	     84.0f, 38.0f, 81.0f);
  CHECK (m1 * m2 == p);
}

TEST_CASE ("operator*(Matrix3, Vector3) function works", "[Matrix3]") {
  CHECK (A_START_MATRIX * BASIS_I == A_START_MATRIX.getRight ());
  CHECK (A_START_MATRIX * BASIS_J == A_START_MATRIX.getUp ());
  CHECK (A_START_MATRIX * BASIS_K == A_START_MATRIX.getBack ());
  CHECK (IDENTITY_MATRIX * A_VECTOR == A_VECTOR);
  Matrix3 t = A_START_MATRIX;
  t.transpose ();
  CHECK (A_START_MATRIX * A_VECTOR == Vector3 (t.getRight ().dot (A_VECTOR),
					       t.getUp ().dot (A_VECTOR),
					       t.getBack ().dot (A_VECTOR)));
}

TEST_CASE ("operator==(Matrix3, Matrix3) function works", "[Matrix3]") {
  CHECK (A_START_MATRIX == A_START_MATRIX);
  CHECK (IDENTITY_MATRIX == IDENTITY_MATRIX);
  CHECK (ZERO_MATRIX == ZERO_MATRIX);
  CHECK (! (A_START_MATRIX == IDENTITY_MATRIX));
  CHECK (! (A_START_MATRIX == ZERO_MATRIX));
  CHECK (! (IDENTITY_MATRIX == ZERO_MATRIX));
}
