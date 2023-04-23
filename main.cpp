
#include "canvaswidget.h"
#include "scoretest.h"

#include <QApplication>
#include <QGraphicsView>
#include <QVBoxLayout>

int main(int argc, char **argv) {
    ScoreTest scoreTest = ScoreTest();
    scoreTest.testAll();
    QApplication app (argc, argv);

    CanvasWidget* mainWidget = new CanvasWidget(&app);

    mainWidget->show();

    return app.exec();
}
