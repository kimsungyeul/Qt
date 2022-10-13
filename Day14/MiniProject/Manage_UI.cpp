#include"Manage_UI.h"

using namespace std;

ManageUi::ManageUi() {													// �����ڿ��� ��,��ǰ,������Ʈ�ѿ� �����޸��Ҵ�
	cmu = new ClientManager();
	pmu = new ProductManager();
	smu = new ShopListManager();
}

ManageUi::~ManageUi() {													// �Ҹ��ںҷ����� delete�ǰ� ����
	delete cmu;
	delete pmu;
	delete smu;
}

void ManageUi::printTitle() {											// ù Ÿ��Ʋ ��¿�
	cout << setw(6) << setfill(' ') << "��ǰ ���� ���α׷�" << endl;
}

void ManageUi::printMenu() {											// ù Ÿ��Ʋ ��� ��¿�
	cout << setw(6) << setfill(' ') << "1. �� ���� ����" << endl;
	cout << setw(6) << setfill(' ') << "2. ��ǰ ���� ����" << endl;
	cout << setw(6) << setfill(' ') << "3. ���� ���� ����" << endl;
	cout << setw(6) << setfill(' ') << "9. �� ��" << endl;
	cout << setw(6) << setfill(' ') << "��ȣ�Է�>> ";
}

void ManageUi::processMenu(int menuNo) {								// Ÿ��Ʋ ������ ���μ��� ����
	cout << "�޴���ȣ: " << menuNo << endl << endl;
	if (menuNo == 1) {						// �� ���� ���� 
		ClientManageUi();
	}
	//	addClientUi();
	else if (menuNo == 2) {					// ��ǰ ���� ���� 
		ProductManageUi();
	}
	else if (menuNo == 3)					// ���� ���� ����
		ShopListManageUi();
	else {
		wordJudgeUi(menuNo);
	}
}

void ManageUi::printClientMenu() {										// ���������� �޴�
	cout << setw(6) << setfill(' ') << "1. �� ���" << endl;
	cout << setw(6) << setfill(' ') << "2. �� ��ȸ" << endl;
	cout << setw(6) << setfill(' ') << "3. �� ���" << endl;
	cout << setw(6) << setfill(' ') << "9. ���θ޴�" << endl;
	cout << setw(6) << setfill(' ') << "��ȣ����>> ";
}

void ManageUi::printProductMenu() {										// ��ǰ�������� �޴�
	cout << setw(6) << setfill(' ') << "1. ��ǰ ���" << endl;
	cout << setw(6) << setfill(' ') << "2. ��ǰ �˻�" << endl;
	cout << setw(6) << setfill(' ') << "3. ��ǰ ���" << endl;
	cout << setw(6) << setfill(' ') << "9. ���θ޴�" << endl;
	cout << setw(6) << setfill(' ') << "��ȣ����>> ";
}

void ManageUi::printShopListMenu() {									// ������������ �޴�
	cout << setw(6) << setfill(' ') << "1. ���� ��� ���" << endl;
	cout << setw(6) << setfill(' ') << "2. ���� ��� �˻�" << endl;
	cout << setw(6) << setfill(' ') << "3. ���� ��ü ���" << endl;
	cout << setw(6) << setfill(' ') << "9. ���θ޴�" << endl;
	cout << setw(6) << setfill(' ') << "��ȣ����>> ";
}

void ManageUi::processClientMenu(int menuNo) {							// ���޴� Ui
	if (menuNo == 1) {
		cmu->inputClient();												// �����
	}
	else if (menuNo == 2)
		cmu->reference();												// ���˻�
	else if (menuNo == 3) {
		cmu->displayInfoAll();											// ���Ե� ��ü�����
	}
	else
		wordJudgeUi(menuNo);
}

void ManageUi::processProductMenu(int menuNo) {							// ��ǰ�޴� Ui
	if (menuNo == 1) {
		pmu->inputProduct();											// ��ǰ���
	}
	else if (menuNo == 2) {
		pmu->referenceP();												// ��ǰ�˻�
	}
	else if (menuNo == 3) {
		pmu->displayPinfoAll();											// ��ϵ� ��ü��ǰ���
	}
	else
		wordJudgeUi(menuNo);
}

