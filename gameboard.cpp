#include "gameboard.h"
#include <QDebug>

GameBoard::GameBoard(Ui::MainWindow* uiMainWindow, QObject* parent)
    : QObject(parent), ui(uiMainWindow)
{
    if (!dbManager.openDatabase()) {
        qDebug() << "Failed to open database!";
    }
}

void GameBoard::loadGame()
{
    categories = dbManager.loadRandomCategories();
    updateCategoryLabels();
    // setupQuestionButtons();  // optional
}

const QList<Category>& GameBoard::getCategories() const
{
    return categories;
}

void GameBoard::updateCategoryLabels()
{
    QStringList labels = { "cat1", "cat2", "cat3", "cat4", "cat5" };

    for (int i = 0; i < categories.size() && i < 5; ++i) {
        labels[i] = categories[i].name;
    }

    ui->cat1->setText(labels[0]);
    ui->cat2->setText(labels[1]);
    ui->cat3->setText(labels[2]);
    ui->cat4->setText(labels[3]);
    ui->cat5->setText(labels[4]);

    qDebug() << "Updated category buttons:" << labels;
}





