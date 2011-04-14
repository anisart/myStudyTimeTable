#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QScrollArea>
///////////////////////////////////
#include <QPushButton>
///////////////////////////////////

class MainWidget : public QScrollArea
{
    Q_OBJECT
    ////////////////////////////
    QPushButton *addBtn;
    QWidget *inScroll;
    ////////////////////////////

public:
    explicit MainWidget(QWidget *parent = 0);
    void createTable();

signals:

public slots:
    void on_addBtn_clicked();

};


#endif // MAINWIDGET_H
