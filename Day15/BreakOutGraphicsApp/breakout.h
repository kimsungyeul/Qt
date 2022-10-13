#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QGraphicsView>
#include <QGraphicsScene>

class Breakout : public QGraphicsView
{
public:
    Breakout(QWidget *parent = nullptr);

    void start();

    QGraphicsScene* scene;
};

#endif // BREAKOUT_H
