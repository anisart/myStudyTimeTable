#include "editwindow.h"
#include <QLabel>
#include <QStringList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlQuery>

#include <QDebug>
#include <QSqlError>

EditWindow::EditWindow(QString mode, Row *row, QWidget *parent) :
    QWidget(parent)
{
    dayBox = new QComboBox(this);
    QStringList days;
    days<<"Monday"<<"Thuesday"<<"Wednesday"<<"Thursday"<<"Friday"<<"Saturday"<<"Sunday";
    dayBox->addItems(days);
    subjEdit = new QLineEdit(this);
    typeEdit = new QLineEdit(this);
    profEdit = new QLineEdit(this);
    locEdit = new QLineEdit(this);
    startTime = new QTimeEdit(this);
    endTime = new QTimeEdit(this);
    QHBoxLayout *timeLayout = new QHBoxLayout;
    QHBoxLayout *dayLayout = new QHBoxLayout;
    QHBoxLayout *btnLayout = new QHBoxLayout;
    backBtn = new QPushButton("Back",this);

    setLayout(new QVBoxLayout(this));
    layout()->addWidget(new QLabel("Subject"));
    layout()->addWidget(subjEdit);
    layout()->addWidget(new QLabel("Type"));
    layout()->addWidget(typeEdit);
    layout()->addWidget(new QLabel("Professor"));
    layout()->addWidget(profEdit);
    layout()->addWidget(new QLabel("Location"));
    layout()->addWidget(locEdit);  
    layout()->addWidget(new QLabel("Time"));

    timeLayout->addWidget(new QLabel("from"));
    timeLayout->addWidget(startTime);
    timeLayout->addWidget(new QLabel("to"));
    timeLayout->addWidget(endTime);
    layout()->addItem(timeLayout);

    dayLayout->addWidget(new QLabel("Weekday"));
    dayLayout->addWidget(dayBox);
    layout()->addItem(dayLayout);
    commitBtn = new QPushButton("Commit",this);
    btnLayout->addWidget(commitBtn);

    if (mode == "new")
    {
        connect(commitBtn,SIGNAL(clicked()),this,SLOT(on_commitBtnN_clicked()));
    }
    if (mode == "edit")
    {
        connect(commitBtn,SIGNAL(clicked()),this,SLOT(on_commitBtnE_clicked()));
        subjEdit->setText(row->subj);
        typeEdit->setText(row->type);
        profEdit->setText(row->prof);
        locEdit->setText(row->loc);
        startTime->setTime(row->stime);
        endTime->setTime(row->etime);
        dayBox->setCurrentIndex(row->weekday);
        _id = row->_id;
    }

    btnLayout->addWidget(backBtn);
    layout()->addItem(btnLayout);

    connect(backBtn,SIGNAL(clicked()),this,SLOT(on_backBtn_clicked()));
}

void EditWindow::on_commitBtnN_clicked()
{
    QSqlQuery query;
    query.exec("insert into weeks (subject, type, professor, location, \
               start_h, start_m, end_h, end_m, weekday) values ('"
               + subjEdit->text() + "','" + typeEdit->text() + "','"
               + profEdit->text() + "','" + locEdit->text() + "','"
               + QString::number(startTime->time().hour()) + "','"
               + QString::number(startTime->time().minute()) + "','"
               + QString::number(endTime->time().hour()) + "','"
               + QString::number(endTime->time().minute()) + "','"
               + QString::number(dayBox->currentIndex()) + "')");
    qDebug()<<query.lastError();
    close();
}

void EditWindow::on_commitBtnE_clicked()
{
    QSqlQuery query;
    query.exec("update weeks set \
               subject='" + subjEdit->text()
               + "',type='" + typeEdit->text()
               + "',professor='" + profEdit->text()
               + "',location='" + locEdit->text()
               + "',start_h='" + QString::number(startTime->time().hour())
               + "',start_m='" + QString::number(startTime->time().minute())
               + "',end_h='" + QString::number(endTime->time().hour())
               + "',end_m='" + QString::number(endTime->time().minute())
               + "',weekday='" + QString::number(dayBox->currentIndex())
               + "' where _id=" + QString::number(_id));
    qDebug()<<query.lastError();
    close();
}

void EditWindow::on_backBtn_clicked()
{
    close();
}
