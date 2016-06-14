#include "mainwidget.h"
#include "ui_mainwidget.h"
#define pi 3.14
using namespace std;

MainWidget::MainWidget(QWidget *parent, const char* name, bool fs ) :
    QGLWidget(parent)//,ui(new Ui::MainWidget)
{
    //ui->setupUi(this);
    fullscreen = fs;
    iz=-20;
    ix=-5;
    iy=-5;
    rx=0;
    ry=0;
    rz=0;
    ncy=100;
    zoomed=0.1;

    setMouseTracking(true);
    getdata();
    setGeometry( 0, 0, 640, 480 );

    //setcaption( "NeHe's OpenGL Framework" );
    if ( fullscreen )
        showFullScreen();
}


MainWidget::~MainWidget()
{
    //delete ui;
}

void MainWidget::initializeGL()
{
    loadGLTextures();
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

   // gluOrtho2D(-5.0,5.0,-5.0,5.0);
    //glRotatef( rx, 1.0, 0.0, 0.0 );
    //glRotatef( ry, 0.0, 1.0, 0.0 );
    //glRotatef( rz, 0.0, 0.0, 1.0 );
    //(0,0,0)

    glColor3f(1.0, 1.0, 1.0);
    //cyl1(10,0,-10,10,10,-10);
    //cyl1(0,0,0,10,10,-10);
    //cyl1(0,0,0,-10,-10,-10);
    //移动绘图原点，人始终站在坐标原点
    //glRotatef( 90, 0.0, 1.0, 0.0 );

    //qDebug()<<rx;
    glBindTexture( GL_TEXTURE_2D, texture[0] );
    for(int i=0;i<ncy;i++)
        cyl1(cy[i]);




    glColor3f( 1.0, 1.0, 0.0 );

    //glLoadIdentity();
    //glTranslatef(2*cyR, 0.0,0.0 );

    //glRotatef( 90, 0.0, 1.0, 0.0 );
    //gluCylinder(quadratic,cyR,cyR,cyL,32,32);

    //glRotatef( rTri, 0.0, 1.0, 0.0 );//绕y轴旋转
    //glRotatef( rx, 1.0, 0.0, 0.0 );
    //glRotatef( ry, 0.0, 1.0, 0.0 );
    //glRotatef( rz, 0.0, 0.0, 1.0 );
    //gluCylinder(quadratic,0.6f,0.6f,0.4f,32,32);



    //glLoadIdentity();
    //glTranslatef( -1.5, cyR*2, -20.0 );//移动绘图原点，人始终站在坐标原点
    //gluCylinder(quadratic,cyR,cyR,cyL,10,10);

    //triangle1();


    //glLoadIdentity();//重置位置
    //glTranslatef( 1.5, 0.0, -7.0 );
    //glRotatef( rQuad, 1.0, 1.0, 1.0 );
    //rect1();

    //glTranslatef( 3.0, 0.0, 0.0 );


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
void MainWidget::cyl1(Cylinder c)
{
    zoom(c);

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

}


void MainWidget::changeview()
{
    glTranslatef(ix, iy, iz);
    glRotatef(rx,1.0,0.0,0.0);
    glRotatef(ry,0.0,1.0,0.0);
    glRotatef(rz,0.0,0.0,1.0);
}
void MainWidget::getdata()
{
    ifstream fin1(FROMFILE);
    ifstream fin2(TOFILE);

    //fin1>>x1>>y1>>z1;
    //qDebug()<<x1<<y1<<z1;

    for (int i=0;i<ncy;i++)
    {
        fin1>>cy[i].x1>>cy[i].y1>>cy[i].z1;
        fin2>>cy[i].x2>>cy[i].y2>>cy[i].z2;
        cy[i].r=cyR;
        qDebug()<<cy[i].x1<<cy[i].x2;
    }
    fin1.close();
    fin2.close();;
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
