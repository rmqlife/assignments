#ifndef GPOINT_H
#define GPOINT_H

#include "gvect.h"
#include "list"
#include "triangle.h"
#include "QDebug"
#define MAX_DOUBLE 18910351655
#define DISPLAY -20
using namespace std;
class Gpoint
{   
public:
   double x,y,z,p;//Æë´Î×ø±ê
   Gpoint(double x0=0,double y0=0,double z0=0,double p0=1);
   void move(int mx,int my,int mz);
   void set(double x0, double y0, double z0, double p0=1);
   Gpoint(const Gpoint& RightSides);
   void debug();
   friend double pdist(Gpoint &p1,Gpoint &p2);
   Gvect operator -(Gpoint &p1);
   Gpoint operator +(Gvect &v1);
   //list<Triangle> t;
};

#endif // GPOINT_H
