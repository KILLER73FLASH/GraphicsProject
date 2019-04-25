/*
  File: Scene.cpp
  Author: Chad Hogg
  Course: CSCI375
  Assignment: A08Scene
  Description: A collection of all Meshes in the world.
*/
#include "Scene.h"
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

// Initialize this Scene.
// You may want to have multiple ctors.
// Determine sensible parameters. 
Scene::Scene () {
  current = 0;
}

// Remove all meshes from this Scene.
// Resource management is up to you (whether you release
//   mesh resources (VAOs, VBOs, IBOs, etc.).
Scene::~Scene () {
  meshes.clear();
  names.clear();
  current = 0;
}

// Prevent Scene-s from being copied and copy assigned!
//DECIDE HOW TO DO THIS

// Add Mesh "mesh" with name "meshName" to this Scene. 
// Return type is up to you
void
Scene::add (const std::string& meshName, Mesh* mesh) {
  meshes.push_back(mesh);
  names.push_back(meshName);
}

// Remove the mesh named "meshName" from this Scene. 
// Return type is up to you.
// Whether you destroy the mesh is up to you.
void
Scene::remove (const std::string& meshName) {
  auto iter = std::find(names.begin(), names.end(), meshName);

  if (iter != names.end()) {
    current = std::distance(names.begin(), iter);
    names.erase(names.begin() + current);
    meshes.erase(meshes.begin() + current);
  }
}

// Remove all meshes from this Scene.
// Whether you destroy them is up to you.
void
Scene::clear () {
  meshes.clear();
  names.clear();
  current = 0;
}

// Set the active mesh to the mesh named "meshName".
// The active mesh is the one affected by transforms. 
void
Scene::setActiveMesh (const std::string& meshName) {
  auto iter = std::find(names.begin(), names.end(), meshName);

  if (iter != names.end()) {
    current = std::distance(names.begin(), iter);
  }
}

// Return the active mesh. 
Mesh*
Scene::getActiveMesh () {
  return meshes[current];
}

// Draw all meshes in this Scene.
// Determine sensible parameters. 
void
Scene::draw (ShaderProgram *shaderProgram, Camera cam) {
  for (unsigned int i =0; i < meshes.size(); i++)
    meshes[i]->draw(shaderProgram, cam);
}

// Changes the active mesh to the next one.
// Switch to first if you were at last.
void
Scene::activateNextMesh () {
  if (current == (meshes.size() - 1))
    current = 0;
  else
    current++;
}

// Changes the active mesh to the previous one.
// Switch to last if you were at first.
void
Scene::activatePreviousMesh () {
  if (current == 0)
    current = meshes.size() - 1;
  else
    current--;
}
