#include "backgroundscene.h"
#include "canvaswidget.h"
#include "constants.h"
#include "gamestatemachine.h"
#include "score.h"
#include "soundeffectmanager.h"
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QMessageBox>


CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle("Hanami Basket");

    labelFont.setBold(true);
    labelFont.setPointSize(16);

    setUpGameLevelLabels();

    QHBoxLayout *gameLevelLayout = new QHBoxLayout;
    gameLevelLayout->addWidget(gameLevelTextLabel);
    gameLevelLayout->addWidget(gameLevelValueLabel);
    gameLevelLayout->setAlignment(Qt::AlignCenter);

    setUpLivesLabels();

    QHBoxLayout *livesLayout = new QHBoxLayout;
    livesLayout->addWidget(livesTextLabel);
    livesLayout->addWidget(livesCountLabel);
    livesLayout->setAlignment(Qt::AlignCenter);

    setUpScoreLabels();

    QHBoxLayout *scoreLayout = new QHBoxLayout;
    scoreLayout->addWidget(scoreTextLabel);
    scoreLayout->addWidget(scoreCountLabel);
    scoreLayout->setAlignment(Qt::AlignCenter);

    QHBoxLayout *infoLayout = new QHBoxLayout;
    infoLayout->addLayout(gameLevelLayout);
    infoLayout->addLayout(livesLayout);
    infoLayout->addLayout(scoreLayout);

    QGraphicsView* mainView = new QGraphicsView(this);
    mainView->setFixedSize(BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
    mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    BackgroundScene* mainScene = new BackgroundScene(this);
    mainView->setScene(mainScene);

    GameStateMachine* gameStateMachine = GameStateMachine::instance();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(infoLayout);
    mainLayout->addWidget(mainView);
    mainLayout->setAlignment(Qt::AlignCenter);

    setLayout(mainLayout);

    connect(gameStateMachine, &GameStateMachine::gameLevelUpdated, this, &CanvasWidget::updateGameLevelLabel);
    connect(gameStateMachine, &GameStateMachine::scoreUpdated, this, &CanvasWidget::updateScoreLabel);
    connect(gameStateMachine, &GameStateMachine::livesCountUpdated, this, &CanvasWidget::updateLivesLabel);
    connect(gameStateMachine, &GameStateMachine::terminateTheGame, this, &CanvasWidget::terminateTheGame);

    SoundEffectManager* soundEffectManager = SoundEffectManager::instance();
    connect(gameStateMachine, &GameStateMachine::scoreUpdated, soundEffectManager, &SoundEffectManager::playCollisionSound);
    connect(gameStateMachine, &GameStateMachine::livesCountUpdated, soundEffectManager, &SoundEffectManager::playMissSound);
}

void CanvasWidget::setUpGameLevelLabels() {
    gameLevelTextLabel = new QLabel("Game Level: ");

    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    gameLevelValueLabel = new QLabel(gameStateMachine->getCurrentGameLevelLabelText());

    gameLevelTextLabel->setFont(labelFont);
    gameLevelValueLabel->setFont(labelFont);
}


void CanvasWidget::setUpScoreLabels() {
    scoreTextLabel = new QLabel("Your Score: ");
    scoreCountLabel = new QLabel(QString::number(0));

    scoreTextLabel->setFont(labelFont);
    scoreCountLabel->setFont(labelFont);
}

void CanvasWidget::setUpLivesLabels() {
    livesTextLabel = new QLabel("Lives Left: ");
    livesCountLabel = new QLabel(QString::number(DEFAULT_LIVES));

    livesTextLabel->setFont(labelFont);
    livesCountLabel->setFont(labelFont);
}


void CanvasWidget::updateScoreLabel(int newScore) {
    scoreCountLabel->setText(QString::number(newScore));
}

void CanvasWidget::updateLivesLabel(int newLives) {
    if(newLives < 0) {
        return;
    }
    livesCountLabel->setText(QString::number(newLives));
}

void CanvasWidget::updateGameLevelLabel() {
    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    gameLevelValueLabel->setText(gameStateMachine->getCurrentGameLevelLabelText());
}

void CanvasWidget::loseTheGame() {
    QMessageBox *msgBox = new QMessageBox();
    msgBox->setWindowTitle("Game Over");
    msgBox->setIconPixmap(QPixmap("../../../../Hanami-Basket/icon.icns"));
    msgBox->setInformativeText("Your score is " + scoreCountLabel->text());
    msgBox->setText("Oops...You died...");

    int result = msgBox->exec();

    if(result){
        emit backToStart();
    }
}

void CanvasWidget::winTheGame() {
    QMessageBox *msgBox = new QMessageBox();
    msgBox->setWindowTitle("Congratulations");
    msgBox->setIconPixmap(QPixmap("../../../../Hanami-Basket/icon.icns"));
    msgBox->setInformativeText("Your score is " + scoreCountLabel->text());
    msgBox->setText("You win the game!");

    int result = msgBox->exec();

    if(result){
        emit backToStart();
    }
}


void CanvasWidget::terminateTheGame(TerminationState terminationState) {
    GameStateMachine* gameStateMachine = GameStateMachine::instance();

    gameStateMachine->insertNewScoreRecord();

    disconnect(gameStateMachine, &GameStateMachine::scoreUpdated, this, &CanvasWidget::updateScoreLabel);
    disconnect(gameStateMachine, &GameStateMachine::livesCountUpdated, this, &CanvasWidget::updateLivesLabel);

    SoundEffectManager* soundEffectManager = SoundEffectManager::instance();

    disconnect(gameStateMachine, &GameStateMachine::scoreUpdated, soundEffectManager, &SoundEffectManager::playCollisionSound);
    disconnect(gameStateMachine, &GameStateMachine::livesCountUpdated, soundEffectManager, &SoundEffectManager::playMissSound);

    switch (terminationState) {
    case Lose:
        loseTheGame();
        break;
    case Win:
        winTheGame();
        break;
    default:
        break;
    }

    gameStateMachine->resetScoreAndLivesState();
}

