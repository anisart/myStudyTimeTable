#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QTimeEdit>

class EditWindow : public QWidget
{
    Q_OBJECT
    QPushButton *commitBtn, *backBtn;
    QLineEdit *subjEdit, *typeEdit, *profEdit, *locEdit;
    QTimeEdit *startTime, *endTime;
    QComboBox *dayBox;

public:
    explicit EditWindow(QWidget *parent = 0);

signals:

public slots:
    void on_commitBtn_clicked();
    void on_backBtn_clicked();
};

#endif // EDITWINDOW_H
