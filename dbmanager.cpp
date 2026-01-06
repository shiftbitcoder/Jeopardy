#include "dbmanager.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

dbmanager::dbmanager(){

}
bool dbmanager::openDatabase(){
    qDebug() << "Available SQL Driver:" << QSqlDatabase::drivers();

    QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataDir);

    QString dbPath = dataDir + "/jeopardy.db";

    if (!QFile::exists(dbPath)) {
        if (!QFile::copy(":/db/jeopardy.db", dbPath)) {
            qDebug() << "Failed to copy database to" << dbPath;
            return false;
        } else {
            qDebug() << "Database copied to:" << dbPath;
        }
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Database Error:" << db.lastError().text();
        return false;   // ✅ return on failure
    }

    qDebug() << "Database opened successfully at:" << dbPath;
    return true;        // ✅ return on success
}

QList<Category> dbmanager::loadRandomCategories(){
    QList<Category> categories;

    if (!openDatabase()){
        return categories;
    }

    QSqlQuery query ("SELECT * FROM categories ORDER BY RANDOM() LIMIT 5");

    if (query.exec()){
        while(query.next()){
            Category category;
            category.name=query.value("cat_name").toString();
            category.cat_id = query.value("category_id").toInt();
            category.questions =loadRandomQuestions(category.cat_id);

            categories.append(category);
        }
    }else{
        qDebug()<<"Error fetching random categories "<< query.lastError().text();
    }
    db.close();
    return categories;
}

QList<Questions> dbmanager::loadRandomQuestions(int category_id){
    QList<Questions> questions;

    if (!openDatabase()){
        return questions;
    }
    for (int points=100; points<500; points+=100){
        QSqlQuery query;
        query.prepare("Select * FROM questions where category_id = :category_id and points = :level");
        query.bindValue("category_id", category_id);
        query.bindValue("points", points);
    }
}
