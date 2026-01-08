#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"   // <-- Include this!
#include "gameboard.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;  // now Ui::MainWindow is defined
    GameBoard gameBoard;

    //void updateCategoryLabels();
};

#endif // MAINWINDOW_H


