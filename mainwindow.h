#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
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
