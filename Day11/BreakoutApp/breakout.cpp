#if 0
// 패들의 충돌처리
#include <QLabel>
#include <QApplication>

#include "breakout.h"

#define WIDTH   50
#define HEIGHT  12
#define SCR_WIDTH   300
#define SCR_HEIGHT  400

Breakout::Breakout(QWidget *parent)
    : QWidget(parent), xDir(1), yDir(-1)        /* 두 변수를 초기화 */
{
    ball = new QLabel(this);
    ball->setGeometry(SCR_WIDTH*0.8, SCR_HEIGHT*0.875, 10, 10);
    ball->setStyleSheet("QLabel{ background-color:red; border-radius: 5px; }");
    paddle = new QLabel(this);
    paddle->setGeometry(SCR_WIDTH*0.7, SCR_HEIGHT*0.9, WIDTH, HEIGHT);
    paddle->setStyleSheet("QLabel{ background-color:blue; }");

    score = new QLabel(this);

    for(int y=0,i=0; y<5; y++){
        for(int x=0; x<6; x++, i++){
            bricks[i] = new QLabel(this);
            bricks[i]->setStyleSheet("QLabel{ background-color:cyan;"
                                      "border:1px solid black }");
            bricks[i]->setGeometry(x*WIDTH, y*HEIGHT+30, WIDTH, HEIGHT);
        }
    }

    resize(SCR_WIDTH, SCR_HEIGHT);

    setMouseTracking(true);

    timerId = startTimer(10);                   /* QObject의 타이머를 시작 */
}

Breakout::~Breakout()
{
    delete ball;
    delete paddle;

    for(int i=0; i<NO_OF_BRICKS; i++){
        delete bricks[i];
    }
}

void Breakout::keyPressEvent(QKeyEvent* e){
    int x = paddle->pos().x();

    int windowWidth = Breakout::size().width();

    switch(e->key()){
    case Qt::Key_Left:
        x = (x<0)?0:x;
        paddle->move(x-MOVE_SPEED,paddle->y());
        break;
    case Qt::Key_Right:
        //x = (x+WIDTH>SCR_WIDTH)? SCR_WIDTH-WIDTH : x;
        x = (x+WIDTH>windowWidth)? windowWidth-WIDTH : x;
        paddle->move(x+MOVE_SPEED,paddle->y());
        break;
    case Qt::Key_Escape:
        qApp->exit();
        break;
    default:
        QWidget::keyPressEvent(e);
    }
}

void Breakout::mouseMoveEvent(QMouseEvent* e){
    int x = e->pos().x();
    int windowWidth = Breakout::size().width();
    //x = (x<0)?0:(x+WIDTH > width())?width()-WIDTH:x;
    x = (x<0)?0:(x+WIDTH > windowWidth)?windowWidth-WIDTH:x;
    paddle->move(x,paddle->y());
}

void Breakout::timerEvent(QTimerEvent* e){
    Q_UNUSED(e);
    moveObjects();
    checkCollision();
}

void Breakout::moveObjects(){
    ball->move(ball->x() + xDir, ball->y() + yDir);

    if((ball->x() <= 0) || (ball->x()+10 >= SCR_WIDTH)){
        xDir *= -1;
    }

    if(ball->y() <= 0){
        yDir = 1;

    }
}

