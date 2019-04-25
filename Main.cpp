/* 
  Filename: Main.cpp
  Authors: Gary M. Zoppetti & Chad Hogg & Joshua Kilhefner
  Course: CSCI375
  Assignment: A02Mesh
  Description: A beginning OpenGL program that uses OpenGL 3.3 to draw a 
    triangle. The triangle is now specified with 3D coordinates.
   A virtual camera has been defined and limited key-based movement has been 
    added.
*/

/******************************************************************/
// System includes
#include <cstdio>
#include <cstdlib>
#include <vector>

// Use GLEW so we can access the latest OpenGL functionality
// Always include GLEW before GLFW!
#include <GL/glew.h>
// Use GLFW so we can create windows and handle events in a
//   platform-independent way
#include <GLFW/glfw3.h>

// GLM is a header-only library, so we do not need to link to it
// It provides matrix classes and mathematical functions
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
// Need for "value_ptr", which allows us to get a pointer from a matrix
#include <glm/gtc/type_ptr.hpp>
// Transforms like lookat, perspective, rotate, scale, translate
#include <glm/gtc/matrix_transform.hpp>

/******************************************************************/
// Local includes
#include "ShaderProgram.h"
#include "Mesh.h"
#include "Camera.h"
#include "Vector3.h"
#include "Matrix3.h"
#include "KeyBuffer.h"
#include "MouseBuffer.h"
#include "Scene.h"

/******************************************************************/
// Type declarations/globals variables/prototypes

// We use one VAO for each object we draw
//std::vector<Mesh*> g_mesh;
Scene g_meshes;

// Need a shader program to transform and light the primitives
ShaderProgram* g_shaderProgram;
Camera g_camera;
KeyBuffer keyList;
MouseBuffer movement;
/******************************************************************/

// Initializes all of the libraries.
void
init (GLFWwindow*& window);

// Initializes the GLFW library -- should only be called by init().
void
initGlfw ();

// Initializes the GLEW library -- should only be called by init().
void
initGlew ();

// Creates and initializes the window -- should only be called by init().
void
initWindow (GLFWwindow*& window);

// Re-renders the window -- should be called when size changes.
void
resetViewport (GLFWwindow* window, int width, int height);

// Creates the geometric objects -- should only be called by init().
void
initScene ();

// Sets up our shader programs -- should only be called by init().
void
initShaders ();

// Initializes the camera -- should only be called by init().
void
initCamera ();

// Move geometric objects around using game logic.
void
updateScene (double time);

// Draws the scene onto the window.
void
drawScene (GLFWwindow* window);

// Respond to any user input.
void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
	     int modifiers);

// Clean up as program exits.
void
releaseGlResources ();

// Prints an error from GLFW.
void
outputGlfwError (int error, const char* description);

// Key buffer thing
void
processKeys();

// Cursor position
void
cursorPosition(GLFWwindow* window, double xCoord, double yCoord);

// Mouse buttons
void
mouseButtons(GLFWwindow* window, int button, int action, int mods);
/******************************************************************/

int
main (int argc, char* argv[])
{
  GLFWwindow* window;
  init (window);

  // Game/render loop
  double previousTime = glfwGetTime ();
  while (!glfwWindowShouldClose (window))
  {
    double currentTime = glfwGetTime ();
    // Compute frame times, which we can use later for frame rate computation,
    //   animation, and physics.
    double deltaTime = currentTime - previousTime;
    previousTime = currentTime;
    updateScene (deltaTime);
    drawScene (window);
    // Process events in the event queue, which results in callbacks
    //   being invoked.
    glfwPollEvents ();
    processKeys();
  }

  releaseGlResources ();
  // Destroying the window destroys the OpenGL context
  glfwDestroyWindow (window);
  glfwTerminate ();

  return EXIT_SUCCESS;
}

/******************************************************************/

void
init (GLFWwindow*& window)
{
  // Always initialize GLFW before GLEW
  initGlfw ();
  initWindow (window);
  initGlew ();
  initShaders ();
  initCamera ();
  initScene ();
}

