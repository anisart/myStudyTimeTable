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

    subjBox = new QComboBox(this);
    QSqlQuery query;
    query.exec("select subject from subjects");
    while (query.next())
        subjBox->addItem(query.value(0).toString());
    qDebug()<<query.lastError();
    subjBox->addItem("Add new");

    insl = new QWidget(this);
    subjEdit = new QLineEdit(this);
    typeEdit = new QLineEdit(this);
    profEdit = new QLineEdit(this);
    QVBoxLayout *inslLayout = new QVBoxLayout;
    inslLayout->addWidget(new QLabel("Subject"));
    inslLayout->addWidget(subjEdit);
    inslLayout->addWidget(new QLabel("Type"));
    inslLayout->addWidget(typeEdit);
    inslLayout->addWidget(new QLabel("Professor"));
    inslLayout->addWidget(profEdit);
    insl->setLayout(inslLayout);

    locEdit = new QLineEdit(this);
    startTime = new QTimeEdit(this);
    endTime = new QTimeEdit(this);
    QHBoxLayout *timeLayout = new QHBoxLayout;
    QHBoxLayout *dayLayout = new QHBoxLayout;
    QHBoxLayout *btnLayout = new QHBoxLayout;
    backBtn = new QPushButton("Back",this);

    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addWidget(new QLabel("Subject"));
    vbl->addWidget(subjBox);
    vbl->addWidget(insl);
    insl->hide();
    vbl->addWidget(new QLabel("Location"));
    vbl->addWidget(locEdit);
    vbl->addWidget(new QLabel("Time"));

    timeLayout->addWidget(new QLabel("from"));
    timeLayout->addWidget(startTime);
    timeLayout->addWidget(new QLabel("to"));
    timeLayout->addWidget(endTime);
    vbl->addItem(timeLayout);

    dayLayout->addWidget(new QLabel("Weekday"));
    dayLayout->addWidget(dayBox);
    vbl->addItem(dayLayout);

    commitBtn = new QPushButton("Commit",this);
    btnLayout->addWidget(commitBtn);

    if (mode == "new")
    {
        connect(commitBtn,SIGNAL(clicked()),this,SLOT(on_commitBtnN_clicked()));
    }
    if (mode == "edit")
    {
        connect(commitBtn,SIGNAL(clicked()),this,SLOT(on_commitBtnE_clicked()));
        //////////////////////////////////
        locEdit->setText(row->loc);
        startTime->setTime(row->stime);
        endTime->setTime(row->etime);
        dayBox->setCurrentIndex(row->weekday);
        _id = row->_id;
    }

    btnLayout->addWidget(backBtn);
    vbl->addItem(btnLayout);

    setLayout(vbl);

    connect(backBtn,SIGNAL(clicked()),this,SLOT(on_backBtn_clicked()));
    connect(subjBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_subjBox_changed(QString)));
}

void EditWindow::on_subjBox_changed(QString item)
{
    if (item != "Add new")
        insl->hide();
//    SubjWindow *subjWin = new SubjWindow;
//    subjWin->show();
    else
        insl->show();
}

void EditWindow::on_commitBtnN_clicked()
{
    QSqlQuery query;
    query.exec("select id from subjects where subject = '" + subjBox->currentText() + "'");
    qDebug()<<subjBox->currentText();
    query.next();
    qDebug()<<query.value(0).toInt();
    int subj_id = query.value(0).toInt();

    query.exec("insert into weeks (subject_id, location, "
               "start_h, start_m, end_h, end_m, weekday) values ("
               + QString::number(subj_id) + ",'"
               + locEdit->text() + "',"
               + QString::number(startTime->time().hour()) + ","
               + QString::number(startTime->time().minute()) + ","
               + QString::number(endTime->time().hour()) + ","
               + QString::number(endTime->time().minute()) + ","
               + QString::number(dayBox->currentIndex()) + ")");
    qDebug()<<query.lastError();
    close();
}

void EditWindow::on_commitBtnE_clicked()
{
    QSqlQuery query;
    query.exec("update weeks set "
               "subject='testSubj"
               "',type='testType"
               "',professor='testProf"
               "',location='" + locEdit->text()
               + "',start_h=" + QString::number(startTime->time().hour())
               + ",start_m=" + QString::number(startTime->time().minute())
               + ",end_h=" + QString::number(endTime->time().hour())
               + ",end_m=" + QString::number(endTime->time().minute())
               + ",weekday=" + QString::number(dayBox->currentIndex())
               + " where id=" + QString::number(_id));
    qDebug()<<query.lastError();
    close();
}

void EditWindow::on_backBtn_clicked()
{
    close();
}

void EditWindow::new_subject_added(QString subject)
{
    subjBox->removeItem(subjBox->currentIndex());
    subjBox->addItem(subject);
    subjBox->addItem("Add new");
}
