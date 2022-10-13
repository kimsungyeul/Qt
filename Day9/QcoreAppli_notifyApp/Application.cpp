#include "Application.h"
#include "widget.h"

Application::Application(int& argc,char** argv) : QApplication(argc,argv)
{
}

// 모든 이벤트가 notify를 거쳐간다.
bool Application::notify(QObject* receiver, QEvent* e){
    qDebug() << "Application : notify called";

    if(e->type() == QEvent::MouseButtonPress){
        qDebug() << "Application : mouse event";
        return false;       // event를 무시(ignore)
    }

    Widget* obj = dynamic_cast<Widget*>(receiver);              // 상속관계 확인용 dynamic_cast

    if(obj != nullptr){                 // 상속이맞다면
        qDebug() << "Cast successful : " << obj->metaObject()->className();      // Widget과 관련된 Object라면 여기로 들어간다.
        qDebug() << e->type();
    }
    else{                               // 상속이 아니라면
        qDebug() << "Cast failed : ";                                   // Widget과 관련이없는 Object관련된 함수면 출력이안되므로
    }                                                                   // classname 확인 불가능

    return QApplication::notify(receiver,e);
}
