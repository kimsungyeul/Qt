#include <iostream>			
#include <vector>
#include <set>
#include"clientmanager.h"
#include"client.h"
#include"productmanager.h"
#include"product.h"
#include"shoplistmanager.h"
#include"shoplist.h"

using namespace std;

class ManageUi {
public:
	ManageUi();											// �����ڿ��� ��,��ǰ,������Ʈ�ѿ� �޸��Ҵ�
	~ManageUi();										// �Ҹ��ںҷ����� delete�ǰ� ����

	void printTitle();									// ù Ÿ��Ʋ ��¿�
	void printMenu();									// ù Ÿ��Ʋ ��� ��¿�
	void processMenu(int);								// Ÿ��Ʋ ������ ���μ��� ����

	void printClientMenu();								// ���������� �޴�
	void printProductMenu();							// ��ǰ�������� �޴�
	void printShopListMenu();							// ������������ �޴�

	void processClientMenu(int);						// ���޴� Ui
	void processProductMenu(int);						// ��ǰ�޴� Ui
	void processShopListMenu(int);						// ���θ޴� Ui

	void find_Shop_Record_Client_Ui();					// ���� ����ϰ˻� Ui
	void find_Shop_Record_Research_Ui();				// ���α�� �˻� Ui
	void find_Shop_Record_Id_Ui();						// ������ ID�� ���α�� ã������ Ui
	void find_Shop_Record_Name_Ui();					// ������ �̸����� ���α�� ã������ Ui
	void find_Shop_Price_Total_Ui();					// ������ ���� or ���� �Ѿ� �˻��� Ui

	void find_Shop_Client_ByName(vector<int>&);			// ���α�� -> �̸����ΰ˻� -> ���̸����ΰ˻� Ui
	void find_Shop_Product_ByName(vector<int>&);		// ���α�� -> �̸����ΰ˻� -> ��ǰ�̸����ΰ˻� Ui
	int find_Shop_Price_Client();						// ������ ������ �Һ��� �ݾ� ��¿� Ui

	vector<int> findClientByCode();						// ���̸��� ID�� ã������ �Լ�
	vector<int> findClientByName();						// ���α�ϰ˻� -> ���̸����� �˻� Ui
	vector<int> selectProductList(int);					// ���ε�� 1.���˻� �� 2�ܰ�(��ǰ����)
	
	void ClientManageUi();								// ù������ ���������� Ui
	void ProductManageUi();								// ù������ ��ǰ�������� Ui
	void ShopListManageUi();							// ù������ ������������ Ui

	void find_display_id_A_sel();						// ���κ� �� ID ���

	void modidelShop_Sel(int);							// ���� sid key�޾� �������� Ȯ��
	void modidelShop_Sel(vector<int>&);					// ������ sid�޾� ����/���� ����

	void displayPrice_Client(int,int);					// ��ID,�ѱ��űݾ��� �޾� ��¿� Ui
	void displayPrice_Client_All(float);				// ���峻�� �� ���� ���� Ui
	void wordJudgeUi(int);								// int�� �Է¹����� ��µǴ� ����ó�� �Լ�
	void wordJudgeUi(string);							// string�� �Է¹����� ��µǴ� ����ó�� �Լ�

private:
	ClientManager* cmu;									// �� ��Ʈ�ѿ� �����޸� �Ҵ�
	ProductManager* pmu;								// ��ǰ ��Ʈ�ѿ� �����޸� �Ҵ�
	ShopListManager* smu;								// ���� ��Ʈ�ѿ� �����޸� �Ҵ�
};
