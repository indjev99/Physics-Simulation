#include "../headers/point.h"
#include "../headers/window_size.h"

#include<stdlib.h>
#include<math.h>

void point::randomise()
{
    x=rand()%(int(2*scale+1))-scale;
    y=rand()%(int(2*scale+1))-scale;
}

point point::operator+()
{
    point c;
    c.x=+x;
    c.y=+y;
    return c;
}
point point::operator-()
{
    point c;
    c.x=-x;
    c.y=-y;
    return c;
}
point point::operator+(point a)
{
    point c;
    c.x=x+a.x;
    c.y=y+a.y;
    return c;
}
point point::operator-(point a)
{
    point c;
    c.x=x-a.x;
    c.y=y-a.y;
    return c;
}
point point::operator+(long double k)
{
    point c;
    c.x=x+x*k/dist();
    c.y=y+y*k/dist();
    return c;
}
point point::operator-(long double k)
{
    point c;
    c.x=x-x*k/dist();
    c.y=y-y*k/dist();
    return c;
}
point point::operator*(long double k)
{
    point c;
    c.x=x*k;
    c.y=y*k;
    return c;
}
point point::operator/(long double k)
{
    point c;
    c.x=x/k;
    c.y=y/k;
    return c;
}
point point::operator+=(point a)
{
    x+=a.x;
    y+=a.y;
    return *this;
}
point point::operator-=(point a)
{
    x-=a.x;
    y-=a.y;
    return *this;
}
point point::operator+=(long double k)
{
    x+=x*k/dist();
    y+=y*k/dist();
    return *this;
}
point point::operator-=(long double k)
{
    x-=x*k/dist();
    y-=y*k/dist();
    return *this;
}
point point::operator*=(long double k)
{
    x*=k;
    y*=k;
    return *this;
}
point point::operator/=(long double k)
{
    x/=k;
    y/=k;
    return *this;
}
long double point::dist()
{
    return sqrt(x*x+y*y);
}
point point::unit()
{
    point c;
    c.x=x/dist();
    c.y=y/dist();
    return c;
}
