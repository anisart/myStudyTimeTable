#ifndef ROW_H
#define ROW_H

#include <QSqlQuery>
#include <QMouseEvent>
#include <QPushButton>
#include <QTime>

class Row : public QWidget
{
    Q_OBJECT

    QSqlQuery query;
    QPushButton *backBtn, *editBtn, *deleteBtn, *fileBtn ;
    QWidget *parentW;

    void deleteRow();

public:
    explicit Row(QSqlQuery dataQuery, int wday, QWidget *parent = 0);
    QString subj, prof, type, loc, _id;
    QTime stime, etime;
    int weekday;

signals:

public slots:
    void on_editBtn_clicked();
    void on_deleteBtn_clicked();
    void on_fileBtn_clicked();

protected:
    void mouseReleaseEvent(QMouseEvent *e);


};


#endif // ROW_H
