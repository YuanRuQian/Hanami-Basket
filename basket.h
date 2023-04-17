#ifndef BASKET_H
#define BASKET_H

#include <QGraphicsPixmapItem>
#include <QObject>

class Basket : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Basket(QObject *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;
public:
    void startCollisionDetection();
signals:
    void collisionDetected();
private:
    void detectCollisions();
};

#endif // BASKET_H
