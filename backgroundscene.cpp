#include "backgroundscene.h"
#include "constants.h"
#include "cherryblossom.h"
#include "gamestatemachine.h"
#include "basket.h"


#include <QBrush>
#include <QTimer>
#include <QGraphicsItem>

class CanvasWidget;

BackgroundScene::BackgroundScene(CanvasWidget* canvas, QObject* parent)
    : QGraphicsScene(parent),canvasWidget(canvas)
{
    this->setSceneRect(0,0,BACKGROUND_WIDTH,BACKGROUND_HEIGHT);
    this->setBackgroundBrush(QBrush(QImage("://images/background.png").scaledToHeight(BACKGROUND_HEIGHT).scaledToWidth(BACKGROUND_WIDTH)));

    this->setUpBasket();
    this->addItem(basket);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &BackgroundScene::addCherryBlossom);
    timer->start(500);

    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    connect(gameStateMachine, &GameStateMachine::terminateTheGame, this, &BackgroundScene::handleTermination);
}

void BackgroundScene::setUpBasket()
{
    basket = new Basket();

    basket->setPos(BACKGROUND_WIDTH / 2 - BASKET_SIZE / 2, BACKGROUND_HEIGHT - BASKET_SIZE);

    basket->setFlag(QGraphicsItem::ItemIsFocusable);
    basket->setFocus();

    basket->startCollisionDetection();
}

void BackgroundScene::addCherryBlossom()
{
    QList<QGraphicsItem*> items = this->items();
    int numBlossoms = 0;
    for (QGraphicsItem* item : items) {
        if (dynamic_cast<CherryBlossom*>(item) != nullptr) {
            numBlossoms++;
        }
    }

    if (numBlossoms < NUM_CHERRY_BLOSSOMS) {
        CherryBlossom* cherryBlossom = new CherryBlossom();
        int randomX = arc4random_uniform(BACKGROUND_WIDTH - CHERRYBLOSSOM_SIZE);
        cherryBlossom->setPos(randomX, 0);
        this->addItem(cherryBlossom);
    }
}

void BackgroundScene::clearCherryBlossom()
{
    QList<QGraphicsItem*> items = this->items();
    for (QGraphicsItem* item : items) {
        if (CherryBlossom* cherryBlossom = dynamic_cast<CherryBlossom*>(item)) {
            this->removeItem(cherryBlossom);
            delete cherryBlossom;
        }
    }
}

void BackgroundScene::handleTermination() {
    timer->stop();
    clearCherryBlossom();
}
