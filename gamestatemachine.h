#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

#include <QObject>
#include <QString>

enum GameLevel {
    Easy,
    Medium,
    Hard
};

struct GameLevelConfig {
    float BASKET_MOVE_STEP;
    float CHERRYBLOSSOM_FALLING_SPEED;
};


class GameStateMachine : public QObject
{
    Q_OBJECT

public:
    static GameStateMachine* instance();

    QString getCurrentGameLevelLabelText();
    float getCurrentCherryBlossomFallingSpeed();
    float getCurrentBasketMoveStep();

private:
    // Private constructor and destructor to prevent direct instantiation and deletion
    explicit GameStateMachine(QObject *parent = nullptr);
    ~GameStateMachine();

    // Singleton instance
    static GameStateMachine* m_instance;

    std::map<GameLevel, GameLevelConfig> GAME_DEFAULT_LEVEL_CONFIG;


signals:
    void gameover();
    void restartGame();
    void scoreUpdated(int score);
    void livesCountUpdated(int livesCount);
    void terminateTheGame();
    void gameLevelUpdated();


public slots:
    void handleBasketCollision();
    void handleMissDetection();
    void setGameLevelWithText(QString gameLevelText);
    void setGameUsername(QString username);


private:
    int score;
    int livesCount;
    GameLevel gameLevel;
    void updateGameLevel();
    void setUpGameLevelConfig();
    GameLevelConfig getDefaultGameLevelConfig();
    void setGameLevel(GameLevel gameLevel);
    QString username;
};

#endif // GAMESTATEMACHINE_H
