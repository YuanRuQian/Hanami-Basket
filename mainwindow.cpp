#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvaswidget.h"

MainWindow::MainWindow(QApplication* gameApp, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->gameApp = gameApp;

    // TODO:set Profile info


    // TODO: set Profile Picture


    // set User Name
    name = "JOJO";
    ui->userName_1->setText(name);
    ui->userName_2->setText(name);
    ui->userName_3->setText(name);

    // set Current Date
    date = QDate::currentDate();
    QString dateString = date.toString("yyyy-MM-dd");
    ui->currentDate_1->setText(dateString);
    ui->currentDate_2->setText(dateString);
    ui->currentDate_3->setText(dateString);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_start_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);

}


void MainWindow::on_scores_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_back1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_back2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// TODO: Change Difficulty Level

void MainWindow::on_easy_clicked()
{

    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    gameStateMachine->setGameLevelWithText(QString("Easy"));
    game = new CanvasWidget(gameApp);
    ui->stackedWidget->insertWidget(4,game);
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_medium_clicked()
{
    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    gameStateMachine->setGameLevelWithText(QString("Medium"));
    game = new CanvasWidget(gameApp);
    ui->stackedWidget->insertWidget(4,game);
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_hard_clicked()
{
    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    gameStateMachine->setGameLevelWithText(QString("Hard"));
    game = new CanvasWidget(gameApp);
    ui->stackedWidget->insertWidget(4,game);
    ui->stackedWidget->setCurrentIndex(4);
}

