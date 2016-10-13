//IUPAC Name Generator

#include "../headers/window_functions.h"
#include "../headers/run.h"

#include<iostream>
#include<conio.h>
#include<stdlib.h>

GLFWwindow *window;

int main()
{
    system("chcp 1251");
    system("cls");

    system("cls");

    std::string message;

    message=initializeGLFW();
    std::cerr<<message<<std::endl;
    if (message!="GLFW initialized successfully.") return -1;

    message=createWindow(window);
    std::cerr<<message<<std::endl;
    if (message!="Window created successfully.") return -1;

    message=setCallbacks(window);
    std::cerr<<message<<std::endl;
    if (message!="Callbacks set successfully.") return -1;

    system("cls");
    run(window);

    stopGraphics(window);

    return 0;
}
