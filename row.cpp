#include "row.h"
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QVariant>
#include "editwindow.h"
#include "viewwindowlist.h"
#include <QDebug>
#include <QDialog>
#include <QSqlError>
#include <QPushButton>

Row::Row(QSqlQuery dataQuery, int wday, QWidget *parent) :
    QWidget(parent)
{
    QGridLayout *gl = new QGridLayout();


    stime = QTime(dataQuery.value(0).toInt(),dataQuery.value(1).toInt());
    etime = QTime(dataQuery.value(2).toInt(),dataQuery.value(3).toInt());
    subj = dataQuery.value(4).toString();
    prof = dataQuery.value(5).toString();
    type = dataQuery.value(6).toString();
    loc = dataQuery.value(7).toString();
    _id = dataQuery.value(8).toString();
    weekday = wday;

    QLabel *stimeLab = new QLabel(stime.toString("H:mm"));
    QLabel *etimeLab = new QLabel("~" + etime.toString("H:mm"));
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

    gl->setColumnStretch(.1,.1);
    setLayout(gl);
    setMaximumHeight(70);

    parentW=parent;
}

void Row::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug()<<"release id = "<<_id;
    ////////////////////////////////////
    QVBoxLayout *gl = new QVBoxLayout();

    QLabel *Lab = new QLabel("Time lessons: " + stime.toString("H:mm")+ " to "
                             + etime.toString("H:mm"));
    QLabel *subjLab = new QLabel("Subject: "+subj);
    QLabel *profLab = new QLabel("Professor: "+prof);
    QLabel *typeLab = new QLabel("Type: "+ type);
    QLabel *locLab = new QLabel("Location: "+loc);
    QDialog *info=new QDialog();


    gl->addWidget(subjLab);
    gl->addWidget(profLab);
    gl->addWidget(typeLab);
    gl->addWidget(Lab);
    gl->addWidget(locLab);



    backBtn = new QPushButton("Back",this);
    editBtn = new QPushButton("Edit",this);
    deleteBtn = new QPushButton("Delete",this);
    fileBtn = new QPushButton("Files",this);

    QVBoxLayout *vbl=new QVBoxLayout();
    vbl->addLayout(gl);
    #ifdef Q_WS_MAEMO_5
    QGridLayout *btns=new QGridLayout();
    btns->addWidget(fileBtn,0,0);
    btns->addWidget(editBtn,0,1);
    btns->addWidget(deleteBtn,1,0);
    btns->addWidget(backBtn,1,1);
    vbl->addLayout(btns);
    #else
    vbl->addWidget(fileBtn);
    vbl->addWidget(editBtn);
    vbl->addWidget(deleteBtn);
    vbl->addWidget(backBtn);
    #endif
    info->setLayout(vbl);
    connect(backBtn,SIGNAL(clicked()),info,SLOT(close()));
    connect(editBtn,SIGNAL(clicked()),this,SLOT(on_editBtn_clicked()));
    connect(editBtn,SIGNAL(clicked()),info,SLOT(close()));
    connect(deleteBtn,SIGNAL(clicked()),this,SLOT(on_deleteBtn_clicked()));
    connect(deleteBtn,SIGNAL(clicked()),info,SLOT(close()));
    connect(fileBtn,SIGNAL(clicked()),this,SLOT(on_fileBtn_clicked()));
    connect(fileBtn,SIGNAL(clicked()),info,SLOT(close()));
    info->setMaximumSize(200,400);
    info->showMaximized();



}

void Row::on_editBtn_clicked()
{
    EditWindow *editWin = new EditWindow("edit",this);
    editWin->showFullScreen();
    connect(editWin,SIGNAL(dataChanged()),parentW,SLOT(close()));
}

void Row::deleteRow()
{
    query.exec("delete from weeks where  id = " + _id);
    qDebug()<<query.lastError();
}


void Row::on_deleteBtn_clicked()
{
    deleteRow();
    close();
}
void Row::on_fileBtn_clicked()
{
    QSqlQuery query;
    query.exec("select subject_id from weeks where id = " + _id);
    query.next();
    QWidget *wig=new QWidget();
    QPushButton *closeBtn=new QPushButton("Close");
    QVBoxLayout *vbl=new QVBoxLayout();
    ViewWindowList *viewWin= new ViewWindowList(query.value(0).toString(),this);
    vbl->addWidget(viewWin);
    vbl->addWidget(closeBtn);
    wig->setLayout(vbl);
    wig->showFullScreen();
    connect(closeBtn,SIGNAL(clicked()),wig,SLOT(close()));
}
