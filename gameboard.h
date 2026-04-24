#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include <QList>
#include <QStringList>
#include <QPushButton>
#include <QDebug>

#include "ui_mainwindow.h"
#include "dbmanager.h"
#include "categories.h"
#include "questions.h"

class GameBoard : public QObject
{
    Q_OBJECT

public:
    explicit GameBoard(Ui::MainWindow* uiMainWindow, QObject* parent = nullptr);

    void loadGame();

    const QList<Category>& getCategories() const;
    void handleQuestionClicked(int cat, int q, QPushButton* button);

private:
    Ui::MainWindow* ui;
    DbManager dbManager;

    QList<Category> categories;
    QList<QList<Questions>> questions;

    void updateCategoryLabels();
    void updateQuestionButtons();
};

#endif // GAMEBOARD_H
