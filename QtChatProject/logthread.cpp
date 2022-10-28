#include "logthread.h"

#include <QTreeWidgetItem>
#include <QFile>

LogThread::LogThread(QObject *parent)                               // 기본 LogThread 생성자
    : QThread{parent}
{

}

void LogThread::run()                                               // Thread 시작시 실행되는 코드
{
    Q_FOREVER {                                                     // 프로그램종료까지 반복
        if(itemList.count() > 0) {                                  // itemList가 하나로 있다면
            QFile file("log.txt");                                  // log.txt파일명 생성
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) // 파일을 열수없다면 리턴
                return;

            QTextStream out(&file);                                 // 파일출력 스트림 생성
            foreach(auto item, itemList) {                          // itemList항목 체크
                out << item->text(0) << ", ";                       // ", "의 0번째 인자를 text(0)에 저장
                out << item->text(1) << ", ";                       // ", "의 첫번째 인자를 text(1)에 저장
                out << item->text(2) << ", ";                       // ", "의 두번째 인자를 text(2)에 저장
                out << item->text(3) << ", ";                       // ", "의 세번째 인자를 text(3)에 저장
                out << item->text(4) << ", ";                       // ", "의 네번째 인자를 text(4)에 저장
                out << item->text(5) << "\n";                       // ", "의 다섯번째 인자를 text(5)에 저장
            }
            file.close();                                           // 파일 Close
        }
        sleep(60);                                                  // 1분마다 저장
    }
}

void LogThread::appendData(QTreeWidgetItem* item)                   // server의 로그기록을 저장하기위한 슬롯
{
    itemList.append(item);                                          // itemList에 item항목 추가
}
