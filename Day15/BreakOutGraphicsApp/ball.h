#ifndef BALL_H
#define BALL_H

#include <QGraphicsEllipseItem>

// 원형 공을 위해서 QGraphicsEllipseItem 클래스 사용
class Ball : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Ball(QGraphicsItem *parent = nullptr);
    double getCenterX();

public slots:
    void move();                            // 이동을 위한 QTimer의 슬롯

private:
    double xVelocity, yVelocity;            // 공의 속도
    void reverseVelocityIfOutOfBounds();
    void handlePaddleCollision();
    void handleBlockCollision();
};

#endif // BALL_H
