#include "cherryblossom.h"
#include "constants.h"
#include <QTimer>

CherryBlossom::CherryBlossom(QObject *parent)
    : QObject{parent}, timer_{new QTimer{this}}
{
    this->setPixmap((QPixmap("://images/cherryBlossom.gif")).scaled(CHERRYBLOSSOM_SIZE,CHERRYBLOSSOM_SIZE));
    connect(timer_, &QTimer::timeout, this, &CherryBlossom::falling);
    timer_->start(CHERRYBLOSSOM_FALLING_INTERVAL);
}


void CherryBlossom::falling()
{
    // move the cherry blossom downwards
    setPos(x(), y() + CHERRYBLOSSOM_FALLING_SPEED);

    // add a slight horizontal oscillation to imitate the randomness of real world petal falling movement
    qreal dx = qSin(y() / CHERRYBLOSSOM_WIND_FREQUENCY) * CHERRYBLOSSOM_WIND_EFFECT;
    setPos(x() + dx, y());

    // if the cherry blossom has fallen off the screen, delete it and create a new one
    if (y() > BACKGROUND_HEIGHT || x() < -CHERRYBLOSSOM_SIZE || x() > BACKGROUND_WIDTH + CHERRYBLOSSOM_SIZE) {
        timer_->stop();
        this->deleteLater();
    }
}
