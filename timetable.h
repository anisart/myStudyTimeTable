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
    explicit TimeTable(QWidget *parent = 0);
    void createTable();
signals:

public slots:

};

#endif // TIMETABLE_H
