#include "mainwindow.h"
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QDesktopServices>
#include <QSqlQuery>
#include <QVBoxLayout>
#include <QStringList>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // Create QTabWidget
    QTabWidget *tabWidget = new QTabWidget(this);
    tabWidget->setContextMenuPolicy(Qt::NoContextMenu);
    my_TTU = new TimeTable(this,"1");
    tabWidget->addTab(my_TTU, "Upper");
    my_TTL  = new TimeTable(this,"0");
    tabWidget->addTab(my_TTL, "Lower");
    setCentralWidget(tabWidget);
    createMyMenu();
}
void MainWindow::createMyMenu()
{
        //add menu item help to File
        menu_add_file = new QAction(tr("Attach image or text file"), this);
        menuBar()->addAction(menu_add_file);
        connect(menu_add_file, SIGNAL(triggered()), this, SLOT(add_fileAction()));
        //add menu item help to menu
        menu_editTTAction = new QAction(tr("Add item"), this);
        menuBar()->addAction(menu_editTTAction);
        connect(menu_editTTAction, SIGNAL(triggered()), this, SLOT(editTTAction()));
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
    connect(edit,SIGNAL(dataChanged()),this,SLOT(close()));
}

//Handle action for help Version.
void MainWindow::versionAction()
{

        //do your task for version menu item.
        QMessageBox msgBox;
        msgBox.setInformativeText("Version: 11.05.001(Release)");
        msgBox.setStandardButtons(QMessageBox::Ok);
        int ret = msgBox.exec();


}
void MainWindow::add_fileAction()
{
QFileDialog *dialog=new QFileDialog(this);
QStringList filters;
filters<<"Image or text files (*.jpg *.png *.bmp *.txt)";
dialog->setFilters(filters);
dialog->setDirectory(QDesktopServices::storageLocation(QDesktopServices::PicturesLocation));
dialog->showFullScreen();
connect(dialog,SIGNAL(fileSelected(QString)),this,SLOT(saveFiles(QString)));

}
void MainWindow::saveFiles(QString path_file)
{
    path=path_file;
    QWidget *wig=new QWidget();
    QPushButton *closeBtn=new QPushButton("close");
    QVBoxLayout *vbl=new QVBoxLayout();
    QListWidget *list=new QListWidget();
    QSqlQuery query;
    query.exec("select subject from subjects");
    while(query.next())
    {
        list->addItem(query.value(0).toString());
    }
    vbl->addWidget(list);
    vbl->addWidget(closeBtn);
    wig->setLayout(vbl);
    wig->showFullScreen();
    connect(list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(on_save_clicked(QListWidgetItem*)));
    connect(list,SIGNAL(itemClicked(QListWidgetItem*)),wig,SLOT(close()));
    connect(closeBtn,SIGNAL(clicked()),wig,SLOT(close()));


}
void MainWindow::on_save_clicked(QListWidgetItem *item)
{
    QSqlQuery query;
    query.exec("select id from subjects where subject = '" + item->text() + "'");
    query.next();
    query.exec("insert into files (path, subject_id) values ('" + path + "','"
               + query.value(0).toString() + "')");
}

MainWindow::~MainWindow()
{

}
