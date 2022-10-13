#include<iostream>
#include<string>
#include<sstream>
#include <vector>
#include <algorithm>
#include <fstream>

#include "Manage_UI.h"
#include "client.h"
#include "product.h"
#include "shoplist.h"

int main(int argc, char** argv) {
    ManageUi* ui = new ManageUi;				            // 동적인 class선언 , -> 이용 함수호출 
    ui->printTitle();										// 프로그램 제목
    while (true)
    {
        ui->printMenu();									// 메뉴 출력

        int menuNo;                                         // 메뉴번호입력
        cin >> menuNo;
        if (menuNo == 9)
            break;
        ui->processMenu(menuNo);							// 선택한 변수 process 실행
    }
    delete ui;                                              //프로그램종료시 메모리해제
    return 0;
}