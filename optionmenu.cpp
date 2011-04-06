#include "optionmenu.h"
#include "editwindow.h"
#include <QMessageBox>
#include <QAction>
#include <QMenuBar>
#include "mainwidget.h"
OptionsMenu::OptionsMenu(QWidget *parent) :
    QMainWindow(parent)
{
    MainWidget *m = new MainWidget;
    setCentralWidget(m);
    m->showMaximized();
//     setCentralWidget(m);
        //create menu
        createMyMenu();
}

void OptionsMenu::createMyMenu()
{
        //add menu item help to menu
        menu_helpAction = new QAction(tr("Help"), this);
        menuBar()->addAction(menu_helpAction);
        connect(menu_helpAction, SIGNAL(triggered()), this, SLOT(helpAction()));

        //add menu item help to About
        menu_aboutAction = new QAction(tr("Additem element"), this);

       menuBar()->addAction(menu_aboutAction);
        connect(menu_aboutAction, SIGNAL(triggered()), this, SLOT(aboutAction()));

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
void OptionsMenu::helpAction()
{

        //do your task for help menu item.
        QMessageBox msgBox;
        msgBox.setInformativeText("myHelp");
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();

}

//Handle action for help About.
void OptionsMenu::aboutAction()
{

//        //do your task for help about item.
//        QMessageBox msgBox;
//        msgBox.setInformativeText("Testing menu in Qt.");
//        msgBox.setStandardButtons(QMessageBox::Ok);
//        int ret = msgBox.exec();
//        void MainWidget::on_addBtn_clicked()

                      editWin.showMaximized();



}

//Handle action for help Version.
void OptionsMenu::versionAction()
{

        //do your task for version menu item.
        QMessageBox msgBox;
        msgBox.setInformativeText("Version pre dev");
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();


}

OptionsMenu::~OptionsMenu()
{
    delete menu_helpAction;
    delete menu_aboutAction;
    delete menu_versionAction;
    delete menu_exitAction;

}
