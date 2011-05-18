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
    QStackedWidget(parent)
{

    QWidget *firstWidget = new QWidget(this);

    QGridLayout *gl = new QGridLayout();


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

    gl->setColumnStretch(.1,.1);
    firstWidget->setLayout(gl);
    setMaximumHeight(50);
    addWidget(firstWidget);


}

void Row::mousePressEvent(QMouseEvent *e)
{
    qDebug()<<"press id = "<<_id;
}

void Row::mouseReleaseEvent(QMouseEvent *e)
{
    qDebug()<<"release id = "<<_id;
    setCurrentIndex(1);
    ////////////////////////////////////
    QVBoxLayout *gl = new QVBoxLayout();

    QLabel *Lab = new QLabel("Time lessons: " + stime.toString("h:mm")+ " to " + etime.toString("h:mm"));
    QLabel *subjLab = new QLabel("Subject: "+subj);
    QLabel *profLab = new QLabel("Professor: "+prof);
    QLabel *typeLab = new QLabel("Type: "+ type);
    QLabel *locLab = new QLabel("Location: "+loc);
    QDialog *info=new QDialog();

    typeLab->setFixedWidth(70);
    locLab->setFixedWidth(70);


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
    vbl->addWidget(fileBtn);
    vbl->addWidget(editBtn);
    vbl->addWidget(deleteBtn);
    info->setLayout(vbl);
    vbl->addWidget(backBtn);
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
void Row::on_backBtn_clicked()
{
    setCurrentIndex(0);
}

void Row::on_editBtn_clicked()
{
    EditWindow *editWin = new EditWindow("edit",this);
    editWin->showFullScreen();
    setCurrentIndex(0);
}

void Row::deleteRow()
{
    query.exec("delete from weeks where  id = " + QString::number(_id));
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
    query.exec("select subject_id from weeks where id = "+QString::number(_id));
    query.next();
    QWidget *wig=new QWidget();
    QPushButton *closeBtn=new QPushButton("Close");
    QVBoxLayout *vbl=new QVBoxLayout();
    ViewWindowList *viewWin= new ViewWindowList(query.value(0).toInt(),this);
    vbl->addWidget(viewWin);
    vbl->addWidget(closeBtn);
    wig->setLayout(vbl);
    wig->showFullScreen();
    connect(closeBtn,SIGNAL(clicked()),wig,SLOT(close()));
}
