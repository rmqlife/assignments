#include <qapplication.h>
#include <qmessagebox.h>
#include "mainwidget.h"
#include "mainwindow.h"
//#include "mainwindow.h"

int main( int argc, char **argv )
{
    bool fs = false;
    QApplication a(argc,argv);
     switch( QMessageBox::information( 0,
                                      "Start FullScreen?",
                                      "Would You Like To Run In Fullscreen Mode?",
                                      QMessageBox::Yes,
                                      QMessageBox::No | QMessageBox::Default ) )
    {
    case QMessageBox::Yes:
        fs = true;
        break;
    case QMessageBox::No:
        fs = false;
        break;
    }


    MainWidget w( 0, 0, fs );
    //MainWindow w;
    //w.show();
    w.show();
    return a.exec();

}
