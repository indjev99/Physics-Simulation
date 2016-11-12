#include "../headers/graph.h"
#include "../headers/draw.h"
#include "../headers/window_functions.h"
#include "../headers/run.h"

#include<iostream>
#include<math.h>
#include<stdlib.h>
#include<chrono>
#include<ctime>


void input(graph& g)
{
    int n,m,a,b;
    std::cin>>n>>m;
    g.reset(n);
    for (int i=0;i<n;++i)
    {
        std::cin>>g.vertices[i].x>>g.vertices[i].y;
    }
    for (int i=0;i<m;++i)
    {
        std::cin>>a>>b;
        g.addEdge(a-1,b-1);
    }
}
void stats(graph& g)
{
    point p;
    long double r;
    p=g.getCentreOfMass();
    std::cout<<"Centre of mass: ("<<p.x<<";"<<p.y<<")\n";
    p=g.getMomentum();
    std::cout<<"Momentum: ("<<p.x<<";"<<p.y<<")\n";
    r=g.getSpringPotentialEnergy();
    std::cout<<"Spring Potential Energy: "<<r<<"\n";
    r=g.getElectrostaticPotentialEnergy();
    std::cout<<"Electrostatic Potential Energy: "<<r<<"\n";
    r=g.getPotentialEnergy();
    std::cout<<"Potential Energy: "<<r<<"\n";
    r=g.getKinteicEnergy();
    std::cout<<"Kinetic Energy: "<<r<<"\n";
    r=g.getEnergy();
    std::cout<<"Energy: "<<r<<std::endl;
}
void run(GLFWwindow* w)
{
    int c=1;
    for (int i=-90;i<=90;i+=10)
    {
        std::cout<<i<<" "<<0<<"\n";
    }
    std::cout<<"\n";
    for (int i=-90;i<90;i+=10)
    {
        std::cout<<c<<" "<<c+1<<"\n";
        ++c;
    }
    srand(time(NULL));

    bool paused=0;
    bool draw=0;

    graph g;

    g.updates_per_sec=1000;
    g.EPS=0.01;
    g.spring_target=0;
    g.spring_stiffness=10;
    g.electromagnetic_constant=00000;
    g.resistance=0.0;

    int n=2;
    g.reset(n);
    //g.vertices[0]={0,0};
    //g.vertices[n-1]={50,0};
    for (int i=0;i<n;++i)
    {
        for (int j=i+1; j<n;++j)
        {
            //if (!(rand()%4))
                g.addEdge(i,j);
        }
    }
    /*g.reset(5);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,2);
    g.addEdge(2,3);
    g.addEdge(3,4);
    g.addEdge(4,1);*/

    std::chrono::high_resolution_clock::time_point start_time,curr_time;

    while (!glfwWindowShouldClose(w))
    {
        start_time=std::chrono::high_resolution_clock::now();
        if (!draw)
        {
            //for (int i=0;i<5;++i)
                drawWindow(w,g);
        }
        if (!paused)
        {
            for (int i=0;i<15;++i)
                g.update();
        }
        if (pressed==1)
        {
            pressed=0;
            paused=!paused;
        }
        if (pressed==2)
        {
            pressed=0;
            g.randomise();
        }
        if (pressed==3)
        {
            pressed=0;
            input(g);
        }
        if (pressed==4)
        {
            pressed=0;
            stats(g);
        }
        if (pressed==5)
        {
            pressed=0;
            draw=!draw;
        }
        if (pressed==6)
        {
            ++n;
            pressed=0;
            g.reset(n);
            //g.vertices[0]={-100,-100};
            //g.vertices[n-1]={100,100};
            for (int i=0;i<n;++i)
            {
                for (int j=i+1; j<n;++j)
                {
                    //if (!(rand()%4))
                        g.addEdge(i,j);
                }
            }
        }
        do
        {
            glfwPollEvents();
            curr_time=std::chrono::high_resolution_clock::now();
        }
        while(!glfwWindowShouldClose(w) && std::chrono::duration_cast<std::chrono::duration<long double>>(curr_time-start_time).count()<0.01);
        //std::cout<<std::chrono::duration_cast<std::chrono::duration<long double>>(curr_time-start_time).count()<<"\n";
    }
}
