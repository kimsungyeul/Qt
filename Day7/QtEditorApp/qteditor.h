#ifndef QTEDITOR_H
#define QTEDITOR_H

#if 1
// MyCode
#include <QMainWindow>
#include <QList>

class QAction;
class QTextEdit;
class QLabel;
class QMdiArea;
class QMdiSubWindow;
class QFontComboBox;
class QDoubleSpinBox;

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

    QLabel* statusLabel;
    QMdiArea* mdiArea;
    QMenu* windowMenu;
    QMdiSubWindow* subWindow;
    QList<QAction*> actions;
    QTextEdit* prevTextEdit = nullptr;
    QFontComboBox* fontComboBox;
    QDoubleSpinBox* sizeSpinBox;
    QHash<QAction*, QWidget*> windowHash;

public:
    QtEditor(QWidget *parent = nullptr);
    ~QtEditor();

public slots:
    // File Menu
    void newFile();
    void openFile();
    void saveFile();
    void saveasFile();
    void printFile();

    // Edit Menu
    void undo();
    void redo();
    void copy();
    void cut();
    void paste();
    void zoomIn();
    void zoomOut();

    // Format Menu
    void alignText();
    void setColor();
    void setFont();

    // Window Menu
    void connectWindow(QMdiSubWindow*);

    void setTextFont(QFont);
    void setTextSize(qreal);
    void setFontWidget();       /*QFontComboBox와 QDoubleSpinBox 설정*/
    void setCurrentWindow();
    void about();
    void selectWindow();
    void closeWindow();
    //void alignText();
};
#endif
#endif // QTEDITOR_H
