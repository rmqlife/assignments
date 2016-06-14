#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "math.h"
#include "algorithm"
#define pi 3.14
using namespace std;
void MainWidget::LoadtoTriangles()
{
    for(int i=0;i<obj0.m_nVertices;i++)//put all point into plist
    {
        Gpoint p;
        p.x=obj0.m_pVertexList[i].x;
        p.y=obj0.m_pVertexList[i].y;
        p.z=obj0.m_pVertexList[i].z;
        plist.push_back(p);
    }
    for (int i=0;i<obj0.m_nTriangles;i++)
    {

         Triangle tempt;
         for (int j=0;j<3;j++)
         {
            tempt.p[j]=obj0.m_pTriangleList[i][j];

         }
         count(tempt);
         triangles.push_back(tempt);
    }
    sort(triangles.begin(),triangles.end(),greater<Triangle>());

}


void MainWidget::count(Triangle &t)
{
double min=MAX_DOUBLE;
for (int i=0;i<3;i++)
{
    double k=pdist(plist[t.p[i]],plist[t.p[(i+1)%3]]);
    if (k<min)
    {
        min=k;
        t.tode[0]=t.p[i];
        t.tode[1]=t.p[(i+1)%3];
    }
}
t.value=min;
}




void MainWidget::DeleteTriangle()
{
Triangle t=triangles.back();//权值最小的面片
int p[2];
p[0]=t.tode[0];//该面片的最小边tode，
p[1]=t.tode[1];
pinsert(p[0],p[1]);//将新的点的信息加入plist,p[0]是新的点

//查找同时含有这两条边的三角形，并删除，可能删掉1个或2个
triangles.pop_back();//

for(int i=0;i<triangles.size();i++)//修改属性
    for (int j=0;j<3;j++)
    {
        if (triangles[i].p[j]==p[1])
        {
            triangles[i].p[j]=p[0];
            count(triangles[j]);

            for (int k=0;k<3;k++)
                if (triangles[i].p[k]==p[0])
                    triangles[i].value=-1;//删掉标志

        }else if (triangles[i].p[j]==p[0])
            count(triangles[j]);

    }

sort(triangles.begin(),triangles.end(),greater<Triangle>());

while (triangles.front().value<0)
    triangles.pop_back();
}


void MainWidget::pinsert(int a, int b)
{
Gpoint p;
p.x=(plist[a].x+plist[b].x)/2;
p.y=(plist[a].y+plist[b].y)/2;
p.z=(plist[a].z+plist[b].z)/2;
plist[a]=p;
}







MainWidget::MainWidget(QWidget *parent, const char* name, bool fs ) :
    QGLWidget(parent)//,ui(new Ui::MainWidget)
{
    //ui->setupUi(this);

    fullscreen = fs;
    iz=-2;
    ix=0;
    iy=0;
    rx=0;
    ry=0;
    rz=0;
    ncy=100;
    zoomed=1;
    search();
    setMouseTracking(true);
    //getdata();
    setGeometry( 0, 0, 640, 480 );

    //setcaption( "NeHe's OpenGL Framework" );
    if ( fullscreen )
        showFullScreen();
}

void MainWidget::getdata()
{
    obj0.LoadFromObj("d:/test_data/cube.obj");
    qDebug()<<obj0.m_nTriangles<<obj0.m_nVertices;
    int k=obj0.m_pTriangleList[2][1];

    qDebug()<<obj0.m_pVertexList[k].r<<
    obj0.m_pVertexList[k].g<<
    obj0.m_pVertexList[k].b;

    //qDebug()<<k;
}


void MainWidget::search()
{
    getdata();
    LoadtoTriangles();
    for (int i=0;i<3;i++)
        DeleteTriangle();
    obj0.m_nTriangles=triangles.size();
    for (int i=0;i<plist.size();i++)
    {
        obj0.m_pVertexList[i].x=plist[i].x;
        obj0.m_pVertexList[i].y=plist[i].y;
        obj0.m_pVertexList[i].z=plist[i].z;
    }
    for (int i=0;i<triangles.size();i++)
    {
        for (int j=0;j<3;j++)
            obj0.m_pTriangleList[i][j]=triangles[i].p[j];

    }
    obj0.m_nTriangles=triangles.size();
    obj0.m_nVertices=triangles.size();
}



MainWidget::~MainWidget()
{
    //delete ui;
}

void MainWidget::initializeGL()
{
    //loadGLTextures();
    glEnable(GL_TEXTURE_2D);

    glShadeModel( GL_SMOOTH );
    glClearColor( 0.0, 0.0, 0.0, 0.0 );
    glClearDepth( 1.0 );
    glEnable( GL_DEPTH_TEST );
    glDepthFunc( GL_LEQUAL );
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );


    quadratic=gluNewQuadric();	 //   创建二次几何体
    gluQuadricNormals(quadratic,   GLU_SMOOTH);	 //   使用平滑法线
    gluQuadricTexture(quadratic,   GL_TRUE);	 //   使用纹理

}



