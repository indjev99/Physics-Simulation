#include "../headers/window_size.h"
#include "../headers/window_functions.h"
#include "../headers/draw.h"

#include<iostream>
#include<GLFW/glfw3.h>

double mxpos=0;
double mypos=0;
int pressed=0;

void error_callback(int error, const char* description)
{
    std::cerr<<error<<": "<<description<<std::endl;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key==GLFW_KEY_ESCAPE && action==GLFW_PRESS) glfwSetWindowShouldClose(window,1);
    if (key==GLFW_KEY_SPACE && action==GLFW_PRESS) pressed=1;
    if (key==GLFW_KEY_R && action==GLFW_PRESS) pressed=2;
    if (key==GLFW_KEY_I && action==GLFW_PRESS) pressed=3;
    if (key==GLFW_KEY_S && action==GLFW_PRESS) pressed=4;
    if (key==GLFW_KEY_D && action==GLFW_PRESS) pressed=5;
    if (key==GLFW_KEY_G && action==GLFW_PRESS) pressed=6;
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (action==GLFW_PRESS)
    {
        pressed=button;
        glfwGetCursorPos(window,&mxpos,&mypos);
        mxpos=mxpos*2-WINDOWS_WIDTH;
        mypos=-mypos*2+WINDOWS_HEIGHT;
        mxpos/=ORIGINAL_WINDOWS_HEIGHT;
        mypos/=ORIGINAL_WINDOWS_HEIGHT;
    }
}
void window_size_callback(GLFWwindow* window, int width, int height)
{
    WINDOWS_WIDTH=width;
    WINDOWS_HEIGHT=height;
    pressed=-2;
}
std::string setCallbacks(GLFWwindow* w)
{
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(w,key_callback);
    glfwSetMouseButtonCallback(w,mouse_button_callback);
    glfwSetWindowSizeCallback(w,window_size_callback);
    return "Callbacks set successfully.";
}
std::string initializeGLFW()
{
    if (!glfwInit())
        return "Unable to initialize GLFW.";
    return "GLFW initialized successfully.";
}
std::string createWindow(GLFWwindow*& w)
{
    w=glfwCreateWindow(WINDOWS_WIDTH,WINDOWS_HEIGHT,"Graph Drawer",NULL,NULL);
    if (!w)
    {
        glfwTerminate();
        return "Unable to open window.";
    }
    return "Window created successfully.";
}
void stopGraphics(GLFWwindow*& w)
{
    glfwDestroyWindow(w);
    glfwTerminate();
}
