#version 330
/*
  Filename: Vec3.frag
  Authors: Gary M. Zoppetti, Ph.D. & Chad Hogg
  Course: CSCI375
  Assignment: A02Mesh
  Description: A fragment shader that simply copies its input to its output
    with an alpha value.
*/

// First, the inputs from earlier in the pipeline
// Computed vertex color outputted by the vertex shader
// Type and name must be an exact match
// This color was already computed by interpolating the colors of the vertices
//   that define this fragment. (R, G, B)
in  vec3 vColor;

// Second, the outputs the shader produces
// We output a color with an alpha channel (R, G, B, A)
out vec4 fColor;

void
main ()
{
  // Output fragment color, with red, green, blue, and alpha components (RGBA)
  fColor = vec4 (vColor, 1.0);
}
