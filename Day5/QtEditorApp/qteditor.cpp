#if 0
// qteditor.cpp base code
#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
}

QtEditor::~QtEditor()
{
}
#endif

#if 0
// CentralWidget Example for TextEditor
#include<QTextEdit>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    QTextEdit* textedit = new QTextEdit(this);
    setCentralWidget(textedit);
}

QtEditor::~QtEditor()
{
}
#endif

#if 0
// QMenubar class Example
#include<QTextEdit>
#include<QMenuBar>
#include<QMenu>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    QTextEdit* textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    QMenuBar* menubar = this->menuBar();
    QMenu* fileMenu = menubar->addMenu("&FIle");
}

QtEditor::~QtEditor()
{
}
#endif

#if 0
// QMenubar class add item Example
// QAction class Example
// newFIle add slots
#include<QTextEdit>
#include<QMenuBar>
#include<QMenu>
#include<QAction>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    QTextEdit* textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    QMenuBar* menubar = this->menuBar();
    setMenuBar(menubar);

    // Qt\Examples\Qt-6.3.1\widgets\mainwindows\mdi\images -> Working directory   image copy
    QAction* newAct = new QAction(QIcon("new.png"),"&New",this);//&N : accelerator
    newAct->setShortcut(tr("Ctrl+N"));                          // Shortcut
    newAct->setStatusTip(tr("make new file"));                  // not code yet
    connect(newAct,SIGNAL(triggered()),SLOT(newFile()));

    QMenu* fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
}

QtEditor::~QtEditor()
{
}

void QtEditor::newFile(){
    qDebug("Make New File");
}
#endif

#if 0
// quitAct add
#include<QTextEdit>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QApplication>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    QTextEdit* textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    QMenuBar* menubar = this->menuBar();
    setMenuBar(menubar);

    // Qt\Examples\Qt-6.3.1\widgets\mainwindows\mdi\images -> Working directory   image copy
    QAction* newAct = new QAction(QIcon("new.png"),"&New",this);//&N : accelerator
    newAct->setShortcut(tr("Ctrl+N"));                          // Shortcut
    newAct->setStatusTip(tr("make new file"));                  // not code yet
    connect(newAct,SIGNAL(triggered()),SLOT(newFile()));

    QAction* quitAct = new QAction("&Quit",this);
    connect(quitAct,SIGNAL(triggered()),qApp,SLOT(quit()));

    QMenu* fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(quitAct);
    //connect(aboutQtAct,SIGNAL(triggered()),qApp,SLOT(aboutQT()));
}

QtEditor::~QtEditor()
{
}

void QtEditor::newFile(){
    qDebug("Make New File");
}

#endif

#if 0
// Act add in menubar(File)
#include<QTextEdit>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QApplication>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    QTextEdit* textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    QMenuBar* menubar = this->menuBar();
    setMenuBar(menubar);

    // Qt\Examples\Qt-6.3.1\widgets\mainwindows\mdi\images -> Working directory   image copy
    QAction* newAct = makeAction("new.png","&New","Ctrl+N",\
                                 "make new file", this, SLOT(newFile()));

    QAction* quitAct = makeAction("quit.png","&Quit","Ctrl+Q",\
                                  "Quit this program", qApp,SLOT(quit()));

    QAction* openAct = makeAction("open.png","&Open","Ctrl+O",\
                                  "open file", this,SLOT(openFile()));

    QAction* saveAct = makeAction("save.png","&Save","Ctrl+S",\
                                  "Save this program", this,SLOT(saveFile()));

    QAction* saveasAct = makeAction("saveas.png","&Saveas","Ctrl+Shift+A",\
                                    "Save as this program", this,SLOT(saveasFile()));

    QAction* printAct = makeAction("print.png","&Print","Ctrl+P",\
                                   "Print this  program", this,SLOT(printFile()));

    QMenu* fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveasAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);
    fileMenu->addSeparator();

    //connect(aboutQtAct,SIGNAL(triggered()),qApp,SLOT(aboutQT()));
}

QtEditor::~QtEditor()
{
}

