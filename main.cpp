#include <QApplication>
#include "mainwindow.h"
#include "database.h"

int main(int my_argc, char **my_argv)
{
    QApplication my_app(my_argc,my_argv);
    openDB();
     initDB();
    MainWindow my_window;
    my_window.showMaximized();
    return my_app.exec();
}