/******************************************************************/

void
initGlfw ()
{
  glfwSetErrorCallback (outputGlfwError);
  if (!glfwInit ())
  {
    fprintf (stderr, "Failed to init GLFW -- exiting\n");
    exit (EXIT_FAILURE);
  }
}

/******************************************************************/

void
initWindow (GLFWwindow*& window)
{
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
  // Necessary on MacOS! Was needed in one case on Linux too.
  glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
  window = glfwCreateWindow (1200, 900, "OpenGL Engine", nullptr, nullptr);
  if (window == nullptr)
  {
    fprintf (stderr, "Failed to init the window -- exiting\n");
    glfwTerminate ();
    exit (EXIT_FAILURE);
  }
  glfwSetWindowPos (window, 200, 100);

  glfwMakeContextCurrent (window);
  // Swap buffers after 1 frame
  glfwSwapInterval (1);
  glfwSetKeyCallback (window, recordKeys);
  // Mouse button press here!
  glfwSetMouseButtonCallback(window, mouseButtons);
  // Mouse cursor here a well
  glfwSetCursorPosCallback(window, cursorPosition);
  glfwSetFramebufferSizeCallback (window, resetViewport);

  // Specify background color
  glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
  // Enable depth testing so occluded surfaces aren't drawn
  glEnable (GL_DEPTH_TEST);
  // Enable the culling of back-facing triangles
  // A triangle must be wound CCW in window coordinates to be front facing
  // If it is wound CW it is back facing and will NOT be displayed!
  glEnable (GL_CULL_FACE);
  // The next two setting are default, but we'll be explicit.
  glFrontFace (GL_CCW);
  glCullFace (GL_BACK);
  // Set initial viewport size
  int width, height;
  glfwGetFramebufferSize (window, &width, &height);
  glViewport (0, 0, width, height);
}

/******************************************************************/

void
initGlew ()
{
  GLenum status = glewInit ();
  if (status != GLEW_OK)
  {
    fprintf (stderr, "Failed to initialize GLEW -- exiting"
	     " (%s).\n",
	     glewGetErrorString (status));
    exit (EXIT_FAILURE);
  }
  const GLubyte* version = glewGetString (GLEW_VERSION);
  fprintf (stderr, "Using GLEW version %s.\n", version);
  version = glGetString (GL_VERSION);
  fprintf (stderr, "Using OpenGL version %s\n", version);
}

/******************************************************************/

void
resetViewport (GLFWwindow* window, int width, int height)
{
  // Render into entire window
  // Origin for window coordinates is lower-left of window
  glViewport (0, 0, width, height);
}

/******************************************************************/

