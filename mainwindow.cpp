#include "mainwindow.h"
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    my_TT=new TimeTable();
    setCentralWidget(my_TT);
    createMyMenu();
}
void MainWindow::createMyMenu()
{
        //add menu item help to menu
        menu_editTTAction = new QAction(tr("Add item"), this);
        menuBar()->addAction(menu_editTTAction);
        connect(menu_editTTAction, SIGNAL(triggered()), this, SLOT(editTTAction()));
        connect(menu_editTTAction, SIGNAL(triggered()), this, SLOT(close()));
        //add menu item help to Version
        menu_versionAction = new QAction(tr("Version"), this);
        menuBar()->addAction(menu_versionAction);
        connect(menu_versionAction, SIGNAL(triggered()), this, SLOT(versionAction()));

        //add menu item help to Exit
        menu_exitAction = new QAction(tr("Exit"), this);
        menuBar()->addAction(menu_exitAction);
        connect(menu_exitAction, SIGNAL(triggered()), this, SLOT(close()));
 }

//Handle action for help menu.
void MainWindow::editTTAction()
{


    edit= new EditWindow();
    edit->showFullScreen();

}

//Handle action for help Version.
void MainWindow::versionAction()
{

        //do your task for version menu item.
        QMessageBox msgBox;
        msgBox.setInformativeText("Version pre dev");
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();


}

MainWindow::~MainWindow()
{
    delete menu_editTTAction;
    delete menu_versionAction;
    delete menu_exitAction;

}
