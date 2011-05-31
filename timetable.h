#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>

class TimeTable : public QScrollArea
{
    Q_OBJECT
    QWidget *inScroll;
    QLabel dayLabel[7];



public:
    explicit TimeTable(QWidget *parent = 0, QString weekIsUpper= 0);
    void createTable(QString week);
signals:
    void closed();

public slots:

protected:
    void closeEvent(QCloseEvent *);

};


#endif // TIMETABLE_H
