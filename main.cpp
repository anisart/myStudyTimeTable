#include <QApplication>
#include "mainwindow.h"
#include "database.h"



int main(int my_argc, char **my_argv)
{
    QApplication::setGraphicsSystem("raster");
    QApplication my_app(my_argc,my_argv);
    my_app.setStyleSheet("#day { color: blue; background-color: yellow }");
    openDB();
    initDB();

    MainWindow my_window;
    my_window.showMaximized();
    QWidgetList allWidgets = QApplication::allWidgets();
    foreach(QWidget* widget, allWidgets)
           widget->setContextMenuPolicy(Qt::NoContextMenu);
    return my_app.exec();
}

