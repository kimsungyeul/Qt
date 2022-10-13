#include"Manage_UI.h"

using namespace std;

ManageUi::ManageUi() {													// 생성자에서 고객,상품,쇼핑컨트롤용 동적메모리할당
	cmu = new ClientManager();
	pmu = new ProductManager();
	smu = new ShopListManager();
}

ManageUi::~ManageUi() {													// 소멸자불려질시 delete되게 설정
	delete cmu;
	delete pmu;
	delete smu;
}

void ManageUi::printTitle() {											// 첫 타이틀 출력용
	cout << setw(6) << setfill(' ') << "상품 관리 프로그램" << endl;
}

void ManageUi::printMenu() {											// 첫 타이틀 목록 출력용
	cout << setw(6) << setfill(' ') << "1. 고객 정보 관리" << endl;
	cout << setw(6) << setfill(' ') << "2. 상품 정보 관리" << endl;
	cout << setw(6) << setfill(' ') << "3. 쇼핑 정보 관리" << endl;
	cout << setw(6) << setfill(' ') << "9. 종 료" << endl;
	cout << setw(6) << setfill(' ') << "번호입력>> ";
}

void ManageUi::processMenu(int menuNo) {								// 타이틀 선택후 프로세스 실행
	cout << "메뉴번호: " << menuNo << endl << endl;
	if (menuNo == 1) {						// 고객 정보 관리 
		ClientManageUi();
	}
	//	addClientUi();
	else if (menuNo == 2) {					// 상품 정보 관리 
		ProductManageUi();
	}
	else if (menuNo == 3)					// 쇼핑 정보 관리
		ShopListManageUi();
	else {
		wordJudgeUi(menuNo);
	}
}

void ManageUi::printClientMenu() {										// 고객정보관리 메뉴
	cout << setw(6) << setfill(' ') << "1. 고객 등록" << endl;
	cout << setw(6) << setfill(' ') << "2. 고객 조회" << endl;
	cout << setw(6) << setfill(' ') << "3. 고객 목록" << endl;
	cout << setw(6) << setfill(' ') << "9. 메인메뉴" << endl;
	cout << setw(6) << setfill(' ') << "번호선택>> ";
}

void ManageUi::printProductMenu() {										// 상품정보관리 메뉴
	cout << setw(6) << setfill(' ') << "1. 제품 등록" << endl;
	cout << setw(6) << setfill(' ') << "2. 제품 검색" << endl;
	cout << setw(6) << setfill(' ') << "3. 제품 목록" << endl;
	cout << setw(6) << setfill(' ') << "9. 메인메뉴" << endl;
	cout << setw(6) << setfill(' ') << "번호선택>> ";
}

void ManageUi::printShopListMenu() {									// 쇼핑정보관리 메뉴
	cout << setw(6) << setfill(' ') << "1. 쇼핑 기록 등록" << endl;
	cout << setw(6) << setfill(' ') << "2. 쇼핑 기록 검색" << endl;
	cout << setw(6) << setfill(' ') << "3. 쇼핑 전체 목록" << endl;
	cout << setw(6) << setfill(' ') << "9. 메인메뉴" << endl;
	cout << setw(6) << setfill(' ') << "번호선택>> ";
}

void ManageUi::processClientMenu(int menuNo) {							// 고객메뉴 Ui
	if (menuNo == 1) {
		cmu->inputClient();												// 고객등록
	}
	else if (menuNo == 2)
		cmu->reference();												// 고객검색
	else if (menuNo == 3) {
		cmu->displayInfoAll();											// 가입된 전체고객목록
	}
	else
		wordJudgeUi(menuNo);
}

void ManageUi::processProductMenu(int menuNo) {							// 제품메뉴 Ui
	if (menuNo == 1) {
		pmu->inputProduct();											// 제품등록
	}
	else if (menuNo == 2) {
		pmu->referenceP();												// 제품검색
	}
	else if (menuNo == 3) {
		pmu->displayPinfoAll();											// 등록된 전체제품목록
	}
	else
		wordJudgeUi(menuNo);
}

void ManageUi::processShopListMenu(int menuNo) {						// 쇼핑메뉴 Ui
	if (menuNo == 1) {
		cout << endl;
		find_Shop_Record_Client_Ui();									// 쇼핑고객 등록 Ui
	}
	else if (menuNo == 2) {	
		cout << endl;
		find_Shop_Record_Research_Ui();									// 쇼핑검색
	}
	else if (menuNo == 3) {												// 등록된 전체쇼핑목록
		smu->displaySinfoAll();
	}
	else
		wordJudgeUi(menuNo);
}