void
initScene ()
{
  Mesh* cube = new Mesh();
  //g_mesh.push_back(cube);
  g_meshes.add("Cube", cube);
  std::vector<float> cubeVertices {
				   // Front Face
				   5.0f, -5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   -5.0f, 5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   -5.0f, -5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   -5.0f, 5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   5.0f, -5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   5.0f, 5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   // Right Face
				   5.0f, 5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   5.0f, -5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   5.0f, 5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f,
				   5.0f, 5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f,
				   5.0f, -5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   5.0f, -5.0f, -10.0f,
				   1.0f, 0.0f, 0.0,
				   // Back Face
				   5.0f, -5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f,
				   -5.0f, -5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f,
				   -5.0f, 5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f,
				   -5.0f, 5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f,
				   5.0f, 5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f,
				   5.0f, -5.0f, -10.0f,
				   1.0f, 0.0f, 0.0,
				   // Left Face
				   -5.0f, 5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f,
				   -5.0f, -5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f,
				   -5.0f, 5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   -5.0f, 5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   -5.0f, -5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f,
				   -5.0f, -5.0f, 0.0f,
				   1.0f, 0.0f, 0.0,
				   // Top Face
				   -5.0f, 5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f,
				   -5.0f, 5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   5.0f, 5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f,
				   5.0f, 5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f,
				   -5.0f, 5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   5.0f, 5.0f, 0.0f,
				   1.0f, 0.0f, 0.0,
				   // Bottom Face
				   -5.0f, -5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   -5.0f, -5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f,
				   5.0f, -5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   5.0f, -5.0f, 0.0f,
				   1.0f, 0.0f, 0.0f,
				   -5.0f, -5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f,
				   5.0f, -5.0f, -10.0f,
				   1.0f, 0.0f, 0.0f
  };
  cube->addGeometry(cubeVertices);
  cube->prepareVao();
  
  Mesh* pyramid = new Mesh();
  //g_mesh.push_back(pyramid);
  g_meshes.add("Pyramid", pyramid);
  std::vector<float> pyramidVertices {
				      // Base
				      6.0f, 5.0f, -11.0f,
				      1.0f, 1.0f, 1.0f,
				      -6.0f, 5.0f, 1.0f,
				      1.0f, 1.0f, 1.0f,
				      -6.0f, 5.0f, -11.0f,
				      1.0f, 1.0f, 1.0f,
				      6.0f, 5.0f, -11.0f,
				      1.0f, 1.0f, 1.0f,
				      6.0f, 5.0f, 1.0f,
				      1.0f, 1.0f, 1.0f,
				      -6.0f, 5.0f, 1.0f,
				      1.0f, 1.0f, 1.0f,
				      // Left
				      -6.0f, 5.0f, -11.0f,
				      1.0f, 1.0f, 1.0f,
				      -6.0f, 5.0f, 1.0f,
				      1.0f, 1.0f, 1.0f,
				      0.0f, 8.0f, -5.0f,
				      1.0f, 1.0f, 1.0f,
				      // Right
				      6.0f, 5.0f, 1.0f,
				      1.0f, 1.0f, 1.0f,
				      6.0f, 5.0f, -11.0f,
				      1.0f, 1.0f, 1.0f,
				      0.0f, 8.0f, -5.0f,
				      1.0f, 1.0f, 1.0f,
				      // Back
				      6.0f, 5.0f, -11.0f,
				      1.0f, 1.0f, 1.0f,
				      -6.0f, 5.0f, -11.0f,
				      1.0f, 1.0f, 1.0f,
				      0.0f, 8.0f, -5.0f,
				      1.0f, 1.0f, 1.0f,
				      // Front
				      -6.0f, 5.0f, 1.0f,
				      1.0f, 1.0f, 1.0f,
				      6.0f, 5.0f, 1.0f,
				      1.0f, 1.0f, 1.0f,
				      0.0f, 8.0f, -5.0f,
				      1.0f, 1.0f, 1.0f
  };
  pyramid->addGeometry(pyramidVertices);
  pyramid->prepareVao();
  AiScene firstObject ("computer_science_building.obj");
  Mesh* CSBuilding = new Mesh(firstObject);
  g_meshes.add("CSBuilding", CSBuilding);
  CSBuilding->prepareVao();
  AiScene secondObject ("bear.obj");
  Mesh* bear = new Mesh(secondObject);
  g_meshes.add("bear", bear);
  bear->prepareVao();
}

/******************************************************************/

void
initShaders ()
{
  // Create shader programs, which consist of linked shaders.
  // No need to use the program until we draw or set uniform variables.
  g_shaderProgram = new ShaderProgram ();
  g_shaderProgram->createVertexShader ("Vec3Norm.vert"); //Change to Vec3Norm.vert
  g_shaderProgram->createFragmentShader ("Vec3.frag");
  g_shaderProgram->link ();
}

/******************************************************************/

