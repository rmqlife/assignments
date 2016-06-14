#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#define STEP 0.1
#define RSTEP 1
#define cyR 0.5
#define cyL 20
//#define FROMFILE "D:/thread/threadfrom.txt"
//#define TOFILE "D:/thread/threadto.txt"
#include <qgl.h>
#include <QKeyEvent>
#include <QDebug>
#include <math.h>
#include <QMouseEvent>
#include <QPoint>
#include <gpoint.h>
//#include <fstream>
#include <QMainWindow>
#include <QLabel>
#include <SimpleObject.h>
#include <vector>
#include "Vec3f.h"
#include <list>
#include "vector"
#include "triangle.h"
namespace Ui {
    class MainWidget;
}
using namespace std;
struct Cylinder
{
    GLfloat x1,x2,y1,y2,z1,z2,r;
};




class MainWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0,const char* name = 0, bool fs = false);
    ~MainWidget();
    void cyl1(GLfloat x1,GLfloat y1,GLfloat z1,GLfloat x2,GLfloat y2,GLfloat z2);//以这两个点作为圆柱的始末点坐标
    //void cyl1(Cylinder c);
    void showobj(SimpleOBJ::CSimpleObject c);
    void zoom(Cylinder &c);
    void changeview();
    //void getdata();
    GLUquadricObj   *quadratic;
//private:
    //Ui::MainWidget *ui;

protected:
    void initializeGL();
    void paintGL();
    void getdata();
    void resizeGL( int width, int height );
    void keyPressEvent( QKeyEvent *e );
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void triangle1();
    void rect1();
    void count(Triangle &t);
    void loadGLTextures();
    Cylinder cy[200];
    int ncy;
    void search();
    void LoadtoTriangles();
    void DeleteTriangle();
    void pinsert(int a,int b);
private:
    vector<Triangle> triangles;
    vector<Gpoint> plist;
protected:
    SimpleOBJ::CSimpleObject obj0;
    bool fullscreen;
    GLfloat rTri;
    GLfloat rQuad;
    GLfloat rx;
    GLuint texture[1];
    GLfloat ry;
    GLfloat rz;
    GLfloat ix;
    GLfloat iy;
    GLfloat iz;
    QPoint lastpos;
    GLfloat zoomed;

};

#endif // MAINWIDGET_H
