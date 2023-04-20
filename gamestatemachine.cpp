// gamestatemachine.cpp

#include "gamestatemachine.h"
#include "constants.h"

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

    score = 0;
    livesCount = DEFAULT_LIVES;

    // Create state machine
    stateMachine = new QStateMachine(this);

    // Create states
    gameplayState = new QState();


    // Add states as child states of the state machine
    stateMachine->addState(gameplayState);


    // Set initial state
    stateMachine->setInitialState(gameplayState);

    // Start the state machine
    stateMachine->start();
}

void GameStateMachine::handleBasketCollision()
{
    score += SCORE_PER_COLLISION;
    emit scoreUpdated(score);

    qDebug() << "\n\nTriggered: GameStateMachine::handleBasketCollision()";
    qDebug() << "Score updated: New score =" << score << "\n\n";
}

void GameStateMachine::handleMissDetection() {
    livesCount--;

    qDebug() << "\n\nTriggered: GameStateMachine::handleMissDetection()";
    qDebug() << "LivesCount updated: New livesCount =" << livesCount << "\n\n";

    emit livesCountUpdated(livesCount);

    if(livesCount == 0) {
        qDebug() << "Oops you died... Bye...\n\n";
        emit terminateTheGame();
    }

}

GameStateMachine::~GameStateMachine()
{
    // Clean up the state machine and its child states
    delete stateMachine;
    delete gameplayState;
}


