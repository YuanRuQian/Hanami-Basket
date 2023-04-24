#include "mainwindow.h"
#include "canvaswidget.h"
#include "scoretest.h"
#include "usertest.h"
#include "gamestatemachine.h"

#include <QApplication>
#include <QGraphicsView>
#include <QVBoxLayout>

int main(int argc, char **argv) {
    UserTest().testAll();
    ScoreTest().testAll();

    QApplication app (argc, argv);

//    GameStateMachine* gameStateMachine = GameStateMachine::instance();
//    gameStateMachine->setGameLevelWithText(QString("Medium"));

//    CanvasWidget* mainWidget = new CanvasWidget(&app);

//    mainWidget->show();


    MainWindow *w = new MainWindow(&app);
    w->show();

    return app.exec();
}
