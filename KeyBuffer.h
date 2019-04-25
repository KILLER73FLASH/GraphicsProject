
#ifndef KEYBUFFER_H
#define KEYBUFFER_H

#include <string>

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "ShaderProgram.h"
#include <GLFW/glfw3.h>

class KeyBuffer {
public:
// Initialize the buffer with all keys set up
// The size of the buffer should be "GLFW_KEY_LAST + 1"
KeyBuffer ();

// Record that "key" is down
void
setKeyDown (int key);

// Record that all keys are up
void
reset ();

// Record that "key" is up
void
setKeyUp (int key);

// Return true if "key" is down, false o/w
bool
isKeyDown (int key) const;


bool keyList[GLFW_KEY_LAST +1];
};

#endif