QAction* QtEditor::makeAction(QString icon, QString name, QString shortCut,
                              QString toolTip, QObject* recv, const char* slot){
    QAction* act = new QAction(name,this);
    if(icon.length()){
        act->setIcon(QIcon(icon));
    }
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act,SIGNAL(triggered()),recv,slot);

    return act;
}

void QtEditor::newFile(){
    qDebug("Make New File");
}

void QtEditor::openFile(){
    qDebug("open file");
}

void QtEditor::saveFile(){
    qDebug("Save this program");
}

void QtEditor::saveasFile(){
    qDebug("Save as this program");
}

void QtEditor::printFile(){
    qDebug("Print this program");
}


#endif

#if 0
// QToolBar Example
#include<QTextEdit>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QApplication>
#include<QToolBar>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    QTextEdit* textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    QMenuBar* menubar = this->menuBar();
    setMenuBar(menubar);

    // Qt\Examples\Qt-6.3.1\widgets\mainwindows\mdi\images -> Working directory   image copy
    QAction* newAct = makeAction("new.png","&New","Ctrl+N",\
                                 "make new file", this, SLOT(newFile()));

    QAction* quitAct = makeAction("quit.png","&Quit","Ctrl+Q",\
                                  "Quit this program", qApp,SLOT(quit()));

    QAction* openAct = makeAction("open.png","&Open","Ctrl+O",\
                                  "open file", this,SLOT(openFile()));

    QAction* saveAct = makeAction("save.png","&Save","Ctrl+S",\
                                  "Save this program", this,SLOT(saveFile()));

    QAction* saveasAct = makeAction("saveas.png","&Saveas","Ctrl+Shift+A",\
                                    "Save as this program", this,SLOT(saveasFile()));

    QAction* printAct = makeAction("print.png","&Print","Ctrl+P",\
                                   "Print this  program", this,SLOT(printFile()));

    QMenu* fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveasAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);
    fileMenu->addSeparator();

    QToolBar* fileToolBar = addToolBar("&File");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar->addAction(newAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);

    QMenu* windowMenu = menubar->addMenu("&Window");
    windowMenu->addAction(fileToolBar->toggleViewAction());

    //connect(aboutQtAct,SIGNAL(triggered()),qApp,SLOT(aboutQT()));
}

QtEditor::~QtEditor()
{
}

QAction* QtEditor::makeAction(QString icon, QString name, QString shortCut,
                              QString toolTip, QObject* recv, const char* slot){
    QAction* act = new QAction(name,this);
    if(icon.length()){
        act->setIcon(QIcon(icon));
    }
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act,SIGNAL(triggered()),recv,slot);

    return act;
}

void QtEditor::newFile(){
    qDebug("Make New File");
}

void QtEditor::openFile(){
    qDebug("open file");
}

void QtEditor::saveFile(){
    qDebug("Save this program");
}

void QtEditor::saveasFile(){
    qDebug("Save as this program");
}

void QtEditor::printFile(){
    qDebug("Print this program");
}
#endif

