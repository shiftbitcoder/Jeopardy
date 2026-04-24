#include "gameboard.h"
#include "questiondialog.h"
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
    questions.clear();

        for (int i = 0; i < categories.size() && i < 5; ++i) {
            questions.append(
                dbManager.loadRandomQuestions(categories[i].cat_id)
            );
        }

        updateQuestionButtons();
        for (int cat = 0; cat < 5; ++cat) {
            for (int q = 0; q < 5; ++q) {

                QString name = QString("cat%1_%2").arg(cat+1).arg(q+1);
                QPushButton* button = ui->centralwidget->findChild<QPushButton*>(name);

                if (button) {
                    connect(button, &QPushButton::clicked, this, [=]() {
                        handleQuestionClicked(cat, q, button);;
                    });
                }
            }
        }
}

const QList<Category>& GameBoard::getCategories() const
{
    return categories;
}

void GameBoard::updateCategoryLabels()
{
    QStringList labels = { "cat1", "cat2", "cat3", "cat4", "cat5" };

    for (int i = 0; i < categories.size() && i < 5; ++i) {
        labels[i] = categories[i].cat_name;
    }

    ui->cat1->setText(labels[0]);
    ui->cat2->setText(labels[1]);
    ui->cat3->setText(labels[2]);
    ui->cat4->setText(labels[3]);
    ui->cat5->setText(labels[4]);

    qDebug() << "Updated category buttons:" << labels;
}

void GameBoard::updateQuestionButtons()
{
    for (int cat = 0; cat < questions.size(); ++cat) {
        for (int q = 0; q < questions[cat].size(); ++q) {

            QString buttonName =
                QString("cat%1_%2").arg(cat + 1).arg(q + 1);

            QPushButton* button =
                ui->centralwidget->findChild<QPushButton*>(buttonName);

            if (button) {
                button->setText(
                    QString::number(questions[cat][q].points)
                );
            } else {
                qDebug() << "Button not found:" << buttonName;
            }
        }
    }
}


void GameBoard::handleQuestionClicked(int cat, int q, QPushButton* button)
{
    Questions& question = questions[cat][q];

    questiondialog dlg(
        question.question,
        question.answer,
        question.points,
        nullptr
    );

    dlg.exec();

    // 🚨 MARK BUTTON AS USED AFTER DIALOG CLOSES
    button->setEnabled(false);
    button->setStyleSheet(
        "background-color: #444;"
        "color: #999;"
    );
}



