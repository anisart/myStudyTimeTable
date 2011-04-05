#include "editwindow.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QStringList>
#include <QVBoxLayout>
#include <QTimeEdit>
#include <QHBoxLayout>

EditWindow::EditWindow(QWidget *parent) :
    QWidget(parent)
{
    QComboBox *dayBox = new QComboBox(this);
    QStringList days;
    days<<"Monday"<<"Thuesday"<<"Wednesday"<<"Thursday"<<"Friday"<<"Saturday"<<"Sunday";
    QLineEdit *subjEdit = new QLineEdit(this);
    QLineEdit *typeEdit = new QLineEdit(this);
    QLineEdit *profEdit = new QLineEdit(this);
    QLineEdit *locEdit = new QLineEdit(this);
    QTimeEdit *startTime = new QTimeEdit(this);
    QTimeEdit *endTime = new QTimeEdit(this);
    QHBoxLayout *timeLayout = new QHBoxLayout;
    QHBoxLayout *dayLayout = new QHBoxLayout;

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

    dayBox->addItems(days);
}