void
initCamera ()
{
  Vector3 eyePoint = Vector3 (0, 0, 0);
  Vector3 localBackDirection = Vector3 (0, 0, 1);
  // Define the projection, which will remain constant
  double verticalFov = (50.0);
  double aspectRatio = 1200.0 / 900;
  // Near plane
  double nearZ = 0.01;
  // Far plane
  double farZ = 40.0;
  g_camera = Camera(eyePoint, localBackDirection, nearZ, farZ, aspectRatio, verticalFov);
  g_camera.setProjectionSymmetricPerspective(verticalFov, aspectRatio, nearZ,
					  farZ);
  // Enable shader program so we can set uniforms
  g_shaderProgram->enable ();
  g_shaderProgram->setUniformMatrix ("uProjection", g_camera.getProjectionMatrix());
  // Define the camera's coordinate system
  g_camera.setPosition(Vector3 (0, 0, 15.0f));
  //g_camera.at = glm::vec3 (0, 0, 0);
  //g_camera.up = glm::vec3 (0, 1, 0);
}

/******************************************************************/

void
updateScene (double time)
{
  // No updates in this simple program.
}

/******************************************************************/

void
drawScene (GLFWwindow* window)
{
   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   // Create view matrix
   //glm::mat4 modelView();
   /*for (auto i = g_mesh.begin(); i < g_mesh.end(); i++){
     (*i)->draw(g_shaderProgram, g_camera);
     }*/
   g_meshes.draw(g_shaderProgram, g_camera);
  
  // Swap the front and back buffers.
  // We draw to the back buffer, which is then swapped with the front
  //   for display.
  glfwSwapBuffers (window);
}


/******************************************************************/

void
recordKeys (GLFWwindow* window, int key, int scanCode, int action,
	     int modifiers)
{
  // Actions are GLFW_PRESS, GLFW_RELEASE, and GLFW_REPEAT
  // Exit if ESC is pressed
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
  {
    glfwSetWindowShouldClose (window, GL_TRUE);
    return;
  }
  if (key == GLFW_KEY_MINUS && action == GLFW_PRESS)
    g_meshes.activatePreviousMesh();
  if (key == GLFW_KEY_EQUAL && action == GLFW_PRESS)
    g_meshes.activateNextMesh();
  /*if (key == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    g_camera.setPosition(Vector3 (0, 0, 15.0f));
  if (key == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
  g_camera.setPosition(Vector3 (0, 0, 15.0f));*/

  
  if (action == GLFW_PRESS)
    keyList.setKeyDown(key);
  if (action == GLFW_RELEASE)
    keyList.setKeyUp(key);
  
}

/******************************************************************/

void
releaseGlResources ()
{
  // Delete OpenGL resources, particularly important if program will
  //   continue running
  delete g_shaderProgram;
  /*for (auto i = g_mesh.begin(); i < g_mesh.end(); i++) {
    delete *i;
    }*/
  g_meshes.clear();
  
}

/******************************************************************/

void
outputGlfwError (int error, const char* description)
{
  fprintf (stderr, "GLFW error: %s, code %d\n", description, error);
}

/******************************************************************/

