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

#include "KeyBuffer.h"

// Initialize the buffer with all keys set up
// The size of the buffer should be "GLFW_KEY_LAST + 1"
KeyBuffer::KeyBuffer (){
  for (int i = 0; i < GLFW_KEY_LAST + 1; i++)
    keyList[i] = false;   
}

// Record that "key" is down
void
KeyBuffer::setKeyDown (int key){
  keyList[key] = true;
}

// Record that all keys are up
void
KeyBuffer::reset (){
  for (int i = 0; i < GLFW_KEY_LAST + 1; i++)
    keyList[i] = false;
}

// Record that "key" is up
void
KeyBuffer::setKeyUp (int key){
  keyList[key] = false;
}

// Return true if "key" is down, false o/w
bool
KeyBuffer::isKeyDown (int key) const{
  return keyList[key];
}