void Breakout::checkCollision(){
    if(ball->geometry().bottom() > height()) {      /* 공이 아래로 가면 게임 종료 */
        killTimer(timerId);
        qDebug("Game lost");
    }

    /* 남은 블록이 없으면 게임 종료 */
    int j = 0;
    for(int i=0; i<NO_OF_BRICKS; i++){
        if(bricks[i]->isHidden()){
            j++;
        }
    }

    if(j == NO_OF_BRICKS){
        killTimer(timerId);
        qDebug("Victory");
    }

    /* 사용자(패들)와 충돌을 처리 */
    if((ball->geometry()).intersects(paddle->geometry())){
        int paddleLPos = paddle->geometry().left();
        int ballLPos = ball->geometry().left();
        int first = paddleLPos + 8;
        int second = paddleLPos + 16;
        int third = paddleLPos + 24;
        int fourth = paddleLPos + 32;

        /* 패들의 맞은 부분에 따라서 공의 반사되는 방향 조정 */
        if(ballLPos < first){
            xDir = -1;
            yDir = -1;
        }
        if(ballLPos >= first && ballLPos < second){
            xDir = 1;
            yDir *= -1;
        }
        if(ballLPos >= second && ballLPos < third){
            xDir = 0;
            yDir *= -1;
        }
        if(ballLPos >= third && ballLPos < fourth){
            xDir = 1;
            yDir *= -1;
        }
        if(ballLPos > fourth){
            xDir = 1;
            yDir = -1;
        }
    }

    /* 블록의 충돌을 처리 */
    for(int i=0; i<NO_OF_BRICKS; i++){
        if((ball->geometry()).intersects(bricks[i]->geometry())){
            int ballLeft = ball->geometry().left();
            int ballHeight = ball->geometry().height();
            int ballWidth = ball->geometry().width();
            int ballTop = ball->geometry().top();

            /* 현재 블록의 위치를 계산 */
            QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
            QPoint pointLeft(ballLeft - 1, ballTop);
            QPoint pointTop(ballLeft, ballTop - 1);
            QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);
            if(!bricks[i]->isHidden()){             /* 공과 블록의 충돌 검사 */
                if(bricks[i]->geometry().contains(pointRight)){
                    xDir = -1;
                }
                else if(bricks[i]->geometry().contains(pointLeft)){
                    xDir = 1;
                }
                if(bricks[i]->geometry().contains(pointTop)){
                    yDir = 1;
                }
                else if(bricks[i]->geometry().contains(pointBottom)){
                    yDir = -1;
                }
                bricks[i]->setHidden(true);
            }

        }
    }
}

void Breakout::autoMode(){
    //if((ball->geometry()).intersects(paddle->geometry())){
    if((ball->geometry()).bottom()){
        int paddleLPos = paddle->geometry().left();
        int ballLPos = ball->geometry().left();
        int first = paddleLPos + 8;
        int second = paddleLPos + 16;
        int third = paddleLPos + 24;
        int fourth = paddleLPos + 32;

        /* 패들의 맞은 부분에 따라서 공의 반사되는 방향 조정 */
        if(ballLPos < first){
            xDir = -1;
            yDir = -1;
        }
        if(ballLPos >= first && ballLPos < second){
            xDir = -1;
            yDir *= -1;
        }
        if(ballLPos >= second && ballLPos < third){
            xDir = 0;
            yDir *= -1;
        }
        if(ballLPos >= third && ballLPos < fourth){
            xDir = 1;
            yDir *= -1;
        }
        if(ballLPos > fourth){
            xDir = 1;
            yDir = -1;
        }
    }
}

#endif

#if 0
// Sound 추가
// Auto Mode 추가
#include <QLabel>
#include <QApplication>
#include <QMessageBox>
#include <QtMultimedia/QtMultimedia>

#include "breakout.h"

#define WIDTH   50
#define HEIGHT  12
#define SCR_WIDTH   300
#define SCR_HEIGHT  400

