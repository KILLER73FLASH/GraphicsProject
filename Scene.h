/*
  File: Scene.h
  Author: Chad Hogg
  Course: CSCI375
  Assignment: A08Scene
  Description: A collection of all Meshes in the world.
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>

#include "Matrix3.h"
#include "Matrix4.h"
#include <glm/mat4x4.hpp>
#include "Vector3.h"
#include "Transform.h"
#include "Mesh.h"

#include <string>
#include <cstring>
#include <vector>

#ifndef SCENE_H
#define SCENE_H

class Scene
{
 public:
  // Initialize this Scene.
  // You may want to have multiple ctors.
  // Determine sensible parameters. 
  Scene (/*std::vector<Mesh*> objects*/);

  // Remove all meshes from this Scene.
  // Resource management is up to you (whether you release
  //   mesh resources (VAOs, VBOs, IBOs, etc.).
  ~Scene ();

  // Prevent Scene-s from being copied and copy assigned!
  //DECIDE HOW TO DO THIS

  // Add Mesh "mesh" with name "meshName" to this Scene. 
  // Return type is up to you
  void
  add (const std::string& meshName, Mesh* mesh);

  // Remove the mesh named "meshName" from this Scene. 
  // Return type is up to you.
  // Whether you destroy the mesh is up to you.
  void
  remove (const std::string& meshName);

  // Remove all meshes from this Scene.
  // Whether you destroy them is up to you.
  void
  clear ();

  // Set the active mesh to the mesh named "meshName".
  // The active mesh is the one affected by transforms. 
  void
  setActiveMesh (const std::string& meshName);

  // Return the active mesh. 
  Mesh*
  getActiveMesh ();

  // Draw all meshes in this Scene.
  // Determine sensible parameters. 
  void
  draw (ShaderProgram *shaderProgram, Camera cam);

  // Changes the active mesh to the next one.
  // Switch to first if you were at last.
  void
  activateNextMesh ();

  // Changes the active mesh to the previous one.
  // Switch to last if you were at first.
  void
  activatePreviousMesh ();


 private:
  //TODO: Some data members will be needed
  std::vector<Mesh*> meshes;
  std::vector<std::string> names;
  unsigned int current;

};

#endif//SCENE_H
