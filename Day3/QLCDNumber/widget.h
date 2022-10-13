#ifndef WIDGET_H
#define WIDGET_H

#if 0
//Header base code
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
};
#endif

#endif // WIDGET_H

#if 0
// QRadioButton ex
#include <QWidget>

class QRadioButton;
class QButtonGroup;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QRadioButton* radioButton[8];
    QButtonGroup* buttonGroup;
};

#endif

#if 0
// QCheckBox ex
#include <QWidget>
#include<QCheckBox>

class QCheckBox;
class QButtonGroup;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QCheckBox* checkBox[4];
    QButtonGroup* buttonGroup;

public slots:
    void selectButton(int id);
};

#endif

#if 0
// QCheckBox ex2
#include <QWidget>
#include<QCheckBox>
#include<QLabel>
#include<QString>

class QCheckBox;
class QButtonGroup;
class QLabel;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QCheckBox* checkBox[4];
    QButtonGroup* buttonGroup;
    QLabel* label;

public slots:
    void selectButton(int id);
};

#endif

#if 1
// QDial + QSlider Example
#include<QWidget>
#include<QDial>
#include<QSlider>
#include<QStyleFactory>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QSlider* slider;
    QDial* dial;
};

#endif
