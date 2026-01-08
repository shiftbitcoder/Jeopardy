#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
     ui(new Ui::MainWindow),
     gameBoard (ui,this)
{
    ui->setupUi(this);

    gameBoard.loadGame();
    //updateCategoryLabels();
}

MainWindow::~MainWindow()
{
    delete ui;
}



