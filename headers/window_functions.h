#ifndef WINDOW_FUNCTIONS_H_INCLUDED
#define WINDOW_FUNCTIONS_H_INCLUDED

#include<string>
#include<GLFW/glfw3.h>

extern double mxpos;
extern double mypos;
extern int pressed;

void error_callback(int error, const char* description);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void window_size_callback(GLFWwindow* window, int width, int height);
std::string setCallbacks(GLFWwindow* w);
std::string initializeGLFW();
std::string createWindow(GLFWwindow*& w);
void stopGraphics(GLFWwindow*& w);

#endif //WINDOW_FUNCTIONS_H_INCLUDED
