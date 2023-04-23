
#include "canvaswidget.h"
#include "scoretest.h"
#include "gamestatemachine.h"

#include <QApplication>
#include <QGraphicsView>
#include <QVBoxLayout>

int main(int argc, char **argv) {
    ScoreTest scoreTest = ScoreTest();
    scoreTest.testAll();
    QApplication app (argc, argv);

    GameStateMachine* gameStateMachine = GameStateMachine::instance();
    gameStateMachine->setGameLevelWithText(QString("X"));

    CanvasWidget* mainWidget = new CanvasWidget(&app);

    mainWidget->show();

    return app.exec();
}
