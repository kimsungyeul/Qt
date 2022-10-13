#if 1
// 09/20 QFileDialog class start
// Edit Menu Quiz (mycode)
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
//------- start------//
#include<QFileDialog>
#include<QDebug>
#include<QColorDialog>
#include<QFontDialog>
#include<QPrinter>
#include<QPrintDialog>
#include<QHash>

#include "qteditor.h"

QtEditor::QtEditor(QWidget *parent)
    : QMainWindow(parent)
{
    mdiArea = new QMdiArea(this);
    setCentralWidget(mdiArea);

#if 0
    QTextEdit* textedit = new QTextEdit(this);
    textedit->setFontPointSize(13);
    connect(textedit, SIGNAL(destroyed(QObject*)), SLOT(closeWindow()));
    mdiArea->addSubWindow(textedit);
#else
    //newFile();                    // window메뉴 선언보다 아래잇어야함
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
                                  tr("open file"), this,SLOT(openFile()));

    QAction* saveAct = makeAction(":/images/save.png",tr("&Save"),tr("Ctrl+S"),\
                                  tr("Save this program"), this,SLOT(saveFile()));

    QAction* saveasAct = makeAction(":/images/saveas.png",tr("&Saveas"),QKeySequence::SaveAs,\
                                    tr("Save as this program"), this,SLOT(saveasFile()));

    QAction* printAct = makeAction(":/images/print.png",tr("&Print"),QKeySequence::Print,\
                                   tr("Print this  program"), this,SLOT(printFile()));

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
                                   tr("Save as this program"), this,SLOT(()));

    QAction* zoominAct = makeAction(":/images/zoomin.png",tr("&Zomm&In"),tr("Ctrl++"),\
                                    tr("Zoomin this program"), this,SLOT(zoomIn()));

    QAction* zoomnoutAct = makeAction(":/images/zoomout.png",tr("Zoom&Out"),tr("Ctrl+-"),\
                                      tr("Zoomout this  program"), this,SLOT(zoomOut()));

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
    QAction* colorAct = makeAction("","&Color",tr("Ctrl+Shift+C"),tr("Color Select"),\
                                   this, SLOT(setColor()));
    QAction* fontAct = makeAction("","&Font",tr("Ctrl+Alt+F"),\
                                  tr("Font Select"), this,SLOT(setFont()));

