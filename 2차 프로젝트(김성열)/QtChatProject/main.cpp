#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;                                                     // 영어로된 Text를 국제화시키기위한 클래스
    const QStringList uiLanguages = QLocale::system().uiLanguages();            // 시스템의 사용가능한 언어를 QStringList변수에 저장
    for (const QString &locale : uiLanguages) {                                 // 언어와 사용할 언어 반복
        const QString baseName = "QtChatProject_" + QLocale(locale).name();     // 프로젝트명과 선택한언어를 basename 지정
        if (translator.load(":/i18n/" + baseName)) {                            // 국제와사용코드가 있다면 실행
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;                                                               // MainWindow클래스 생성
    w.show();                                                                   // MainWindow Ui 프로그램 실행
    return a.exec();
}
