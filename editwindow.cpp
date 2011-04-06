#include "editwindow.h"
#include <QLabel>
#include <QStringList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSqlQuery>

EditWindow::EditWindow(QWidget *parent) :
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
    commitBtn = new QPushButton("Commit",this);

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

    layout()->addWidget(commitBtn);
    connect(commitBtn,SIGNAL(clicked()),this,SLOT(on_commitBtn_clicked()));
}

void EditWindow::on_commitBtn_clicked()
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
}