void ManageUi::find_Shop_Record_Client_Ui() {							// 쇼핑 고객기록검색 Ui
RESEL:
	cout << "**고객검색**" << endl;
	cout << "1. 고객ID검색" << endl;
	cout << "2. 고객이름검색" << endl;
	cout << "9. 이전메뉴" << endl;
	
	int menuNo;															// 메뉴선택변수
	vector<int> vec;													// 고객ID 및 이릋
	int totprice=0;														// 고객들이 소비한 전체가격 저장용 변수
	while (1) {
		try {
			cout << "번호선택>> ";
			cin >> menuNo;
			if (menuNo != 1 && menuNo != 2 && menuNo != 9) {
				throw menuNo;
			}
			if (menuNo == 1) {									
				vec = findClientByCode();								// 고객이름을 ID로 찾기위한 함수
				if (vec.empty() == 1) {
					goto RESEL;
				}
				totprice = smu->inputShopList(vec);
				pmu->updateProductStock(vec);							// 고객이 구매후 가게에 남은 재고 Update
				cmu->updateClientTotalprice(vec, totprice);				// 고객이 가게에 사용한 총 금액 누적 Update
				vec.clear();
				goto RESEL;
			}
			else if (menuNo == 2) {
				vec = findClientByName();								// 고객이름을 이름으로 찾기위한 함수
				if (vec.empty() == 1) {
					goto RESEL;
				}
				totprice = smu->inputShopList(vec);
				pmu->updateProductStock(vec);							// 고객이 구매후 가게에 남은 재고 Update
				cmu->updateClientTotalprice(vec, totprice);				// 고객이 가게에 사용한 총 금액 누적 Update
				vec.clear();
				goto RESEL;
			}
			else if (menuNo == 9) {
				return;
			}
		}
		catch (int expn) {
			wordJudgeUi(expn);											// 예외처리
		}
	}
}

void ManageUi::find_Shop_Record_Research_Ui() {							// 쇼핑기록 검색 Ui
SHOPREC:
	cout << "**쇼핑 기록 검색**" << endl;
	cout << "1. ID 검색(고객,제품,쇼핑)" << endl;						
	cout << "2. 이름 검색(고객,제품)" << endl;							
	cout << "3. 총액 검색(고객,매장)" << endl;							
	cout << "9. 이전 메뉴" << endl;

	int menuNo;															// 메뉴 선택용 변수

	while (1) {
		try {
			cout << "번호선택>> ";
			cin >> menuNo;
			if (menuNo != 1 && menuNo != 2 && menuNo !=3 && menuNo != 9) {
				throw menuNo;
			}

			if (menuNo == 1) {
				find_Shop_Record_Id_Ui();								// ID를 활용한 쇼핑별 검색
				goto SHOPREC;
			}
			else if (menuNo == 2) {
				find_Shop_Record_Name_Ui();								// 이름을 활용한 쇼핑별 검색
				goto SHOPREC;
			}
			else if (menuNo == 3) {
				find_Shop_Price_Total_Ui();								// 쇼핑총액(고객,매장)검색
				goto SHOPREC;
			}
			else if (menuNo == 9) {										// 이전화면
				return;
			}
		}
		catch (int expn) {												// 예외처리
			wordJudgeUi(expn);
		}
	}
}

