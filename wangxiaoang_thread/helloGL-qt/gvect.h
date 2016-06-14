#ifndef GVECT_H
#define GVECT_H
class Gvect
{
public:
    double x,y,z,p;
    Gvect(double x0=0,double y0=0,double z0=0,double p0=1);
    Gvect(const Gvect& RightSides);
    friend double dot(Gvect v1,Gvect v2);//dot multiple
    void debug();
    Gvect normal();
    double length();
    Gvect reverse();
    Gvect operator +(Gvect v1);
    Gvect operator -(Gvect v1);
    Gvect times(double t);
    friend Gvect cross(Gvect v1,Gvect v2);//cross multiple
};

#endif // GVECT_H
