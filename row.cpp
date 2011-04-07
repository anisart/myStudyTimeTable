#include "row.h"
#include <QGridLayout>
#include <QLabel>
#include <QVariant>
#include <QTime>

#include <QDebug>
#include <QSqlError>

Row::Row(QSqlQuery dataQuery, QWidget *parent) :
    QStackedWidget(parent)
{
    backBtn = new QPushButton("Back",this);
    editBtn = new QPushButton("Edit",this);
    deleteBtn = new QPushButton("Delete",this);

    QWidget *firstWidget = new QWidget(this);
    QWidget *secondWidget = new QWidget(this);
    QGridLayout *gl = new QGridLayout();
    QHBoxLayout *vbl = new QHBoxLayout();

    QLabel *stime = new QLabel(QTime(dataQuery.value(0).toInt(),dataQuery.value(1).toInt()).toString("h:mm"));
    QLabel *etime = new QLabel("~"+QTime(dataQuery.value(2).toInt(),dataQuery.value(3).toInt()).toString("h:mm"));
    QLabel *subj = new QLabel(dataQuery.value(4).toString());
    QLabel *prof = new QLabel(dataQuery.value(5).toString());
    QLabel *type = new QLabel(dataQuery.value(6).toString());
    QLabel *loc = new QLabel(dataQuery.value(7).toString());
    id = dataQuery.value(8).toInt();

    type->setFixedWidth(70);
    loc->setFixedWidth(70);

    gl->addWidget(stime,0,0);
    gl->addWidget(etime,1,0);
    gl->addWidget(subj,0,1);
    gl->addWidget(prof,1,1);
    gl->addWidget(type,0,2);
    gl->addWidget(loc,1,2);

    gl->setColumnStretch(1,1);

    firstWidget->setLayout(gl);

    vbl->addWidget(backBtn);
    vbl->addWidget(editBtn);
    vbl->addWidget(deleteBtn);
    secondWidget->setLayout(vbl);

    addWidget(firstWidget);
    addWidget(secondWidget);

    connect(backBtn,SIGNAL(clicked()),this,SLOT(on_backBtn_clicked()));
    connect(editBtn,SIGNAL(clicked()),this,SLOT(on_editBtn_clicked()));
    connect(deleteBtn,SIGNAL(clicked()),this,SLOT(on_deleteBtn_clicked()));
}

void Row::mousePressEvent(QMouseEvent *e)
{
    qDebug()<<"press id = "<<id;
}

void Row::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug()<<"release id = "<<id;
    setCurrentIndex(1);
}

void Row::deleteRow()
{
    query.exec("delete from weeks where _id = " + QString::number(id));
    qDebug()<<query.lastError();
}

void Row::on_backBtn_clicked()
{
    setCurrentIndex(0);
}

void Row::on_editBtn_clicked()
{

}

void Row::on_deleteBtn_clicked()
{
    deleteRow();
    hide();
}
