#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>

class Application : public QApplication
{
public:
    Application(int&, char**);

public:
    bool notify(QObject*, QEvent*) override;
};

#endif // APPLICATION_H
