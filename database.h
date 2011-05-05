#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QDir>
#include <QSqlQuery>

QSqlDatabase db;

bool openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    #ifdef Q_OS_LINUX
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("STT.db");
    path = QDir::toNativeSeparators(path);
    db.setDatabaseName(path);
    #else
    db.setDatabaseName("STT.db");
    #endif

    return db.open();
}

void initDB()
{
    QSqlQuery query;
    query.exec("create table weeks"
               "(id integer primary key, "
               "subject_id integer, "
               "location text, "
               "start_h integer, "
               "start_m integer, "
               "end_h integer, "
               "end_m integer, "
               "weekday integer,"
               "is_week_upper boolean)");
    query.exec("create table subjects"
               "(id integer primary key, "
               "subject text, "
               "subject_full text, "
               "type text, "
               "professor text, "
               "professor_full text)");
}

bool deleteDB()
{
    db.close();

    #ifdef Q_OS_LINUX
    QString path(QDir::home().path());
    path.append(QDir::separator()).append("STT.db");
    path = QDir::toNativeSeparators(path);
    return QFile::remove(path);
    #else
    return QFile::remove("STT.db");
    #endif
 }
#endif
