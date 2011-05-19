#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QMessageBox>
#include "editwindow.h"
#include "timetable.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
   TimeTable *my_TT;
   EditWindow *edit;
   QString path;


public:
    explicit MainWindow(QWidget *parent = 0);
    void createMyMenu();
    ~MainWindow();

public Q_SLOTS:
    void editTTAction();
    void versionAction();
    void add_fileAction();
    void saveFiles(QString);
    void on_save_clicked(QListWidgetItem *item);
private:

        QAction* menu_editTTAction;
        QAction* menu_versionAction;
        QAction* menu_exitAction;
        QAction* menu_add_file;

};

#endif // MAINWINDOW_H
