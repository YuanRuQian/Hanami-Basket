#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDate>

#include "canvaswidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void play_background_music();

    void on_start_clicked();

    void on_scores_clicked();

    void on_back1_clicked();

    void on_back2_clicked();

    void on_easy_clicked();

    void on_medium_clicked();

    void on_hard_clicked();

    void on_loginButton_clicked();

    void on_signupButton_clicked();

    void on_guestButton_clicked();

    void on_signupButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QDate date;
    CanvasWidget *game;

    QString userProfileName;

};
#endif // MAINWINDOW_H
