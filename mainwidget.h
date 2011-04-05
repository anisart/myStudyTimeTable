#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
///////////////////////////////////
#include <QPushButton>
#include <editwindow.h>
///////////////////////////////////

class MainWidget : public QWidget
{
    Q_OBJECT
    ////////////////////////////
    QPushButton *addBtn;
    EditWindow editWin;
    ////////////////////////////

public:
    explicit MainWidget(QWidget *parent = 0);

signals:

public slots:
    void on_addBtn_clicked();

};


#endif // MAINWIDGET_H
