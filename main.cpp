#include <QApplication>
#include <mainwidget.h>
//#include <QFile>

int main(int c, char **v)
{
    QApplication app(c,v);
//    QFile qss(":/style.qss");
//    qss.open(QFile::ReadOnly);
//    app.setStyleSheet(qss.readAll());
//    qss.close();
    MainWidget *mWidget = new MainWidget;

    mWidget->showMaximized();

    return app.exec();
}
