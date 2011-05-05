#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "editwindow.h"
#include "timetable.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
   TimeTable *my_TT;
   EditWindow *edit;


public:
    explicit MainWindow(QWidget *parent = 0);
    void createMyMenu();
    ~MainWindow();

public Q_SLOTS:
    void editTTAction();
    void versionAction();

private:

        QAction* menu_editTTAction;
        QAction* menu_versionAction;
        QAction* menu_exitAction;

};

#endif // MAINWINDOW_H
