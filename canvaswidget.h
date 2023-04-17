#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QLabel>
#include <QWidget>

class CanvasWidget : public QWidget
{
    Q_OBJECT
private:
    QLabel* scoreTextLabel;
    QLabel* scoreCountLabel;
    int score;

    void setUpScoreLabels();

public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    void increaseScoreByOne();
signals:

};

#endif // CANVASWIDGET_H
