
#include "canvaswidget.h"
#include "scoretest.h"
#include "usertest.h"
#include "gamestatemachine.h"

#include <QApplication>
#include <QGraphicsView>
#include <QVBoxLayout>

int main(int argc, char **argv) {
    //  UserTest::testAll();
    // ScoreTest().testAll();

    QApplication app (argc, argv);

    CanvasWidget* mainWidget = new CanvasWidget(&app);

    mainWidget->show();

    return app.exec();
}