Breakout::Breakout(QWidget *parent)
    : QWidget(parent), xDir(1), yDir(-1)        /* 두 변수를 초기화 */
{
    ball = new QLabel(this);
    ball->setGeometry(SCR_WIDTH*0.8, SCR_HEIGHT*0.875, 10, 10);
    ball->setStyleSheet("QLabel{ background-color:red; border-radius: 5px; }");
    paddle = new QLabel(this);
    paddle->setGeometry(SCR_WIDTH*0.7, SCR_HEIGHT*0.9, WIDTH, HEIGHT);
    paddle->setStyleSheet("QLabel{ background-color:blue; }");

    score = new QLabel(this);
    score->setText("Score : 0   ");
    score->setAlignment(Qt::AlignLeft | Qt::AlignTop);

#if 1
    for(int y=0,i=0; y<5; y++){
        for(int x=0; x<6; x++, i++){
            bricks[i] = new QLabel(this);
            bricks[i]->setStyleSheet("QLabel{ background-color:cyan;"
                                      "border:1px solid black }");
            bricks[i]->setGeometry(x*WIDTH, y*HEIGHT+30, WIDTH, HEIGHT);
        }
    }

#else
    for(int y=0,i=0; y<10; y++){
        for(int x=0; x<11; x++, i++){
            bricks[i] = new QLabel(this);
            bricks[i]->setStyleSheet("QLabel{ background-color:cyan;"
                                      "border:1px solid black }");
            bricks[i]->setGeometry(x*WIDTH, y*HEIGHT+30, WIDTH, HEIGHT);
        }
    }
#endif

    resize(SCR_WIDTH, SCR_HEIGHT);

    setMouseTracking(true);

    /* 사운드 출력을 위한 재생 리스트와 미디어 플레이어의 초기화 */
    /* 사운드 출력을 위한 미디어 플레이어의 초기화 */
    QAudioOutput *bgAudioOutput = new QAudioOutput;
    bgAudioOutput->setVolume(10);

    bgPlayer = new QMediaPlayer( );
    bgPlayer->setAudioOutput(bgAudioOutput);
    bgPlayer->setLoops(QMediaPlayer::Infinite);         /* 무한 반복 */
    bgPlayer->setSource(QUrl::fromLocalFile(QFileInfo("background.wav" ).absoluteFilePath( )));
    bgPlayer->play( );
    /* 효과음 출력을 위한 플레이어 */
    QAudioOutput *bgEffectOutput = new QAudioOutput;
    bgEffectOutput->setVolume(200);

    effectPlayer = new QMediaPlayer( );
    effectPlayer->setAudioOutput(bgEffectOutput);
    effectPlayer->setLoops(QMediaPlayer::Once);
    effectPlayer->setSource(QUrl::fromLocalFile(QFileInfo("effect.wav").absoluteFilePath( )));

    autoModeMsg();

    timerId = startTimer(5);                   /* QObject의 타이머를 시작 */   // ball 속도와 관련
}

Breakout::~Breakout()
{
    delete ball;
    delete paddle;

    for(int i=0; i<NO_OF_BRICKS; i++){
        delete bricks[i];
    }
}

void Breakout::keyPressEvent(QKeyEvent* e){
    int x = paddle->pos().x();

    int windowWidth = Breakout::size().width();

    switch(e->key()){
    case Qt::Key_Left:
        x = (x<0)?0:x;
        paddle->move(x-MOVE_SPEED,paddle->y());
        break;
    case Qt::Key_Right:
        //x = (x+WIDTH>SCR_WIDTH)? SCR_WIDTH-WIDTH : x;
        x = (x+WIDTH>windowWidth)? windowWidth-WIDTH : x;
        paddle->move(x+MOVE_SPEED,paddle->y());
        break;
    case Qt::Key_Escape:
        qApp->exit();
        break;
    default:
        QWidget::keyPressEvent(e);
    }
}

void Breakout::mouseMoveEvent(QMouseEvent* e){
    int x = e->pos().x();
    int windowWidth = Breakout::size().width();
    //x = (x<0)?0:(x+WIDTH > width())?width()-WIDTH:x;
    x = (x<0)?0:(x+WIDTH > windowWidth)?windowWidth-WIDTH:x;
    paddle->move(x,paddle->y());
}

void Breakout::timerEvent(QTimerEvent* e){
    Q_UNUSED(e);
    moveObjects();
    checkCollision();
    autoMode();
}

void Breakout::moveObjects(){
    ball->move(ball->x() + xDir, ball->y() + yDir);

    if((ball->x() <= 0) || (ball->x()+10 >= SCR_WIDTH)){
        xDir *= -1;
    }

    if(ball->y() <= 0){
        yDir = 1;

    }
}

