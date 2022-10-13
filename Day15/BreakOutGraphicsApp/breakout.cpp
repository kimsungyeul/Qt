#include "breakout.h"
#include "ball.h"
#include "paddle.h"
#include "block.h"

Breakout::Breakout(QWidget *parent)
    : QGraphicsView(parent)
{
    // scene 초기화
    scene = new QGraphicsScene(0, 0, 400, 600);
    setScene(scene);

    //마우스 트래킹 설정
    setMouseTracking(true);
}

void Breakout::start(){
    //공 생성
    Ball* ball = new Ball();
    ball->setPos(200, 500);
    scene->addItem(ball);

    // 사용자 캐릭터 생성
    Paddle* paddle = new Paddle();
    paddle->setPos(150, 575);
    scene->addItem(paddle);
    paddle->grabMouse();

    // 블록의 그리드 생성
    for(size_t i=0, n=7; i<n; ++i){
        for(size_t j=0, n=5; j<n; j++){
            Block* block = new Block();
            block->setPos(i*52*1.1, j*30);      // 블록들을 배치
            scene->addItem(block);
        }
    }
}

