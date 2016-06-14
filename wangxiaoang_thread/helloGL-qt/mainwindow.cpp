#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    glwindow=new MainWidget(0,0,false);
    //QHBoxLayout lay;
    //lay.addWidget(glwindow);
    //setLayout(&lay);
    //glwindow->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
