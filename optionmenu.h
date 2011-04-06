#ifndef OPTIONMENU_H
#define OPTIONMENU_H


#include<editwindow.h>
#include <QtGui/QMainWindow>
#include <QPushButton>
class OptionsMenu : public QMainWindow
{
    Q_OBJECT
    QPushButton *addBtn;
    EditWindow editWin;

public:
     OptionsMenu(QWidget *parent = 0);
    ~OptionsMenu();

    //function to create menu.
    void createMyMenu();

public Q_SLOTS: //slots to receive action of menu trigger.
    void helpAction();
    void aboutAction();
    void versionAction();


private:

    //Actions foe menu item
        QAction* menu_helpAction;
        QAction* menu_aboutAction;
        QAction* menu_versionAction;
        QAction* menu_exitAction;
};

#endif // OPTIONMENU_H
