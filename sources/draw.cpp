#include "../headers/graph.h"
#include "../headers/window_size.h"
#include "../headers/window_functions.h"
#include "../headers/draw.h"

#include<math.h>
#include<vector>

const long double DEG2RAD=3.14159/180.0;

const long double GRAPH_COLOUR_R=0;
const long double GRAPH_COLOUR_G=0;
const long double GRAPH_COLOUR_B=0;

const long double BACKGROUND_COLOUR_R=1;
const long double BACKGROUND_COLOUR_G=1;
const long double BACKGROUND_COLOUR_B=1;

long double vertex_radius=0.015;
long double thickness=0.0066;

void drawPartEllipse(float x, float y, float radiusX, float radiusY, long double alpha, long double beta)
{
    alpha=round(alpha*2);
    beta=round(beta*2);
    glBegin(GL_TRIANGLES);
    for(int i=alpha;i<beta;++i)
    {
        float rad=i*0.5*DEG2RAD;
        float rad2=(i+1)*0.5;
        while (rad2>=360) rad2-=360;
        rad2*=DEG2RAD;
        glVertex2f(cos(rad)*radiusX+x,sin(rad)*radiusY+y);
        glVertex2f(cos(rad2)*radiusX+x,sin(rad2)*radiusY+y);
        glVertex2f(x,y);
    }
    glEnd();
}
void drawEdge(long double x1, long double y1, long double x2, long double y2, int num)
{
    long double scale=1.0*ORIGINAL_WINDOWS_HEIGHT/WINDOWS_HEIGHT;
    long double offset,x,y,deltax,deltay;
    glColor3f(GRAPH_COLOUR_R,GRAPH_COLOUR_G,GRAPH_COLOUR_B);
    glLineWidth(4.0);
    glBegin(GL_LINES);
    long double alpha,beta;
    deltax=x2-x1;
    deltay=y2-y1;
    if (deltax==0)
    {
        x=1;
        y=0;
    }
    else
    {
        alpha=atan(deltay/deltax);
        beta=90*DEG2RAD-alpha;
        x=cos(beta);
        y=sin(beta);
    }
    x=-x;
    for (int i=0;i<num;++i)
    {
        offset=((num-1)*0.5-i)*0.02;
        glVertex2f((x1+offset*x)*scale,(y1+offset*y)*scale);
        glVertex2f((x2+offset*x)*scale,(y2+offset*y)*scale);
    }
    glEnd();
}
void drawVertex(long double x, long double y)
{
    long double scale2=1.0*ORIGINAL_WINDOWS_HEIGHT/WINDOWS_HEIGHT;

    glColor3f(GRAPH_COLOUR_R,GRAPH_COLOUR_G,GRAPH_COLOUR_B);
    drawPartEllipse(x/scale*scale2,y/scale*scale2,vertex_radius*scale2,vertex_radius*scale2,0,360);

    glColor3f(BACKGROUND_COLOUR_R,BACKGROUND_COLOUR_G,BACKGROUND_COLOUR_B);
    drawPartEllipse(x/scale*scale2,y/scale*scale2,(vertex_radius-thickness)*scale2,(vertex_radius-thickness)*scale2,0,360);
}
void drawGraph(GLFWwindow* w, graph& g)
{
    long double proportion=1.0*WINDOWS_WIDTH/WINDOWS_HEIGHT;

    point p,p2;

    glColor3f(BACKGROUND_COLOUR_R,BACKGROUND_COLOUR_G,BACKGROUND_COLOUR_B);

    glBegin(GL_QUADS);

    glVertex2f(-1.0*proportion,-1.0);
    glVertex2f(1.0*proportion,-1.0);
    glVertex2f(1.0*proportion,1.0);
    glVertex2f(-1.0*proportion,1.0);

    glEnd();

    for (int i=0;i<g.edges.size();++i)
    {
        p=g.vertices[i];
        for (int j=0;j<g.edges[i].size();++j)
        {
            p2=g.vertices[g.edges[i][j]];
            drawEdge(p.x/scale,p.y/scale,p2.x/scale,p2.y/scale,1);
        }
    }

    for (int i=0;i<g.vertices.size();++i)
    {
        p=g.vertices[i];
        drawVertex(p.x,p.y);
    }

}

void drawWindow(GLFWwindow*& w, graph& g)
{
    glfwSetWindowShouldClose(w,0);

    float ratio;
    int width, height;

    glfwMakeContextCurrent(w);
    glfwGetFramebufferSize(w,&width,&height);
    ratio=width/(float)height;
    glViewport(0,0,width,height);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio,ratio,-1.f,1.f,1.f,-1.f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawGraph(w,g);

    glfwSwapBuffers(w);
}
