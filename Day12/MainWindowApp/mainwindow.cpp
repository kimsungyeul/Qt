#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include<QTextEdit>
void MainWindow::on_actionNew_triggered()
{
    QTextEdit* textedit = new QTextEdit(this);
    ui->mdiArea->addSubWindow(textedit);
    textedit->show();
}

#include<QPrinter>
#include<QPainter>
#include<QPrintDialog>
void MainWindow::mousePressEvent(QMouseEvent*){
//    QPixmap pixmap = grab();
//    pixmap.save("window.png");
    QPrinter printer(QPrinter::HighResolution);
    printer.setFullPage(true);
    QPrintDialog printDialog(&printer, this);
    if(printDialog.exec() == QDialog::Accepted){
        QPixmap pixmap = grab();
        pixmap.save("window.png");
        QPainter paint(&printer);
        paint.drawPixmap(0, 0, pixmap.scaled(1280,720));
    }
}