void ManageUi::processShopListMenu(int menuNo) {						// ���θ޴� Ui
	if (menuNo == 1) {
		cout << endl;
		find_Shop_Record_Client_Ui();									// ���ΰ� ��� Ui
	}
	else if (menuNo == 2) {	
		cout << endl;
		find_Shop_Record_Research_Ui();									// ���ΰ˻�
	}
	else if (menuNo == 3) {												// ��ϵ� ��ü���θ��
		smu->displaySinfoAll();
	}
	else
		wordJudgeUi(menuNo);
}

void ManageUi::find_Shop_Record_Client_Ui() {							// ���� ����ϰ˻� Ui
RESEL:
	cout << "**���˻�**" << endl;
	cout << "1. ��ID�˻�" << endl;
	cout << "2. ���̸��˻�" << endl;
	cout << "9. �����޴�" << endl;
	
	int menuNo;															// �޴����ú���
	vector<int> vec;													// ��ID �� �̐i
	int totprice=0;														// ������ �Һ��� ��ü���� ����� ����
	while (1) {
		try {
			cout << "��ȣ����>> ";
			cin >> menuNo;
			if (menuNo != 1 && menuNo != 2 && menuNo != 9) {
				throw menuNo;
			}
			if (menuNo == 1) {									
				vec = findClientByCode();								// ���̸��� ID�� ã������ �Լ�
				if (vec.empty() == 1) {
					goto RESEL;
				}
				totprice = smu->inputShopList(vec);
				pmu->updateProductStock(vec);							// ���� ������ ���Կ� ���� ��� Update
				cmu->updateClientTotalprice(vec, totprice);				// ���� ���Կ� ����� �� �ݾ� ���� Update
				vec.clear();
				goto RESEL;
			}
			else if (menuNo == 2) {
				vec = findClientByName();								// ���̸��� �̸����� ã������ �Լ�
				if (vec.empty() == 1) {
					goto RESEL;
				}
				totprice = smu->inputShopList(vec);
				pmu->updateProductStock(vec);							// ���� ������ ���Կ� ���� ��� Update
				cmu->updateClientTotalprice(vec, totprice);				// ���� ���Կ� ����� �� �ݾ� ���� Update
				vec.clear();
				goto RESEL;
			}
			else if (menuNo == 9) {
				return;
			}
		}
		catch (int expn) {
			wordJudgeUi(expn);											// ����ó��
		}
	}
}

void ManageUi::find_Shop_Record_Research_Ui() {							// ���α�� �˻� Ui
SHOPREC:
	cout << "**���� ��� �˻�**" << endl;
	cout << "1. ID �˻�(��,��ǰ,����)" << endl;						
	cout << "2. �̸� �˻�(��,��ǰ)" << endl;							
	cout << "3. �Ѿ� �˻�(��,����)" << endl;							
	cout << "9. ���� �޴�" << endl;

	int menuNo;															// �޴� ���ÿ� ����

	while (1) {
		try {
			cout << "��ȣ����>> ";
			cin >> menuNo;
			if (menuNo != 1 && menuNo != 2 && menuNo !=3 && menuNo != 9) {
				throw menuNo;
			}

			if (menuNo == 1) {
				find_Shop_Record_Id_Ui();								// ID�� Ȱ���� ���κ� �˻�
				goto SHOPREC;
			}
			else if (menuNo == 2) {
				find_Shop_Record_Name_Ui();								// �̸��� Ȱ���� ���κ� �˻�
				goto SHOPREC;
			}
			else if (menuNo == 3) {
				find_Shop_Price_Total_Ui();								// �����Ѿ�(��,����)�˻�
				goto SHOPREC;
			}
			else if (menuNo == 9) {										// ����ȭ��
				return;
			}
		}
		catch (int expn) {												// ����ó��
			wordJudgeUi(expn);
		}
	}
}

