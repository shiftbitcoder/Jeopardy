#include "dbmanager.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStandardPaths>
#include <QDir>
#include <QFile>
#include <QDebug>

DbManager::DbManager(){
    if (QSqlDatabase::contains("jeopardy_connection")) {
            db = QSqlDatabase::database("jeopardy_connection");
        } else {
            db = QSqlDatabase::addDatabase("QSQLITE", "jeopardy_connection");
        }
}

DbManager::~DbManager()
{
    if (db.isOpen())
        db.close();
}


bool DbManager::openDatabase() {
    // Use your actual database path
    QString dbPath = "/home/aser1206/Codes/Jeopardy/db/jeopardy.db";

    //QString dbPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/jeopardy.db";



    // Open the database
    db.setDatabaseName(dbPath);
    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
        return false;
    }

    qDebug() << "Database opened successfully at:" << dbPath;

    // Check what tables exist
    QStringList tables = db.tables();
    if (tables.isEmpty()) {
        qDebug() << "WARNING: Database appears empty! No tables found.";
        return false;
    }

    qDebug() << "Tables in database:" << tables;

    // Ensure 'categories' table exists
    if (!tables.contains("categories", Qt::CaseInsensitive)) {
        qDebug() << "WARNING: 'categories' table not found! Queries will fail.";
        return false;
    }

    return true;
}


QList<Category> DbManager::loadRandomCategories()
{
    QList<Category> categories;

    if (!openDatabase()) {
        qDebug() << "Database failed to open!";
        return categories;
    }

    QSqlQuery query(db);
    //QString sql = "SELECT category_id, cat_name FROM categories ORDER BY RANDOM() LIMIT 5";
    QString sql = R"(SELECT category_id, cat_name
                      FROM categories
                      WHERE cat_name IS NOT NULL AND TRIM(cat_name) != ''
                      ORDER BY RANDOM()
                      LIMIT 5)";


    if (!query.exec(sql)) {
        qDebug() << "Error fetching random categories:" << query.lastError().text()
                 << "Query:" << sql;
        return categories;
    }

    while (query.next()) {
        Category category;
        category.cat_id = query.value(0).toInt();   // safer with index
        category.name   = query.value(1).toString();
        // category.questions = loadRandomQuestions(category.cat_id); // still optional
        categories.append(category);

        qDebug() << "Fetched category:"
                 << category.cat_id
                 << category.name
                 << "Questions:" << category.questions.size();
    }

    qDebug() << "Total categories fetched:" << categories.size();

    if (categories.isEmpty())
        qDebug() << "No categories fetched from database!";

    return categories;
}


QList<Questions> DbManager::loadRandomQuestions(int category_id)
{
    QList<Questions> questions;

    if (!openDatabase())
        return questions;

    // Define mapping from Level enum to database point value
    const QList<std::pair<Level, int>> levelMap = {
        {Level::VeryLow, 100},
        {Level::Low, 200},
        {Level::Medium, 300},
        {Level::High, 400},
        {Level::VeryHigh, 500}
    };

    for (const auto& [lvl, points] : levelMap) {
        QSqlQuery query(db);
        query.prepare(
            "SELECT * FROM questions "
            "WHERE qcat_id = :category_id AND level = :level "
            "ORDER BY RANDOM() LIMIT 1"
        );

        query.bindValue(":category_id", category_id);
        query.bindValue(":level", points); // db stores 100,200,...

        if (!query.exec()) {
            qDebug() << "Query failed for category ID"
                     << category_id << ":" << query.lastError().text();
            continue;
        }

        if (query.next()) {
            Questions q;
            q.q_id    = query.value("q_id").toInt();
            q.cat_id  = query.value("qcat_id").toInt();
            q.question = query.value("question").toString();
            q.answer   = query.value("answer").toString();
            q.level    = lvl; // assign the Level enum
            questions.append(q);
        }
    }

    return questions;
}