#if 0
// Widget add in QToolBar Example
// use addWidget method
#include<QTextEdit>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QApplication>
#include<QToolBar>
#include<QFontComboBox>
#include<QDoubleSpinBox>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    QTextEdit* textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    QMenuBar* menubar = this->menuBar();
    setMenuBar(menubar);

    // Qt\Examples\Qt-6.3.1\widgets\mainwindows\mdi\images -> Working directory   image copy
    QAction* newAct = makeAction("new.png","&New","Ctrl+N",\
                                 "make new file", this, SLOT(newFile()));

    QAction* quitAct = makeAction("quit.png","&Quit","Ctrl+Q",\
                                  "Quit this program", qApp,SLOT(quit()));

    QAction* openAct = makeAction("open.png","&Open","Ctrl+O",\
                                  "open file", this,SLOT(openFile()));

    QAction* saveAct = makeAction("save.png","&Save","Ctrl+S",\
                                  "Save this program", this,SLOT(saveFile()));

    QAction* saveasAct = makeAction("saveas.png","&Saveas","Ctrl+Shift+A",\
                                    "Save as this program", this,SLOT(saveasFile()));

    QAction* printAct = makeAction("print.png","&Print","Ctrl+P",\
                                   "Print this  program", this,SLOT(printFile()));

    QMenu* fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveasAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);
    fileMenu->addSeparator();

    QToolBar* fileToolBar = addToolBar("&File");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar->addAction(newAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);

    QMenu* windowMenu = menubar->addMenu("&Window");
    windowMenu->addAction(fileToolBar->toggleViewAction());

    QFontComboBox* fontComboBox = new QFontComboBox(this);
    connect(fontComboBox,SIGNAL(currentFontChanged(QFont)),\
            textedit,SLOT(setCurrentFont(QFont)));
    QDoubleSpinBox* sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox,SIGNAL(valueChanged(double)),textedit,SLOT(setFontPointSize(qreal)));

    addToolBarBreak();      // next toolbar is bottom line

    QToolBar* formatToolbar = addToolBar("&Format");
    formatToolbar->addSeparator();
    formatToolbar->addWidget(fontComboBox);
    formatToolbar->addWidget(sizeSpinBox);

    //connect(aboutQtAct,SIGNAL(triggered()),qApp,SLOT(aboutQT()));
}

QtEditor::~QtEditor()
{
}

QAction* QtEditor::makeAction(QString icon, QString name, QString shortCut,
                              QString toolTip, QObject* recv, const char* slot){
    QAction* act = new QAction(name,this);
    if(icon.length()){
        act->setIcon(QIcon(icon));
    }
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act,SIGNAL(triggered()),recv,slot);

    return act;
}

void QtEditor::newFile(){
    qDebug("Make New File");
}

void QtEditor::openFile(){
    qDebug("open file");
}

void QtEditor::saveFile(){
    qDebug("Save this program");
}

void QtEditor::saveasFile(){
    qDebug("Save as this program");
}

void QtEditor::printFile(){
    qDebug("Print this program");
}
#endif

#if 0
// QStatusBar class add Example
#include<QTextEdit>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QApplication>
#include<QToolBar>
#include<QFontComboBox>
#include<QDoubleSpinBox>
#include<QLabel>
#include<QStatusBar>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    QTextEdit* textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    QMenuBar* menubar = this->menuBar();
    setMenuBar(menubar);

    // Qt\Examples\Qt-6.3.1\widgets\mainwindows\mdi\images -> Working directory   image copy
    QAction* newAct = makeAction("new.png","&New","Ctrl+N",\
                                 "make new file", this, SLOT(newFile()));

    QAction* quitAct = makeAction("quit.png","&Quit","Ctrl+Q",\
                                  "Quit this program", qApp,SLOT(quit()));

    QAction* openAct = makeAction("open.png","&Open","Ctrl+O",\
                                  "open file", this,SLOT(openFile()));

    QAction* saveAct = makeAction("save.png","&Save","Ctrl+S",\
                                  "Save this program", this,SLOT(saveFile()));

    QAction* saveasAct = makeAction("saveas.png","&Saveas","Ctrl+Shift+A",\
                                    "Save as this program", this,SLOT(saveasFile()));

    QAction* printAct = makeAction("print.png","&Print","Ctrl+P",\
                                   "Print this  program", this,SLOT(printFile()));

    QMenu* fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveasAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);
    fileMenu->addSeparator();

    QToolBar* fileToolBar = addToolBar("&File");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar->addAction(newAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);

    QMenu* windowMenu = menubar->addMenu("&Window");
    windowMenu->addAction(fileToolBar->toggleViewAction());

    QFontComboBox* fontComboBox = new QFontComboBox(this);
    connect(fontComboBox,SIGNAL(currentFontChanged(QFont)),\
            textedit,SLOT(setCurrentFont(QFont)));
    QDoubleSpinBox* sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox,SIGNAL(valueChanged(double)),textedit,SLOT(setFontPointSize(qreal)));

    addToolBarBreak();      // next toolbar is bottom line

    QToolBar* formatToolbar = addToolBar("&Format");
    formatToolbar->addSeparator();
    formatToolbar->addWidget(fontComboBox);
    formatToolbar->addWidget(sizeSpinBox);

    QStatusBar* statusbar = statusBar();
    QLabel* statusLabel = new QLabel("Qt Editor",statusbar);
    statusLabel->setObjectName("StatusLabel");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started",1500);
    //connect(aboutQtAct,SIGNAL(triggered()),qApp,SLOT(aboutQT()));
}

