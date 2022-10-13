#if 0
// QDir 클래스
#include <QDir>
#include <QListWidget>
#include <QLineEdit>
#include <QFileInfo>
#include <QPushButton>
#include <QVBoxLayout>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    directory = new QDir(".");
    dirListWidget = new QListWidget(this);
    filenameLineEdit = new QLineEdit(this);

    QPushButton* makeDir = new QPushButton("Make Directory",this);
    QPushButton* removeDir = new QPushButton("Remove Directory",this);
    QPushButton* renameDir = new QPushButton("Rename Directory",this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(dirListWidget);
    layout->addWidget(filenameLineEdit);
    layout->addWidget(makeDir);
    layout->addWidget(removeDir);
    layout->addWidget(renameDir);

    connect(dirListWidget,SIGNAL(itemClicked(QListWidgetItem*)),\
            SLOT(selectItem(QListWidgetItem*)));
    connect(dirListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),\
            SLOT(changeDir()));
    connect(makeDir,SIGNAL(clicked()),SLOT(makeDir()));
    connect(removeDir,SIGNAL(clicked()),SLOT(removeDir()));
    connect(renameDir,SIGNAL(clicked()),SLOT(renameDir()));

    refreshDir();
}

Widget::~Widget()
{
}

void Widget::refreshDir(){
    dirListWidget->clear();
    for(int index=0; index < directory->count(); index++){
        dirListWidget->addItem(directory->entryList().at(index));
    }
}

void Widget::selectItem(QListWidgetItem* item){
    filenameLineEdit->setText(item->text());
}

void Widget::changeDir(){
    QString file = directory->absoluteFilePath(dirListWidget->currentItem()->text());
    QFileInfo checkDir(file);
    if(checkDir.isDir()){
        directory->cd(file);
        refreshDir();
    }
}

