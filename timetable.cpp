#include "timetable.h"
#include "row.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QDebug>
#include <QVariant>
#include <QString>
#include <QAction>
#include <QMenuBar>


TimeTable::TimeTable(QWidget *parent) :
    QScrollArea(parent)
{
    inScroll = new QWidget(this);


    inScroll->setLayout(new QVBoxLayout);

    createTable();

    setWidgetResizable(true);
    //setBackgroundRole(QPalette::Dark);
    setWidget(inScroll);
    setContentsMargins(0,0,0,0);
}
void TimeTable::createTable()
{
    QSqlQuery query;
    QString queryStr1("select W.start_h, W.start_m, W.end_h, W.end_m, "
                      "S.subject, S.professor, S.type, W.location, W.id "
                      "from weeks W, subjects S where (weekday = ");
    QString queryStr2(") AND (W.subject_id = S.id)"
                      "order by W.start_h, W.start_m");

    inScroll->layout()->addWidget(new QLabel("Monday"));
    query.exec(queryStr1 + "0" + queryStr2);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,0,this));

    inScroll->layout()->addWidget(new QLabel("Thuesday"));
    query.exec(queryStr1 + "1" + queryStr2);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,1,this));

    inScroll->layout()->addWidget(new QLabel("Wednesday"));
    query.exec(queryStr1 + "2" + queryStr2);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,2,this));

    inScroll->layout()->addWidget(new QLabel("Thursday"));
    query.exec(queryStr1 + "3" + queryStr2);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,3,this));

    inScroll->layout()->addWidget(new QLabel("Friday"));
    query.exec(queryStr1 + "4" + queryStr2);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,4,this));

    inScroll->layout()->addWidget(new QLabel("Saturday"));
    query.exec(queryStr1 + "5" + queryStr2);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,5,this));

    inScroll->layout()->addWidget(new QLabel("Sunday"));
    query.exec(queryStr1 + "6" + queryStr2);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,6,this));
}