void Breakout::checkCollision(){
    if(ball->geometry().bottom() > height()) {      /* 공이 아래로 가면 게임 종료 */
        killTimer(timerId);
        qDebug("Game lost");
        int ret = QMessageBox::information(this,"Game Status","GAME OVER\nReGame?",QMessageBox::Yes | QMessageBox::No);
        if(ret == QMessageBox::Yes){
            for(int i=0; i<NO_OF_BRICKS; i++){
                bricks[i]->setHidden(false);
            }
            ball->setGeometry(SCR_WIDTH*0.8, SCR_HEIGHT*0.875, 10, 10);
            paddle->setGeometry(SCR_WIDTH*0.7, SCR_HEIGHT*0.9, WIDTH, HEIGHT);
            score->setText("Score : 0   ");
            autoModeMsg();
            timerId = startTimer(5);

        }
        else{
            bricks[30]->setHidden(false);
            qApp->quit();
        }
    }

    /* 남은 블록이 없으면 게임 종료 */
    int j = 0;
    for(int i=0; i<NO_OF_BRICKS; i++){
        if(bricks[i]->isHidden()){
            ++j;
            score->setText(QString("Score : %1   ").arg(j));
        }
    }
    //score->setText(QString("Score : %1").arg(j));

    if(j == NO_OF_BRICKS){
        killTimer(timerId);
        qDebug("Victory");
        int ret = QMessageBox::information(this,"Game Status","VICTORY\nRegame?",QMessageBox::Yes | QMessageBox::No);
        if(ret == QMessageBox::Yes){
            for(int i=0; i<NO_OF_BRICKS; i++){
                bricks[i]->setHidden(false);
            }
            ball->setGeometry(SCR_WIDTH*0.8, SCR_HEIGHT*0.875, 10, 10);
            paddle->setGeometry(SCR_WIDTH*0.7, SCR_HEIGHT*0.9, WIDTH, HEIGHT);
            score->setText("Score : 0   ");
            autoModeMsg();
            timerId = startTimer(5);
        }
        else{
            bricks[30]->setHidden(false);
            qApp->quit();
        }
    }

    /* 사용자(패들)와 충돌을 처리 */
    if((ball->geometry()).intersects(paddle->geometry())){
        int paddleLPos = paddle->geometry().left();
        int ballLPos = ball->geometry().left();
        int first = paddleLPos + 8;
        int second = paddleLPos + 16;
        int third = paddleLPos + 24;
        int fourth = paddleLPos + 32;

        /* 패들의 맞은 부분에 따라서 공의 반사되는 방향 조정 */
        if(ballLPos < first){
            xDir = -1;
            yDir = -1;
        }
        if(ballLPos >= first && ballLPos < second){
            xDir = 1;
            yDir *= -1;
        }
        if(ballLPos >= second && ballLPos < third){
            xDir = 0;
            yDir *= -1;
        }
        if(ballLPos >= third && ballLPos < fourth){
            xDir = 1;
            yDir *= -1;
        }
        if(ballLPos > fourth){
            xDir = 1;
            yDir = -1;
        }
        effectPlayer->stop();               /* 패들과 충돌했을때 사운드 출력 */
        effectPlayer->play();
    }

    /* 블록의 충돌을 처리 */
    for(int i=0; i<NO_OF_BRICKS; i++){
        if((ball->geometry()).intersects(bricks[i]->geometry())){
            int ballLeft = ball->geometry().left();
            int ballHeight = ball->geometry().height();
            int ballWidth = ball->geometry().width();
            int ballTop = ball->geometry().top();

            /* 현재 블록의 위치를 계산 */
            QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
            QPoint pointLeft(ballLeft - 1, ballTop);
            QPoint pointTop(ballLeft, ballTop - 1);
            QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);
            if(!bricks[i]->isHidden()){             /* 공과 블록의 충돌 검사 */
                if(bricks[i]->geometry().contains(pointRight)){
                    xDir = -1;
                }
                else if(bricks[i]->geometry().contains(pointLeft)){
                    xDir = 1;
                }
                if(bricks[i]->geometry().contains(pointTop)){
                    yDir = 1;
                }
                else if(bricks[i]->geometry().contains(pointBottom)){
                    yDir = -1;
                }
                bricks[i]->setHidden(true);

                /* 블록과 충돌했을때 사운드 출력 */
                effectPlayer->stop();
                effectPlayer->play();
            }

        }
    }
}