/**************************** Windows -> slot ***********************************/
    QAction *cascadeAct = makeAction("", "&Cascade", tr("Ctrl+7"), tr("Cascade windows"),\
                                     mdiArea, SLOT(cascadeSubWindows()));
    QAction *tileAct = makeAction("", "&Tile", tr("Ctrl+8"), tr("Tile windows"),\
                                  mdiArea, SLOT(tileSubWindows()));
    QAction *prevAct = makeAction("", "&Previous Window", tr("Ctrl+<"), tr("Previous Window"),\
                                  mdiArea, SLOT(activatePreviousSubWindow()));
    QAction *nextAct = makeAction("", "&Next Window", tr("Ctrl+>"), tr("Next Window"),\
                                  mdiArea, SLOT(activateNextSubWindow()));
    //QAction *windowAct = makeAction("","&Hash Window", tr("Ctrl+H"), tr("Hash Window"), mdiArea,SLOT(selectWindow()));

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

    QMenu* formatMenu = menubar->addMenu("&Format");
    QMenu* alignMenu = formatMenu->addMenu(QIcon("align.png"),"&Align");
    alignMenu->addAction(alignLeftAct);
    alignMenu->addAction(alignCenterAct);
    alignMenu->addAction(alignRightAct);
    alignMenu->addAction(alignJustifyAct);

    formatMenu->addAction(colorAct);
    formatMenu->addAction(fontAct);

    QToolBar* alignToolBar = addToolBar("&Align");
    alignToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    alignToolBar->addAction(alignLeftAct);
    alignToolBar->addAction(alignCenterAct);
    alignToolBar->addAction(alignRightAct);
    alignToolBar->addAction(alignJustifyAct);
    alignToolBar->addAction(colorAct);
    alignToolBar->hide();

    addToolBarBreak();      // next toolbar is bottom line

    /* 09/19 */
    //Dock Widget
    QLabel* label = new QLabel("DockWIdget",this);
    QDockWidget* dock = new QDockWidget("Dock Widget", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea,dock);
    dock->setWidget(label);

    QToolBar* windowToolBar = addToolBar("&Window");
    windowToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    windowToolBar->addAction(cascadeAct);
    windowToolBar->addAction(tileAct);
    windowToolBar->addAction(prevAct);
    windowToolBar->addAction(nextAct);
    windowToolBar->addSeparator();
    //windowToolBar->addAction(windowAct);
    windowToolBar->hide();

    //QMenu* windowMenu = menubar->addMenu("&Window");
    windowMenu = menubar->addMenu("&Window");
    newFile();
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
    windowMenu->addAction(newAct);


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

    //const QMetaObject* metaObject = this->metaObject( );          //recv 가 아니라 this면 mdiArea는 참조못함
    const QMetaObject* metaObject = recv->metaObject( );
    // SLOT( ) 함수는 const char* 형으로 변환된걸 QString으로 저장
    QString str(slot);
    // SLOT( ) 매크로를 사용하면 문자 “1”부터 시작하니 QString의 첫번째 글자를 삭제
    str.remove(0, 1);
    // indexOfSlot( ) 함수는 const char*을 사용하니 QString을 변환
    qDebug() << metaObject->indexOfSlot(str.toLatin1( )) << " : " << str;
    if(metaObject->indexOfSlot(str.toLatin1()) != -1){
        connect(act, SIGNAL(triggered()), recv, slot);
    }

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

    //const QMetaObject* metaObject = this->metaObject( );
    const QMetaObject* metaObject = recv->metaObject( );
    // SLOT( ) 함수는 const char* 형으로 변환된걸 QString으로 저장
    QString str(slot);
    // SLOT( ) 매크로를 사용하면 문자 “1”부터 시작하니 QString의 첫번째 글자를 삭제
    str.remove(0, 1);
    // indexOfSlot( ) 함수는 const char*을 사용하니 QString을 변환
    qDebug() << metaObject->indexOfSlot(str.toLatin1( )) << " : " << str;
    if(metaObject->indexOfSlot(str.toLatin1()) != -1){
        connect(act, SIGNAL(triggered()), recv, slot);
    }

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

    QAction* windowAct = new QAction("New File",this);
    windowMenu->addAction(windowAct);
    QTextEdit* textedit = new QTextEdit;
    connect(textedit, SIGNAL(destroyed(QObject*)), windowAct, SLOT(deleteLater()));
    connect(textedit, SIGNAL(destroyed(QObject*)), this, SLOT(closeWindow()));
    connect(textedit, SIGNAL(cursorPositionChanged()), SLOT(setFontWidget()));
    mdiArea->addSubWindow(textedit);
    windowHash[windowAct] = textedit;
    connect(windowAct, SIGNAL(triggered()), SLOT(selectWindow()));
    textedit->show();
}

void QtEditor::openFile(){
    QString filename = QFileDialog::getOpenFileName(this,"Select file to open",\
                                                    ".","Text File(*.txt *.html *.c *.cpp *.h)");
    qDebug() << filename;
}

void QtEditor::saveFile(){
    QString filename = QFileDialog::getSaveFileName(this,"Select file to save",\
                                                    ".", "Text File(*.txt *.html *.c *.cpp *.h)");
    qDebug() << filename;
}

void QtEditor::saveasFile(){
    QString filename = QFileDialog::getSaveFileName(this,"Select file to save as",\
                                                    ".","Text File(*.txt *.html *.c *.cpp *.h)");
    qDebug() << filename;
}

void QtEditor::printFile(){
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);
    QPrintDialog printDialog(&printer,this);
    if(printDialog.exec() == QDialog::Accepted){
        QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
        textedit->print(&printer);
    }
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

void QtEditor::setColor(){
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QColor color = QColorDialog::getColor(textedit->textColor(),this);
    //QColor color = QColorDialog::getColor(Qt::blue,this);
    if(color.isValid()){
        textedit->setTextColor(color);
    }
}

void QtEditor::setFont(){
    bool ok;
    QTextEdit* textedit = (QTextEdit*)mdiArea->currentSubWindow()->widget();
    QFont font = QFontDialog::getFont(&ok,textedit->currentFont(),this);
    if(ok){
        textedit->setCurrentFont(font);
    }
}

void QtEditor::selectWindow(){
    QTextEdit* textedit = (QTextEdit*)windowHash[(QAction*)sender()];
    if(textedit){
        textedit->setFocus();
    }
}

void QtEditor::closeWindow(){
    QTextEdit* textedit = (QTextEdit*)sender();
    windowMenu->removeAction(windowHash.key(textedit));
    delete windowHash.key(textedit);
}

#endif
