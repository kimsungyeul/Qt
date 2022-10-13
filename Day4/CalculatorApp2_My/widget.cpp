#include "widget.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QButtonGroup>

Widget::Widget(QWidget *parent)
    : QWidget(parent), m_isFirst(true) {
    m_label = new QLabel("0", this);			// 레이블 객체의 생성
    m_label->setAlignment(Qt::AlignRight | Qt::AlignVCenter);	// 계산기는 오른쪽 정렬

    // 버튼에 표시될 문자열
    const char ButtonChar[16][2] = {
        "7", "8", "9", "/",	            // QPushButton 생성자의 첫번째 인자로 문자열만 사용 가능
        "4", "5", "6", "x",
        "1", "2", "3", "-",
        "0", "C", "=", "+"
    };

    gridLayout = new QGridLayout();
    buttonGroup = new QButtonGroup(this);
    connect(buttonGroup,SIGNAL(idClicked(int)),this,SLOT(click(int)));

    for(int y = 0; y < WIDTH; ++y) {		// 4 x 4의 2차원으로 배치
        for(int x = 0; x < WIDTH; ++x) {
            int n = x+y*WIDTH;		 	// 2차원 공간을 1차원으로 변환
            m_buttons.append(new QPushButton(ButtonChar[n], this));
            gridLayout->addWidget(m_buttons.at(n),y,x);
            buttonGroup->addButton(m_buttons.at(n),n);
        }
    }

    vBoxLayout = new QVBoxLayout();
    vBoxLayout->addWidget(m_label);
    vBoxLayout->addLayout(gridLayout);
    setLayout(vBoxLayout);

    setWindowTitle("Calculator");                           // 윈도우의 타이틀바 설정
}

Widget::~Widget( ) {                                        // 생성자에서 할당한 객체들의 정리 작업
    delete m_label;
    Q_FOREACH(auto b, buttonGroup->buttons()) delete b; 	// QButtonGroup 클래스 안의 객체 삭제
    m_buttons.clear( );                                     // QVector 클래스 안의 객체 삭제
}

void Widget::click(int id){
    //QButtonGroup* buttonGroup = dynamic_cast<QButtonGroup*>(sender());
    //QPushButton* button = dynamic_cast<QPushButton*>(buttonGroup->button(id));
    QPushButton* button = dynamic_cast<QPushButton*>(dynamic_cast<QButtonGroup*>(sender())->button(id));
    QString bstr = button->text();

    switch(id){
    case 0: case 1: case 2 : \
    case 4: case 5: case 6:  \
    case 8: case 9: case 10: \
    case 12:
        if(button != nullptr) bstr;                     // 버튼의 문자열
        if(m_label != nullptr) {
            QString lstr = m_label->text( );            // 레이블의 문자열
            m_label->setText((m_isFirst)?bstr:lstr+bstr);
            m_isFirst = false;
        }
        break;
    case 3: case 7: case 11: case 15:
        if(button != nullptr) m_op = button->text( );	// 버튼의 문자열이 연산자
        if(m_label != nullptr) {
            m_num1 = m_label->text( );                  // 현재 레이블의 문자열을 멤버 변수로 설정
            m_isFirst = true;                           // m_label->setText("0");
        }
        break;
    case 13:
        m_label->setText("0");
    case 14:
        qreal result = 0;
        if(m_op == "+")                                 // 덧셈
            result = m_num1.toDouble( ) + m_label->text( ).toDouble( ); // QString을 double로
        else if(m_op == "-")                            // 뺄셈
            result = m_num1.toDouble( ) - m_label->text( ).toDouble( );
        else if(m_op == "x")                            // 곱셈
            result = m_num1.toDouble( ) * m_label->text( ).toDouble( );
        else if(m_op == "/")                            // 나눗셈 : 에러 처리 필요
            result = m_num1.toDouble( ) / m_label->text( ).toDouble( );
        m_label->setText(QString::number(result));	// 숫자를 QString으로 변경
        m_isFirst = true;
        break;
    }
}