void
processKeys() {

  // Translate camera/eye point using WASD keys
  //const float MOVEMENT_DELTA = 1.0f;
  if (keyList.isKeyDown(GLFW_KEY_W))
    g_camera.moveBack(-0.1f);
  if (keyList.isKeyDown(GLFW_KEY_S))
    g_camera.moveBack(0.1f);
  if (keyList.isKeyDown(GLFW_KEY_A))
    g_camera.moveRight(-0.1f);
  if (keyList.isKeyDown(GLFW_KEY_D))
    g_camera.moveRight(0.1f);
  if (keyList.isKeyDown(GLFW_KEY_C))
    g_camera.moveUp(-0.1f);
  if (keyList.isKeyDown(GLFW_KEY_F))
    g_camera.moveUp(0.1f);
  if (keyList.isKeyDown(GLFW_KEY_J))
    g_meshes.getActiveMesh()->yaw(0.5f);
  if (keyList.isKeyDown(GLFW_KEY_L))
    g_meshes.getActiveMesh()->yaw(-0.5f);
  if (keyList.isKeyDown(GLFW_KEY_K))
    g_meshes.getActiveMesh()->pitch(-0.5f);
  if (keyList.isKeyDown(GLFW_KEY_I))
    g_meshes.getActiveMesh()->pitch(0.5f);
  if (keyList.isKeyDown(GLFW_KEY_N))
    g_meshes.getActiveMesh()->roll(-0.5f);
  if (keyList.isKeyDown(GLFW_KEY_M))
    g_meshes.getActiveMesh()->roll(0.5f);
  if (keyList.isKeyDown(GLFW_KEY_R))
    g_camera.setPosition(Vector3 (0, 0, 15.0f));
  if (keyList.isKeyDown(GLFW_KEY_KP_1)) 
    g_meshes.getActiveMesh()->moveRight(0.1f);
  if (keyList.isKeyDown(GLFW_KEY_KP_2))
    g_meshes.getActiveMesh()->moveRight(-0.1f);
  if (keyList.isKeyDown(GLFW_KEY_KP_3))
    g_meshes.getActiveMesh()->moveUp(0.1f);
  if (keyList.isKeyDown(GLFW_KEY_KP_4))
    g_meshes.getActiveMesh()->moveUp(-0.1f);
  if (keyList.isKeyDown(GLFW_KEY_KP_5))
    g_meshes.getActiveMesh()->moveBack(0.1f);
  if (keyList.isKeyDown(GLFW_KEY_KP_6))
    g_meshes.getActiveMesh()->moveBack(-0.1f);
  if (keyList.isKeyDown(GLFW_KEY_KP_7))
    g_meshes.getActiveMesh()->scaleLocal(1.01);
  if (keyList.isKeyDown(GLFW_KEY_KP_8))
    g_meshes.getActiveMesh()->scaleLocal(0.99);
  if (keyList.isKeyDown(GLFW_KEY_P)) {
    g_camera.setProjectionSymmetricPerspective(50.0, (1200.0 / 900), 0.01, 40.0);
    g_shaderProgram->enable ();
    g_shaderProgram->setUniformMatrix ("uProjection", g_camera.getProjectionMatrix());
  }
  if (keyList.isKeyDown(GLFW_KEY_LEFT_BRACKET)) {
    g_camera.setProjectionAsymmetricPerspective(-7, 5, -5, 3, 5, 40);
    g_shaderProgram->enable ();
    g_shaderProgram->setUniformMatrix ("uProjection", g_camera.getProjectionMatrix());
  }
  if (keyList.isKeyDown(GLFW_KEY_O)) {
    g_camera.setProjectionOrthographic(-10, 10, -10, 10, 5, 40);
    g_shaderProgram->enable ();
    g_shaderProgram->setUniformMatrix ("uProjection", g_camera.getProjectionMatrix());
  }  
		      
}

/**************************************************************************/
// Mouse Buffer methods
/**************************************************************************/

void
cursorPosition(GLFWwindow* window, double xCoord, double yCoord) {
  if (movement.isLeftKeyDown(GLFW_MOUSE_BUTTON_LEFT)){
    if (xCoord < movement.getX())
      g_camera.yaw((movement.getX() - xCoord) / 5);
    if (xCoord > movement.getX())
      g_camera.yaw((movement.getX() - xCoord) / 5);
    if (yCoord < movement.getY())
      g_camera.pitch((movement.getY() - yCoord) / 5);
    if (yCoord > movement.getY())
      g_camera.pitch((movement.getY() - yCoord) / 5);
  }
  if (movement.isRightKeyDown(GLFW_MOUSE_BUTTON_RIGHT)){
    if (xCoord < movement.getX())
      g_camera.roll((movement.getX() - xCoord) / 5);
    if (xCoord > movement.getX())
      g_camera.roll((movement.getX() - xCoord) / 5);
  }
  movement.setX(xCoord);
  movement.setY(yCoord);
}

void
mouseButtons(GLFWwindow* window, int button, int action, int mods) {
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    movement.setLeftKeyDown(button);
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    movement.setRightKeyDown(button);
  if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
    movement.setLeftKeyUp(button);
  if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
    movement.setRightKeyUp(button);
}
