#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsView>
#include <QVBoxLayout>

int main(int argc, char **argv) {
//    UserTest().testAll();
//    ScoreTest().testAll();

    QApplication app (argc, argv);
    MainWindow *w = new MainWindow();
    w->show();

    return app.exec();
}