QtEditor::~QtEditor()
{
}

QAction* QtEditor::makeAction(QString icon, QString name, QString shortCut,
                              QString toolTip, QObject* recv, const char* slot){
    QAction* act = new QAction(name,this);
    if(icon.length()){
        act->setIcon(QIcon(icon));
    }
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act,SIGNAL(triggered()),recv,slot);

    return act;
}

void QtEditor::newFile(){
    qDebug("Make New File");
}

void QtEditor::openFile(){
    qDebug("open file");
}

void QtEditor::saveFile(){
    qDebug("Save this program");
}

void QtEditor::saveasFile(){
    qDebug("Save as this program");
}

void QtEditor::printFile(){
    qDebug("Print this program");
}
#endif

#if 1
// Edit Menu Quiz (MyCode)
#include<QTextEdit>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QApplication>
#include<QToolBar>
#include<QFontComboBox>
#include<QDoubleSpinBox>
#include<QLabel>
#include<QStatusBar>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    QMenuBar* menubar = this->menuBar();
    setMenuBar(menubar);

    // Qt\Examples\Qt-6.3.1\widgets\mainwindows\mdi\images -> Working directory   image copy
    QAction *newAct = makeAction("new.png", tr("&New"), QKeySequence::New, \
                                 tr("make new file"), this, SLOT(newFile( )));

    QAction *quitAct = makeAction("quit.png", tr("&Quit"), tr("Ctrl+Q"), \
                                  tr("Quit this program"), []{ qApp->quit(); });

    QAction* openAct = makeAction("open.png",tr("&Open"), tr("Ctrl+O"),\
                                  tr("open file"), this,SLOT(openFile()));

    QAction* saveAct = makeAction("save.png",tr("&Save"),tr("Ctrl+S"),\
                                  tr("Save this program"), this,SLOT(saveFile()));

    QAction* saveasAct = makeAction("saveas.png",tr("&Saveas"),QKeySequence::SaveAs,\
                                    tr("Save as this program"), this,SLOT(saveasFile()));

    QAction* printAct = makeAction("print.png",tr("&Print"),QKeySequence::Print,\
                                   tr("Print this  program"), this,SLOT(printFile()));

    QMenu* fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveasAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);
    fileMenu->addSeparator();

    QToolBar* fileToolBar = addToolBar("&File");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar->addAction(newAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);

    QAction* undoAct = makeAction("undo.png",tr("&Undo"),tr("Ctrl+Z"),\
                                  tr("Undo this code"), textedit, SLOT(undo()));

    QAction* redoAct = makeAction("redo.png",tr("&Redo"),tr("Ctrl+Y"),\
                                  tr("Redo this code"), textedit,SLOT(redo()));

    QAction* copyAct = makeAction("copy.png",tr("&Copy"),tr("Ctrl+Shift+C"),\
                                  tr("Copy this code"), textedit,SLOT(copy()));

    QAction* cutAct = makeAction("cut.png",tr("&Cut"),tr("Ctrl+Shift+X"),\
                                 tr("Cut this code"), textedit,SLOT(cut()));

    QAction* pasteAct = makeAction("paste.png",tr("&Paste"),tr("Ctrl+Shift+V"),\
                                   tr("Save as this program"), textedit,SLOT(paste()));

    QAction* zoominAct = makeAction("zoomin.png",tr("&Zomm&In"),tr("Ctrl+Shift+O"),\
                                    tr("Zoomin this program"), textedit,SLOT(zoomIn()));

    QAction* zoomnoutAct = makeAction("zoomout.png",tr("Zoom&Out"),tr("Ctrl+Shift+I"),\
                                      tr("Zoomout this  program"), textedit,SLOT(zoomOut()));

    QMenu* editMenu = menubar->addMenu("&Edit");
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(zoominAct);
    editMenu->addAction(zoomnoutAct);

    QToolBar* editToolBar = addToolBar("&Edit");
    editToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    editToolBar->addAction(undoAct);
    editToolBar->addAction(redoAct);
    editToolBar->addSeparator();
    editToolBar->addAction(cutAct);
    editToolBar->addAction(copyAct);
    editToolBar->addAction(pasteAct);
    editToolBar->addSeparator();
    editToolBar->addAction(zoominAct);
    editToolBar->addAction(zoomnoutAct);
    editToolBar->hide();

    addToolBarBreak();      // next toolbar is bottom line

