#include "basket.h"
#include "constants.h"
#include "cherryblossom.h"
#include "gamestatemachine.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>

Basket::Basket(QObject *parent)
    : QObject{parent}
{
    this->setPixmap(QPixmap("://images/basket.png").scaled(BASKET_SIZE, BASKET_SIZE));

    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    connect(this, &Basket::collisionDetected, gameStateMachine, &GameStateMachine::handleBasketCollision);
}

void Basket::keyPressEvent(QKeyEvent *event)
{
    int prevX = pos().x();

    GameStateMachine* gameStateMachine = GameStateMachine::instance();

    float basketMoveStep = gameStateMachine->getCurrentBasketMoveStep();

    if (event->key() == Qt::Key_Left) {
        // check if the basket is not at the left border of the window
        if (prevX > 0) {
            setPos(prevX - basketMoveStep, pos().y());
        }
    }
    else if (event->key() == Qt::Key_Right) {
        // check if the basket is not at the right border of the window
        if (prevX + BASKET_SIZE < BACKGROUND_WIDTH) {
            setPos(prevX + basketMoveStep, pos().y());
        }
    }
    else {
        // pass the event to the base class implementation
        QGraphicsItem::keyPressEvent(event);
    }
}

void Basket::startCollisionDetection()
{
    // create a timer to periodically check for collisions
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Basket::detectCollisions);
    timer->start(COLLISION_DETECTION_INTERVAL); // adjust the interval as desired
}

void Basket::detectCollisions()
{
    QList<QGraphicsItem*> collisions = scene()->collidingItems(this);
    for (QGraphicsItem* item : collisions) {
        if (dynamic_cast<CherryBlossom*>(item)) {
            scene()->removeItem(item);
            emit collisionDetected();
        }
    }
}


