#include "mainwindow.h"
#include "canvaswidget.h"
#include "scoretest.h"
#include "usertest.h"
#include "gamestatemachine.h"
#include "user.h"

#include <QApplication>
#include <QGraphicsView>
#include <QVBoxLayout>

int main(int argc, char **argv) {
    UserTest().testAll();
//    ScoreTest().testAll();

    QApplication app (argc, argv);
//    GameStateMachine* gameStateMachine = GameStateMachine::instance();
//    gameStateMachine->setGameLevelWithText(QString("Medium"));
//    gameStateMachine->setGameUsername(QString("jojo"));

//    CanvasWidget* mainWidget = new CanvasWidget();

//    mainWidget->show();
    MainWindow *w = new MainWindow();
    w->show();

    return app.exec();
}
