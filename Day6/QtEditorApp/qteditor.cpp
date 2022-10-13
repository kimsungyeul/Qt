#if 0
// Edit Menu Quiz (Undo complate)
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
#include<QDockWidget>
#include<QMdiArea>
#include<QMdiSubWindow>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

#if 1
    QTextEdit* textedit = new QTextEdit(this);
    mdiArea->addSubWindow(textedit);
#else
    newFile();
#endif

    QMenuBar* menubar = this->menuBar();
    setMenuBar(menubar);

    // Qt\Examples\Qt-6.3.1\widgets\mainwindows\mdi\images -> Working directory   image copy
    QAction *newAct = makeAction(":/images/new.png", tr("&New"), QKeySequence::New, \
                                 tr("make new file"), this, SLOT(newFile()));

    QAction *quitAct = makeAction(":/images/quit.png", tr("&Quit"), tr("Ctrl+Q"), \
                                  tr("Quit this program"), []{ qApp->quit(); });

    QAction* openAct = makeAction(":/images/open.png",tr("&Open"), tr("Ctrl+O"),\
                                  tr("open file"), textedit,SLOT(openFile()));

    QAction* saveAct = makeAction(":/images/save.png",tr("&Save"),tr("Ctrl+S"),\
                                  tr("Save this program"), textedit,SLOT(saveFile()));

    QAction* saveasAct = makeAction(":/images/saveas.png",tr("&Saveas"),QKeySequence::SaveAs,\
                                    tr("Save as this program"), textedit,SLOT(saveasFile()));

    QAction* printAct = makeAction(":/images/print.png",tr("&Print"),QKeySequence::Print,\
                                   tr("Print this  program"), textedit,SLOT(printFile()));

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

    QAction* undoAct = makeAction(":/images/undo.png",tr("&Undo"),tr("Ctrl+Z"),\
                                  tr("Undo this code"), this, SLOT(undo()));

    QAction* redoAct = makeAction(":/images/redo.png",tr("&Redo"),tr("Ctrl+Y"),\
                                  tr("Redo this code"), textedit,SLOT(redo()));

    QAction* copyAct = makeAction(":/images/copy.png",tr("&Copy"),tr("Ctrl+Shift+C"),\
                                  tr("Copy this code"), textedit,SLOT(copy()));

    QAction* cutAct = makeAction(":/images/cut.png",tr("&Cut"),tr("Ctrl+Shift+X"),\
                                 tr("Cut this code"), textedit,SLOT(cut()));

    QAction* pasteAct = makeAction(":/images/paste.png",tr("&Paste"),tr("Ctrl+Shift+V"),\
                                   tr("Save as this program"), textedit,SLOT(paste()));

    QAction* zoominAct = makeAction(":/images/zoomin.png",tr("&Zomm&In"),tr("Ctrl+Shift+O"),\
                                    tr("Zoomin this program"), textedit,SLOT(zoomIn()));

    QAction* zoomnoutAct = makeAction(":/images/zoomout.png",tr("Zoom&Out"),tr("Ctrl+Shift+I"),\
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

    QAction* alignLeftAct = makeAction(":/images/left.png","&Left",tr("Ctrl+Alt+L"),\
                                       tr("Left Alignment"), [=]{ textedit->setAlignment(Qt::AlignLeft); });
    QAction* alignCenterAct = makeAction(":/images/center.png","&Center",tr("Ctrl+Alt+C"),\
                                         tr("Center Alignment"), [=]{ textedit->setAlignment(Qt::AlignCenter); });
    QAction* alignRightAct = makeAction(":/images/right.png","&Right",tr("Ctrl+Alt+R"),\
                                        tr("Left Alignment"), [=]{ textedit->setAlignment(Qt::AlignRight); });
    QAction* alignJustifyAct = makeAction(":/images/justify.png","&Justify",tr("Ctrl+Alt+J"),\
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

    /* 09/19 */
    //Dock Widget Example
    QLabel* label = new QLabel("DockWIdget",this);
    QDockWidget* dock = new QDockWidget("Dock Widget", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea,dock);
    dock->setWidget(label);
    //textedit = new QTextEdit(this);
    windowMenu->addAction(dock->toggleViewAction());
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
//    subWindow = mdiArea->currentSubWindow();
//    QTextEdit* textedit = dynamic_cast<QTextEdit*>(subWindow->widget());

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
    //connect(mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow*)),slot);
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
//void QtEditor::alignText(){
//    QAction* action = qobject_cast<QAction*>(sender());
//    if(action->text() == "&Center"){
//        textedit->setAlignment(Qt::AlignCenter);
//    }
//}

void QtEditor::newFile(){
    qDebug("Make New File");
    QTextEdit* textedit = new QTextEdit;
    mdiArea->addSubWindow(textedit);
    textedit->show();
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

void QtEditor::undo(){
    qDebug("Undo");
    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
    if(subWindow != nullptr){
        QTextEdit* textedit= dynamic_cast<QTextEdit*>(subWindow->widget());
        textedit->undo();
    }
}
#endif

#if 1
// Edit Menu Quiz (complate)
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
#include<QDockWidget>
#include<QMdiArea>
#include<QMdiSubWindow>
#include<QFont>

#include<QMessageBox>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

#if 1
    QTextEdit* textedit = new QTextEdit(this);
    mdiArea->addSubWindow(textedit);
#else
    newFile();
#endif

    QMenuBar* menubar = this->menuBar();
    setMenuBar(menubar);
/**************************** File -> slot ***********************************/
    // Qt\Examples\Qt-6.3.1\widgets\mainwindows\mdi\images -> Working directory   image copy
    QAction *newAct = makeAction(":/images/new.png", tr("&New"), QKeySequence::New, \
                                 tr("make new file"), this, SLOT(newFile()));

    QAction *quitAct = makeAction(":/images/quit.png", tr("&Quit"), tr("Ctrl+Q"), \
                                  tr("Quit this program"), []{ qApp->quit(); });

    QAction* openAct = makeAction(":/images/open.png",tr("&Open"), tr("Ctrl+O"),\
                                  tr("open file"), textedit,SLOT(openFile()));

    QAction* saveAct = makeAction(":/images/save.png",tr("&Save"),tr("Ctrl+S"),\
                                  tr("Save this program"), textedit,SLOT(saveFile()));

    QAction* saveasAct = makeAction(":/images/saveas.png",tr("&Saveas"),QKeySequence::SaveAs,\
                                    tr("Save as this program"), textedit,SLOT(saveasFile()));

    QAction* printAct = makeAction(":/images/print.png",tr("&Print"),QKeySequence::Print,\
                                   tr("Print this  program"), textedit,SLOT(printFile()));

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

/**************************** Edit -> slot ***********************************/
    QAction* undoAct = makeAction(":/images/undo.png",tr("&Undo"),tr("Ctrl+Z"),\
                                  tr("Undo this code"), this, SLOT(undo()));

    QAction* redoAct = makeAction(":/images/redo.png",tr("&Redo"),tr("Ctrl+Y"),\
                                  tr("Redo this code"), this,SLOT(redo()));

    QAction* copyAct = makeAction(":/images/copy.png",tr("&Copy"),tr("Ctrl+Shift+C"),\
                                  tr("Copy this code"), this,SLOT(copy()));

    QAction* cutAct = makeAction(":/images/cut.png",tr("&Cut"),tr("Ctrl+Shift+X"),\
                                 tr("Cut this code"), this,SLOT(cut()));

    QAction* pasteAct = makeAction(":/images/paste.png",tr("&Paste"),tr("Ctrl+Shift+V"),\
                                   tr("Save as this program"), this,SLOT(paste()));

    QAction* zoominAct = makeAction(":/images/zoomin.png",tr("&Zomm&In"),tr("Ctrl++"),\
                                    tr("Zoomin this program"), this,SLOT(zoomIn()));

    QAction* zoomnoutAct = makeAction(":/images/zoomout.png",tr("Zoom&Out"),tr("Ctrl+-"),\
                                      tr("Zoomout this  program"), this,SLOT(zoomOut()));
    actions.append(undoAct);			/* QList에 QAction들을 추가 */
    actions.append(redoAct);
    actions.append(copyAct);
    actions.append(cutAct);
    actions.append(pasteAct);
    actions.append(zoominAct);
    actions.append(zoomnoutAct);

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
/**************************** Format -> slot ***********************************/
    //    QMenu* alignMenu = new QMenu("&Align",this);
    //    menubar->addMenu(alignMenu);

    QAction* alignLeftAct = makeAction(":/images/left.png","&Left",tr("Ctrl+Alt+L"),\
                                       tr("Left Alignment"), this,SLOT(alignText()));
    QAction* alignCenterAct = makeAction(":/images/center.png","&Center",tr("Ctrl+Alt+C"),\
                                         tr("Center Alignment"), this,SLOT(alignText()));
    QAction* alignRightAct = makeAction(":/images/right.png","&Right",tr("Ctrl+Alt+R"),\
                                        tr("Left Alignment"), this,SLOT(alignText()));
    QAction* alignJustifyAct = makeAction(":/images/justify.png","&Justify",tr("Ctrl+Alt+J"),\
                                          tr("Justify Alignment"), this,SLOT(alignText()));

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

/**************************** Windows -> slot ***********************************/
    /* 09/19 */
    //Dock Widget
    QLabel* label = new QLabel("DockWIdget",this);
    QDockWidget* dock = new QDockWidget("Dock Widget", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea,dock);
    dock->setWidget(label);

    QAction *cascadeAct = makeAction("", "&Cascade", tr("Ctrl+7"), tr("Cascade windows"), mdiArea, SLOT(cascadeSubWindows()));
    QAction *tileAct = makeAction("", "&Tile", tr("Ctrl+8"), tr("Tile windows"), mdiArea, SLOT(tileSubWindows()));
    QAction *prevAct = makeAction("", "&Previous Window", tr("Ctrl+<"), tr("Previous Window"), mdiArea, SLOT(activatePreviousSubWindow()));
    QAction *nextAct = makeAction("", "&Next Window", tr("Ctrl+>"), tr("Next Window"), mdiArea, SLOT(activateNextSubWindow()));

    QToolBar* windowToolBar = addToolBar("&Window");
    windowToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    windowToolBar->addAction(cascadeAct);
    windowToolBar->addAction(tileAct);
    windowToolBar->addAction(prevAct);
    windowToolBar->addAction(nextAct);
    windowToolBar->hide();

    QMenu* windowMenu = menubar->addMenu("&Window");
    windowMenu->addAction(fileToolBar->toggleViewAction());
    windowMenu->addAction(editToolBar->toggleViewAction());
    windowMenu->addAction(alignToolBar->toggleViewAction());
    windowMenu->addAction(windowToolBar->toggleViewAction());
    windowMenu->addAction(dock->toggleViewAction());

    windowMenu->addSeparator();
    windowMenu->addAction(cascadeAct);
    windowMenu->addAction(tileAct);
    windowMenu->addAction(prevAct);
    windowMenu->addAction(nextAct);


//    QFontComboBox* fontComboBox = new QFontComboBox(this);
//    connect(fontComboBox,SIGNAL(currentFontChanged(QFont)),\
//            textedit,SLOT(setCurrentFont(QFont)));

//    QDoubleSpinBox* sizeSpinBox = new QDoubleSpinBox(this);
//    connect(sizeSpinBox,SIGNAL(valueChanged(double)),textedit,SLOT(setFontPointSize(qreal)));

    connect(mdiArea,SIGNAL(subWindowActivated(QMdiSubWindow*)),this,SLOT(setCurrentWindow()));
    fontComboBox = new QFontComboBox(this);
    connect(fontComboBox,SIGNAL(currentFontChanged(QFont)),SLOT(setTextFont(QFont)));
    sizeSpinBox = new QDoubleSpinBox(this);
    connect(sizeSpinBox,SIGNAL(valueChanged(double)),SLOT(setTextSize(qreal)));


    addToolBarBreak();      // next toolbar is bottom line

    QToolBar* formatToolbar = addToolBar("&Format");
    formatToolbar->addSeparator();
    formatToolbar->addWidget(fontComboBox);
    formatToolbar->addWidget(sizeSpinBox);

    QStatusBar* statusbar = statusBar();

    QLabel* statusLabel = new QLabel("Qt Editor",statusbar);
    statusLabel->setObjectName("StatusLabel");
    statusbar->addPermanentWidget(statusLabel);
    statusbar->showMessage("started",3000);

/**************************** Help -> slot ***********************************/
    QAction* aboutAct = makeAction("", "&About", tr("Ctrl+Shift+A"), tr("About"), this, SLOT(about()));
    QAction* aboutQtAct = makeAction("", "&AboutQt", tr("Ctrl+Shift+Q"), tr("AboutQt"), qApp, SLOT(aboutQt()));
    QMenu* helpMenu = menubar->addMenu("&Help");
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    connect(mdiArea, SIGNAL(subWindowActivated(QMdiSubWindow*)),
                SLOT(connectWindow(QMdiSubWindow*)));

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
    connect(act, SIGNAL(triggered()), recv, slot);

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
    connect(act, SIGNAL(triggered()), recv, slot);

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
//void QtEditor::alignText(){
//    QAction* action = qobject_cast<QAction*>(sender());
//    if(action->text() == "&Center"){
//        textedit->setAlignment(Qt::AlignCenter);
//    }
//}

void QtEditor::newFile(){
    qDebug("Make New File");
    QTextEdit* textedit = new QTextEdit(mdiArea);
    connect(textedit, SIGNAL(destroyed(QObject*)), SLOT(closeWindow()));
    //textedit->setFontPointSize(13);
    mdiArea->addSubWindow(textedit);
    textedit->show();
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

void QtEditor::undo(){
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->undo();
}

void QtEditor::redo(){
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->redo();
}

void QtEditor::copy(){
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->copy();
}

void QtEditor::cut(){
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->cut();
}

void QtEditor::paste(){
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->paste();
}

void QtEditor::zoomIn(){
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->zoomIn();
}

void QtEditor::zoomOut(){
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->zoomOut();
}

//void QtEditor::undo(){
//    qDebug("Undo");
//    QMdiSubWindow* subWindow = mdiArea->currentSubWindow();
//    if(subWindow != nullptr){
//        QTextEdit* textedit= dynamic_cast<QTextEdit*>(subWindow->widget());
//        textedit->undo();
//    }
//}
void QtEditor::alignText(){
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QAction* action = qobject_cast<QAction*>(sender());
    if(action->text().contains("Left",Qt::CaseInsensitive)){
        textedit->setAlignment(Qt::AlignLeft);
    }
    else if(action->text().contains("Right",Qt::CaseInsensitive)){
        textedit->setAlignment(Qt::AlignRight);
    }
    else if(action->text().contains("Center",Qt::CaseInsensitive)){
        textedit->setAlignment(Qt::AlignHCenter);
    }
    else if(action->text().contains("Justify",Qt::CaseInsensitive)){
        textedit->setAlignment(Qt::AlignJustify);
    }
}


void QtEditor::connectWindow(QMdiSubWindow* window)
{
    if(window == nullptr) {		// 모든 창이 닫혔을 때
        prevTextEdit = nullptr;     // prevTextEdit 변수에 저장한 창이 닫히므로 nullptr로 초기화
    } else {				// 창이 열려 있을 때
        QTextEdit *textEdit = qobject_cast<QTextEdit*>(window->widget( ));
        /* 모든 QAction에 연결된 슬롯 해제 */
        if(prevTextEdit != nullptr) {
            Q_FOREACH(QAction *action, actions) {
                action->disconnect(prevTextEdit);
            }
        }
        prevTextEdit = textEdit;			/* 현재 객체를 다음 처리를 위해 저장 */

        // 슬롯들을 위한 배열
        const char *methods[7] = {
            SLOT(undo( )), SLOT(redo( )), SLOT(copy( )), SLOT(cut( )),
            SLOT(paste( )), SLOT(zoomIn( )), SLOT(zoomOut( ))
        };

        /* QAction에 현재 선택된 객체의 슬롯을 연결 */
        int cnt = 0;
        Q_FOREACH(QAction *action, actions) {
            connect(action, SIGNAL(triggered( )), textEdit, methods[cnt++]);
        }
    }
}


void QtEditor::setTextFont(QFont font){
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    textedit->setCurrentFont(font);
}

void QtEditor::setTextSize(qreal size){
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QFont font = textedit->currentFont();
    font.setPointSizeF(size);
    textedit->setCurrentFont(font);
}

void QtEditor::setFontWidget(){
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QFont font = textedit->currentFont();
    fontComboBox->setCurrentFont(font);
    sizeSpinBox->setValue(font.pointSizeF());
}

void QtEditor::setCurrentWindow(){
    qDebug("setCurrentWindow");
    foreach(QMdiSubWindow* window, mdiArea->subWindowList()){
        disconnect(window->widget());
    }

    QMdiSubWindow* currentWindow = mdiArea->currentSubWindow();
    if(currentWindow){
        QTextEdit* textedit = (QTextEdit*)currentWindow->widget();
        connect(textedit,SIGNAL(cursorPositionChanged()),this,SLOT(setFontWidget()));
    }
}

void QtEditor::about(){
    QMessageBox::information(this,"QMessageBOx::showQuestion()","Question Message",QMessageBox::Yes);
}

#endif
