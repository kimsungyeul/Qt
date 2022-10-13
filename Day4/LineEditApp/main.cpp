#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    QLabel label("<font color=green>Hello,World</font>",&w);
    label.setGeometry(10,10,300,30);

    QLineEdit lineEdit1(&w);
    lineEdit1.setEchoMode(QLineEdit::PasswordEchoOnEdit);
    lineEdit1.setGeometry(10,50,300,30);

    QLineEdit lineEdit2(&w);
    lineEdit2.setGeometry(10,90,300,30);

    QObject::connect(&lineEdit1,SIGNAL(textChanged(const QString &)),&label,SLOT(setText(const QString &)));
    QObject::connect(&lineEdit2,SIGNAL(textChanged(const QString &)),&label,SLOT(setText(const QString &)));

    w.show();
    return a.exec();
}
