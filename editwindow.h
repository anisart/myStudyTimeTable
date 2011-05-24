#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTimeEdit>
#include <QScrollArea>
#include "row.h"

class EditWindow : public QScrollArea
{
    Q_OBJECT
    QPushButton *commitBtn, *backBtn;
    QLineEdit *locEdit, *subjEdit, *typeEdit, *profEdit;
    QTimeEdit *startTime, *endTime;
    QComboBox *subjBox, *dayBox;
    QWidget *insl;
    QWidget *inScroll;
    int _id;

public:
    explicit EditWindow(QString mode = "new", Row *row = 0, QWidget *parent = 0);

signals:
    void dataChanged();

public slots:
    void on_subjBox_changed(QString);
    void on_commitBtnN_clicked();
    void on_commitBtnE_clicked();
    void on_backBtn_clicked();
};

#endif // EDITWINDOW_H
