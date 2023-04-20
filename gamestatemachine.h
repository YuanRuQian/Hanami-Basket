#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

#include <QObject>
#include <QStateMachine>
#include <QState>

class GameStateMachine : public QObject
{
    Q_OBJECT

public:
    static GameStateMachine* instance(); // Static method to get the singleton instance
    void setupStateMachine(); // Method to setup the state machine

private:
    // Private constructor and destructor to prevent direct instantiation and deletion
    GameStateMachine(QObject *parent = nullptr);
    ~GameStateMachine();

    // Singleton instance
    static GameStateMachine* m_instance;

private:
    QStateMachine *stateMachine;
    QState *gameplayState;
    int score;
    int livesCount;

signals:
    void gameover();
    void restartGame();
    void scoreUpdated(int score);
    void livesCountUpdated(int livesCount);
    void terminateTheGame();

public slots:
    void handleBasketCollision();
    void handleMissDetection();
};

#endif // GAMESTATEMACHINE_H
