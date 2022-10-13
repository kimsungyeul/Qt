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
    ManageUi* ui = new ManageUi;				            // ������ class���� , -> �̿� �Լ�ȣ�� 
    ui->printTitle();										// ���α׷� ����
    while (true)
    {
        ui->printMenu();									// �޴� ���

        int menuNo;                                         // �޴���ȣ�Է�
        cin >> menuNo;
        if (menuNo == 9)
            break;
        ui->processMenu(menuNo);							// ������ ���� process ����
    }
    delete ui;                                              //���α׷������ �޸�����
    return 0;
}