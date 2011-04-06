#ifndef ROW_H
#define ROW_H

#include <QWidget>
#include <QSqlQuery>
#include <QMouseEvent>

class Row : public QWidget
{
    Q_OBJECT

public:
    explicit Row(QSqlQuery query, QWidget *parent = 0);

signals:

public slots:

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

};

#endif // ROW_H
