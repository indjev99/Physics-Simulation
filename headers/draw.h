#ifndef DRAW_H_INCLUDED
#define DRAW_H_INCLUDED

#include "../headers/graph.h"

#include<GLFW/glfw3.h>

extern const long double DEG2RAD;

extern const long double GRAPH_COLOUR_R;
extern const long double GRAPH_COLOUR_G;
extern const long double GRAPH_COLOUR_B;

extern const long double BACKGROUND_COLOUR_R;
extern const long double BACKGROUND_COLOUR_G;
extern const long double BACKGROUND_COLOUR_B;

extern long double vertex_radius;
extern long double thickness;

void drawPartEllipse(float x, float y, float radiusX, float radiusY, long double alpha, long double beta);
void drawEdge(long double x1, long double y1, long double x2, long double y2, int num);
void drawGraph(GLFWwindow* w, graph& g);
void drawWindow(GLFWwindow*& w, graph& g);

#endif //DRAW_H_INCLUDED
