#ifndef ROW_H
#define ROW_H
#include <QWidget>
#include <QSqlQuery>

class Row : public QWidget
{
    Q_OBJECT
public:
    explicit Row(QSqlQuery query, QWidget *parent = 0);

signals:

public slots:

};


#endif // ROW_H
