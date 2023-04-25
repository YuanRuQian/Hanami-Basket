#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "canvaswidget.h"
#include "user.h"
#include "score.h"
#include "soundeffectmanager.h"

#include <QFileDialog>

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
    ui->calendarWidget->setMaximumDate(date);
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

void MainWindow::on_game_level_choosed(QString gameLevel) {
    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    gameStateMachine->setGameLevelWithText(gameLevel);
    gameStateMachine->setGameUsername(userProfileName);
    game = new CanvasWidget();
    ui->stackedWidget->insertWidget(5,game);
    ui->stackedWidget->setCurrentIndex(5);

    connect(game, &CanvasWidget::backToStart, this, &MainWindow::on_back1_clicked);
}

void MainWindow::on_easy_clicked()
{
    on_game_level_choosed(ui->easy->text());
}


void MainWindow::on_medium_clicked()
{   
    on_game_level_choosed(ui->medium->text());
}


void MainWindow::on_hard_clicked()
{
    on_game_level_choosed(ui->hard->text());
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
            QString password = ui->loginPasswordLineEdit->text();

            if (User::checkUser(username, password)) {
                // LOGIN SUCCESS
                userProfileName = username;

                // set Birthday Greeting
                if(User::isBirthday(userProfileName)){
                    setBirthdayGreeting();
                }

                // set Profile User Name

                ui->userName_1->setText(userProfileName);
                ui->userName_2->setText(userProfileName);
                ui->userName_3->setText(userProfileName);

                setNonGuestUserAvatar();

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

    qDebug() << "User birthday : " << userBirthday << "\n";

    if (User::checkUsername(username)) {
        errorMsg = "User name already exists!";
    }
    else {
        QString password = ui->signUpPasswordLineEdit->text();

        if (! User::checkPassword(password)) {
            errorMsg = "Your password should include at least 8 characters and at least one "
                       "number, one upper and one lower case letter.";
        } else if(userBirthday.isNull()) {
            errorMsg = "Please enter your birthday.";
        } else {
            std::string gender = "";

            if (ui->femaleButton->isChecked()) {
                gender = "female";
            }
            if (ui->maleButton->isChecked()) {
                gender = "male";
            }

            auto addUserReturn = User::addUser(username, password,
                                               ui->firstnameText->toPlainText(),
                                               ui->lastnameText->toPlainText(),
                                               QString::fromStdString(gender),
                                               userAvatar,
                                               userBirthday);

            qDebug() << "addUserReturn: " << addUserReturn << "\n";

            if (addUserReturn == success) {
                // sign up success, go to game page
                ui->stackedWidget->setCurrentIndex(2);

                userProfileName = username;

                // set Birthday Greeting
                if(User::isBirthday(userProfileName)){
                    setBirthdayGreeting();
                }

                ui->userName_1->setText(userProfileName);
                ui->userName_2->setText(userProfileName);
                ui->userName_3->setText(userProfileName);

                setNonGuestUserAvatar();
            }
            else {
                errorMsg = "Oops, there's something wrong while we trying to store your profile..";
            }
        }
    }

    ui->errorMessage_2->setText(QString::fromStdString(errorMsg));
}

void MainWindow::setNonGuestUserAvatar() {
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
}

void MainWindow::on_calendarWidget_selectionChanged()
{
    userBirthday = ui->calendarWidget->selectedDate();
}

void MainWindow::updateProfilePicturePreview(QString fileName) {
    // Load the image using QPixmap
    QPixmap pixmap(fileName);

    if (!pixmap.isNull()) {
        // Scale the pixmap to a fixed size
        QPixmap scaledPixmap = pixmap.scaled(QSize(60, 60), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        // Set the scaled pixmap as the pixmap for the previewLabel
        ui->imagePreviewLabel->setPixmap(scaledPixmap);
    } else {
        // Clear the previewLabel if no image was loaded
        ui->imagePreviewLabel->clear();
    }
}

QString MainWindow::getProfilePicturePath() {
    QFileDialog dialog(this);

    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Image files (*.png *.jpg *.jpeg *.bmp *.gif)"));
    dialog.setViewMode(QFileDialog::Detail);

    // Set the default directory to the user folder instead of the default macos folder in build path
    QString currentPath = QDir::currentPath();
    QString parentPath = QDir(currentPath).absolutePath() + "/../../../..";
    dialog.setDirectory(parentPath);

    if (dialog.exec())
    {
        QString selectedFile = dialog.selectedFiles().first();
        updateProfilePicturePreview(selectedFile);
        return selectedFile;
    }
    else
    {
        return QString();
    }
}

void MainWindow::setBirthdayGreeting() {
    ui->congrats->setText("Happy Birthday, " + userProfileName + "!");
    ui->congrats->show();
}


void MainWindow::on_profilePictureUploader_released()
{
    userAvatar = getProfilePicturePath();
}

