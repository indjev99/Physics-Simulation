#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "../headers/point.h"

#include<vector>

class graph
{
public:
    long double updates_per_sec;
    long double EPS;

    long double spring_target;
    long double spring_stiffness;
    long double electromagnetic_constant;
    long double resistance;

    std::vector<point> velocities;

    std::vector<point> vertices;
    std::vector<std::vector<int>> edges;

    void reset(int nodes);
    void randomise();
    void addEdge(int from, int to);

    void update();
    point getCentreOfMass();
    point getMomentum();
    long double getKinteicEnergy();
    long double getSpringPotentialEnergy();
    long double getElectrostaticPotentialEnergy();
    long double getPotentialEnergy();
    long double getEnergy();

};

#endif // GRAPH_H_INCLUDED
