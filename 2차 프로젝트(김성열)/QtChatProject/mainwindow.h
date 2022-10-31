#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ClientManagerForm;                    // ClientManagerForm클래스 참조
class ProductManagerForm;                   // ProductManagerForm클래스 참조
class OrderManagerForm;                     // OrderManagerForm클래스 참조
class ChatServer;                           // ChatServer클래스 참조

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);  // MainWindow 생성자
    ~MainWindow();                          // MainWindow 소멸자

private slots:
    void on_actionClient_triggered();       // ClientAction 트리거시 실행되는 슬롯

    void on_actionProduct_triggered();      // ProductAction 트리거시 실행되는 슬롯

    void on_actionOrder_triggered();        // OrderAction 트리거시 실행되는 슬롯

    void on_actionServer_triggered();       // ServerAction 트리거시 실행되는 슬롯

private:
    Ui::MainWindow *ui;                     // MainWindow Ui 멤버변수
    ClientManagerForm *clientForm;          // ClientManagerForm 객체 생성
    ProductManagerForm *productForm;        // ProductManagerForm 객체 생성
    OrderManagerForm *orderForm;            // OrderManagerForm 객체 생성
    ChatServer *chatserverForm;             // ChatServer 객체 생성
};
#endif // MAINWINDOW_H
