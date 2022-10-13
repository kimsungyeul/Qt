#if 0
// QLineEdit Widget Example
#include<QApplication>
#include<QLineEdit>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLineEdit* lineEdit = new QLineEdit();
    lineEdit->setEchoMode(QLineEdit::Password);
    lineEdit->setInputMask("099");
    lineEdit->setPlaceholderText("input the number");
    lineEdit->show();

    return a.exec();
}
#endif

#if 0
// QLineEdit Widget Example2
#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget w;

    QLabel label("<font color=green>Hello,World</font>",&w);
    label.setGeometry(10,10,300,30);

    QLineEdit lineEdit1(&w);
    lineEdit1.setEchoMode(QLineEdit::PasswordEchoOnEdit);
    lineEdit1.setGeometry(10,50,300,30);

    QLineEdit lineEdit2(&w);
    lineEdit2.setGeometry(10,90,300,30);

    QObject::connect(&lineEdit1,SIGNAL(textChanged(const QString &)),&label,SLOT(setText(const QString &)));
    QObject::connect(&lineEdit2,SIGNAL(textChanged(const QString &)),&label,SLOT(setText(const QString &)));

    w.show();
    return a.exec();
}

#endif

#if 0
// QCompleter Widget Example
#include<QApplication>
#include<QLineEdit>
#include<QCompleter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QWidget* w = nullptr;

    QLineEdit* lineEdit = new QLineEdit();
    QStringList CompletionList;             // Use the string list
    CompletionList << "Bryan" << "Bart" << "Kelvin" << "Beth" << "Brad" << "Kelly";
    QCompleter* StringCompleter = new QCompleter(CompletionList,lineEdit);
    StringCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    //StringCompleter->setModel(new QDirModel(StringCompleter));
    lineEdit->setCompleter(StringCompleter);
    lineEdit->show();

    return a.exec();
}
#endif

#if 0
// QComboBox Widget Example
// Show you added input data after input->enter
#include<QApplication>
#include<QComboBox>

int main(int argc,char* argv[]){
    QApplication a(argc,argv);

    QComboBox* comboBox = new QComboBox();
    comboBox->addItem("KDE");
    comboBox->addItem("Gnome");
    comboBox->addItem("FVWM");
    comboBox->addItem("CDE");
    comboBox->setEditable(true);
    comboBox->show();

    return a.exec();
}
#endif

#if 0
// QValidator , QRegularExpression , QFormLayout use Example
#include<QApplication>
#include"widget.h"

int main(int argc,char* argv[]){
    QApplication a(argc,argv);
    Widget* w = new Widget();
    w->show();

    return a.exec();
}
#endif

#if 0
// QValidator , QRegularExpression , QFormLayout use Example
#include<QApplication>

#include"widget.h"

int main(int argc,char* argv[]){
    QApplication a(argc,argv);
    Widget* w = new Widget();
    w->show();

    return a.exec();
}
#endif













