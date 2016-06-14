#include "gvect.h"
#include "qdebug.h"
#include "math.h"
Gvect::Gvect(double x0,double y0,double z0,double p0):x(x0),y(y0),z(z0),p(p0)
{

}

Gvect::Gvect(const Gvect &RightSides)
{
    x=RightSides.x;
    y=RightSides.y;
    z=RightSides.z;
    p=RightSides.p;
}

double dot(Gvect v1,Gvect v2)
{
    return (v1.x*v2.x+v1.y*v2.y+v1.z*v2.z);
}

void Gvect::debug()
{
     qDebug()<<x<<y<<z;

}

Gvect Gvect::normal()
{
    double l=this->length();
    return Gvect(x/l,y/l,z/l);
}

double Gvect::length()
{
    return sqrt((double)x*x+y*y+z*z);
}

Gvect Gvect::operator +(Gvect v1)
{
    return Gvect(x+v1.x,y+v1.y,z+v1.z);
}

Gvect Gvect::operator -(Gvect v1)
{
    return Gvect(x-v1.x,y-v1.y,z-v1.z);
}

Gvect Gvect::times(double t)
{
    return Gvect(t*x,t*y,t*z);
}

Gvect Gvect::reverse()
{
    return Gvect(-x,-y,-z);
}

Gvect cross(Gvect v1,Gvect v2)
{
Gvect v;
v.x=v1.y*v2.z-v1.z*v2.y;
v.y=v1.z*v2.x-v1.x*v2.z;
v.z=v1.x*v2.y-v1.y*v2.x;
return v;
}