void Breakout::autoMode(){
    int windowWidth = Breakout::size().width();

    int x = ball->pos().x();
    int y = ball->pos().y();

    if(automode){
        if((paddle->pos().y() < y+13) && (autotrig == true)){
            if(x>WIDTH/2 || (x<windowWidth-WIDTH/2)){
                paddle->move(x-WIDTH/2,paddle->y());
            }
            else if(x<WIDTH/2){
                paddle->move(0,paddle->pos().y());
            }
            else if(x>(windowWidth-WIDTH/2)){
                paddle->move(windowWidth-WIDTH,paddle->pos().y());
            }
            autotrig = false;
        }
        else if((paddle->pos().y() > y+13)){
            autotrig = true;
        }
    }
}

void Breakout::autoModeMsg(){
    int ret = QMessageBox::information(this,"Mode Select","AUTO MODE?",QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes){
        automode = true;
    }
    else if(ret == QMessageBox::No){
        automode = false;
    }
}

#endif

#if 1
// 새 클래스(Ball,Paddle,Brick) 추가
// QLabel을 없애고 역할들을 클래스화시킴
#include <QLabel>
#include <QApplication>
#include <QMessageBox>
#include <QtMultimedia/QtMultimedia>

#include "breakout.h"

#define WIDTH   50
#define HEIGHT  12
#define SCR_WIDTH   300
#define SCR_HEIGHT  400

Breakout::Breakout(QWidget *parent)
    : QWidget(parent), xDir(1), yDir(-1)        /* 두 변수를 초기화 */
{
    ball = new Ball(this);
    ball->setGeometry(SCR_WIDTH*0.8, SCR_HEIGHT*0.875, 10, 10);

    paddle = new Paddle(this);
    paddle->setGeometry(SCR_WIDTH*0.7, SCR_HEIGHT*0.9, WIDTH, HEIGHT);

    score = new QLabel(this);
    score->setText("Score : 0   ");
    score->setAlignment(Qt::AlignLeft | Qt::AlignTop);

#if 1
    for(int y=0,i=0; y<5; y++){
        for(int x=0; x<6; x++, i++){
            bricks[i] = new Brick(this);
            bricks[i]->setStyleSheet("QLabel{ background-color:cyan;"
                                      "border:1px solid black }");
            bricks[i]->setGeometry(x*WIDTH, y*HEIGHT+30, WIDTH, HEIGHT);
        }
    }

#else
    for(int y=0,i=0; y<10; y++){
        for(int x=0; x<11; x++, i++){
            bricks[i] = new QLabel(this);
            bricks[i]->setStyleSheet("QLabel{ background-color:cyan;"
                                      "border:1px solid black }");
            bricks[i]->setGeometry(x*WIDTH, y*HEIGHT+30, WIDTH, HEIGHT);
        }
    }
#endif

    resize(SCR_WIDTH, SCR_HEIGHT);

    setMouseTracking(true);

    /* 사운드 출력을 위한 재생 리스트와 미디어 플레이어의 초기화 */
    /* 사운드 출력을 위한 미디어 플레이어의 초기화 */
    QAudioOutput *bgAudioOutput = new QAudioOutput;
    bgAudioOutput->setVolume(10);

    bgPlayer = new QMediaPlayer( );
    bgPlayer->setAudioOutput(bgAudioOutput);
    bgPlayer->setLoops(QMediaPlayer::Infinite);         /* 무한 반복 */
    bgPlayer->setSource(QUrl::fromLocalFile(QFileInfo("background.wav" ).absoluteFilePath( )));
    bgPlayer->play( );
    /* 효과음 출력을 위한 플레이어 */
    QAudioOutput *bgEffectOutput = new QAudioOutput;
    bgEffectOutput->setVolume(200);

    effectPlayer = new QMediaPlayer( );
    effectPlayer->setAudioOutput(bgEffectOutput);
    effectPlayer->setLoops(QMediaPlayer::Once);
    effectPlayer->setSource(QUrl::fromLocalFile(QFileInfo("effect.wav").absoluteFilePath( )));
/* 작업중 */
    autoModeMsg();

    QPicture picture;
    QPainter painter;

    painter.begin(&picture);            // QPicture에 그리기
    painter.drawEllipse(10,20,80,70);   // 원그리기
    painter.end();
    picture.save("drawing.pic");        // 저장

    timerId = startTimer(5);                   /* QObject의 타이머를 시작 */   // ball 속도와 관련
}

