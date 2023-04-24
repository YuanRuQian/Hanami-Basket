#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvaswidget.h"
#include "user.h"
#include "score.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->congrats->hide();

    userProfileName =  "user_test";

    // check birthday and set Congrats
    if(User::isBirthday(userProfileName)){
        ui->congrats->show();
    }


    //set Profile info: name, avatar, date


    // TODO: set Profile Picture


    // set User Name
    ui->userName_1->setText(userProfileName);
    ui->userName_2->setText(userProfileName);
    ui->userName_3->setText(userProfileName);

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

    Score bestScore = Score::getGlobalBestScore();
    QVector<Score> scoreHistory = Score::getScoreHistory(userProfileName);

    QString scoreText = "Best Score: " + QString::number(bestScore.score) + "\nUser: " + bestScore.username + "\n";
    scoreText += "\nYour Score History:";

    for(int i = 0; i<scoreHistory.size(); i++){
        scoreText += "\n" + scoreHistory[i].time.toString(Score::TIME_FORMAT) + ": ";
        scoreText += QString::number(scoreHistory[i].score);
    }

    ui->scoreHistory->setText(scoreText);
}


void MainWindow::on_back1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_back2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_easy_clicked()
{

    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    gameStateMachine->setGameLevelWithText(QString("Easy"));
    gameStateMachine->setGameUsername(userProfileName);
    game = new CanvasWidget();
    ui->stackedWidget->insertWidget(4,game);
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_medium_clicked()
{
    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    gameStateMachine->setGameLevelWithText(QString("Medium"));
    gameStateMachine->setGameUsername(userProfileName);
    game = new CanvasWidget();
    ui->stackedWidget->insertWidget(4,game);
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on_hard_clicked()
{
    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    gameStateMachine->setGameLevelWithText(QString("Hard"));
    gameStateMachine->setGameUsername(userProfileName);
    game = new CanvasWidget();
    ui->stackedWidget->insertWidget(4,game);
    ui->stackedWidget->setCurrentIndex(4);
}

