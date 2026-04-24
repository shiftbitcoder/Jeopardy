#ifndef QUESTIONDIALOG_H
#define QUESTIONDIALOG_H

#include <QDialog>
#include <QTimer>

namespace Ui {
class questiondialog;
}

class questiondialog : public QDialog
{
    Q_OBJECT

public:
    explicit questiondialog(const QString& question,
                            const QString& answer,
                            int points,
                            QWidget *parent = nullptr);

    ~questiondialog();

private slots:
    void on_showAnswerButton_clicked();
     void updateTimer();

private:
    Ui::questiondialog *ui;
    QString answerText;
    QTimer *timer;
    int timeLeft;
};



#endif