Breakout::~Breakout()
{
    delete ball;
    delete paddle;

    for(int i=0; i<NO_OF_BRICKS; i++){
        delete bricks[i];
    }
}

void Breakout::keyPressEvent(QKeyEvent* e){
    int x = paddle->pos().x();

    int windowWidth = Breakout::size().width();

    switch(e->key()){
    case Qt::Key_Left:
        x = (x<0)?0:x;
        paddle->move(x-MOVE_SPEED,paddle->y());
        break;
    case Qt::Key_Right:
        //x = (x+WIDTH>SCR_WIDTH)? SCR_WIDTH-WIDTH : x;
        x = (x+WIDTH>windowWidth)? windowWidth-WIDTH : x;
        paddle->move(x+MOVE_SPEED,paddle->y());
        break;
    case Qt::Key_Escape:
        qApp->exit();
        break;
    default:
        QWidget::keyPressEvent(e);
    }
}

void Breakout::mouseMoveEvent(QMouseEvent* e){
    int x = e->pos().x();
    int windowWidth = Breakout::size().width();
    //x = (x<0)?0:(x+WIDTH > width())?width()-WIDTH:x;
    x = (x<0)?0:(x+WIDTH > windowWidth)?windowWidth-WIDTH:x;
    paddle->move(x,paddle->y());
}

void Breakout::timerEvent(QTimerEvent* e){
    Q_UNUSED(e);
    moveObjects();
    checkCollision();
    autoMode();
}

void Breakout::paintEvent(QPaintEvent* e){
    Q_UNUSED(e);
    QPicture picture;
    picture.load("drawing.pic");            // 저장한 내용 불러오기
    QPainter painter;
    painter.begin(this);                    // 위젯 설정
    painter.drawPicture(0, 0, picture);     // 그리기
    painter.end();
}

void Breakout::moveObjects(){
    ball->move(ball->x() + xDir, ball->y() + yDir);

    if((ball->x() <= 0) || (ball->x()+10 >= SCR_WIDTH)){
        xDir *= -1;
    }

    if(ball->y() <= 0){
        yDir = 1;

    }
}

