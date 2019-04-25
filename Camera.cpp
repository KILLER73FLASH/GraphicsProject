/*
  Filename: Camera.cpp
  Authors: Joshua Kilhefner
  Course: CSCI375
  Assignment: A03Camera
  Description: A class that simplifies loading and running OpenGL shaders.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <memory>
#include <math.h>

#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Camera.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "Matrix4.h"
#include "Transform.h"

Camera::Camera(){
  
}

Camera::Camera(const Vector3& eyePoint, const Vector3& localBackDirection, float nearClipPlaneDistance, float farClipPlaneDistance, float aspectRatio, float verticalFieldOfViewDegrees){
  m_world.m_position = eyePoint;
  m_world.m_rotScale.setBack(localBackDirection);
  m_world.m_rotScale.setRight(Vector3(0,1,0).cross(m_world.m_rotScale.m_back));
  m_world.m_rotScale.setUp(m_world.m_rotScale.m_back.cross(m_world.m_rotScale.m_right));
  nearPlane = nearClipPlaneDistance;
  farPlane = farClipPlaneDistance;
  aRatio = aspectRatio;
  fieldOfView = verticalFieldOfViewDegrees;
  
}

void
Camera::setPosition(const Vector3& position){
  m_world.m_position = position;
  m_world.m_rotScale.setToIdentity();
}

void
Camera::moveRight(float distance){
  m_world.moveRight(distance);
}

void
Camera::moveUp(float distance){
  m_world.moveUp(distance);
}

void
Camera::moveBack(float distance){
  m_world.moveBack(distance);
}

void
Camera::yaw(float degrees){
  m_world.yaw(degrees);
}
void
Camera::pitch(float degrees){
  m_world.pitch(degrees);
}

void
Camera::roll(float degrees){
  m_world.roll(degrees);
}

Transform
Camera::getViewMatrix(){
  //viewMatrix = glm::lookAt(convert(eye), (convert(eye) - convert(cam.m_back)), convert(cam.m_up));
  Transform view = m_world;
  view.invertRt();
  view.getTransform();
  return view;
}

void
Camera::setProjectionSymmetricPerspective(double verticalFovDegrees, double aspectRatio, double nearZ, double farZ){
  nearPlane = nearZ;
  farPlane = farZ;
  aRatio = aspectRatio;
  fieldOfView = verticalFovDegrees;
  projectionMatrix.setToPerspectiveProjection(fieldOfView, aRatio, nearPlane, farPlane);
}

void
Camera::setProjectionAsymmetricPerspective(double left, double right, double bottom, double top, double nearZ, double farZ) {
  projectionMatrix.setToPerspectiveProjection(left, right, bottom, top, nearZ, farZ);
}

void
Camera::setProjectionOrthographic(double left, double right, double bottom, double top, double nearZ, double farZ) {
  projectionMatrix.setToOrthographicProjection(left, right, bottom, top, nearZ, farZ);
}

Matrix4
Camera::getProjectionMatrix(){
  
  return projectionMatrix;
}
