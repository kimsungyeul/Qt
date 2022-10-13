#include "widget.h"
#include "breakout.h"

#include <QApplication>

Breakout* game;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    game = new Breakout(0);
    game->show();
    game->start();

    return a.exec();
}
