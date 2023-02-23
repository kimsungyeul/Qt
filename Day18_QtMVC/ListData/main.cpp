#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;
    QListWidget listWidget(&w);
    for(int var = 1; var <= 9; ++var){
        listWidget.addItem(QString::number(var) + " item");
    }

    QPushButton b("Change", &w);
    b.move(50,50);
    QObject::connect(&b, &QPushButton::clicked, [&](){
        QListWidgetItem *itm = listWidget.currentItem();
        itm->setText("Change");
        itm->setForeground(Qt::red);
        itm->setBackground(Qt::yellow);
    });

    w.resize(150,180);
    w.show();
    return a.exec();
}
