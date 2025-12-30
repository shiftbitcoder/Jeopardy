#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QDebug>
#include <QStandardPaths>
#include <QFile>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "Available SQL Driver:" << QSqlDatabase::drivers();

    // 1. Get writable app data directory
    QString dataDir =
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);

    // Ensure directory exists
    QDir().mkpath(dataDir);

    QString dbPath = dataDir + "/jeopardy.db";

    // 2. Copy database from resources on first run
    if (!QFile::exists(dbPath)) {
        if (!QFile::copy(":/db/jeopardy.db", dbPath)) {
            qDebug() << "Failed to copy database to" << dbPath;
            return;
        } else {
            qDebug() << "Database copied to:" << dbPath;
        }
    }

    // 3. Open SQLite database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Database Error:" << db.lastError().text();
    } else {
        qDebug() << "Database opened successfully at:" << dbPath;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