void ManageUi::find_Shop_Record_Id_Ui() {								// ������ ID�� ���α�� ã������ Ui
SHOPIDREC:
	cout << endl;
	cout << "**���α��(ID) �˻�**" << endl;
	cout << "1. ��ID�˻�" << endl;									// ��ID�˻� -> ��ID�Է� -> ��ID�� �����Ѹ�� ���/���� -> ��
	cout << "2. ��ǰID�˻�" << endl;									// ��ǰID�˻� -> ��ǰID�Է� -> ��ǰID�� ������ ��� ���/���� -> ��
	cout << "3. ����ID�˻�" << endl;									// ����ID�˻� -> ����ID�Է� -> ����ID ���/��� (����) -> ��
	cout << "4. ID ��ü���" << endl;									// ���α���ִ� ��,��ǰ,����ID �ߺ������� ��ϼ��ú� ��� ���
	cout << "9. �����޴�" << endl;

	int menuNo,CID_code,PID_code,SID_code,SID_code_res;
	vector<int> vec;

	while (1) {
		try {
			cout << "��ȣ����>> ";
			cin >> menuNo;
			if (menuNo != 1 && menuNo != 2 && menuNo != 3 && menuNo != 4 && menuNo != 9) {
				throw menuNo;
			}
			if (menuNo == 1) {
				cout << endl;
				cout << "**��ID�� �˻�**" << endl;
				while (1) {
					try {
						cout << "�˻��� ID�Է�(9. ����ȭ��)>> ";
						cin >> CID_code;
						if (CID_code == 9) {
							goto SHOPIDREC;
						}
						vec = smu->SCsearch(CID_code);					// ��ID�Է��� ������ ID�� vector�� ����
						if (!cin || vec.empty() == 1) {
							throw CID_code;
						}
						break;
					}
					catch (int& expn) {
						wordJudgeUi(expn);
					}
				}
				smu->displaySMinfo(vec);
				modidelShop_Sel(vec);									// ��ID�ΰ˻��� ���θ���Ʈ ����/����/��˻��� Ui
				vec.clear();		
				goto SHOPIDREC;
			}
			else if (menuNo == 2) {
				cout << endl;
				cout << "**��ǰID�� �˻�**" << endl;
				while (1) {
					try {
						cout << "�˻��� ID�Է�(9. ����ȭ��)>> ";
						cin >> PID_code;
						if (PID_code == 9) {
							goto SHOPIDREC;
						}
						vec = smu->SPsearch(PID_code);					// ��ǰID�Է��� ������ ID�� vector�� ����
						if (!cin || vec.empty() == 1) {
							throw PID_code;
						}
						break;								
					}
					catch (int& expn) {
						wordJudgeUi(expn);
					}
				}
				smu->displaySMinfo(vec);
				modidelShop_Sel(vec);									// ��ǰID�ΰ˻��� ���θ���Ʈ ����/����/��˻��� Ui
				vec.clear();
				goto SHOPIDREC;
			}
			else if (menuNo == 3) {
				cout << endl;
				cout << "**����ID�� �˻�**" << endl;
				while (1) {
					try {
						cout << "�˻��� ID�Է�(9. ����ȭ��)>> ";
						cin >> SID_code;
						if (SID_code == 9) {
							goto SHOPIDREC;
						}
						SID_code_res = smu->findbySid(SID_code);		// ����ID �Է¹޾� ���翩�� Ȯ��
						if (SID_code_res == 0) {
							throw SID_code;
						}
						break;								
					}
					catch (int& expn) {
						wordJudgeUi(expn);
					}
				}
				smu->displaySinfoSingle(SID_code);						// ����SID �Է��� ��������
				modidelShop_Sel(SID_code);								// ����ID�ΰ˻��� ���θ���Ʈ ����/����/��˻��� Ui
				goto SHOPIDREC;
			}
			else if (menuNo == 4) {									
				find_display_id_A_sel();								// �� ID ������ ���� ���
				goto SHOPIDREC;
			}
			else if (menuNo == 9) {
				return;
			}
		}
		catch (int expn) {
			wordJudgeUi(expn);
		}
	}
}

