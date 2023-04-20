#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QLabel>
#include <QWidget>
#include <QApplication>

class CanvasWidget : public QWidget
{
    Q_OBJECT
private:
    QApplication* gameApp;

    QFont labelFont;

    QLabel* scoreTextLabel;
    QLabel* scoreCountLabel;

    void setUpScoreLabels();

    QLabel* livesTextLabel;
    QLabel* livesCountLabel;

    void setUpLivesLabels();

public:
    CanvasWidget(QApplication* gameApp, QWidget *parent = nullptr);


private:
    void terminateTheGame();
    void updateScoreLabel(int newScore);
    void updateLivesLabel(int newLives);

};

#endif // CANVASWIDGET_H
