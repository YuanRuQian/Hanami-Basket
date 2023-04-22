#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

#include <QObject>

class GameStateMachine : public QObject
{
    Q_OBJECT

public:
    static GameStateMachine* instance(); // Static method to get the singleton instance

private:
    // Private constructor and destructor to prevent direct instantiation and deletion
    explicit GameStateMachine(QObject *parent = nullptr);
    ~GameStateMachine();

    // Singleton instance
    static GameStateMachine* m_instance;

signals:
    void gameover();
    void restartGame();
    void scoreUpdated(int score);
    void livesCountUpdated(int livesCount);
    void terminateTheGame();

public slots:
    void handleBasketCollision();
    void handleMissDetection();

private:
    int score;
    int livesCount;
};

#endif // GAMESTATEMACHINE_H
