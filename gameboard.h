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
    int currentTeam    = 1;
    int teamCount      = 2;
    int TeamScore1     = 0;
    int TeamScore2     = 0;
    int TeamScore3     = 0;
    int TeamScore4     = 0;
    int PresenterScore = 0;

    QList<Category> categories;
    QList<QList<Questions>> questions;

    void updateCategoryLabels();
    void updateQuestionButtons();
    void addScore (int points);
    void updateScoreUI();
};

#endif // GAMEBOARD_H
