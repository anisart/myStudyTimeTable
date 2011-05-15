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
#include "camera.h"


TimeTable::TimeTable(QWidget *parent) :
    QScrollArea(parent)
{
    inScroll = new QWidget(this);


    inScroll->setLayout(new QVBoxLayout);

    for (int i = 0; i < 7; i++)
        dayLabel[i].setObjectName("day");

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

    dayLabel[0].setText("Monday");
    inScroll->layout()->addWidget(&dayLabel[0]);
    query.exec(queryStr1 + "0" + queryStr2);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,0,this));

    dayLabel[1].setText("Thuesday");
    inScroll->layout()->addWidget(&dayLabel[1]);
    query.exec(queryStr1 + "1" + queryStr2);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,1,this));

    dayLabel[2].setText("Wednesday");
    inScroll->layout()->addWidget(&dayLabel[2]);
    query.exec(queryStr1 + "2" + queryStr2);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,2,this));

    dayLabel[3].setText("Thursday");
    inScroll->layout()->addWidget(&dayLabel[3]);
    query.exec(queryStr1 + "3" + queryStr2);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,3,this));

    dayLabel[4].setText("Friday");
    inScroll->layout()->addWidget(&dayLabel[4]);
    query.exec(queryStr1 + "4" + queryStr2);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,4,this));

    dayLabel[5].setText("Saturday");
    inScroll->layout()->addWidget(&dayLabel[5]);
    query.exec(queryStr1 + "5" + queryStr2);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,5,this));

    dayLabel[6].setText("Sunday");
    inScroll->layout()->addWidget(&dayLabel[6]);
    query.exec(queryStr1 + "6" + queryStr2);
    while (query.next())
        inScroll->layout()->addWidget(new Row(query,6,this));

}
