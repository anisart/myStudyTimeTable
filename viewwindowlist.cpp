#include "viewwindowlist.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>
#include <QVariant>
#include <QString>
#include <QListWidget>
#include <QSqlQuery>
#include <QDesktopServices>
#include <QUrl>
#include <QPushButton>
ViewWindowList::ViewWindowList(int subject_id,QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout *vbl=new QVBoxLayout();
    QListWidget *list=new QListWidget();
    QSqlQuery query;
    query.exec("select path from files where subject_id="+QString::number(subject_id));
    while(query.next())
    {
        list->addItem(query.value(0).toString());
    }
    vbl->addWidget(list);
    setLayout(vbl);
    connect(list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(on_view_clicked(QListWidgetItem*)));
}

void ViewWindowList::on_view_clicked(QListWidgetItem *item)
{
    QDesktopServices::openUrl(QUrl("File:///"+item->text()));
    qDebug()<<item->text();

}

