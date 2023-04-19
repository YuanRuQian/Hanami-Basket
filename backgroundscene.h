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

public:
    explicit BackgroundScene(CanvasWidget* canvas, QObject* parent = nullptr);
    CanvasWidget* canvasWidget;

private:
    void setUpBasket();
    void addCherryBlossom();

public slots:
    void increaseScoreByOne();

};

#endif // BACKGROUNDSCENE_H
