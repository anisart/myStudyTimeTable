#include <QApplication>
#include "optionmenu.h"
//#include <QFile>
#include "database.h"

int main(int c, char **v)
{
    QApplication app(c,v);
//    QFile qss(":/style.qss");
//    qss.open(QFile::ReadOnly);
//    app.setStyleSheet(qss.readAll());
//    qss.close();

    openDB();
    initDB();

   OptionsMenu menu;

    menu.showMaximized();


    return app.exec();
}
