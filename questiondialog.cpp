#include "questiondialog.h"
#include "ui_questiondialog.h"

questiondialog::questiondialog(const QString& question,
                               const QString& answer,
                               int points,
                               QWidget *parent)
    : QDialog(parent),
      ui(new Ui::questiondialog),
      answerText(answer),
      timer(new QTimer(this)),
      timeLeft(30)
{
    ui->setupUi(this);

    ui->questionLabel->setText(question);
    ui->answerLabel->setVisible(false);

    ui->timerLabel->setText(QString::number(timeLeft));

    connect(timer, &QTimer::timeout, this, &questiondialog::updateTimer);

    timer->start(1000);
}

questiondialog::~questiondialog()
{
    delete ui;
}

void questiondialog::on_showAnswerButton_clicked()
{
    ui->answerLabel->setText(answerText);
    ui->answerLabel->setVisible(true);
}

void questiondialog::updateTimer()
{
    timeLeft--;

    ui->timerLabel->setText(QString::number(timeLeft));

    if (timeLeft <= 0) {
        timer->stop();

        ui->showAnswerButton->setEnabled(false);

        // optional auto-show answer:
        ui->answerLabel->setText(answerText);
        ui->answerLabel->setVisible(true);
    }
}
