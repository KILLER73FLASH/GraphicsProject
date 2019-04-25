/*
  Filename: Mesh.h
  Author: Joshua Kilhefner
  Course: CSCI 375
  Assignment: A02Mesh
*/

#ifndef MESH_H
#define MESH_H

#include <string>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "ShaderProgram.h"
#include "Camera.h"
#include "Transform.h"
#include "AiScene.h"


class Mesh {
  
public:

  // Initialize the mesh. Generate a VAO and VBO.
  // Use member initializers when possible.
  Mesh ();


  Mesh (const AiScene& object);
  
  // Free allocated resources. Delete generate VAO and VBO.
  ~Mesh ();

  // Append geometry to the mesh.
  // Do NOT buffer the data in a VBO until "prepareVao" is called.
  // It should be possible to add geometry multiple times before preparing the VAO.
  void
  addGeometry (const std::vector<float>& geometry);

  // Set the state of the VAO for rendering.
  // Bind VAO, VBO, buffer the data, etc.
  void
  prepareVao ();

  // Draw the mesh.
  // Determine the appropriate parameters.
  // Enable the shader program, set the model-view uniform, etc.
  void
  draw(ShaderProgram *g_shaderProgram, Camera g_camera);

   Transform
  getWorld () const;

  // Key: "1"
  void
  moveRight (float distance);

  // Key: "2"
  void
  moveUp (float distance);

  void
  moveBack (float distance);

  void
  moveLocal (float distance, const Vector3& localDirection);

  // Key: "3"
  void
  moveWorld (float distance, const Vector3& worldDirection);

  // Key: "4"
  void
  pitch (float angleDegrees);

  // Key: "5"
  void
  yaw (float angleDegrees);

  // Key: "6"
  void
  roll (float angleDegrees);

  void
  rotateLocal (float angleDegrees, const Vector3& axis);

  // Key: "7"
  void
  alignWithWorldY ();

  // Key: "8"
  void
  scaleLocal (float scale);

  void
  scaleLocal (float scaleX, float scaleY, float scaleZ);
    
  // Key: "9"
  void
  scaleWorld (float scale);

  void
  scaleWorld (float scaleX, float scaleY, float scaleZ);

  // Key: "0"
  void
  shearLocalXByYz (float shearY, float shearZ);

  void
  shearLocalYByXz (float shearX, float shearZ);

  void
  shearLocalZByXy (float shearX, float shearY);
  
  //Transform m_world;
private:

  GLuint m_Vao;
  GLuint m_Vbo;
  std::vector<float> vertices;
  Transform m_world;
  
};

#endif
