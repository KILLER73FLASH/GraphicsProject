/*
  Filename: ShaderProgram.cpp
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A02Mesh
  Description: A class that simplifies loading and running OpenGL shaders.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <memory>

#include <GL/glew.h>

#include <glm/gtc/type_ptr.hpp>

#include "ShaderProgram.h"
#include "Matrix4.h"
#include "Transform.h"

ShaderProgram::ShaderProgram ()
    : m_programId (glCreateProgram ()), m_vertexShaderId (0), m_fragmentShaderId (0)
{
}

ShaderProgram::~ShaderProgram ()
{
  // Delete shaders and delete the program object.
  // We assume shaders are not shared among multiple programs.
  glDeleteShader (m_vertexShaderId);
  glDeleteShader (m_fragmentShaderId);
  glDeleteProgram (m_programId);
}

GLint
ShaderProgram::getAttributeLocation (const std::string& attributeName) const
{
  return glGetAttribLocation (m_programId, attributeName.c_str ());
}

GLint
ShaderProgram::getUniformLocation (const std::string& uniformName) const
{
  return glGetUniformLocation (m_programId, uniformName.c_str ());
}

void
ShaderProgram::setUniformMatrix (const std::string& uniform, const Matrix4& value)
{
  GLint location = this->getUniformLocation (uniform);
  glUniformMatrix4fv (location, 1, GL_FALSE, value.data());
}

void
ShaderProgram::createVertexShader (const std::string& vertexShaderFilename)
{
  m_vertexShaderId = glCreateShader (GL_VERTEX_SHADER);
  if (m_vertexShaderId == 0)
  {
    fprintf (stderr, "Failed to create vertex shader object; exiting\n");
    exit (-1);
  }
  compileShader (vertexShaderFilename, m_vertexShaderId);
}

void
ShaderProgram::createFragmentShader (const std::string& fragmentShaderFilename)
{
  m_fragmentShaderId = glCreateShader (GL_FRAGMENT_SHADER);
  if (m_fragmentShaderId == 0)
  {
    fprintf (stderr, "Failed to create fragment shader object; exiting\n");
    exit (-1);
  }
  compileShader (fragmentShaderFilename, m_fragmentShaderId);
}

void
ShaderProgram::compileShader (const std::string& shaderFilename,
			      GLuint shaderId)
{
  std::string sourceCode = readShaderSource (shaderFilename);
  const GLchar* sourceCodePtr = sourceCode.c_str ();
  // One array of char*. Do not need to specify length if null-terminated.
  glShaderSource (shaderId, 1, &sourceCodePtr, nullptr);
  glCompileShader (shaderId);
  GLint isCompiled;
  glGetShaderiv (shaderId, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
    std::string logFile = shaderFilename + ".log";
    writeInfoLog (shaderId, true, logFile);
    fprintf (stderr, "Compilation error for %s -- see log; exiting\n",
	     shaderFilename.c_str ());
    exit (-1);
  }
  glAttachShader (m_programId, shaderId);
}

void
ShaderProgram::link () const
{
  fprintf (stdout, "Linking shader program %d\n", m_programId);
  glLinkProgram (m_programId);
  GLint isLinked;
  glGetProgramiv (m_programId, GL_LINK_STATUS, &isLinked);
  if (isLinked == GL_FALSE)
  {
    writeInfoLog (0, false, "Link.log");
    fprintf (stderr, "Link error -- see log\n");
    exit (-1);
  }
  // After linking, the shader objects no longer need to be attached.
  // A shader won't be deleted until it is detached.
  glDetachShader (m_programId, m_vertexShaderId);
  glDetachShader (m_programId, m_fragmentShaderId);
}

void
ShaderProgram::enable ()
{
  glUseProgram (m_programId);
}

void
ShaderProgram::disable ()
{
  glUseProgram (0);
}

std::string
ShaderProgram::readShaderSource (const std::string& filename) const
{
  std::ifstream inFile (filename);
  if (!inFile)
  {
    fprintf (stderr, "File %s does not exist; exiting\n", filename.c_str ());
    exit (-1);
  }
  std::string fileString
    { std::istreambuf_iterator<char> (inFile), std::istreambuf_iterator<char> () };

  return fileString;
}

void
ShaderProgram::writeInfoLog (GLuint shaderId, bool isShader,
			     const std::string& logFilename) const
{
  GLint infoLogLength = 0;
  if (isShader)
    glGetShaderiv (shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
  else
    glGetProgramiv (m_programId, GL_INFO_LOG_LENGTH, &infoLogLength);
  if (infoLogLength > 0)
  {
    // Avoid the overhead of vector<char>, which has to initialize
    //   each char.
    std::unique_ptr<char[]> infoLog (new char[infoLogLength]);
    if (isShader)
      glGetShaderInfoLog (shaderId, infoLogLength, nullptr, infoLog.get ());
    else
      glGetProgramInfoLog (m_programId, infoLogLength, nullptr, infoLog.get ());
    std::ofstream logStream (logFilename);
    logStream << infoLog.get () << std::endl;
  }
}
