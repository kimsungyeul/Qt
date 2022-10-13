#if 0
// Graphics View.1
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene;
    scene->addRect(-10, -10, 120, 50);                      /* 아이템을 간단히 추가 */
    QGraphicsItem *item = new QGraphicsTextItem("Hello World");
    scene->addItem(item);

    QGraphicsView *view = new QGraphicsView;
    view->setScene(scene);
    view->show();

    return a.exec();
}
#endif

#if 0
// Graphics View.2
#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsRectItem *rect = scene->addRect(-10, -10, 120, 50);
    rect->setPen(QPen(Qt::red));
    rect->setBrush(QBrush(Qt::yellow));
    QGraphicsItem *item = new QGraphicsTextItem("Hello World");
    scene->addItem(item);
    QGraphicsView *view = new QGraphicsView(scene);
    view->show();

    return a.exec();
}
#endif

#if 1
// Animation example
#include <QtWidgets>

int main(int argc, char **argv)
{
     QApplication a(argc, argv);

     QGraphicsRectItem *rect = new QGraphicsRectItem(0, 0, 40, 20);
     rect->setBrush(QBrush(Qt::blue));

     QTimeLine *timeLine = new QTimeLine(5000);    // 전체 애니메이션 시간은 5000ms
     timeLine->setFrameRange(0, 100);                        // 0 ~ 100까지의 프레임 범위

     QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
     animation->setItem(rect);
     animation->setTimeLine(timeLine);

     for (int i = 0; i < 200; ++i)        // 0.0 ~ 1.0 범위의 속성 설정
          animation->setPosAt(i /200.0, QPointF(i , i));
     animation->setRotationAt(80.0/200.0, 30);
     animation->setRotationAt(180.0/200.0, 90);

     QGraphicsScene *scene = new QGraphicsScene( );
     scene->setSceneRect(0, 0, 250, 250);
     scene->addItem(rect);

     QGraphicsView *view = new QGraphicsView(scene);
     view->show( );
     timeLine->start( );

     return a.exec( );
}
#endif
