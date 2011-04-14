#include "row.h"
#include <QGridLayout>
#include <QLabel>
#include <QVariant>
#include "editwindow.h"

#include <QDebug>
#include <QSqlError>

Row::Row(QSqlQuery dataQuery, int wday, QWidget *parent) :
    QStackedWidget(parent)
{
    backBtn = new QPushButton("Back",this);
    editBtn = new QPushButton("Edit",this);
    deleteBtn = new QPushButton("Delete",this);

    QWidget *firstWidget = new QWidget(this);
    QWidget *secondWidget = new QWidget(this);
    QGridLayout *gl = new QGridLayout();
    QHBoxLayout *vbl = new QHBoxLayout();

    stime = QTime(dataQuery.value(0).toInt(),dataQuery.value(1).toInt());
    etime = QTime(dataQuery.value(2).toInt(),dataQuery.value(3).toInt());
    subj = dataQuery.value(4).toString();
    prof = dataQuery.value(5).toString();
    type = dataQuery.value(6).toString();
    loc = dataQuery.value(7).toString();
    _id = dataQuery.value(8).toInt();
    weekday = wday;

    QLabel *stimeLab = new QLabel(stime.toString("h:mm"));
    QLabel *etimeLab = new QLabel("~" + etime.toString("h:mm"));
    QLabel *subjLab = new QLabel(subj);
    QLabel *profLab = new QLabel(prof);
    QLabel *typeLab = new QLabel(type);
    QLabel *locLab = new QLabel(loc);

    typeLab->setFixedWidth(70);
    locLab->setFixedWidth(70);

    gl->addWidget(stimeLab,0,0);
    gl->addWidget(etimeLab,1,0);
    gl->addWidget(subjLab,0,1);
    gl->addWidget(profLab,1,1);
    gl->addWidget(typeLab,0,2);
    gl->addWidget(locLab,1,2);

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
    qDebug()<<"press id = "<<_id;
}

void Row::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug()<<"release id = "<<_id;
    setCurrentIndex(1);
}

void Row::deleteRow()
{
    query.exec("delete from weeks where id = " + QString::number(_id));
    qDebug()<<query.lastError();
}

void Row::on_backBtn_clicked()
{
    setCurrentIndex(0);
}

void Row::on_editBtn_clicked()
{
//    EditWindow editWin("edit",this);
    EditWindow *editWin = new EditWindow("edit",this);
    editWin->showMaximized();
    setCurrentIndex(0);
}

void Row::on_deleteBtn_clicked()
{
    deleteRow();
    close();
}
