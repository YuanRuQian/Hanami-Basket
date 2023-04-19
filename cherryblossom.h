#ifndef CHERRYBLOSSOM_H
#define CHERRYBLOSSOM_H

#include <QGraphicsPixmapItem>
#include <QObject>

class QMovie; // Forward declaration

class CherryBlossom : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit CherryBlossom(QObject *parent = nullptr);

public slots:
    void falling();

private slots:
    void updatePixmap();

private:
    QMovie* movie_; // QMovie instance for animated GIF
    QTimer *timer_;
};

#endif // CHERRYBLOSSOM_H
