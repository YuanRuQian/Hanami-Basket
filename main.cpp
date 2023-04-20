
#include "canvaswidget.h"

#include <QApplication>
#include <QGraphicsView>
#include <QVBoxLayout>

int main(int argc, char **argv) {
    QApplication app (argc, argv);

    CanvasWidget* mainWidget = new CanvasWidget();

    mainWidget->show();

    return app.exec();
}
