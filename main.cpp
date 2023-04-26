#include "mainwindow.h"

#include <QApplication>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QCoreApplication>

#include <QApplication>
#include <QFileInfo>
#include <QDir>
#include "mainwindow.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Get the current path
    fs::path currentPath = fs::current_path();

    // Go four folders up in the directory hierarchy
    for (int i = 0; i < 4; ++i) {
        currentPath = currentPath.parent_path();
    }

    // Convert the path to a string
    std::string newPath = currentPath.string();

    std::cout << "New folder path: " << newPath << std::endl;

    // Search for the folder that contains qt-droplet-game.pro file
    std::string targetFile = "qt-droplet-game.pro";
    fs::directory_iterator endIter;
    for (fs::directory_iterator dirIter(currentPath); dirIter != endIter; ++dirIter) {
        if (dirIter->is_directory()) {
            fs::path filePath = dirIter->path() / targetFile;
            if (fs::exists(filePath)) {
                std::string folderPath = dirIter->path().string();
                std::cout << "Found target file in folder: " << folderPath << std::endl;
                break; // Stop searching after finding the target file in the first folder
            }
        }
    }

    // folderPath should be the Hanami-Basket folder

    MainWindow *w = new MainWindow();
    w->show();

    return app.exec();
}





