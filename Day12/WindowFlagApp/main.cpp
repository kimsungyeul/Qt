//Window Flag 예제
// 타이틀바가없는 기기들에서 사용
#include "widget.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QLabel* hello = new QLabel("Hello Qt!", 0, Qt::FramelessWindowHint | Qt::WindowTitleHint        // 12장 36P 참조해서 windowflags에 여러가지 옵션활용가능
                               | Qt::WindowSystemMenuHint
                               | Qt::WindowMaximizeButtonHint
                               | Qt::WindowContextHelpButtonHint);
    hello->setCursor(Qt::OpenHandCursor);
    hello->showMaximized();
    return a.exec();
}
