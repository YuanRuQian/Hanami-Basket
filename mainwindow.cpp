#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvaswidget.h"
#include "user.h"
#include "score.h"
#include "soundeffectmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    play_background_music();

    ui->congrats->hide();

//    userProfileName =  "user_test";

    // set Profile Current Date
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

void MainWindow::play_background_music() {
    SoundEffectManager* soundEffectManager = SoundEffectManager::instance();
    soundEffectManager->playBackgroundMusic();
}


void MainWindow::on_start_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);

}


void MainWindow::on_scores_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);

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
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_back2_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_easy_clicked()
{

    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    gameStateMachine->setGameLevelWithText(QString("Easy"));
    gameStateMachine->setGameUsername(userProfileName);
    game = new CanvasWidget();
    ui->stackedWidget->insertWidget(5,game);
    ui->stackedWidget->setCurrentIndex(5);

    connect(game, &CanvasWidget::backToStart, this, &MainWindow::on_back1_clicked);
}


void MainWindow::on_medium_clicked()
{   
    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    gameStateMachine->setGameLevelWithText(QString("Medium"));
    gameStateMachine->setGameUsername(userProfileName);
    game = new CanvasWidget();
    ui->stackedWidget->insertWidget(5,game);
    ui->stackedWidget->setCurrentIndex(5);

    connect(game, &CanvasWidget::backToStart, this, &MainWindow::on_back1_clicked);
}


void MainWindow::on_hard_clicked()
{
    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    gameStateMachine->setGameLevelWithText(QString("Hard"));
    gameStateMachine->setGameUsername(userProfileName);
    game = new CanvasWidget();
    ui->stackedWidget->insertWidget(5,game);
    ui->stackedWidget->setCurrentIndex(5);

    connect(game, &CanvasWidget::backToStart, this, &MainWindow::on_back1_clicked);
}


void MainWindow::on_loginButton_clicked()
{
    std::string errorMsg = "";
    QString username = ui->usernameText->toPlainText();

    if (username != "") {
        // CHECK IF USERNAME EXISTS
        if (! User::checkUsername(username)) {
            errorMsg = "User does not exist!";
        }
        else {
            // CHECK IF USERNAME MATCHES PASSWORD
            QString password = ui->passwordText->toPlainText();

            if (User::checkUser(username, password)) {
                // LOGIN SUCCESS
                userProfileName = username;

                // set Birthday Greeting
                if(User::isBirthday(userProfileName)){
                    ui->congrats->show();
                }

                // set Profile User Name

                ui->userName_1->setText(userProfileName);
                ui->userName_2->setText(userProfileName);
                ui->userName_3->setText(userProfileName);

                // set Profile User Avatar
                QString avatarPath = User::getAvatarPath(userProfileName, false);

                QGraphicsScene *avatarScene = new QGraphicsScene();
                QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
                QPixmap p (avatarPath);
                //    qDebug()<< p.width() << p.height();
                if(p.width() == p.height()){
                    item->setPixmap(p.scaled(ui->avatar_1->size()));
                }
                else{
                    item->setPixmap(p.scaled(ui->avatar_1->size() * 1.5));
                }

                avatarScene->addItem(item);
                ui->avatar_1->setScene(avatarScene);
                ui->avatar_2->setScene(avatarScene);
                ui->avatar_3->setScene(avatarScene);

                // go to game page
                ui->stackedWidget->setCurrentIndex(2);
            }
            else {
                errorMsg = "Invalid password!";
            }
        }
    }
    else {
        errorMsg = "User name cannot be blank!";
    }

    ui->errorMessage->setText(QString::fromStdString(errorMsg));
}


void MainWindow::on_signupButton_clicked()
{
    // go to sign up page
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_guestButton_clicked()
{
    userProfileName = "Guest";

    ui->userName_1->setText(userProfileName);
    ui->userName_2->setText(userProfileName);
    ui->userName_3->setText(userProfileName);

    // set Profile Guest Avatar
    QString avatarPath = User::getAvatarPath(userProfileName, true);

    QGraphicsScene *avatarScene = new QGraphicsScene();
    QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
    QPixmap p (avatarPath);
    //    qDebug()<< p.width() << p.height();
    if(p.width() == p.height()){
        item->setPixmap(p.scaled(ui->avatar_1->size()));
    }
    else{
        item->setPixmap(p.scaled(ui->avatar_1->size() * 1.5));
    }

    avatarScene->addItem(item);
    ui->avatar_1->setScene(avatarScene);
    ui->avatar_2->setScene(avatarScene);
    ui->avatar_3->setScene(avatarScene);

    // go to game page
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_signupButton_3_clicked()
{
    std::string errorMsg = "";
    QString username = ui->usernameText_3->toPlainText();

    if (User::checkUsername(username)) {
        errorMsg = "User name already exists!";
    }
    else {
        QString password = ui->passwordText_3->toPlainText();

        if (! User::checkPassword(password)) {
            errorMsg = "Your password should include at least 8 characters and at least one "
                       "number, one upper and one lower case letter.";
        }
        else {
            std::string gender = "";

            if (ui->femaleButton->isChecked()) {
                gender = "female";
            }
            if (ui->maleButton->isChecked()) {
                gender = "male";
            }
            if (ui->femaleButton->isChecked()) {
                gender = "nonbinary";
            }

            // User(QString uname, QString pwd, QString firstN, QString lastN, QString gender, QString avatar, QDate bDay);
            User currentUser(username, password,
                             ui->firstnameText->toPlainText(),
                             ui->lastnameText->toPlainText(),
                             QString::fromStdString(gender),
                             QString::fromStdString(""),
                             ui->birthdayEdit->date());

            if (User::addUser(currentUser)) {
                // sign up success, go to game page
                ui->stackedWidget->setCurrentIndex(2);

                userProfileName = username;

                ui->userName_1->setText(userProfileName);
                ui->userName_2->setText(userProfileName);
                ui->userName_3->setText(userProfileName);
            }
            else {
                errorMsg = "Oops, there's something wrong while we trying to store your profile..";
            }
        }
    }

    ui->errorMessage_2->setText(QString::fromStdString(errorMsg));
}