//    QMenu* alignMenu = new QMenu("&Align",this);
//    menubar->addMenu(alignMenu);
    QAction* alignLeftAct = makeAction("left.png","&Left",tr("Ctrl+Alt+L"),\
                                       tr("Left Alignment"), [=]{ textedit->setAlignment(Qt::AlignLeft); });
    QAction* alignCenterAct = makeAction("center.png","&Center",tr("Ctrl+Alt+C"),\
                                      tr("Center Alignment"), [=]{ textedit->setAlignment(Qt::AlignCenter); });
    QAction* alignRightAct = makeAction("right.png","&Right",tr("Ctrl+Alt+R"),\
                                      tr("Left Alignment"), [=]{ textedit->setAlignment(Qt::AlignRight); });
    QAction* alignJustifyAct = makeAction("justify.png","&Justify",tr("Ctrl+Alt+J"),\
                                      tr("Justify Alignment"), [=]{ textedit->setAlignment(Qt::AlignJustify); });

    QMenu* formatMenu = menubar->addMenu("&Format");
    QMenu* alignMenu = formatMenu->addMenu(QIcon("align.png"),"&Align");
    alignMenu->addAction(alignLeftAct);
    alignMenu->addAction(alignCenterAct);
    alignMenu->addAction(alignRightAct);
    alignMenu->addAction(alignJustifyAct);

    QToolBar* alignToolBar = addToolBar("&Align");
    alignToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    alignToolBar->addAction(alignLeftAct);
    alignToolBar->addAction(alignCenterAct);
    alignToolBar->addAction(alignRightAct);
    alignToolBar->addAction(alignJustifyAct);
    alignToolBar->hide();

    QMenu* windowMenu = menubar->addMenu("&Window");
    windowMenu->addAction(fileToolBar->toggleViewAction());
    windowMenu->addAction(editToolBar->toggleViewAction());
    windowMenu->addAction(alignToolBar->toggleViewAction());

    QFontComboBox* fontComboBox = new QFontComboBox(this);
    connect(fontComboBox,SIGNAL(currentFontChanged(QFont)),\
            textedit,SLOT(setCurrentFont(QFont)));

    QDoubleSpinBox* sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox,SIGNAL(valueChanged(double)),textedit,SLOT(setFontPointSize(qreal)));

    addToolBarBreak();      // next toolbar is bottom line

    QToolBar* formatToolbar = addToolBar("&Format");
    formatToolbar->addSeparator();
    formatToolbar->addWidget(fontComboBox);
    formatToolbar->addWidget(sizeSpinBox);

    QStatusBar* statusbar = statusBar();
    QLabel* statusLabel = new QLabel("Qt Editor",statusbar);
    statusLabel->setObjectName("StatusLabel");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started",1500);
    //connect(aboutQtAct,SIGNAL(triggered()),qApp,SLOT(aboutQT()));
}

QtEditor::~QtEditor()
{
}

template <typename T>
QAction *QtEditor::makeAction(QString icon, QString text, \
                              T shortCut, QString toolTip, \
                              QObject* recv, const char* slot)
{
    QAction *act = new QAction(text, this);
    if(icon.length( ))
        act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered( )), recv, slot);
    return act;
}

template <>
QAction *QtEditor::makeAction(QString icon, QString text, \
                              const char* shortCut, QString toolTip, \
                              QObject* recv, const char* slot)
{
    QAction *act = new QAction(text, this);
    if(icon.length( ))
        act->setIcon(QIcon(icon));
    act->setShortcut(QString(shortCut));
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered( )), recv, slot);
    return act;
}

