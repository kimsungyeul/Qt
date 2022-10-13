#ifndef FILTER_H
#define FILTER_H

#include <QObject>

class Filter : public QObject           // QObject interface
{
    Q_OBJECT
public:
    explicit Filter(QObject* parent = nullptr);

public:
    bool eventFilter(QObject*, QEvent*) override;
};

#endif // FILTER_H