void ManageUi::find_Shop_Record_Name_Ui() {								// ������ �̸����� ���α�� ã������ Ui
SHOPNAMEREC:
	cout << endl;
	cout << "**���α��(Name) �˻�**" << endl;
	cout << "1. ���̸��˻�" << endl;					
	cout << "2. ��ǰ�̸��˻�" << endl;					
	cout << "9. �����޴�" << endl;

	int menuNo, CID_sel, PID_sel;
	vector<int> vec;													// �˻��� ���� ��(CID) or ��ǰ(PID)�Է¹ޱ�� ����
	vector<int> vec1;													// ���� ����ID ����� ����

	while (1) {
		try {
			cout << "��ȣ����>> ";
			cin >> menuNo;
			if (menuNo != 1 && menuNo != 2 && menuNo != 9) {
				throw menuNo;
			}
			if (menuNo == 1) {
				find_Shop_Client_ByName(vec);								// ���̸����´� Cid���
				if (vec.empty() == 1) {
					goto SHOPNAMEREC;
				}
				CID_sel = cmu->findbyMulCID_Sel(vec);						// ����/���� Pid �� Cid �ϳ� ����
				vec1 = smu->SCsearch(CID_sel);								// ���θ�ϳ� ������ ��ID�� ���θ�ϳ� ��ϵ� ���� ����SID���
				smu->displaySMinfo(vec1);									// ���� SID Ui ���
				if (vec1.empty() == 1) {									// ���� ������ ��Ͽ� ���ٸ� �������� �ٽð˻�
					cout << "�˻������ �����ϴ�." << endl << endl;
				}
				else {
					modidelShop_Sel(vec1);									// ���� SID�� ������ ����/����
				}
				vec.clear();
				vec1.clear();

				goto SHOPNAMEREC;
			}
			else if (menuNo == 2) {
				find_Shop_Product_ByName(vec);								// ��ǰ�̸����´� Pid���
				if (vec.empty() == 1) {										// vec�� ����ٸ� ���α������ goto
					goto SHOPNAMEREC;
				}
				PID_sel = smu->findbyMulSLID_Sel(vec);						// ����/���� Pid�� Pid �ϳ� ����
				vec1 = smu->SPsearch(PID_sel);								// ���θ�ϳ� ������ ��ǰID�� ���θ�ϳ� ��ϵ� ��ǰ�� ����SID���
				smu->displaySMinfo(vec1);									// ���� SID Ui ���
				if (vec1.empty() == 1) {									// ���� ������ ��Ͽ� ���ٸ� �������� �ٽð˻�	
					cout << "�˻������ �����ϴ�." << endl << endl;
				}
				else {
					modidelShop_Sel(vec1);									// ���� SID�� ������ ����/����
				}
				vec.clear();
				goto SHOPNAMEREC;
			}
			else if (menuNo == 9) {
				return;
			}
		}
		catch (int expn) {
			wordJudgeUi(expn);
		}
	}
}

void ManageUi::find_Shop_Price_Total_Ui() {									// ������ ���� or ���� �Ѿ� �˻��� Ui
SHOPNAMEREC:
	cout << endl;
	cout << "**�Ѿ�(TotalPrice) �˻�**" << endl;
	cout << "1. ���� �Ѿ� �˻�" << endl;					
	cout << "2. �����Ѿ� �˻�" << endl;						
	cout << "9. �����޴�" << endl;

	int menuNo;																// �޴� ���ÿ� ����
	int cid_check;															// �� ���ÿ� ����
	int totprice;															// ��ü�ݾ���¿� ����

	while (1) {
		try {
			cout << "��ȣ����>> ";
			cin >> menuNo;
			if (menuNo != 1 && menuNo != 2 && menuNo != 9) {
				throw menuNo;
			}
			if (menuNo == 1) {
				cid_check = find_Shop_Price_Client();						// ���̸����´� Cid���
				if (cid_check == 0) {
					goto SHOPNAMEREC;
				}
				totprice = cmu->PriceSearch(cid_check);						// ����/���� Pid �� Cid �ϳ� ����
				displayPrice_Client(cid_check, totprice);
				goto SHOPNAMEREC;
			}
			else if (menuNo == 2) {
				displayPrice_Client_All(cmu->PriceClient_All());
				goto SHOPNAMEREC;
			}
			else if (menuNo == 9) {
				return;
			}
		}
		catch (int expn) {
			wordJudgeUi(expn);
		}
	}
}

