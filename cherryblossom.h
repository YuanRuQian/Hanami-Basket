#ifndef CHERRYBLOSSOM_H
#define CHERRYBLOSSOM_H

#include <QGraphicsPixmapItem>
#include <QObject>

class QTimer;

class CherryBlossom : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit CherryBlossom(QObject *parent = nullptr);

public slots:
    void falling();

private:
    QTimer *timer_;
};

#endif // CHERRYBLOSSOM_H
