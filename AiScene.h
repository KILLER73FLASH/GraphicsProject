/*
  Filename: AiScene.h
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A06Transform
  Description: A class that simplifies importing scenes with the AssImp library.
*/

#ifndef AISCENE_H
#define AISCENE_H

#include <string>
#include <vector>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>

// Make sure you add "-lassimp" to your Makefile!

class AiScene
{
public:
  AiScene (const std::string& fileName);

  // Nothing to do as Importer dtor cleans up!
  ~AiScene () = default;

  // Disable default copy ctor and copy assignment.
  AiScene (const AiScene&) = delete;
  AiScene& operator= (const AiScene&) = delete;
  
  // Read vertex data for mesh number "meshNum".
  // A scene may consist of multiple meshes. 
  std::vector<float>
  readVertexData (unsigned meshNum) const;

  // You may find other methods useful...
  
private:
  // Importer dtor destroys the scene!
  Assimp::Importer m_importer;
  // Don't really need to hold this as the Importer can obtain it
  //   with GetScene. 
  const aiScene* m_scene;
};

#endif//AISCENE_H
