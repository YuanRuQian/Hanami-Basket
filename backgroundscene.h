#ifndef BACKGROUNDSCENE_H
#define BACKGROUNDSCENE_H

#include "basket.h"
#include "canvaswidget.h"

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QLabel>


class BackgroundScene: public QGraphicsScene
{
    Q_OBJECT
private:
    Basket* basket;
    QTimer* timer;

public:
    BackgroundScene(CanvasWidget* canvas, QObject *parent = nullptr);
    CanvasWidget* canvasWidget;

private:
    void setUpBasket();
    void addCherryBlossom();
    void handleTermination();
    void clearCherryBlossom();
};

#endif // BACKGROUNDSCENE_H
