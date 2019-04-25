#version 330
/*
  Filename: Vec3.vert
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A02Mesh
  Description: Transforms vertices from 3-D world coordinates to 4-D clip
    space coordinates.
*/

// First, we specify the attributes that are inputs to the shader program
// These were specified in Main.cpp
// Positions are the first attributes, and they are 2-D vectors (X, Y)
layout (location = 0) in vec3 aPosition;
// Colors are the second attributes, and they are 3-D vectors (R, G, B)
layout (location = 1) in vec3 aColor;

// Second, we specify uniform inputs that are the same for all vertices in a
//   single draw command
// Matrix to transform world space to eye space
uniform mat4 uModelView;
// Matrix to transform eye space to clip space
uniform mat4 uProjection;

// Finally, we specify any additional outputs our shader produces
// We want to output a color, which is a 3-D vector (R, G, B)
out vec3 vColor;

/*********************************************************/

void
main ()
{
  // Every vertex shader must write gl_Position
  // It is a 4-D vector (X, Y, Z, W)
  // Transform the vertex from world space to clip space
  gl_Position = uProjection * uModelView * vec4 (aPosition, 1.0);
  // Just pass along the color unchanged to the next stage
  vColor = aColor;
}
