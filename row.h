#ifndef ROW_H
#define ROW_H

#include <QStackedWidget>
#include <QSqlQuery>
#include <QMouseEvent>
#include <QPushButton>
#include <QTime>

class Row : public QStackedWidget
{
    Q_OBJECT

    QSqlQuery query;
    QPushButton *backBtn, *editBtn, *deleteBtn;

    void deleteRow();

public:
    explicit Row(QSqlQuery dataQuery, int wday, QWidget *parent = 0);
    QString subj, prof, type, loc;
    QTime stime, etime;
    int weekday, _id;

signals:

public slots:
    void on_backBtn_clicked();
    void on_editBtn_clicked();
    void on_deleteBtn_clicked();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);


};


#endif // ROW_H
