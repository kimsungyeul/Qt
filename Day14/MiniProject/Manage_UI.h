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
	ManageUi();											// 생성자에서 고객,상품,쇼핑컨트롤용 메모리할당
	~ManageUi();										// 소멸자불려질시 delete되게 설정

	void printTitle();									// 첫 타이틀 출력용
	void printMenu();									// 첫 타이틀 목록 출력용
	void processMenu(int);								// 타이틀 선택후 프로세스 실행

	void printClientMenu();								// 고객정보관리 메뉴
	void printProductMenu();							// 상품정보관리 메뉴
	void printShopListMenu();							// 쇼핑정보관리 메뉴

	void processClientMenu(int);						// 고객메뉴 Ui
	void processProductMenu(int);						// 제품메뉴 Ui
	void processShopListMenu(int);						// 쇼핑메뉴 Ui

	void find_Shop_Record_Client_Ui();					// 쇼핑 고객기록검색 Ui
	void find_Shop_Record_Research_Ui();				// 쇼핑기록 검색 Ui
	void find_Shop_Record_Id_Ui();						// 종류별 ID로 쇼핑기록 찾기위한 Ui
	void find_Shop_Record_Name_Ui();					// 종류별 이름으로 쇼핑기록 찾기위한 Ui
	void find_Shop_Price_Total_Ui();					// 쇼핑후 고객별 or 매장 총액 검색용 Ui

	void find_Shop_Client_ByName(vector<int>&);			// 쇼핑기록 -> 이름으로검색 -> 고객이름으로검색 Ui
	void find_Shop_Product_ByName(vector<int>&);		// 쇼핑기록 -> 이름으로검색 -> 제품이름으로검색 Ui
	int find_Shop_Price_Client();						// 쇼핑한 고객들의 소비한 금액 출력용 Ui

	vector<int> findClientByCode();						// 고객이름을 ID로 찾기위한 함수
	vector<int> findClientByName();						// 쇼핑기록검색 -> 고객이름으로 검색 Ui
	vector<int> selectProductList(int);					// 쇼핑등록 1.고객검색 후 2단계(제품선택)
	
	void ClientManageUi();								// 첫페이지 고객정보관리 Ui
	void ProductManageUi();								// 첫페이지 제품정보관리 Ui
	void ShopListManageUi();							// 첫페이지 쇼핑정보관리 Ui

	void find_display_id_A_sel();						// 쇼핑별 각 ID 출력

	void modidelShop_Sel(int);							// 단일 sid key받아 수정여부 확인
	void modidelShop_Sel(vector<int>&);					// 여러개 sid받아 수정/삭제 여부

	void displayPrice_Client(int,int);					// 고객ID,총구매금액을 받아 출력용 Ui
	void displayPrice_Client_All(float);				// 매장내에 총 수입 계산용 Ui
	void wordJudgeUi(int);								// int로 입력받으면 출력되는 예외처리 함수
	void wordJudgeUi(string);							// string로 입력받으면 출력되는 예외처리 함수

private:
	ClientManager* cmu;									// 고객 컨트롤용 동적메모리 할당
	ProductManager* pmu;								// 제품 컨트롤용 동적메모리 할당
	ShopListManager* smu;								// 쇼핑 컨트롤용 동적메모리 할당
};