template <typename T, typename Functor>
QAction* QtEditor::makeAction(QString icon, QString text, T shortCut,
                              QString toolTip, Functor lambda)
{
    QAction *act = new QAction(text, this);
    if(icon.length( ))
         act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    act->setToolTip(toolTip);
    connect(act, &QAction::triggered, this, lambda);
    return act;
}

/*
// If No used Template specialization, using bottom code for templateFunc
template <typename T, typename Functor>
QAction* QtEditor::makeAction(QString icon, QString text, T shortCut,
                              QString toolTip, Functor lambda)
{
    QAction *act = new QAction(text, this);
    if(icon.length( ))
         act->setIcon(QIcon(icon));
    QKeySequence keySequence(shortCut);
    act->setShortcut(keySequence);
    act->setStatusTip(toolTip);
    act->setToolTip(toolTip);
    connect(act, &QAction::triggered, this, lambda);
    return act;
}
*/

// No used if use Lamdafunction
void QtEditor::alignText(){
    QAction* action = qobject_cast<QAction*>(sender());
    if(action->text() == "&Center"){
        textedit->setAlignment(Qt::AlignCenter);
    }
}

void QtEditor::newFile(){
    qDebug("Make New File");
}

void QtEditor::openFile(){
    qDebug("open file");
}

void QtEditor::saveFile(){
    qDebug("Save this program");
}

void QtEditor::saveasFile(){
    qDebug("Save as this program");
}

void QtEditor::printFile(){
    qDebug("Print this program");
}
#endif

#if 0
// Edit Menu Quiz (ProCode)
#include<QTextEdit>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QApplication>
#include<QToolBar>
#include<QFontComboBox>
#include<QDoubleSpinBox>
#include<QLabel>
#include<QStatusBar>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    QTextEdit* textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    QMenuBar* menubar = this->menuBar();
    setMenuBar(menubar);

    // Qt\Examples\Qt-6.3.1\widgets\mainwindows\mdi\images -> Working directory   image copy
    QAction *newAct = makeAction("new.png", tr("&New"), QKeySequence::New, \
                                 tr("make new file"), this, SLOT(newFile( )));

    QAction *quitAct = makeAction("quit.png", tr("&Quit"), tr("Ctrl+Q"), \
                                  tr("Quit this program"), []{ qApp->quit(); });

    QAction* openAct = makeAction("open.png",tr("&Open"), tr("Ctrl+O"),\
                                  tr("open file"), this,SLOT(openFile()));

    QAction* saveAct = makeAction("save.png",tr("&Save"),tr("Ctrl+S"),\
                                  tr("Save this program"), this,SLOT(saveFile()));

    QAction* saveasAct = makeAction("saveas.png",tr("&Saveas"),QKeySequence::SaveAs,\
                                    tr("Save as this program"), this,SLOT(saveasFile()));

    QAction* printAct = makeAction("print.png",tr("&Print"),QKeySequence::Print,\
                                   tr("Print this  program"), this,SLOT(printFile()));

    QMenu* fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveasAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);
    fileMenu->addSeparator();

    QToolBar* fileToolBar = addToolBar("&File");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar->addAction(newAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);

    QAction* undoAct = makeAction("undo.png",tr("&Undo"),tr("Ctrl+Z"),\
                                  tr("Undo this code"), textedit, SLOT(undo()));

    QAction* redoAct = makeAction("redo.png",tr("&Redo"),tr("Ctrl+Y"),\
                                  tr("Redo this code"), textedit,SLOT(redo()));

    QAction* copyAct = makeAction("copy.png",tr("&Copy"),tr("Ctrl+Shift+C"),\
                                  tr("Copy this code"), textedit,SLOT(copy()));

    QAction* cutAct = makeAction("cut.png",tr("&Cut"),tr("Ctrl+Shift+X"),\
                                 tr("Cut this code"), textedit,SLOT(cut()));

    QAction* pasteAct = makeAction("paste.png",tr("&Paste"),tr("Ctrl+Shift+V"),\
                                   tr("Save as this program"), textedit,SLOT(paste()));

    QAction* zoominAct = makeAction("zoomin.png",tr("&Zomm&In"),tr("Ctrl+Shift+O"),\
                                    tr("Zoomin this program"), textedit,SLOT(zoomIn()));

    QAction* zoomnoutAct = makeAction("zoomout.png",tr("Zoom&Out"),tr("Ctrl+Shift+I"),\
                                      tr("Zoomout this  program"), textedit,SLOT(zoomOut()));
    //action->setShortcut(QKeySequence(Qt::CTRL+Qt::Key_Up));

    QMenu* editMenu = menubar->addMenu("&Edit");
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);
    editMenu->addSeparator();
    editMenu->addAction(cutAct);
    editMenu->addAction(copyAct);
    editMenu->addAction(pasteAct);
    editMenu->addSeparator();
    editMenu->addAction(zoominAct);
    editMenu->addAction(zoomnoutAct);

    QMenu* windowMenu = menubar->addMenu("&Window");
    windowMenu->addAction(fileToolBar->toggleViewAction());

    QFontComboBox* fontComboBox = new QFontComboBox(this);
    connect(fontComboBox,SIGNAL(currentFontChanged(QFont)),\
            textedit,SLOT(setCurrentFont(QFont)));

    QDoubleSpinBox* sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox,SIGNAL(valueChanged(double)),textedit,SLOT(setFontPointSize(qreal)));

    addToolBarBreak();      // next toolbar is bottom line

    QToolBar* formatToolbar = addToolBar("&Format");
    formatToolbar->addSeparator();
    formatToolbar->addWidget(fontComboBox);
    formatToolbar->addWidget(sizeSpinBox);

    QStatusBar* statusbar = statusBar();
    QLabel* statusLabel = new QLabel("Qt Editor",statusbar);
    statusLabel->setObjectName("StatusLabel");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started",1500);
    //connect(aboutQtAct,SIGNAL(triggered()),qApp,SLOT(aboutQT()));
}

