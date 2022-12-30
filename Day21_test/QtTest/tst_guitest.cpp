#include <QtTest>
#include <QCoreApplication>
#include <QtWidgets>

// add necessary includes here

class GuiTest : public QWidget
{
    Q_OBJECT

public:
    GuiTest(QWidget *parent = nullptr);
    ~GuiTest();

    QLineEdit* lineEdit;

private slots:
    void test_case1_data( );
    void test_case1();

};

GuiTest::GuiTest(QWidget *parent) : QWidget(parent)
{
    lineEdit = new QLineEdit(this);
}

GuiTest::~GuiTest()
{

}

//void GuiTest::test_case1()
//{
////    QTest::keyClicks(lineEdit, "hi KDE");

//    QTestEventList events;
//    events.addKeyClick('a');
//    events.addKeyClick(Qt::Key_Backspace);
//    events.addDelay(200);

////    QLineEdit *lineEdit = new QLineEdit(myParent);
//    /* ~ 중간 표시 생략  ~ */
//    events.simulate(lineEdit);
//    QCOMPARE(lineEdit->text( ), "");
//    events.simulate(lineEdit);
//    QCOMPARE(lineEdit->text( ), " ");
//}

void GuiTest::test_case1_data( )
{
    QTest::addColumn<QTestEventList>("events");
    QTest::addColumn<QString>("expected");

    QTestEventList list1;
    list1.addKeyClick('a');
    QTest::newRow("char") << list1 << "a";

    QTestEventList list2;
    list2.addKeyClick('a');
    list2.addKeyClick(Qt::Key_Backspace);
    QTest::newRow("there+back-again") << list2 << "";
}

void GuiTest::test_case1()
{
    QFETCH(QTestEventList, events);
    QFETCH(QString, expected);

    events.simulate(lineEdit);

    QCOMPARE(lineEdit->text(), expected);
}

QTEST_MAIN(GuiTest)

#include "tst_guitest.moc"
