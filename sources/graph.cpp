#include "../headers/graph.h"

#include<iostream>
#include<math.h>

void graph::reset(int nodes)
{
    vertices.resize(nodes);
    velocities.resize(nodes);
    edges.resize(nodes);
    for (int i=0;i<nodes;++i)
    {
        vertices[i].randomise();
        velocities[i]={0,0};
        edges[i].resize(0);
    }
}
void graph::randomise()
{
    int nodes=vertices.size();
    for (int i=0;i<nodes;++i)
    {
        vertices[i].randomise();
        velocities[i]={0,0};
    }
}
void graph::addEdge(int from, int to)
{
    edges[from].push_back(to);
    edges[to].push_back(from);
}
void graph::update()
{
    int n=vertices.size();

    std::vector<point> v2(n);

    point p,p2;

    for (int i=0;i<n;++i)
    {
        p=vertices[i];
        //velocities[i]={0,0}
        velocities[i]-=velocities[i]*velocities[i].dist()*resistance/2/updates_per_sec;
        for (int j=0;j<edges[i].size();++j)
        {
            p2=vertices[edges[i][j]]-p;
            //if (p2.dist()>spring_target)
                if (i<2 || i>40) velocities[i]+=(p2-spring_target)*0.1*spring_stiffness/updates_per_sec;
                else velocities[i]+=(p2-spring_target)*spring_stiffness/updates_per_sec;
        }
        for (int j=0;j<n;++j)
        {
            p2=vertices[j]-p;
            if (p2.dist()>EPS)
            {
                velocities[i]-=p2.unit()/p2.dist()/p2.dist()*electromagnetic_constant/updates_per_sec;
            }
            else if (i!=j)
            {
                //std::cerr<<"Under EPS: "<<p2.dist()<<"\n";
            }
        }
        //velocities[i]+=point({0,-100})/updates_per_sec;
        if (i==0 || i==vertices.size()-1)
        {
            velocities[i]={0,velocities[i].y};
            //velocities[i]={0,0};
        }
        v2[i]=p+velocities[i]/updates_per_sec;
    }
    vertices=v2;
}
point graph::getCentreOfMass()
{
    point centre={0,0};
    for (int i=0;i<vertices.size();++i)
    {
        centre+=vertices[i];
    }
    centre/=vertices.size();
    return centre;
}
point graph::getMomentum()
{
    point momentum={0,0};
    for (int i=0;i<velocities.size();++i)
    {
        momentum+=velocities[i];
    }
    return momentum;
}
long double graph::getKinteicEnergy()
{
    long double energy=0;
    for (int i=0;i<velocities.size();++i)
    {
        energy+=velocities[i].dist()*velocities[i].dist()/2;
    }
    return energy;
}
long double graph::getSpringPotentialEnergy()
{
    long double energy=0;
    point p,p2;
    for (int i=0;i<vertices.size();++i)
    {
        p=vertices[i];
        for (int j=0;j<edges[i].size();++j)
        {
            if (edges[i][j]<i) continue;
            p2=p-vertices[edges[i][j]];
            energy+=(p2-spring_target).dist()*(p2-spring_target).dist()*spring_stiffness/2;
        }
    }
    return energy;
}
long double graph::getElectrostaticPotentialEnergy()
{
    long double energy=0;
    point p,p2;
    for (int i=0;i<vertices.size();++i)
    {
        p=vertices[i];
        for (int j=i+1;j<vertices.size();++j)
        {
            p2=vertices[j]-p;
            energy+=electromagnetic_constant/p2.dist();
        }
    }
    return energy;
}
long double graph::getPotentialEnergy()
{
    return getSpringPotentialEnergy()+getElectrostaticPotentialEnergy();
}
long double graph::getEnergy()
{
    return getPotentialEnergy()+getKinteicEnergy();
}
