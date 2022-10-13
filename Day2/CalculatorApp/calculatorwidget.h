#ifndef CALCULATORWIDGET_H
#define CALCULATORWIDGET_H

//My
#include <QApplication>
#include <QString>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

#define WIDTH 4

class QLabel;

class CalculatorWidget : public QWidget
{
    Q_OBJECT

public:
    CalculatorWidget(QWidget *parent = nullptr);
    ~CalculatorWidget();

private:
    QLabel* label;
    QString num1,op;
    QPushButton* button[16];
    bool isFirst;

public slots:
    void numButton();
    void opButton();
};
#endif  // CALCULATORWIDGET_H

#if 0
//Pro
#include <QWidget>
#include <QVector>

class QLabel;
class QPushButton;

class CalculatorWidget : public QWidget
{
    Q_OBJECT

public:
    CalculatorWidget(QWidget *parent = nullptr);
    ~CalculatorWidget();

private:
    QLabel* label;
    QVector<QPushButton*> button;
    QString num1, op;
    bool isFirst;

public slots:
    void numButton();
    void opButton();
};
#endif
