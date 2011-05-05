#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QWidget>
#include <QScrollArea>

class TimeTable : public QScrollArea
{
    Q_OBJECT
    QWidget *inScroll;
public:
    explicit TimeTable(QWidget *parent = 0);
    void createTable();
signals:

public slots:

};

#endif // TIMETABLE_H
