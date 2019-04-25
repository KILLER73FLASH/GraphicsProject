
#ifndef MOUSEBUFFER_H
#define MOUSEBUFFER_H

#include <string>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "ShaderProgram.h"
#include <GLFW/glfw3.h>

class MouseBuffer {
public:
  
  MouseBuffer ();
  
  // Record that "key" is down
  void
  setRightKeyDown (int key);

  void
  setLeftKeyDown (int ky);

  // Record that all keys are up
  void
  reset ();
  
  // Record that "key" is up
  void
  setRightKeyUp (int key);

  void
  setLeftKeyUp (int key);
  
  // Return true if "key" is down, false o/w
  bool
  isRightKeyDown (int key) const;

  bool
  isLeftKeyDown (int Key) const;

  double
    getX();

  double
    getY();

  void
    setX(double x);

  void
    setY(double y);
  
  bool rightKey;
  bool leftKey;
  double xCoord;
  double yCoord;
};

#endif