QtEditor::~QtEditor()
{
//    QAction *newAct = makeAction("new.png", tr("&New"), QKeySequence::New, \
//                                 tr("make new file"), this, SLOT(newFile( )));

//    QAction *quitAct = makeAction("quit.png", tr("&Quit"), tr("Ctrl+Q"), \
//                                  tr("Quit this program"), []{ qApp->quit(); });
}


template <typename T>
QAction *QtEditor::makeAction(QString icon, QString text, \
                              T shortCut, QString toolTip, \
                              QObject* recv, const char* slot)
{
    QAction *act = new QAction(text, this);
    if(icon.length( ))
        act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered( )), recv, slot);
    return act;
}

template <>
QAction *QtEditor::makeAction(QString icon, QString text, \
                              const char* shortCut, QString toolTip, \
                              QObject* recv, const char* slot)
{
    QAction *act = new QAction(text, this);
    if(icon.length( ))
        act->setIcon(QIcon(icon));
    act->setShortcut(QString(shortCut));
    act->setStatusTip(toolTip);
    connect(act, SIGNAL(triggered( )), recv, slot);
    return act;
}

template <typename T, typename Functor>
QAction* QtEditor::makeAction(QString icon, QString text, T shortCut,
                              QString toolTip, Functor lambda)
{
    QAction *act = new QAction(text, this);
    if(icon.length( ))
         act->setIcon(QIcon(icon));
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    act->setToolTip(toolTip);
    connect(act, &QAction::triggered, this, lambda);
    return act;
}

void QtEditor::newFile(){
    qDebug("Make New File");
}

void QtEditor::openFile(){
    qDebug("open file");
}

void QtEditor::saveFile(){
    qDebug("Save this program");
}

void QtEditor::saveasFile(){
    qDebug("Save as this program");
}

void QtEditor::printFile(){
    qDebug("Print this program");
}
#endif

