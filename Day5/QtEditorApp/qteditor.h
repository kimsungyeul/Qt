#ifndef QTEDITOR_H
#define QTEDITOR_H

#if 1
// MyCode
#include <QMainWindow>

class QAction;
class QTextEdit;

class QtEditor : public QMainWindow
{
    Q_OBJECT
private:
    template <typename T>
    QAction* makeAction(QString icon, QString text, T shortCut,
                        QString toolTip, QObject* rect, const char* slot);
    template <>
    QAction* makeAction(QString icon, QString text, const char* shortCut,
                        QString toolTip, QObject* rect, const char* slot);

    template <typename T, typename Functor>
    QAction* makeAction(QString icon, QString text, T shortCut,
                        QString toolTip, Functor lambda);

    QTextEdit* textedit;

public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveasFile();
    void printFile();
    void alignText();
};
#endif

#if 0
// ProCode
#include <QMainWindow>

class QAction;

class QtEditor : public QMainWindow
{
    Q_OBJECT
private:
    template <typename T>
    QAction* makeAction(QString icon, QString text, T shortCut,
                        QString toolTip, QObject* rect, const char* slot);
    template <>
    QAction* makeAction(QString icon, QString text, const char* shortCut,
                        QString toolTip, QObject* rect, const char* slot);

    template <typename T, typename Functor>
    QAction* makeAction(QString icon, QString text, T shortCut,
                        QString toolTip, Functor lambda);
public:
    QtEditor(QWidget *parent = nullptr);
~QtEditor();

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveasFile();
    void printFile();
};
#endif

#if 0
// test
#include <QMainWindow>

class QAction;
class QTextEdit;

class QtEditor : public QMainWindow
{
    Q_OBJECT
private:
    QAction* makeAction(QString icon, QString name, QString shortCut,\
                        QString toolTip, QObject* recv, const char* slot);

    QTextEdit* textedit;

public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();

public slots:
    void newFile();
    void openFile();
    void saveFile();
    void saveasFile();
    void printFile();
    void alignText();
};
#endif
#endif // QTEDITOR_H
