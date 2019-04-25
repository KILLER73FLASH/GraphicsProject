/*
  Filename: AiScene.cpp
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A06Transform
  Description: A class that simplifies importing scenes with the AssImp library.
*/

#include <cstdio>
#include <cstdlib>

#include <assimp/postprocess.h>

#include "AiScene.h"

AiScene::AiScene (const std::string& fileName)
{
  // Meshes may not consist of triangles, so have the importer
  //   triangulate.
  // Meshes may not have normals, so if they don't, have the importer
  //   generate them. 
  // Vertices may not be unique, so have them joined if they are the same.
  unsigned flags = aiProcess_Triangulate | aiProcess_GenSmoothNormals
      | aiProcess_JoinIdenticalVertices;
  m_scene = m_importer.ReadFile (fileName, flags);
  if (m_scene == nullptr)
  {
    auto error = m_importer.GetErrorString ();
    fprintf (stderr, "Failed to load model %s with error '%s'. Exiting\n",
	     fileName.c_str (), error);
    exit (-1);
  }
}

std::vector<float>
AiScene::readVertexData (unsigned meshNum) const
{
  // Get the correct mesh object
  const aiMesh* mesh = m_scene->mMeshes[meshNum];
  // Container for holding vertex data
  std::vector<float> vertexData;
  
  // Go through array of faces
  for (unsigned faceNum = 0; faceNum < mesh->mNumFaces; ++faceNum)
  {
    // Get a face
    const aiFace& face = mesh->mFaces[faceNum];
    // Faces are triangles, so three indices
    const unsigned INDICES_PER_FACE = 3;
    // Go through the 3 indices
    for (unsigned indexNum = 0; indexNum < INDICES_PER_FACE; ++indexNum)
    {
      // Get vertex number at location "indexNum"
      // Indexing is used so data isn't duplicated
      auto vertexNum = face.mIndices[indexNum];
      aiVector3D position = mesh->mVertices[vertexNum];
      // TODO: Put the position in vertexData
      vertexData.push_back(position.x);
      vertexData.push_back(position.y);
      vertexData.push_back(position.z);
      aiVector3D normal = mesh->mNormals[vertexNum];
      // TODO: Put the normal in vertexData
      vertexData.push_back(normal.x);
      vertexData.push_back(normal.y);
      vertexData.push_back(normal.z);
    }
  }
  return vertexData;
}
