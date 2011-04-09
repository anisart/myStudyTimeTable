#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTimeEdit>
#include "row.h"

class EditWindow : public QWidget
{
    Q_OBJECT
    QPushButton *commitBtn, *backBtn;
    QLineEdit *subjEdit, *typeEdit, *profEdit, *locEdit;
    QTimeEdit *startTime, *endTime;
    QComboBox *dayBox;
    int _id;

public:
    explicit EditWindow(QString mode = "new", Row *row = 0, QWidget *parent = 0);

signals:

public slots:
    void on_commitBtnN_clicked();
    void on_commitBtnE_clicked();
    void on_backBtn_clicked();
};

#endif // EDITWINDOW_H