void MainWidget::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glColor3f( 1.0, 1.0, 0.0 );

    int num=obj0.m_nTriangles;
    changeview();
    glBegin( GL_TRIANGLES );

    for (int i=0;i<num;i++)
    {


        for (int j=0;j<3;j++)
        {

        int k=obj0.m_pTriangleList[i][j];
        GLfloat x=obj0.m_pVertexList[k].x;
        GLfloat y=obj0.m_pVertexList[k].y;
        GLfloat z=obj0.m_pVertexList[k].z;
        GLfloat r=obj0.m_pVertexList[k].r;
        GLfloat g=obj0.m_pVertexList[k].g;
        GLfloat b=obj0.m_pVertexList[k].b;
        glColor3f( r,g,b );//前侧面

       //glColor3f( 1,1,1 );
        glVertex3f( x,y,z );
        //qDebug()<<x<<y<<z;
        }


    }
    glEnd();
    glLoadIdentity();
}

void MainWidget::resizeGL( int width, int height )
{
    if ( height == 0 )
    {
        height = 1;
    }
    glViewport( 0, 0, (GLint)width, (GLint)height );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

}

void MainWidget::keyPressEvent( QKeyEvent *e )
{
    switch ( e->key() )
    {
    case Qt::Key_F2:
        fullscreen = !fullscreen;
        if ( fullscreen )
        {
            showFullScreen();
        }
        else
        {
            showNormal();
            setGeometry( 0, 0, 640, 480 );
        }
        updateGL();
        break;

    case Qt::Key_Escape:
        close();
    case Qt::Key_Up:
        rx=rx-RSTEP;updateGL();break;
    case Qt::Key_Down:
        rx=rx+RSTEP;updateGL();break;
    case Qt::Key_Right:
        ry=ry+RSTEP;updateGL();break;
    case Qt::Key_Left:
        ry=ry-RSTEP;updateGL();break;

    case Qt::Key_A:
        ix=ix+STEP;updateGL();break;
    case Qt::Key_D:
        ix=ix-STEP;updateGL();break;
    case Qt::Key_W:
        iy=iy-STEP;updateGL();break;
    case Qt::Key_S:
        iy=iy+STEP;updateGL();break;
    case Qt::Key_J:
        iz=iz+STEP;updateGL();break;
    case Qt::Key_K:
        iz=iz-STEP;updateGL();break;
    }
}

void MainWidget::mousePressEvent(QMouseEvent *e)
{
    qDebug()<<e->x()<<e->y();
    lastpos=e->pos();
}

void MainWidget::mouseMoveEvent(QMouseEvent *e)
{
    //qDebug()<<e->x()<<e->y();
    GLfloat dx= GLfloat(e->x()-lastpos.x())/width();
    GLfloat dy= GLfloat(e->y()-lastpos.y())/height();


    if (e->button() & Qt::LeftButton)
    {
        qDebug()<<e->x()<<e->y();
        rx += 180*dy;
        ry += 180*dx;
        updateGL();
    }
    if (e->button() & Qt::RightButton)
    {
        rx += 180*dy;
        rz += 180*dx;
        updateGL();
    }
    lastpos=e->pos();
}

void MainWidget::wheelEvent(QWheelEvent *e)
{
    qDebug()<<e->delta();
    iz+=STEP*e->delta()/120;
    updateGL();

}

void MainWidget::triangle1()
{
    changeview();

    glBegin( GL_TRIANGLES );

    /*glColor3f( 1.0, 0.0, 0.0 );//red
    glVertex3f( 0.0, 1.0, 0.0 );
    glColor3f( 0.0, 1.0, 0.0 );//green
    glVertex3f( -1.0, -1.0, 0.0 );
    glColor3f( 0.0, 0.0, 1.0 );//blue
    glVertex3f( 1.0, -1.0, 0.0 );*/

    glColor3f( 1.0, 0.0, 0.0 );//前侧面
    glVertex3f( 0.0, 1.0, 0.0 );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f( -1.0, -1.0, 1.0 );
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f( 1.0, -1.0, 1.0 );

    glColor3f( 1.0, 0.0, 0.0 );//右侧面
    glVertex3f( 0.0, 1.0, 0.0 );
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f( 1.0, -1.0, 1.0 );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f( 1.0, -1.0, -1.0 );

    glColor3f( 1.0, 0.0, 0.0 );//后侧面
    glVertex3f( 0.0, 1.0, 0.0 );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f( 1.0, -1.0, -1.0 );
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f( -1.0, -1.0, -1.0 );

    glColor3f( 1.0, 0.0, 0.0 );//左侧面
    glVertex3f( 0.0, 1.0, 0.0 );
    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f( -1.0, -1.0, -1.0 );
    glColor3f( 0.0, 1.0, 0.0 );
    glVertex3f( -1.0, -1.0, 1.0 );



    glEnd();
//    changeview();
    glLoadIdentity();

}