void ManageUi::find_Shop_Client_ByName(vector<int>& vec) {					// ���α�� -> �̸����ΰ˻� -> ���̸����ΰ˻� Ui
	string name;

	cout << "**�̸��˻�**" << endl;
	while (1) {
		try {
			cout << "�˻��� ���̸��Է�(9. ����ȭ��) >> ";
			cin >> name;
			if (name == "9") {
				break;
			}
			cmu->findbyMulName(vec,name);									// �ߺ��̸����´� Cid����, �̸��Է�
			if (!cin || vec.empty() == 1) {									// �Է��̸��� ���ٸ� �̵���̸� ����� �ٽð˻�
				throw name;
			}								
			return;
		}
		catch (string& expn) {
			wordJudgeUi(expn);
		}
	}
}

void ManageUi::find_Shop_Product_ByName(vector<int>& vec) {				// ���α�� -> �̸����ΰ˻� -> ��ǰ�̸����ΰ˻� Ui
	string name;

	cout << "**�̸��˻�**" << endl;
	while (1) {
		try {
			cout << "�˻��� ��ǰ�̸��Է�(9. ����ȭ��) >> ";
			cin >> name;
			if (name == "9") {
				break;
			}
			pmu->findbyMulPname(vec, name);								// �ߺ��̸����´� Pid����, �̸��Է�
			if (!cin || vec.empty() == 1) {								// �Է��̸��� ���ٸ� �̵���̸� ����� �ٽð˻�
				throw name;
			}								
			return;
		}
		catch (string& expn) {
			wordJudgeUi(expn);
		}
	}
}

int ManageUi::find_Shop_Price_Client() {								// ������ ������ �Һ��� �ݾ� ��¿� Ui
	int CID_price_sel,CID_check;													
	cout << endl;
	cout << "**�� �Ѿ� �˻�**" << endl;
	while (1) {
		try {
PRICESEL:
			cout << "�˻��� ID�Է�(1.����� / 9.����ȭ��)>> ";
			cin >> CID_price_sel;
			if (CID_price_sel == 9) {
				return 0;
			}
			else if (CID_price_sel == 1) {
				cout << "**��� �� ID���**" << endl;
				cmu->displayInfoAll_ID();								// ������ ������ ID�� ��� ������ ( �ߺ����� �� )
				goto PRICESEL;
			}
			CID_check = cmu->findbyId(CID_price_sel);					// �˻��� �� ID�Է��� ���翩�� Ȯ��
			if (!cin || CID_check == 0) {
				throw CID_check;
			}
			return CID_check;								
		}
		catch (int& expn) {
			wordJudgeUi(expn);
		}
	}
}

vector<int> ManageUi::findClientByCode() {								// ���̸��� ID�� ã������ �Լ�
	int flag = true;
	int code;
	int ID_check;					// ID Ȯ�ο� ����
	vector<int> vecbyid;			// ���ε��->���˻��� ��ǰ�˻�����µǴ� ������ �����ϱ����� vector
	cout << endl;
	cout << "**�ڵ�˻�**" << endl;
	while (flag) {
		try {
CODESEL:
			cout << "�˻��� ID�Է�(1.ID��� / 9.����ȭ��)>> ";
			cin >> code;
			if (code == 9) {
				flag = false;
				return vecbyid;
			}
			else if (code == 1) {
				cmu->displayInfoAll_ID();
				goto CODESEL;
			}
			ID_check = cmu->findbyId(code);
			if (ID_check == 0) {
				throw code;                                                                                                                                                                                                                                                                                                                                   
			}
			return selectProductList(ID_check);								// ���ε�� 1.���˻� �� 2�ܰ�(��ǰ����)			
		}
		catch (int& expn) {
			wordJudgeUi(expn);
		}
	}
}

