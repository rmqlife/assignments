#include "gpoint.h"
#include "math.h"
Gpoint::Gpoint(double x0,double y0,double z0,double p0):x(x0),y(y0),z(z0),p(p0)
{

}



Gpoint::Gpoint(const Gpoint &RightSides)
{
    x=RightSides.x;
    y=RightSides.y;
    z=RightSides.z;
    p=RightSides.p;
}

void Gpoint::move(int mx, int my, int mz)
{
    x+=mx;
    y+=my;
    z+=mz;
}


void Gpoint::debug()
{
 qDebug()<<x<<y<<z<<p;
}

void Gpoint::set(double x0, double y0, double z0, double p0)
{
x=x0;
y=y0;
z=z0;
p=p0;
}

double pdist(Gpoint &p1,Gpoint &p2)
{
double t=(p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y)+
        (p1.z-p2.z)*(p1.z-p2.z);
return sqrt(t);
}

Gvect Gpoint::operator -(Gpoint &p1)
{
    Gvect result(this->x-p1.x,this->y-p1.y,this->z-p1.z);
    return result;
}


Gpoint Gpoint::operator +(Gvect &v1)
{
    Gpoint result(x+v1.x,y+v1.y,z+v1.z);
    return result;
}