void Breakout::checkCollision(){
    if(ball->geometry().bottom() > height()) {      /* 공이 아래로 가면 게임 종료 */
        killTimer(timerId);
        qDebug("Game lost");
        int ret = QMessageBox::information(this,"Game Status","GAME OVER\nReGame?",
                                           QMessageBox::Yes | QMessageBox::No);
        if(ret == QMessageBox::Yes){
            for(int i=0; i<NO_OF_BRICKS; i++){
                bricks[i]->setHidden(false);
            }

            ball->setGeometry(SCR_WIDTH*0.8, SCR_HEIGHT*0.875, 10, 10);
            paddle->setGeometry(SCR_WIDTH*0.7, SCR_HEIGHT*0.9, WIDTH, HEIGHT);
            score->setText("Score : 0   ");
            autoModeMsg();
            timerId = startTimer(5);
        }
        else{
            bricks[30]->setHidden(false);
            qApp->quit();
        }
    }

    /* 남은 블록이 없으면 게임 종료 */
    int j = 0;
    for(int i=0; i<NO_OF_BRICKS; i++){
        if(bricks[i]->isHidden()){
            ++j;
            score->setText(QString("Score : %1   ").arg(j));
        }
    }

    if(j == NO_OF_BRICKS){
        killTimer(timerId);
        qDebug("Victory");
        int ret = QMessageBox::information(this,"Game Status","VICTORY\nRegame?",\
                                           QMessageBox::Yes | QMessageBox::No);
        if(ret == QMessageBox::Yes){
            for(int i=0; i<NO_OF_BRICKS; i++){
                bricks[i]->setHidden(false);
            }
            ball->setGeometry(SCR_WIDTH*0.8, SCR_HEIGHT*0.875, 10, 10);
            paddle->setGeometry(SCR_WIDTH*0.7, SCR_HEIGHT*0.9, WIDTH, HEIGHT);
            score->setText("Score : 0   ");
            autoModeMsg();
            timerId = startTimer(5);
        }
        else{
            bricks[30]->setHidden(false);
            qApp->quit();
        }
    }

    /* 사용자(패들)와 충돌을 처리 */
    if((ball->geometry()).intersects(paddle->geometry())){
        int paddleLPos = paddle->geometry().left();
        int ballLPos = ball->geometry().left();
        int first = paddleLPos + 8;
        int second = paddleLPos + 16;
        int third = paddleLPos + 24;
        int fourth = paddleLPos + 32;

        /* 패들의 맞은 부분에 따라서 공의 반사되는 방향 조정 */
        if(ballLPos < first){
            xDir = -1;
            yDir = -1;
        }
        if(ballLPos >= first && ballLPos < second){
            xDir = 1;
            yDir *= -1;
        }
        if(ballLPos >= second && ballLPos < third){
            xDir = 0;
            yDir *= -1;
        }
        if(ballLPos >= third && ballLPos < fourth){
            xDir = 1;
            yDir *= -1;
        }
        if(ballLPos > fourth){
            xDir = 1;
            yDir = -1;
        }
        effectPlayer->stop();               /* 패들과 충돌했을때 사운드 출력 */
        effectPlayer->play();
    }

    /* 블록의 충돌을 처리 */
    for(int i=0; i<NO_OF_BRICKS; i++){
        if((ball->geometry()).intersects(bricks[i]->geometry())){
            int ballLeft = ball->geometry().left();
            int ballHeight = ball->geometry().height();
            int ballWidth = ball->geometry().width();
            int ballTop = ball->geometry().top();

            /* 현재 블록의 위치를 계산 */
            QPoint pointRight(ballLeft + ballWidth + 1, ballTop);
            QPoint pointLeft(ballLeft - 1, ballTop);
            QPoint pointTop(ballLeft, ballTop - 1);
            QPoint pointBottom(ballLeft, ballTop + ballHeight + 1);
            if(!bricks[i]->isHidden()){             /* 공과 블록의 충돌 검사 */
                if(bricks[i]->geometry().contains(pointRight)){
                    xDir = -1;
                }
                else if(bricks[i]->geometry().contains(pointLeft)){
                    xDir = 1;
                }
                if(bricks[i]->geometry().contains(pointTop)){
                    yDir = 1;
                }
                else if(bricks[i]->geometry().contains(pointBottom)){
                    yDir = -1;
                }
                bricks[i]->setHidden(true);

                /* 블록과 충돌했을때 사운드 출력 */
                effectPlayer->stop();
                effectPlayer->play();
            }

        }
    }
}

void Breakout::autoMode(){
    int windowWidth = Breakout::size().width();

    int x = ball->pos().x();
    int y = ball->pos().y();

    if(automode){
        if((paddle->pos().y() < y+13) && (autotrig == true)){
            if(x>WIDTH/2 || (x<windowWidth-WIDTH/2)){
                paddle->move(x-WIDTH/2,paddle->y());
            }
            else if(x<WIDTH/2){
                paddle->move(0,paddle->pos().y());
            }
            else if(x>(windowWidth-WIDTH/2)){
                paddle->move(windowWidth-WIDTH,paddle->pos().y());
            }
            autotrig = false;
        }
        else if((paddle->pos().y() > y+13)){
            autotrig = true;
        }
    }
}

void Breakout::autoModeMsg(){
    int ret = QMessageBox::information(this,"Mode Select","AUTO MODE?", QMessageBox::Yes | QMessageBox::No);
    if (ret == QMessageBox::Yes){
        automode = true;
    }
    else {
        automode = false;
    }
}
#endif