#if 0
// test
#include<QTextEdit>
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QApplication>
#include<QToolBar>
#include<QFontComboBox>
#include<QDoubleSpinBox>
#include<QLabel>
#include<QStatusBar>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    textedit = new QTextEdit(this);
    setCentralWidget(textedit);

    QMenuBar* menubar = this->menuBar();
    setMenuBar(menubar);

    // Qt\Examples\Qt-6.3.1\widgets\mainwindows\mdi\images -> Working directory   image copy
    QAction* newAct = makeAction("new.png","&New","Ctrl+N",\
                                 "make new file", this, SLOT(newFile()));

    QAction* quitAct = makeAction("quit.png","&Quit","Ctrl+Q",\
                                  "Quit this program", qApp,SLOT(quit()));

    QAction* openAct = makeAction("open.png","&Open","Ctrl+O",\
                                  "open file", this,SLOT(openFile()));

    QAction* saveAct = makeAction("save.png","&Save","Ctrl+S",\
                                  "Save this program", this,SLOT(saveFile()));

    QAction* saveasAct = makeAction("saveas.png","&Saveas","Ctrl+Shift+A",\
                                    "Save as this program", this,SLOT(saveasFile()));

    QAction* printAct = makeAction("print.png","&Print","Ctrl+P",\
                                   "Print this  program", this,SLOT(printFile()));

    QMenu* fileMenu = menubar->addMenu("&File");
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveasAct);
    fileMenu->addSeparator();
    fileMenu->addAction(printAct);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAct);
    fileMenu->addSeparator();

    QToolBar* fileToolBar = addToolBar("&File");
    fileToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    fileToolBar->addAction(newAct);

    fileToolBar->addSeparator();
    fileToolBar->addAction(quitAct);
/**/
    QAction* alignCenterAct = new QAction("&Center",this);
    connect(alignCenterAct,SIGNAL(triggered(Qt::AlignCenter)),textedit,SLOT(setAlignment(Qt::AlignCenter)));

    QMenu* alignMenu = menubar->addMenu("&Align");
    alignMenu->addAction(alignCenterAct);
/**/

    QMenu* windowMenu = menubar->addMenu("&Window");
    windowMenu->addAction(fileToolBar->toggleViewAction());

    QFontComboBox* fontComboBox = new QFontComboBox(this);
    connect(fontComboBox,SIGNAL(currentFontChanged(QFont)),\
            textedit,SLOT(setCurrentFont(QFont)));
    QDoubleSpinBox* sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox,SIGNAL(valueChanged(double)),textedit,SLOT(setFontPointSize(qreal)));

    addToolBarBreak();      // next toolbar is bottom line

    QToolBar* formatToolbar = addToolBar("&Format");
    formatToolbar->addSeparator();
    formatToolbar->addWidget(fontComboBox);
    formatToolbar->addWidget(sizeSpinBox);

    QStatusBar* statusbar = statusBar();
    QLabel* statusLabel = new QLabel("Qt Editor",statusbar);
    statusLabel->setObjectName("StatusLabel");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started",1500);
    //connect(aboutQtAct,SIGNAL(triggered()),qApp,SLOT(aboutQT()));
}

QtEditor::~QtEditor()
{
}

QAction* QtEditor::makeAction(QString icon, QString name, QString shortCut,\
                              QString toolTip, QObject* recv, const char* slot){
    QAction* act = new QAction(name);
    if(icon.length()){
        act->setIcon(QIcon(icon));
    }
    act->setShortcut(shortCut);
    act->setStatusTip(toolTip);
    connect(act,SIGNAL(triggered()),recv,slot);

    return act;
}

void QtEditor::newFile(){
    qDebug("Make New File");
}

void QtEditor::openFile(){
    qDebug("open file");
}

void QtEditor::saveFile(){
    qDebug("Save this program");
}

void QtEditor::saveasFile(){
    qDebug("Save as this program");
}

void QtEditor::printFile(){
    qDebug("Print this program");
}

void QtEditor::alignText(){
    QAction* action = qobject_cast<QAction*>(sender());
    if(action->text() == "&Center"){
        textedit->setAlignment(Qt::AlignCenter);
    }
}
#endif
