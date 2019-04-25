/*
  Filename: Camera.h
  Author: Joshua Kilhefner
  Course: CSCI 375
  Assignment: A03Camera
*/

#ifndef CAMERA_H
#define CAMERA_H

#include <string>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "ShaderProgram.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "Transform.h"
#include "Matrix4.h"

class Camera {
  
public:
  
  Camera();
  Camera(const Vector3& eyePoint, const Vector3& localBackDirection, float nearClipPlaneDistance, float farClipPlaneDistance, float aspectRatio, float verticalFieldOfViewDegrees);
  
  void
  setPosition(const Vector3& position);
  
  void
  moveRight(float distance);
  
  void
  moveUp(float distance);
  
  void
  moveBack(float distance);
  
  void
  yaw(float degrees);

  void
  pitch(float degrees);

  void
  roll(float degrees);

  Transform
  getViewMatrix();
  
  void
  setProjectionSymmetricPerspective(double verticalFovDegrees, double aspectRatio, double nearZ, double farZ);
  
  void
  setProjectionAsymmetricPerspective(double left, double right, double bottom, double top, double nearZ, double farZ);

  void
  setProjectionOrthographic(double left, double right, double bottom, double top, double nearZ, double farZ);

  Matrix4
  getProjectionMatrix();
  
private:
  
  //Vector3 eye;
  //Vector3 back;
  //Vector3 right;
  //Vector3 up;
  float nearPlane;
  float farPlane;
  float aRatio;
  float fieldOfView;
  //Matrix3 cam;
  Transform m_world;
  //glm::mat4 viewMatrix;
  Transform view;
  Matrix4 projectionMatrix;
  
};

#endif