vector<int> ManageUi::findClientByName() {									// ���α�ϰ˻� -> ���̸����� �˻� Ui
	vector<int> vecbyname,vecsel;
	string name;
	int IDsel_byname;
	int flag = true;
	cout << endl;
	cout << "**���̸��˻�**" << endl;
	while (flag) {
		try {
			cout << "�˻��� �̸��Է�(9. ����ȭ��)>> ";
			cin >> name;
			if (name == "9") {
				flag = false;
				return vecbyname;
			}
			cmu->findbyMulName(vecbyname,name);								// �̸��� �Է¹޾� �������� �ߺ�CID�� ����ϱ� �����Լ�
			if (vecbyname.size() == 0) {
				throw name;
			}
			IDsel_byname = cmu->findbyMulCID_Sel(vecbyname);				// �������� CID�� ���ϴ� ID �������� �Լ�
			vecsel = selectProductList(IDsel_byname);
			return vecsel;
		}
		catch (string expn) {
			wordJudgeUi(expn);
		}
	}
}

vector<int> ManageUi::selectProductList(int id) {					// ���ε�� 1.���˻� �� 2�ܰ�(��ǰ����)
	vector<int> vec,vec1;											// ��ǰ����Ʈ ����� 
	string name;
	int select_pid;
	int PID_check;
	cout << endl;
	cout << "**��ǰ�˻�**" << endl;
	while (1) {
		try {
first:
			cout << "�˻��� ��ǰ�Է�(1.��� / 2.�����޴�)>> ";
			cin >> name;
			if (name == "1") {
				pmu->displayPinfoAll();
				name.clear();
				goto first;
			}
			else if (name == "2") {
				vec.clear();
				return vec;
			}

			pmu->findbyMulPname(vec,name);							// �̸��� �Է¹޾� �������� �ߺ�PID�� ����ϱ� �����Լ�
			if (vec.empty()) {
				throw name;
			}

			while (1) {								
				try {
					cout << "��ǰID �Է�>> ";
					cin >> select_pid;
					PID_check = pmu->findbyPid(select_pid);				// Pid�� �����ϴ��� Ȯ�ο� �Լ�
					if (!cin || PID_check == 0) {
						throw PID_check;
					}
					vec1.emplace_back(id);								// vec1[0] = cid, vec1[1] = pid, vec1[2] = stock, vec1[3] = price
					vec1.emplace_back(PID_check);
					vec1.emplace_back(pmu->findStockbyPid(PID_check));
					vec1.emplace_back(pmu->findPricebyPid(PID_check));
					return vec1;
				}
				catch (int expn) {
					wordJudgeUi(expn);
				}
			}
		}
		catch (string expn) {
			wordJudgeUi(expn);
		}
	}
}

void ManageUi::ClientManageUi() {								// ù������ ���������� Ui
	while (true) {
		try {
			printClientMenu();
			int menuNo;
			cin >> menuNo;
			if (menuNo == 9) {
				cout << endl;
				break;
			}
			if (menuNo != 1 && menuNo != 2 && menuNo != 3) {
				throw menuNo;
			}
			processClientMenu(menuNo);
		}
		catch (int expn) {
			wordJudgeUi(expn);
		}
	}
}

void ManageUi::ProductManageUi() {								// ù������ ��ǰ�������� Ui
	while (true) {
		try {
			printProductMenu();
			int menuNo;
			cin >> menuNo;
			if (menuNo == 9) {
				cout << endl;
				break;
			}
			if (menuNo != 1 && menuNo != 2 && menuNo != 3) {
				throw menuNo;
			}
			processProductMenu(menuNo);
		}
		catch (int expn) {
			wordJudgeUi(expn);
		}
	}
}

