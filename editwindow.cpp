#include "editwindow.h"
#include <QLabel>
#include <QStringList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlQuery>

#include <QDebug>
#include <QSqlError>
#include "mainwindow.h"

EditWindow::EditWindow(QString mode, Row *row, QWidget *parent) :
    QScrollArea(parent)
{
    inScroll = new QWidget(this);
    setWidgetResizable(true);
    setWidget(inScroll);
    setContentsMargins(0,0,0,0);

    dayBox = new QComboBox(this);
    QStringList days;
    days<<"Monday"<<"Thuesday"<<"Wednesday"<<"Thursday"<<"Friday"<<"Saturday"<<"Sunday";
    dayBox->addItems(days);

    weekBox = new QComboBox(this);
    QStringList weeks;
    weeks<<"Lower"<<"Upper";
    weekBox->addItems(weeks);

    subjBox = new QComboBox(this);
    QSqlQuery query;
    query.exec("select subject from subjects");
    while (query.next())
        subjBox->addItem(query.value(0).toString());
    qDebug()<<query.lastError();

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
    startTime->setDisplayFormat("h:mm");
    endTime = new QTimeEdit(this);
    endTime->setDisplayFormat("h:mm");


    QHBoxLayout *timeLayout = new QHBoxLayout;
    QHBoxLayout *dayLayout = new QHBoxLayout;
    QHBoxLayout *weekLayout = new QHBoxLayout;
    QHBoxLayout *btnLayout = new QHBoxLayout;
    backBtn = new QPushButton("Back",this);

    QVBoxLayout *vbl = new QVBoxLayout;
    vbl->addWidget(new QLabel("Subject"));
    vbl->addWidget(subjBox);
    vbl->addWidget(insl);
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

    weekLayout->addWidget(new QLabel("Week"));
    weekLayout->addWidget(weekBox);
    vbl->addItem(weekLayout);

    commitBtn = new QPushButton("Commit",this);
    btnLayout->addWidget(commitBtn);

    if (mode == "new")
    {
        subjBox->addItem("Add new");
        weekBox->addItem("Both");
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

    insl->hide();
    if ((mode == "new") && (subjBox->count() == 1))
        insl->show();

    btnLayout->addWidget(backBtn);
    vbl->addItem(btnLayout);

    inScroll->setLayout(vbl);

    connect(backBtn,SIGNAL(clicked()),this,SLOT(on_backBtn_clicked()));
    connect(subjBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(on_subjBox_changed(QString)));
}

void EditWindow::on_subjBox_changed(QString item)
{
    if (item != "Add new")
        insl->hide();
    else
        insl->show();
}

void EditWindow::on_commitBtnN_clicked()
{
    QSqlQuery query;
    QString subj_id;

    if (subjBox->currentText() != "Add new")
    {
        query.exec("select id from subjects where subject = '" + subjBox->currentText() + "'");
        query.next();
        subj_id = query.value(0).toString();
    }
    else
    {
        if (subjEdit->text() != "")
        {
            query.exec("insert into subjects (subject, type, professor)"
                       "values ('" + subjEdit->text() + "','"
                       + typeEdit->text() + "','" + profEdit->text() + "')");
            query.exec("select id from subjects");
            query.last();
            subj_id = query.value(0).toString();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setInformativeText("Input name of new subject in field 'Subject'!");
            msgBox.setStandardButtons(QMessageBox::Ok);
            int ret = msgBox.exec();
            return;
        }
    }

    switch (weekBox->currentIndex())
    {
    case 0: insertRow(subj_id,"1");
    case 1: insertRow(subj_id,"0");
    case 2: insertRow(subj_id,"1");
            insertRow(subj_id,"0");
    }
    emit dataChanged();
    MainWindow *my_window= new MainWindow();
    close();
    my_window->showMaximized();

}

void EditWindow::on_commitBtnE_clicked()
{
    QSqlQuery query;
    query.exec("select id from subjects where subject = '" + subjBox->currentText() + "'");
    query.next();
    query.exec("update weeks set "
               "subject_id='" + query.value(0).toString()
               + "',location='" + locEdit->text()
               + "',start_h=" + startTime->time().toString("H")
               + ",start_m=" + startTime->time().toString("mm")
               + ",end_h=" + endTime->time().toString("H")
               + ",end_m=" + endTime->time().toString("mm")
               + ",weekday=" + QString::number(dayBox->currentIndex())
               + ",is_week_upper=" + QString::number(weekBox->currentIndex())
               + " where id=" + _id);
    qDebug()<<query.lastError();
    emit dataChanged();
    MainWindow *my_window= new MainWindow();
    close();
    my_window->showMaximized();
}

void EditWindow::on_backBtn_clicked()
{
    close();
}

void EditWindow::insertRow(QString subj, QString week)
{
    QSqlQuery query;
    query.exec("insert into weeks (subject_id, location, start_h, "
               "start_m, end_h, end_m, weekday, is_week_upper) values ("
               + subj + ",'"
               + locEdit->text() + "',"
               + startTime->time().toString("H") + ","
               + startTime->time().toString("mm") + ","
               + endTime->time().toString("H") + ","
               + endTime->time().toString("mm") + ","
               + QString::number(dayBox->currentIndex()) + ","
               + week + ")");
}