void MainWidget::rect1()
{
    glBegin( GL_QUADS );//开始绘制四边形。
    glColor3f( 0.5, 0.5, 1.0 ); //顶面
    glVertex3f( 1.0, 1.0, -1.0 );
    glVertex3f( -1.0, 1.0, -1.0 );
    glVertex3f( -1.0, 1.0, 1.0 );
    glVertex3f( 1.0, 1.0, 1.0 );


    glColor3f( 1.0, 0.5, 0.0 );
    glVertex3f( 1.0, -1.0, 1.0 );//底面
    glVertex3f( -1.0, -1.0, 1.0 );
    glVertex3f( -1.0, -1.0, -1.0 );
    glVertex3f( 1.0, -1.0, -1.0 );

    glColor3f( 1.0, 0.0, 0.0 );
    glVertex3f( 1.0, 1.0, 1.0 );//前面
    glVertex3f( -1.0, 1.0, 1.0 );
    glVertex3f( -1.0, -1.0, 1.0 );
    glVertex3f( 1.0, -1.0, 1.0 );

    glColor3f( 1.0, 1.0, 0.0 );
    glVertex3f( 1.0, -1.0, -1.0 );//后面
    glVertex3f( -1.0, -1.0, -1.0 );
    glVertex3f( -1.0, 1.0, -1.0 );
    glVertex3f( 1.0, 1.0, -1.0 );


    glColor3f( 0.0, 0.0, 1.0 );
    glVertex3f( -1.0, 1.0, 1.0 );//左侧面
    glVertex3f( -1.0, 1.0, -1.0 );
    glVertex3f( -1.0, -1.0, -1.0 );
    glVertex3f( -1.0, -1.0, 1.0 );


    glColor3f( 1.0, 0.0, 1.0 );
    glVertex3f( 1.0, 1.0, -1.0 );//右侧面
    glVertex3f( 1.0, 1.0, 1.0 );
    glVertex3f( 1.0, -1.0, 1.0 );
    glVertex3f( 1.0, -1.0, -1.0 );
    /*glVertex3f( -1.0, 1.0, 0.0 );//左上顶点。正方形
    glVertex3f( 1.0, 1.0, 0.0 );//右上顶点。
    glVertex3f( 1.0, -1.0, 0.0 );//右下顶点。
    glVertex3f( -1.0, -1.0, 0.0 );//左下顶点。*/
    glEnd();

}



void MainWidget::cyl1(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2)
{

    GLfloat x=x2-x1;
    GLfloat y=y2-y1;
    GLfloat z=z2-z1;

    GLfloat l=sqrt(x*x+y*y+z*z);//长度
    GLfloat cosalpha=(x*0+y*0+z*l)/(l*l);//夹角
    GLfloat alpha=acos(cosalpha)*180/pi;

    GLfloat vx=y;
    GLfloat vy=-x;
    GLfloat vz=0;

    glLoadIdentity();
    changeview();

    glTranslatef(x1, y1, z1);
    glRotatef(-alpha, vx, vy, vz );
    gluCylinder(quadratic,cyR,cyR,l,32,32);//后两个参数,渲染需要的三角形数量
}
void MainWidget::showobj(SimpleOBJ::CSimpleObject c)
{



    //zoom(c);
    /*
    GLfloat x=c.x2-c.x1;
    GLfloat y=c.y2-c.y1;
    GLfloat z=c.z2-c.z1;

    GLfloat l=sqrt(x*x+y*y+z*z);//长度
    GLfloat cosalpha=(x*0+y*0+z*l)/(l*l);//夹角
    GLfloat alpha=acos(cosalpha)*180/pi;

    GLfloat vx=y;
    GLfloat vy=-x;
    GLfloat vz=0;

    glLoadIdentity();
    changeview();

    glTranslatef(c.x1, c.y1, c.z1);
    glRotatef(-alpha, vx, vy, vz );
    gluCylinder(quadratic,c.r,c.r,l,32,32);//后两个参数,渲染需要的三角形数量
    */
}


void MainWidget::changeview()
{

    glTranslatef(ix, iy, iz);
    glRotatef(rx,1.0,0.0,0.0);
    glRotatef(ry,0.0,1.0,0.0);
    glRotatef(rz,0.0,0.0,1.0);
}

void MainWidget::zoom(Cylinder &c)
{
c.r=c.r*zoomed;
c.x1=c.x1*zoomed;
c.x2=c.x2*zoomed;
c.y1=c.y1*zoomed;
c.y2=c.y2*zoomed;
c.z1=c.z1*zoomed;
c.z2=c.z2*zoomed;
}

void MainWidget::loadGLTextures()
{
    QImage tex,buf;
    if (!buf.load("d:/thread/thread1.jpg"))
    {
        qWarning("Could not read image,using white color instead");
        QImage dummy(128,128,QImage::Format_RGB32);
        dummy.fill(Qt::green);
        buf=dummy;
    }
    tex=QGLWidget::convertToGLFormat(buf);
    glGenTextures(1,&texture[0]);
    glBindTexture(GL_TEXTURE_2D,texture[0]);
    glTexImage2D(GL_TEXTURE_2D,0,3,tex.width(),tex.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,tex.bits());
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}