void ManageUi::ShopListManageUi() {								// ù������ ������������ Ui
	while (true) {
		try {
			printShopListMenu();
			int menuNo;
			cin >> menuNo;
			if (menuNo == 9) {
				cout << endl;
				break;
			}
			if (menuNo != 1 && menuNo != 2 && menuNo != 3) {
				throw menuNo;
			}
			processShopListMenu(menuNo);
		}
		catch (int expn) {
			wordJudgeUi(expn);
		}
	}
}

void ManageUi::find_display_id_A_sel() {						// ���κ� �� ID ���
	cout << endl;
	cout << "**ID ������ �˻�**" << endl;
	cout << "1. ���ΰ�ID���" << endl;
	cout << "2. ������ǰID���" << endl;
	cout << "3. ����ID���" << endl;
	cout << "9. ���� ȭ��" << endl;
	int ID_sel;
	while (1) {
		try {
			cout << "�˻��� ��ǰID�Է�>> ";
			cin >> ID_sel;
			if (ID_sel != 1 && ID_sel != 2 && ID_sel != 3 && ID_sel != 9) {
				throw ID_sel;
			}
			if (ID_sel == 9) {
				return;
			}
			smu->displayIDinforA(ID_sel);
			return;
		}
		catch (int expn) {
			wordJudgeUi(expn);
		}
	}
}

void ManageUi::modidelShop_Sel(int key) {						// ���� sid key�޾� �������� Ȯ��
	int modidel_Sel;
	try {
		cout << "���� : 1 / ���� : 2 / ����ȭ�� : 3 :";
		cin >> modidel_Sel;
		if (modidel_Sel != 1 && modidel_Sel != 2 && modidel_Sel != 3) {
			throw modidel_Sel;
		}
		if (modidel_Sel == 1) {
			smu->modifyShopList(key);
		}
		else if (modidel_Sel == 2) {
			smu->deleteShopList(key);
		}
		else if (modidel_Sel == 3) {
			return;
		}
	}
	catch(int expn) {
		wordJudgeUi(expn);
	}
}

void ManageUi::modidelShop_Sel(vector<int>& vec) {						// ������ sid�޾� ����/���� ����
	int modidel_Sel,Single_Sid_sel;
	while (1) {
		try {
			cout << "���� : 1 / ���� : 2 / ����ȭ�� : 3 :";
			cin >> modidel_Sel;
			if (modidel_Sel != 1 && modidel_Sel != 2 && modidel_Sel != 3) {
				throw modidel_Sel;
			}
			if (modidel_Sel == 3) {
				return;
			}
			Single_Sid_sel = smu->findbyMulSLID_Sel(vec);				// �Է¹��� sid���͸� ��ȣ(1,2,3,4...)�� �����Ҽ��ְ���
			
			if (modidel_Sel == 1) {
				smu->modifyShopList(Single_Sid_sel);
			}
			else if (modidel_Sel == 2) {
				smu->deleteShopList(Single_Sid_sel);
			}
		}
		catch (int expn) {
			wordJudgeUi(expn);
		}
	}
}

void ManageUi::displayPrice_Client(int cid,int totprice) {				// ��ID,�ѱ��űݾ��� �޾� ��¿� Ui
	cout << endl << "**���� ����� �ݾ�**" << endl;
	cout << "�� ID : " << cid << endl;
	cout << "�� ���űݾ� : " << totprice << " ��" << endl;
}

void ManageUi::displayPrice_Client_All(float totprice_all) {			// ���峻�� �� ���� ���� Ui
	cout << endl << "**���� �Ѿ� (����)**" << endl;
	totprice_all /= 10000;
	cout << totprice_all << " (��)��" << endl << endl;
}

void ManageUi::wordJudgeUi(int expn) {									// int�� �Է¹����� ��µǴ� ����ó�� �Լ�
	cout << "�̵�� ��ȣ �Դϴ�.: " << expn << endl << endl;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

void ManageUi::wordJudgeUi(string expn) {								// string�� �Է¹����� ��µǴ� ����ó�� �Լ�
	cout << "�̵�� �̸� �Դϴ�.: " << expn << endl << endl;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}
