#ifndef VIEWWINDOWLIST_H
#define VIEWWINDOWLIST_H

#include <QWidget>
#include <QListWidget>
#include <QMainWindow>
class ViewWindowList : public QWidget
{
    Q_OBJECT
public:
    explicit ViewWindowList(QString subject_id=0,QWidget *parent = 0);

signals:

public slots:
    void on_view_clicked(QListWidgetItem*);


};

#endif // VIEWWINDOWLIST_H
