#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <memory>
#include <vector>
#include <iomanip>

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

#include "MouseBuffer.h"

// Initialize the buffer with all buttons set up
MouseBuffer::MouseBuffer (){
  xCoord = 0;
  yCoord = 0;
  rightKey = false;
  leftKey = false;
}

// Record that "key" is down
void
MouseBuffer::setRightKeyDown (int key){
  rightKey = true;
}

void
MouseBuffer::setLeftKeyDown (int key) {
  leftKey = true;
}

// Record that all keys are up
void
MouseBuffer::reset (){
  rightKey = false;
  leftKey = false;
}

// Record that "key" is up
void
MouseBuffer::setRightKeyUp (int key){
  rightKey = false;
}

void
MouseBuffer::setLeftKeyUp (int key) {
  leftKey = false;
}

// Return true if "key" is down, false o/w
bool
MouseBuffer::isRightKeyDown (int key) const{
  return rightKey;
}

bool
MouseBuffer::isLeftKeyDown (int key) const {
  return leftKey;
}

double
MouseBuffer::getX() {
  return xCoord;
}

double
MouseBuffer::getY() {
  return yCoord;
}

void
MouseBuffer::setX(double x) {
  xCoord = x;
}

void
MouseBuffer::setY(double y) {
  yCoord = y;
}
