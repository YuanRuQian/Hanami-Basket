// gamestatemachine.cpp

#include "gamestatemachine.h"
#include "constants.h"
#include "score.h"
#include <QDebug>
#include <cmath>

// Initialize the static instance to nullptr
GameStateMachine* GameStateMachine::m_instance = nullptr;

// Static method to get the singleton instance
GameStateMachine* GameStateMachine::instance()
{
    if (!m_instance)
    {
        m_instance = new GameStateMachine();
    }
    return m_instance;
}

GameStateMachine::GameStateMachine(QObject *parent)
    : QObject(parent)
{
    gameLevel = Easy;
    setUpGameLevelConfig();
    score = 0;
    livesCount = DEFAULT_LIVES;
}

void GameStateMachine::handleBasketCollision()
{
    score += SCORE_PER_COLLISION;
    emit scoreUpdated(score);

    qDebug() << "\n\nTriggered: GameStateMachine::handleBasketCollision()";
    qDebug() << "Score updated: New score =" << score << "\n\n";
}

void GameStateMachine::handleMissDetection()
{
    livesCount--;

    qDebug() << "\n\nTriggered: GameStateMachine::handleMissDetection()";
    qDebug() << "LivesCount updated: New livesCount =" << livesCount << "\n\n";

    emit livesCountUpdated(livesCount);

    if (livesCount == 0)
    {
        qDebug() << "Oops you died... Bye...\n\n";
        // TODO: use actual username
        Score::insertNewRecord(QString("null"), score);
        emit terminateTheGame();
    }
}

void GameStateMachine::setGameLevel(GameLevel newGameLevel) {
    gameLevel = newGameLevel;
    emit gameLevelUpdated();
}

void GameStateMachine::setUpGameLevelConfig() {
    // Insert values for each game level
    GameLevelConfig easyConfig = {50, 30};    // Example values for Easy level
    GAME_DEFAULT_LEVEL_CONFIG[Easy] = easyConfig;

    GameLevelConfig mediumConfig = {40, 40};  // Example values for Medium level
    GAME_DEFAULT_LEVEL_CONFIG[Medium] = mediumConfig;

    GameLevelConfig hardConfig = {30, 50};   // Example values for Hard level
    GAME_DEFAULT_LEVEL_CONFIG[Hard] = hardConfig;
}

QString GameStateMachine::getCurrentGameLevelLabelText() {
    std::string labelText;

    switch (gameLevel) {
    case Easy:
        labelText = "Easy";
        break;
    case Medium:
        labelText = "Medium";
        break;
    case Hard:
        labelText = "Hard";
        break;
    default:
        labelText = "?";
        break;
    }
    return QString::fromStdString(labelText);
}

GameLevelConfig GameStateMachine::getDefaultGameLevelConfig() {
    return GAME_DEFAULT_LEVEL_CONFIG[gameLevel];
}

float GameStateMachine::getCurrentCherryBlossomFallingSpeed() {
    GameLevelConfig gameLevelDefaultConfig = getDefaultGameLevelConfig();
    float deafultSpeed = gameLevelDefaultConfig.CHERRYBLOSSOM_FALLING_SPEED;
    int cherryBlossomCollected = score / SCORE_PER_COLLISION;
    int speedUpFactorTimes = std::floor((float)cherryBlossomCollected / CHERRYBLOSSOM_SPEEDUP_THRESHOLD);
    return std::pow(CHERRYBLOSSOM_SPEEDUP_FACTOR, speedUpFactorTimes) * deafultSpeed;
}

float GameStateMachine::getCurrentBasketMoveStep() {
    GameLevelConfig gameLevelDefaultConfig = getDefaultGameLevelConfig();
    return gameLevelDefaultConfig.BASKET_MOVE_STEP;
}

GameStateMachine::~GameStateMachine()
{
    // Clean up the singleton instance
    m_instance = nullptr;
}
