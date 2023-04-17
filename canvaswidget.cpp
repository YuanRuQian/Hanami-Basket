#include "backgroundscene.h"
#include "canvaswidget.h"
#include "constants.h"
#include <QGraphicsView>
#include <QVBoxLayout>


CanvasWidget::CanvasWidget(QWidget *parent)
    : QWidget{parent}
{
    setWindowTitle("Hanami Basket");

    score = 0;

    setUpScoreLabels();

    QHBoxLayout *scoreLayout = new QHBoxLayout;
    scoreLayout->addWidget(scoreTextLabel);
    scoreLayout->addWidget(scoreCountLabel);
    scoreLayout->setAlignment(Qt::AlignCenter);

    QGraphicsView* mainView = new QGraphicsView(this);
    mainView->setFixedSize(BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
    mainView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    BackgroundScene* mainScene = new BackgroundScene(this);
    mainView->setScene(mainScene);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(scoreLayout);
    mainLayout->addWidget(mainView);
    mainLayout->setAlignment(Qt::AlignCenter);

    setLayout(mainLayout);

    connect(mainScene, &BackgroundScene::increaseScoreByOne, this, &CanvasWidget::increaseScoreByOne);
}


void CanvasWidget::setUpScoreLabels() {
    scoreTextLabel = new QLabel("Your Score: ");
    scoreCountLabel = new QLabel(QString::number(score));


    QFont scoreFont;
    scoreFont.setBold(true);
    scoreFont.setPointSize(16);

    scoreTextLabel->setFont(scoreFont);
    scoreCountLabel->setFont(scoreFont);
}


void CanvasWidget::increaseScoreByOne()
{
    score++;
    scoreCountLabel->setText(QString::number(score));
}

