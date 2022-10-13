#include<string>
#include <vector>
#include <algorithm>
#include<iomanip>
#include <fstream>
#include <sstream>
#include <map>
#include <set>

#include "product.h"

using namespace std;

class ProductManager {
public:
    ProductManager();                                   // 생성자 생성시 productList.txt안 데이터 가져오기
    ~ProductManager();                                  // 소멸자가 불려지면 productList.txt안 데이터 입력하기

    void inputProduct();                                // 제품등록용 멤버함수
    Product* Psearch(int);                              // 제품ID 입력시 Product*타입에 객체를 출력
    set<int> findPidList();                             // 제품ID를 입력받아 제품리스트에 있으면 id반환 / 없으면 0반환
    int findbyPid(int);                                 // 제품ID를 입력받아 등록되있는지 확인용 멤버함수
    vector<int> findbyMulPid(int);                      // 제품ID를 입력받아 제품리스트에 있는지 확인용 함수(있다면 vec에 저장후 반환)
    void findbyMulPname(vector<int>&, string);          // selectProductList,find_Shop_Product_ByName함수 내 여러제품찾기

    int findStockbyPid(int);                            // 제품 ID 입력받아 productList 에 제품에등록된 재고 출력용 함수
    int findPricebyPid(int);                            // 제품 ID 입력받아 productList 에 제품에등록된 가격 출력용 함수

    void referenceP();                                  // 등록된 제품검색/수정/삭제용 멤버함수
    void displayPinfo(int);                             // 단일제품ID 입력받아 단일제품내용출력 Ui
    void displayPinfoAll();                             // 모든 제품 출력용 Ui

    void addProduct(Product*);                          // Product* 타입의 value를 입력받으면 productList에 저장
    void deleteProduct(int);                            // 선택된 단일 제품ID 입력받아 삭제
    int makePid();                                      // 50000번부터 시작하여 제품ID 생성용 함수
    
    void modifyProduct(int);                            // 단일 고객 ID입력받아 수정용 멤버함수
    void updateProductStock(vector<int>&);              // 수정된 재고 업데이트용 함수

    void wordjudgeP(int);                               // 입력값 예외처리용 함수
    vector<string> parseCSV(istream&, char);            // 함수 파일입출력시 parsing용 함수
private:
    map<int, Product*> productList;                     // 입력받은 제품리스트key 및 value 저장용 map컨테이너
};