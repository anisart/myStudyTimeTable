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
    query.exec("create table if not exists weeks"
               "(id integer primary key, "
               "subject_id integer, "
               "location text, "
               "start_h integer, "
               "start_m integer, "
               "end_h integer, "
               "end_m integer, "
               "weekday integer,"
               "is_week_upper boolean)");
    query.exec("create table if not exists subjects"
               "(id integer primary key, "
               "subject text, "
               "subject_full text, "
               "type text, "
               "professor text, "
               "professor_full text)");
    query.exec("create table if not exists files"
               "(id integer primary key, "
               "subject_id integer, "
               "path text)");

    QFile file;
    QSqlQuery dquery;
    while (query.next())
        if (!file.exists(query.value(0).toString()))
            dquery.exec("delete from files where id=" + query.value(1).toString());
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
