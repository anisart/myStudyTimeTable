#include "timetable.h"
#include "row.h"
#include "database.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QDebug>
#include <QVariant>
#include <QString>


TimeTable::TimeTable(QWidget *parent) :
    QWidget(parent)
{
    QWidget *inScroll = new QWidget(this);
    QVBoxLayout *vbl = new QVBoxLayout;
    QScrollArea *scroll = new QScrollArea(this);


    openDB();
    initDB();
    QSqlQuery query;
    QString queryString("select start_h, start_m, end_h, end_m, \
                        subject, professor, type, location \
                        from weeks where weekday = ");

    inScroll->setLayout(new QVBoxLayout);
    //inScroll->layout()->setContentsMargins(0,0,0,0);

    inScroll->layout()->addWidget(new QLabel("Monday"));
    query.exec(queryString + "0");
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,this));

    inScroll->layout()->addWidget(new QLabel("Thuesday"));
    query.exec(queryString + "1");
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,this));

    inScroll->layout()->addWidget(new QLabel("Wednesday"));
    query.exec(queryString + "2");
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,this));

    inScroll->layout()->addWidget(new QLabel("Thursday"));
    query.exec(queryString + "3");
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,this));

    inScroll->layout()->addWidget(new QLabel("Friday"));
    query.exec(queryString + "4");
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,this));

    inScroll->layout()->addWidget(new QLabel("Saturday"));
    query.exec(queryString + "5");
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,this));

    inScroll->layout()->addWidget(new QLabel("Sunday"));
    query.exec(queryString + "6");
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,this));

    scroll->setWidgetResizable(true);


    scroll->setWidget(inScroll);
    vbl->addWidget(scroll);

    vbl->setContentsMargins(0,0,0,0);
    setLayout(vbl);
}
