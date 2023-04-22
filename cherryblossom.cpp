#include "cherryblossom.h"
#include "constants.h"
#include "gamestatemachine.h"
#include <QTimer>
#include <QMovie>


CherryBlossom::CherryBlossom(QObject *parent)
    : QObject{parent}, movie_{new QMovie{"://images/cherryBlossom.gif"}}, timer_{new QTimer{this}}
{
    // Set the QMovie as the pixmap for the QGraphicsPixmapItem
    setPixmap(movie_->currentPixmap().scaled(CHERRYBLOSSOM_SIZE, CHERRYBLOSSOM_SIZE));

    // Connect the QMovie's frameChanged signal to the updatePixmap slot
    connect(movie_, &QMovie::frameChanged, this, &CherryBlossom::updatePixmap);

    // Start the QMovie
    movie_->start();

    // Set the QTimer to trigger the falling slot
    connect(timer_, &QTimer::timeout, this, &CherryBlossom::falling);
    timer_->start(CHERRYBLOSSOM_FALLING_INTERVAL);

    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    connect(this, &CherryBlossom::missDetected, gameStateMachine, &GameStateMachine::handleMissDetection);
}

void CherryBlossom::updatePixmap()
{
    // Check if the QMovie has a valid pixmap at the current frame
    if (movie_->isValid()) {
        // Update the pixmap with the current frame of the QMovie
        setPixmap(movie_->currentPixmap().scaled(CHERRYBLOSSOM_SIZE, CHERRYBLOSSOM_SIZE));
    }
}

void CherryBlossom::falling()
{
    // move the cherry blossom downwards
    setPos(x(), y() + CHERRYBLOSSOM_FALLING_SPEED);

    // add a slight horizontal oscillation to imitate the randomness of real world petal falling movement
    qreal dx = qSin(y() / CHERRYBLOSSOM_WIND_FREQUENCY) * CHERRYBLOSSOM_WIND_EFFECT;
    setPos(x() + dx, y());

    if (y() + CHERRYBLOSSOM_SIZE > BACKGROUND_HEIGHT) {
        timer_->stop();     
        this->deleteLater();
        emit missDetected();
    } else if (x() < 0 || x() >= BACKGROUND_WIDTH - CHERRYBLOSSOM_SIZE) {
        timer_->stop();
        this->deleteLater();
    }
}


