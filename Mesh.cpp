/*
  Filename: Mesh.cpp
  Author: Joshua Kilhefner
  Course: CSCI 375
  Assignment: A02Mesh
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <memory>
#include <vector>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Transform.h"
#include "AiScene.h"
#include "Matrix4.h"

Mesh::Mesh ()
  : m_Vao(0), m_Vbo(0)
    
  {
    glGenVertexArrays (1, &m_Vao);
    glGenBuffers (1, &m_Vbo);
}
Mesh::Mesh(const AiScene& object){
  addGeometry(object.readVertexData(0));
  glGenVertexArrays (1, &m_Vao);
  glGenBuffers (1, &m_Vbo);
}

Mesh::~Mesh ()
{
  glDeleteVertexArrays(1, &m_Vao);
  glDeleteBuffers(1, &m_Vbo);
}

void
Mesh::addGeometry (const std::vector<float>& geometry)
{
  vertices.insert(vertices.end(), geometry.begin(), geometry.end());
}

void
Mesh::prepareVao ()
{
  //pointers need updated for every other
  //add this after it works initially
  const GLint POSITION_ATTRIB_INDEX = 0;
  const GLint COLOR_ATTRIB_INDEX = 1;
  
  glBindVertexArray (m_Vao);
  glBindBuffer (GL_ARRAY_BUFFER, m_Vbo);

  glBufferData (GL_ARRAY_BUFFER, vertices.size () * sizeof(float), vertices.data(), GL_STATIC_DRAW);
  glEnableVertexAttribArray (POSITION_ATTRIB_INDEX);
  glVertexAttribPointer (POSITION_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), reinterpret_cast<void*> (0));
  glEnableVertexAttribArray (COLOR_ATTRIB_INDEX);
  glVertexAttribPointer (COLOR_ATTRIB_INDEX, 3, GL_FLOAT, GL_FALSE, (6 * sizeof(float)), reinterpret_cast<void*> (3 * sizeof(float)));
  glBindVertexArray (0);
}

void
Mesh::draw(ShaderProgram *g_shaderProgram, Camera g_camera)
{
  Transform modelView = g_camera.getViewMatrix();
  modelView.combine(m_world);
  g_shaderProgram->enable();
  g_shaderProgram->setUniformMatrix ("uModelView", modelView.getTransform());
  
  glBindVertexArray (m_Vao);
  glDrawArrays (GL_TRIANGLES, 0, (vertices.size() / 6));
  glBindVertexArray (0);

  g_shaderProgram->disable();
  
}

Transform
Mesh::getWorld () const{
   return m_world;
}

// Key: "1"
void
Mesh::moveRight (float distance) {
  m_world.moveRight(distance);
}

// Key: "2"
void
Mesh::moveUp (float distance) {
  m_world.moveUp(distance);
}

void
Mesh::moveBack (float distance) {
  m_world.moveBack(distance);
}

void
Mesh::moveLocal (float distance, const Vector3& localDirection) {
  m_world.moveLocal(distance, localDirection);
}

// Key: "3"
void
Mesh::moveWorld (float distance, const Vector3& worldDirection) {
  m_world.moveWorld(distance, worldDirection);
}

// Key: "4"
void
Mesh::pitch (float angleDegrees) {
  m_world.pitch(angleDegrees);
}

// Key: "5"
void
Mesh::yaw (float angleDegrees) {
  m_world.yaw(angleDegrees);
}

// Key: "6"
void
Mesh::roll (float angleDegrees) {
  m_world.roll(angleDegrees);
}

void
Mesh::rotateLocal (float angleDegrees, const Vector3& axis) {
  m_world.rotateLocal(angleDegrees, axis);
}

// Key: "7"
void
Mesh::alignWithWorldY () {
  m_world.alignWithWorldY();
}

// Key: "8"
void
Mesh::scaleLocal (float scale) {
  m_world.scaleLocal(scale);
}

void
Mesh::scaleLocal (float scaleX, float scaleY, float scaleZ) {
  m_world.scaleLocal(scaleX, scaleY, scaleZ);
}

// Key: "9"
void
Mesh::scaleWorld (float scale) {
  m_world.scaleWorld(scale);
}

void
Mesh::scaleWorld (float scaleX, float scaleY, float scaleZ) {
  m_world.scaleWorld(scaleX, scaleY, scaleZ);
}

// Key: "0"
void
Mesh::shearLocalXByYz (float shearY, float shearZ) {
  m_world.shearLocalXByYz(shearY, shearZ);
}

void
Mesh::shearLocalYByXz (float shearX, float shearZ) {
  m_world.shearLocalYByXz(shearX, shearZ);
}

void
  Mesh::shearLocalZByXy (float shearX, float shearY) {
  m_world.shearLocalZByXy(shearX, shearY);
}
