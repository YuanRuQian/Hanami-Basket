#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H

#include <QObject>

enum GameLevel {
    Easy,
    Medium,
    Hard
};

struct GameLevelConfig {
    int BASKET_MOVE_STEP;
    int CHERRYBLOSSOM_FALLING_SPEED;
};


class GameStateMachine : public QObject
{
    Q_OBJECT

public:
    static GameStateMachine* instance();
    GameLevelConfig getCurrentGameLevelConfig();
    QString getCurrentGameLevelLabelText();

private:
    // Private constructor and destructor to prevent direct instantiation and deletion
    explicit GameStateMachine(QObject *parent = nullptr);
    ~GameStateMachine();

    // Singleton instance
    static GameStateMachine* m_instance;

    std::map<GameLevel, GameLevelConfig> GAME_LEVEL_CONFIG;


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
    void setGameLevel(GameLevel gameLevel);

private:
    int score;
    int livesCount;
    GameLevel gameLevel;
    void updateGameLevel();
    void setUpGameLevelConfig();
};

#endif // GAMESTATEMACHINE_H
