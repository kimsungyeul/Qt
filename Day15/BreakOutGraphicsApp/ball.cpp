#include "ball.h"
#include <QTimer>
#include <QBrush>
#include "breakout.h"
#include "paddle.h"
#include "block.h"

extern Breakout* game;

Ball::Ball(QGraphicsItem *parent)
    : QObject(), QGraphicsEllipseItem(parent)
{
    // 공의 크기 설정
    setRect(0, 0, 20, 20);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);

    // 움직이는 초기값 : 오른쪽으로
    xVelocity = 0;
    yVelocity = -5;
    QTimer* timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(15);
}

double Ball::getCenterX(){
    return x() + rect().width()/2;
}

void Ball::move(){
    // 경계검사
    reverseVelocityIfOutOfBounds();

    // 사용자와의 충돌 검사
    handlePaddleCollision();

    // 블록과의 충돌 검사
    handleBlockCollision();

    //이동
    moveBy(xVelocity,yVelocity);
}

void Ball::reverseVelocityIfOutOfBounds(){
    double screenW = game->width();

    if(mapToScene(rect().topLeft()).x() <= 0){          // 왼쪽
        xVelocity = -1 * xVelocity;
    }
    if(mapToScene(rect().topRight()).x() >= screenW){    // 오른쪽
        xVelocity = -1 * xVelocity;
    }
    if(mapToScene(rect().topLeft()).y() <= 0){          // 윗쪽
        yVelocity = -1 * yVelocity;
    }
}

void Ball::handlePaddleCollision(){
    QList<QGraphicsItem*> cItems = collidingItems();
    for(size_t i=0, n=cItems.size(); i<n; i++){
        Paddle* paddle = dynamic_cast<Paddle*>(cItems[i]);
        if(paddle){
            yVelocity = -1 * yVelocity;               // y 축 방향 바꾸기

            //x축 속도 조정
            double ballX = getCenterX();
            double paddleX = paddle->getCenterX();

            double dvx = ballX - paddleX;
            xVelocity = (xVelocity + dvx)/15;

            break;
        }
    }
}

void Ball::handleBlockCollision(){
    QList<QGraphicsItem*> cItems = collidingItems();
    for(size_t i=0, n=cItems.size(); i<n; ++i){
        Block* block = dynamic_cast<Block*>(cItems[i]);
        if(block){      // 블록과의 충돌시 처리
            double yPad = 15;
            double xPad = 15;
            double ballx = pos().x();
            double bally = pos().y();
            double blockx = block->pos().x();
            double blocky = block->pos().y();

            if(bally > blocky + yPad && yVelocity < 0){     // 바닥과의 충돌
                yVelocity = -1 * yVelocity;
            }
            if(blocky > bally + yPad && yVelocity > 0){     // 위와의 충돌
                yVelocity = -1 * yVelocity;
            }
            if(ballx > blockx + xPad && xVelocity < 0){     // 오른쪽과의 충돌
                xVelocity = -1 * xVelocity;
            }
            if(blockx > ballx + xPad && xVelocity > 0){     // 왼쪽과의 충돌
                xVelocity = -1 * xVelocity;
            }

            game->scene->removeItem(block);             // 충돌한 블록 삭제
            delete block;
        }
    }
}