void ManageUi::find_Shop_Record_Id_Ui() {								// 종류별 ID로 쇼핑기록 찾기위한 Ui
SHOPIDREC:
	cout << endl;
	cout << "**쇼핑기록(ID) 검색**" << endl;
	cout << "1. 고객ID검색" << endl;									// 고객ID검색 -> 고객ID입력 -> 고객ID로 쇼핑한목록 출력/선택 -> 완
	cout << "2. 제품ID검색" << endl;									// 제품ID검색 -> 제품ID입력 -> 제품ID로 쇼핑한 목록 출력/선택 -> 완
	cout << "3. 쇼핑ID검색" << endl;									// 쇼핑ID검색 -> 쇼핑ID입력 -> 쇼핑ID 출력/출력 (단일) -> 완
	cout << "4. ID 전체목록" << endl;									// 쇼핑기록있는 고객,제품,쇼핑ID 중복제거후 목록선택별 기록 출력
	cout << "9. 이전메뉴" << endl;

	int menuNo,CID_code,PID_code,SID_code,SID_code_res;
	vector<int> vec;

	while (1) {
		try {
			cout << "번호선택>> ";
			cin >> menuNo;
			if (menuNo != 1 && menuNo != 2 && menuNo != 3 && menuNo != 4 && menuNo != 9) {
				throw menuNo;
			}
			if (menuNo == 1) {
				cout << endl;
				cout << "**고객ID로 검색**" << endl;
				while (1) {
					try {
						cout << "검색할 ID입력(9. 이전화면)>> ";
						cin >> CID_code;
						if (CID_code == 9) {
							goto SHOPIDREC;
						}
						vec = smu->SCsearch(CID_code);					// 고객ID입력후 쇼핑한 ID를 vector에 삽입
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
				modidelShop_Sel(vec);									// 고객ID로검색된 쇼핑리스트 수정/삭제/재검색용 Ui
				vec.clear();		
				goto SHOPIDREC;
			}
			else if (menuNo == 2) {
				cout << endl;
				cout << "**제품ID로 검색**" << endl;
				while (1) {
					try {
						cout << "검색할 ID입력(9. 이전화면)>> ";
						cin >> PID_code;
						if (PID_code == 9) {
							goto SHOPIDREC;
						}
						vec = smu->SPsearch(PID_code);					// 제품ID입력후 쇼핑한 ID를 vector에 삽입
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
				modidelShop_Sel(vec);									// 제품ID로검색된 쇼핑리스트 수정/삭제/재검색용 Ui
				vec.clear();
				goto SHOPIDREC;
			}
			else if (menuNo == 3) {
				cout << endl;
				cout << "**쇼핑ID로 검색**" << endl;
				while (1) {
					try {
						cout << "검색할 ID입력(9. 이전화면)>> ";
						cin >> SID_code;
						if (SID_code == 9) {
							goto SHOPIDREC;
						}
						SID_code_res = smu->findbySid(SID_code);		// 쇼핑ID 입력받아 존재여부 확인
						if (SID_code_res == 0) {
							throw SID_code;
						}
						break;								
					}
					catch (int& expn) {
						wordJudgeUi(expn);
					}
				}
				smu->displaySinfoSingle(SID_code);						// 단일SID 입력후 단일정보
				modidelShop_Sel(SID_code);								// 쇼핑ID로검색된 쇼핑리스트 수정/삭제/재검색용 Ui
				goto SHOPIDREC;
			}
			else if (menuNo == 4) {									
				find_display_id_A_sel();								// 고객 ID 종류별 선택 목록
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

void ManageUi::find_Shop_Record_Name_Ui() {								// 종류별 이름으로 쇼핑기록 찾기위한 Ui
SHOPNAMEREC:
	cout << endl;
	cout << "**쇼핑기록(Name) 검색**" << endl;
	cout << "1. 고객이름검색" << endl;					
	cout << "2. 제품이름검색" << endl;					
	cout << "9. 이전메뉴" << endl;

	int menuNo, CID_sel, PID_sel;
	vector<int> vec;													// 검색후 다중 고객(CID) or 제품(PID)입력받기용 벡터
	vector<int> vec1;													// 다중 쇼핑ID 저장용 벡터

	while (1) {
		try {
			cout << "번호선택>> ";
			cin >> menuNo;
			if (menuNo != 1 && menuNo != 2 && menuNo != 9) {
				throw menuNo;
			}
			if (menuNo == 1) {
				find_Shop_Client_ByName(vec);								// 고객이름에맞는 Cid출력
				if (vec.empty() == 1) {
					goto SHOPNAMEREC;
				}
				CID_sel = cmu->findbyMulCID_Sel(vec);						// 다중/단일 Pid 중 Cid 하나 선택
				vec1 = smu->SCsearch(CID_sel);								// 쇼핑목록내 선택한 고객ID로 쇼핑목록내 등록된 고객의 다중SID출력
				smu->displaySMinfo(vec1);									// 다중 SID Ui 출력
				if (vec1.empty() == 1) {									// 만일 쇼핑한 목록에 없다면 결과출력후 다시검색
					cout << "검색결과가 없습니다." << endl << endl;
				}
				else {
					modidelShop_Sel(vec1);									// 다중 SID중 선택후 수정/삭제
				}
				vec.clear();
				vec1.clear();

				goto SHOPNAMEREC;
			}
			else if (menuNo == 2) {
				find_Shop_Product_ByName(vec);								// 제품이름에맞는 Pid출력
				if (vec.empty() == 1) {										// vec가 비엇다면 쇼핑기록으로 goto
					goto SHOPNAMEREC;
				}
				PID_sel = smu->findbyMulSLID_Sel(vec);						// 다중/단일 Pid중 Pid 하나 선택
				vec1 = smu->SPsearch(PID_sel);								// 쇼핑목록내 선택한 제품ID로 쇼핑목록내 등록된 제품의 다중SID출력
				smu->displaySMinfo(vec1);									// 다중 SID Ui 출력
				if (vec1.empty() == 1) {									// 만일 쇼핑한 목록에 없다면 결과출력후 다시검색	
					cout << "검색결과가 없습니다." << endl << endl;
				}
				else {
					modidelShop_Sel(vec1);									// 다중 SID중 선택후 수정/삭제
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

void ManageUi::find_Shop_Price_Total_Ui() {									// 쇼핑후 고객별 or 매장 총액 검색용 Ui
SHOPNAMEREC:
	cout << endl;
	cout << "**총액(TotalPrice) 검색**" << endl;
	cout << "1. 고객별 총액 검색" << endl;					
	cout << "2. 매장총액 검색" << endl;						
	cout << "9. 이전메뉴" << endl;

	int menuNo;																// 메뉴 선택용 변수
	int cid_check;															// 고객 선택용 변수
	int totprice;															// 전체금액출력용 변수

	while (1) {
		try {
			cout << "번호선택>> ";
			cin >> menuNo;
			if (menuNo != 1 && menuNo != 2 && menuNo != 9) {
				throw menuNo;
			}
			if (menuNo == 1) {
				cid_check = find_Shop_Price_Client();						// 고객이름에맞는 Cid출력
				if (cid_check == 0) {
					goto SHOPNAMEREC;
				}
				totprice = cmu->PriceSearch(cid_check);						// 다중/단일 Pid 중 Cid 하나 선택
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

void ManageUi::find_Shop_Client_ByName(vector<int>& vec) {					// 쇼핑기록 -> 이름으로검색 -> 고객이름으로검색 Ui
	string name;

	cout << "**이름검색**" << endl;
	while (1) {
		try {
			cout << "검색할 고객이름입력(9. 이전화면) >> ";
			cin >> name;
			if (name == "9") {
				break;
			}
			cmu->findbyMulName(vec,name);									// 중복이름에맞는 Cid벡터, 이름입력
			if (!cin || vec.empty() == 1) {									// 입력이름이 없다면 미등록이름 출력후 다시검색
				throw name;
			}								
			return;
		}
		catch (string& expn) {
			wordJudgeUi(expn);
		}
	}
}

void ManageUi::find_Shop_Product_ByName(vector<int>& vec) {				// 쇼핑기록 -> 이름으로검색 -> 제품이름으로검색 Ui
	string name;

	cout << "**이름검색**" << endl;
	while (1) {
		try {
			cout << "검색할 제품이름입력(9. 이전화면) >> ";
			cin >> name;
			if (name == "9") {
				break;
			}
			pmu->findbyMulPname(vec, name);								// 중복이름에맞는 Pid벡터, 이름입력
			if (!cin || vec.empty() == 1) {								// 입력이름이 없다면 미등록이름 출력후 다시검색
				throw name;
			}								
			return;
		}
		catch (string& expn) {
			wordJudgeUi(expn);
		}
	}
}

int ManageUi::find_Shop_Price_Client() {								// 쇼핑한 고객들의 소비한 금액 출력용 Ui
	int CID_price_sel,CID_check;													
	cout << endl;
	cout << "**고객 총액 검색**" << endl;
	while (1) {
		try {
PRICESEL:
			cout << "검색할 ID입력(1.고객목록 / 9.이전화면)>> ";
			cin >> CID_price_sel;
			if (CID_price_sel == 9) {
				return 0;
			}
			else if (CID_price_sel == 1) {
				cout << "**모든 고객 ID목록**" << endl;
				cmu->displayInfoAll_ID();								// 쇼핑한 종류별 ID를 모두 보여줌 ( 중복제거 후 )
				goto PRICESEL;
			}
			CID_check = cmu->findbyId(CID_price_sel);					// 검색할 고객 ID입력해 존재여부 확인
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

vector<int> ManageUi::findClientByCode() {								// 고객이름을 ID로 찾기위한 함수
	int flag = true;
	int code;
	int ID_check;					// ID 확인용 변수
	vector<int> vecbyid;			// 쇼핑등록->고객검색후 제품검색시출력되는 값들을 저장하기위한 vector
	cout << endl;
	cout << "**코드검색**" << endl;
	while (flag) {
		try {
CODESEL:
			cout << "검색할 ID입력(1.ID목록 / 9.이전화면)>> ";
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
			return selectProductList(ID_check);								// 쇼핑등록 1.고객검색 후 2단계(제품선택)			
		}
		catch (int& expn) {
			wordJudgeUi(expn);
		}
	}
}

vector<int> ManageUi::findClientByName() {									// 쇼핑기록검색 -> 고객이름으로 검색 Ui
	vector<int> vecbyname,vecsel;
	string name;
	int IDsel_byname;
	int flag = true;
	cout << endl;
	cout << "**고객이름검색**" << endl;
	while (flag) {
		try {
			cout << "검색할 이름입력(9. 이전화면)>> ";
			cin >> name;
			if (name == "9") {
				flag = false;
				return vecbyname;
			}
			cmu->findbyMulName(vecbyname,name);								// 이름을 입력받아 여러개의 중복CID를 출력하기 위한함수
			if (vecbyname.size() == 0) {
				throw name;
			}
			IDsel_byname = cmu->findbyMulCID_Sel(vecbyname);				// 여러개의 CID중 원하는 ID 선택위한 함수
			vecsel = selectProductList(IDsel_byname);
			return vecsel;
		}
		catch (string expn) {
			wordJudgeUi(expn);
		}
	}
}

vector<int> ManageUi::selectProductList(int id) {					// 쇼핑등록 1.고객검색 후 2단계(제품선택)
	vector<int> vec,vec1;											// 제품리스트 출력후 
	string name;
	int select_pid;
	int PID_check;
	cout << endl;
	cout << "**제품검색**" << endl;
	while (1) {
		try {
first:
			cout << "검색할 제품입력(1.목록 / 2.이전메뉴)>> ";
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

			pmu->findbyMulPname(vec,name);							// 이름을 입력받아 여러개의 중복PID를 출력하기 위한함수
			if (vec.empty()) {
				throw name;
			}

			while (1) {								
				try {
					cout << "제품ID 입력>> ";
					cin >> select_pid;
					PID_check = pmu->findbyPid(select_pid);				// Pid가 존재하는지 확인용 함수
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

void ManageUi::ClientManageUi() {								// 첫페이지 고객정보관리 Ui
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

void ManageUi::ProductManageUi() {								// 첫페이지 제품정보관리 Ui
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

void ManageUi::ShopListManageUi() {								// 첫페이지 쇼핑정보관리 Ui
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

void ManageUi::find_display_id_A_sel() {						// 쇼핑별 각 ID 출력
	cout << endl;
	cout << "**ID 종류별 검색**" << endl;
	cout << "1. 쇼핑고객ID목록" << endl;
	cout << "2. 쇼핑제품ID목록" << endl;
	cout << "3. 쇼핑ID목록" << endl;
	cout << "9. 이전 화면" << endl;
	int ID_sel;
	while (1) {
		try {
			cout << "검색할 제품ID입력>> ";
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

void ManageUi::modidelShop_Sel(int key) {						// 단일 sid key받아 수정여부 확인
	int modidel_Sel;
	try {
		cout << "수정 : 1 / 삭제 : 2 / 이전화면 : 3 :";
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

void ManageUi::modidelShop_Sel(vector<int>& vec) {						// 여러개 sid받아 수정/삭제 여부
	int modidel_Sel,Single_Sid_sel;
	while (1) {
		try {
			cout << "수정 : 1 / 삭제 : 2 / 이전화면 : 3 :";
			cin >> modidel_Sel;
			if (modidel_Sel != 1 && modidel_Sel != 2 && modidel_Sel != 3) {
				throw modidel_Sel;
			}
			if (modidel_Sel == 3) {
				return;
			}
			Single_Sid_sel = smu->findbyMulSLID_Sel(vec);				// 입력받은 sid벡터를 번호(1,2,3,4...)로 선택할수있게함
			
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

void ManageUi::displayPrice_Client(int cid,int totprice) {				// 고객ID,총구매금액을 받아 출력용 Ui
	cout << endl << "**고객이 사용한 금액**" << endl;
	cout << "고객 ID : " << cid << endl;
	cout << "총 구매금액 : " << totprice << " 원" << endl;
}

void ManageUi::displayPrice_Client_All(float totprice_all) {			// 매장내에 총 수입 계산용 Ui
	cout << endl << "**매장 총액 (만원)**" << endl;
	totprice_all /= 10000;
	cout << totprice_all << " (만)원" << endl << endl;
}

void ManageUi::wordJudgeUi(int expn) {									// int로 입력받으면 출력되는 예외처리 함수
	cout << "미등록 번호 입니다.: " << expn << endl << endl;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}

void ManageUi::wordJudgeUi(string expn) {								// string로 입력받으면 출력되는 예외처리 함수
	cout << "미등록 이름 입니다.: " << expn << endl << endl;
	cin.clear();
	cin.ignore(INT_MAX, '\n');
}
