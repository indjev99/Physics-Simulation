#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

class point
{
public:
    long double x,y;

    point operator+();
    point operator-();
    point operator+(point a);
    point operator-(point a);
    point operator+(long double k);
    point operator-(long double k);
    point operator*(long double k);
    point operator/(long double k);
    point operator+=(point a);
    point operator-=(point a);
    point operator+=(long double k);
    point operator-=(long double k);
    point operator*=(long double k);
    point operator/=(long double k);
    long double dist();
    point unit();

    void randomise();
};

#endif // POINT_H_INCLUDED
