#ifndef DBMANAGER_H
#define DBMANAGER_H

#include "categories.h"
#include "questions.h"
#include <QtSql/QSqlDatabase>
#include <QList>



class DbManager
{
public:
    DbManager();
    ~DbManager();
    bool openDatabase();

    QList<Category> loadRandomCategories();

    QList<Questions> loadRandomQuestions(int category_id);

private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
