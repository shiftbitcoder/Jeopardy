#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QObject>
#include <QList>
#include "dbmanager.h"
#include "categories.h"
#include "questions.h"
#include "gametypes.h"
#include "ui_mainwindow.h"  // for Ui::MainWindow

class GameBoard : public QObject
{
    Q_OBJECT

public:
    explicit GameBoard(Ui::MainWindow* uiMainWindow, QObject* parent = nullptr);

    void loadGame();
    const QList<Category>& getCategories() const;

private:
    Ui::MainWindow* ui;       // pointer to MainWindow's UI
    DbManager dbManager;
    QList<Category> categories;

    void updateCategoryLabels();
    void setupQuestionButtons();
};

#endif // GAMEBOARD_H


