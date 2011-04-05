#include "row.h"
#include <QGridLayout>
#include <QLabel>
#include <QVariant>
#include <QTime>

Row::Row(QSqlQuery query, QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *gl = new QGridLayout;

    QLabel *stime = new QLabel(QTime(query.value(0).toInt(),query.value(1).toInt()).toString("h:mm"));
    QLabel *etime = new QLabel("~"+QTime(query.value(2).toInt(),query.value(3).toInt()).toString("h:mm"));
    QLabel *subj = new QLabel(query.value(4).toString());
    QLabel *prof = new QLabel(query.value(5).toString());
    QLabel *type = new QLabel(query.value(6).toString());
    QLabel *loc = new QLabel(query.value(7).toString());

    type->setFixedWidth(70);
    loc->setFixedWidth(70);

    gl->addWidget(stime,0,0);
    gl->addWidget(etime,1,0);
    gl->addWidget(subj,0,1);
    gl->addWidget(prof,1,1);
    gl->addWidget(type,0,2);
    gl->addWidget(loc,1,2);

    gl->setColumnStretch(1,1);

    setLayout(gl);

}