void Widget::makeDir(){
    if(filenameLineEdit->text().length()){
        directory->mkdir(filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}

void Widget::removeDir(){
    if(filenameLineEdit->text().length() && dirListWidget->currentItem() != NULL){
        directory->rmdir(filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}

void Widget::renameDir(){
    if(filenameLineEdit->text().length() && dirListWidget->currentItem() != NULL){
        directory->rename(dirListWidget->currentItem()->text(),\
                          filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}
#endif

#if 0
// changeDir에 openFile 추가(파일의 읽기)
#include <QDir>
#include <QListWidget>
#include <QLineEdit>
#include <QFileInfo>
#include <QPushButton>
#include <QVBoxLayout>
/* add */
#include <QFile>
#include <QTextEdit>
#include <QMessageBox>
#include <QAction>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    directory = new QDir(".");
    dirListWidget = new QListWidget(this);
    filenameLineEdit = new QLineEdit(this);

    QPushButton* makeDir = new QPushButton("Make Directory",this);
    QPushButton* removeDir = new QPushButton("Remove Directory",this);
    QPushButton* renameDir = new QPushButton("Rename Directory",this);
    QPushButton* copyFile = new QPushButton("Copy File",this);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(dirListWidget);
    layout->addWidget(filenameLineEdit);
    layout->addWidget(makeDir);
    layout->addWidget(removeDir);
    layout->addWidget(renameDir);
    layout->addWidget(copyFile);

    connect(dirListWidget,SIGNAL(itemClicked(QListWidgetItem*)),\
            SLOT(selectItem(QListWidgetItem*)));
    connect(dirListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),\
            SLOT(changeDir()));
    connect(makeDir,SIGNAL(clicked()),SLOT(makeDir()));
    connect(removeDir,SIGNAL(clicked()),SLOT(removeDir()));
    connect(renameDir,SIGNAL(clicked()),SLOT(renameDir()));
    connect(copyFile,SIGNAL(clicked()),SLOT(copyFile()));

    refreshDir();
}

Widget::~Widget()
{
}

void Widget::refreshDir(){
    dirListWidget->clear();
    for(unsigned int index=0; index < directory->count(); index++){
        dirListWidget->addItem(directory->entryList().at(index));
    }
}

void Widget::selectItem(QListWidgetItem* item){
    filenameLineEdit->setText(item->text());
}

void Widget::changeDir(){
    QString filename = directory->absoluteFilePath(dirListWidget->currentItem()->text());
    QFileInfo checkDir(filename);
    if(checkDir.isDir()){
        directory->cd(filename);
        refreshDir();
    }
    else if(checkDir.isFile()){
        QFileInfo fileInfo(filename);
        if(fileInfo.isReadable()){
            QFile file(filename);
            file.open(QIODevice::ReadOnly);
            QByteArray msg = file.readAll();
            file.close();
            QTextEdit* textedit = new QTextEdit(0);
            textedit->setWindowTitle(filename);
            textedit->setPlainText(msg);
            textedit->setReadOnly(true);
            textedit->show();
        }
        else{
            QMessageBox::warning(this, "Error", "Can't Read this file", QMessageBox::Ok);
        }
    }
}

void Widget::makeDir(){
    if(filenameLineEdit->text().length()){
        directory->mkdir(filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}

void Widget::removeDir(){
   if(filenameLineEdit->text().length() && dirListWidget->currentItem() != NULL){
        QString file = directory->absoluteFilePath(dirListWidget->currentItem()->text());
        QFileInfo checkDir(file);
        if(checkDir.isDir()){
            directory->rmdir(file);
        } else if(checkDir.isFile()){
            QFile::remove(file);
        }
    }
    directory->refresh();
    refreshDir();
}

void Widget::renameDir(){
    if(filenameLineEdit->text().length() && dirListWidget->currentItem() != NULL){
        directory->rename(dirListWidget->currentItem()->text(),\
                          filenameLineEdit->text());
        directory->refresh();
        refreshDir();
    }
}

// bool QFile::copy(const std::filesystem::path &newName)
void Widget::copyFile(){
    if(filenameLineEdit->text().length() && dirListWidget->currentItem() != NULL){
         QString filename = directory->absoluteFilePath(dirListWidget->currentItem()->text());
         QFileInfo checkDir(filename);
         if(checkDir.isFile() && filenameLineEdit->text().length()){
            QFile::copy(filename,filenameLineEdit->text());
         }
     }
     refreshDir();
}
#endif

#if 1
// QProcess 클래스(.exe파일실행)예제 , copyFile 추가
#include <QDir>
#include <QListWidget>
#include <QLineEdit>
#include <QFileInfo>
#include <QPushButton>
#include <QVBoxLayout>

#include <QFile>
#include <QMessageBox>
#include <QAction>
/* add */
#include <QProcess>
#include <QTextEdit>

#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    directory = new QDir(".");
    dirListWidget = new QListWidget(this);
    filenameLineEdit = new QLineEdit(this);

    QPushButton* makeDir = new QPushButton("Make Directory",this);
    QPushButton* copyFile = new QPushButton("Copy File",this);
    QPushButton* removeDir = new QPushButton("Remove Directory",this);
    QPushButton* renameDir = new QPushButton("Rename Directory",this);

    outputEdit = new QTextEdit(this);
    outputEdit->setReadOnly(true);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(dirListWidget);
    layout->addWidget(filenameLineEdit);
    layout->addWidget(makeDir);
    layout->addWidget(removeDir);
    layout->addWidget(renameDir);
    layout->addWidget(copyFile);
    layout->addWidget(outputEdit);

    connect(dirListWidget,SIGNAL(itemClicked(QListWidgetItem*)),\
            SLOT(selectItem(QListWidgetItem*)));
    connect(dirListWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),\
            SLOT(changeDir()));
    connect(makeDir,SIGNAL(clicked()),SLOT(makeDir()));
    connect(removeDir,SIGNAL(clicked()),SLOT(removeDir()));
    connect(renameDir,SIGNAL(clicked()),SLOT(renameDir()));
    connect(copyFile,SIGNAL(clicked()),SLOT(copyFile()));

    refreshDir();
}

Widget::~Widget()
{
}

void Widget::refreshDir(){
    dirListWidget->clear();
    directory->refresh();
    for(unsigned int index=0; index < directory->count(); index++){
        dirListWidget->addItem(directory->entryList().at(index));
    }
}

void Widget::selectItem(QListWidgetItem* item){
    filenameLineEdit->setText(item->text());
}

void Widget::changeDir(){                                                                   // directory의 absoluteFilepath는 현재 directory가 보고있는 경로 기준을 절대경로로잡음
    QString filename = directory->absoluteFilePath(dirListWidget->currentItem()->text());   // dirListWidget이 활성화되고 클릭을 해야 currentItem() 및 text()가 활성화된다.
    QFileInfo checkDir(filename);
    if(checkDir.isDir()){
        directory->cd(filename);
        refreshDir();
    }
    else if(checkDir.isExecutable()){
        QProcess cmd;
        QStringList arguments;
        cmd.start(filename, arguments);

        outputEdit->clear();
        if(!cmd.waitForStarted()){
            return;
        }
        QByteArray result = cmd.readAllStandardOutput();
        outputEdit->append(result);
        if(!cmd.waitForFinished()){
            return;
        }
        result = cmd.readAllStandardOutput();
        outputEdit->append(result);
    }
    else if(checkDir.isFile()){
        QFileInfo fileInfo(filename);
        if(fileInfo.isReadable()){
            QFile file(filename);
            file.open(QIODevice::ReadOnly);
            QByteArray msg = file.readAll();
            file.close();

            QTextEdit* textedit = new QTextEdit(0);
            textedit->setWindowTitle(filename);
            textedit->setPlainText(msg);
            textedit->setReadOnly(true);
            textedit->show();
        }
        else{
            QMessageBox::warning(this, "Error", "Can't Read this file", QMessageBox::Ok);
        }
    }
}

void Widget::makeDir(){
    if(filenameLineEdit->text().length()){
        directory->mkdir(filenameLineEdit->text());
        refreshDir();
    }
}

void Widget::removeDir(){
   if(filenameLineEdit->text().length() && dirListWidget->currentItem() != NULL){
        QString file = directory->absoluteFilePath(dirListWidget->currentItem()->text());
        QFileInfo checkDir(file);
        if(checkDir.isDir()){
            directory->rmdir(file);
        } else if(checkDir.isFile()){
            QFile::remove(file);
        }
    }
    refreshDir();
}

void Widget::renameDir(){
    if(filenameLineEdit->text().length() && dirListWidget->currentItem() != NULL){
        directory->rename(dirListWidget->currentItem()->text(),\
                          filenameLineEdit->text());
        refreshDir();
    }
}

// bool QFile::copy(const std::filesystem::path &newName)
void Widget::copyFile(){
    if(filenameLineEdit->text().length() && dirListWidget->currentItem() != NULL){
         QString filename = directory->absoluteFilePath(dirListWidget->currentItem()->text());
         QFileInfo checkDir(filename);
         if(checkDir.isFile() && filenameLineEdit->text().length()){
            QFile::copy(filename,filenameLineEdit->text());
         }
     }
    refreshDir();
}
#endif
