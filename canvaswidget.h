#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include "gamestatemachine.h"
#include <QLabel>
#include <QWidget>
#include <QApplication>

class CanvasWidget : public QWidget
{
    Q_OBJECT
private:
    QFont labelFont;

    QLabel* gameLevelTextLabel;
    QLabel* gameLevelValueLabel;

    void setUpGameLevelLabels();


    QLabel* scoreTextLabel;
    QLabel* scoreCountLabel;

    void setUpScoreLabels();

    QLabel* livesTextLabel;
    QLabel* livesCountLabel;

    void setUpLivesLabels();

public:
    CanvasWidget(QWidget *parent = nullptr);


private:
    void terminateTheGame(TerminationState terminationState);
    void updateScoreLabel(int newScore);
    void updateLivesLabel(int newLives);
    void updateGameLevelLabel();
    void loseTheGame();
    void winTheGame();

signals:
    void backToStart();
};

#endif // CANVASWIDGET_H
