#ifndef PENDULUMCONTROLLER_H
#define PENDULUMCONTROLLER_H

#include <QTimeLine>
#include <QGraphicsItem>

class PendulumController : public QObject
{
    Q_OBJECT
public:
    explicit PendulumController(QGraphicsItem* pendulum, QObject* parent = 0);

private slots:
    void slotRotateItem(int r);
    void slotRestartTimeLine();

private:
    QTimeLine m_timeline;
    QGraphicsItem* m_pendulum;
};

#endif // PENDULUMCONTROLLER_H
