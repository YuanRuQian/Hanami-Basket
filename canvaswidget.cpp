#include "backgroundscene.h"
#include "canvaswidget.h"
#include "constants.h"
#include "gamestatemachine.h"
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QMessageBox>


CanvasWidget::CanvasWidget(QApplication* app, QWidget *parent)
    : QWidget{parent}, gameApp(app)
{
    setWindowTitle("Hanami Basket");

    labelFont.setBold(true);
    labelFont.setPointSize(16);

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

    connect(gameStateMachine, &GameStateMachine::scoreUpdated, this, &CanvasWidget::updateScoreLabel);
    connect(gameStateMachine, &GameStateMachine::livesCountUpdated, this, &CanvasWidget::updateLivesLabel);
    connect(gameStateMachine, &GameStateMachine::terminateTheGame, this, &CanvasWidget::terminateTheGame);
}


void CanvasWidget::setUpScoreLabels() {
    scoreTextLabel = new QLabel("Your Score: ");
    scoreCountLabel = new QLabel(QString::number(0));

    scoreTextLabel->setFont(labelFont);
    scoreCountLabel->setFont(labelFont);
}

void CanvasWidget::setUpLivesLabels() {
    livesTextLabel = new QLabel("Your Lives: ");
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

void CanvasWidget::terminateTheGame() {
    GameStateMachine* gameStateMachine = GameStateMachine::instance();

    connect(gameStateMachine, &GameStateMachine::scoreUpdated, this, &CanvasWidget::updateScoreLabel);
    connect(gameStateMachine, &GameStateMachine::livesCountUpdated, this, &CanvasWidget::updateLivesLabel);

    QMessageBox::information(nullptr, "Game Over", "Oops...You died...");
    gameApp->quit();
}

