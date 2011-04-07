#ifndef ROW_H
#define ROW_H

#include <QStackedWidget>
#include <QSqlQuery>
#include <QMouseEvent>
#include <QPushButton>

class Row : public QStackedWidget
{
    Q_OBJECT
    int id;
    QSqlQuery query;
    QPushButton *backBtn, *editBtn, *deleteBtn;

    void deleteRow();

public:
    explicit Row(QSqlQuery dataQuery, QWidget *parent = 0);

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
