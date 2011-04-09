#include "mainwidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <row.h>
#include "database.h"
#include <QDebug>
#include <QVariant>
#include <QString>

MainWidget::MainWidget(QWidget *parent) :
    QScrollArea(parent)
{
    inScroll = new QWidget(this);
    //////////////////////////////////////////
    addBtn = new QPushButton("Add Item",this);
    //////////////////////////////////////////

    openDB();
    initDB();

    inScroll->setLayout(new QVBoxLayout);
    //inScroll->layout()->setContentsMargins(0,0,0,0);

    createTable();

    setWidgetResizable(true);
    //setBackgroundRole(QPalette::Dark);
    setWidget(inScroll);
    ////////////////////////////////////
    inScroll->layout()->addWidget(addBtn);
    ////////////////////////////////////
    setContentsMargins(0,0,0,0);

    ////////////////////////////////////////
    connect(addBtn,SIGNAL(clicked()),this,SLOT(on_addBtn_clicked()));
    ///////////////////////////////////////////
}

void MainWidget::createTable()
{
    QSqlQuery query;
    QString queryString("select start_h, start_m, end_h, end_m, \
                        subject, professor, type, location, _id \
                        from weeks where weekday = ");
    QString querySortStr(" order by start_h, start_m");;

    inScroll->layout()->addWidget(new QLabel("Monday"));
    query.exec(queryString + "0" + querySortStr);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,0,this));

    inScroll->layout()->addWidget(new QLabel("Thuesday"));
    query.exec(queryString + "1" + querySortStr);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,1,this));

    inScroll->layout()->addWidget(new QLabel("Wednesday"));
    query.exec(queryString + "2" + querySortStr);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,2,this));

    inScroll->layout()->addWidget(new QLabel("Thursday"));
    query.exec(queryString + "3" + querySortStr);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,3,this));

    inScroll->layout()->addWidget(new QLabel("Friday"));
    query.exec(queryString + "4" + querySortStr);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,4,this));

    inScroll->layout()->addWidget(new QLabel("Saturday"));
    query.exec(queryString + "5" + querySortStr);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,5,this));

    inScroll->layout()->addWidget(new QLabel("Sunday"));
    query.exec(queryString + "6" + querySortStr);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,6,this));
}

void MainWidget::on_addBtn_clicked()
{
    editWin.showMaximized();
}
