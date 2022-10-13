#include <map>
#include<string>
#include<vector>
#include<set>
#include<algorithm>
#include<iomanip>
#include <fstream>
#include <sstream>
#include<ctime>

#include "shoplist.h"
using namespace std;

class ShopListManager {
public:
    ShopListManager();                              // 생성자 생성시 clientlist.txt안 데이터 가져오기
    ~ShopListManager();                             // 소멸자가 불려지면 shopList.txt안 데이터 입력하기
    
    int inputShopList(vector<int>&);                // 고객이 제품을 쇼핑한 기록 입력
    ShopList* Ssearch(int);                         // 쇼핑ID를 받아 ShopList타입에 쇼핑value 출력
    vector<int> SCsearch(int);                      // 단일고객아이디 이용 쇼핑내 쇼핑한고객목록 가져오기
    vector<int> SPsearch(int);                      // 제품아이디 이용 쇼핑내 쇼핑한 고객목록 가져오기
                         
    int findbySid(int);                             // 쇼핑목록 내 단일 SID 검색
    vector<int> findMulSLbyCid(int);                // 고객입력받아 고객이쇼핑한 SID출력
    vector<int> findMulSLbyPid(int);                // 쇼핑목록 내 여러개 제품아이디 검색
    vector<int> findbyMulSLSid(int);                // 쇼핑목록 내 여러개 쇼핑아이디 검색(여러개X)
    int findbyMulSLID_Sel(vector<int>&);            // 선택된 SID벡터를 입력받아 번호(1,2,3,4...)로 선택후 출력
    
    void displaySinfoSingle(int);                   // 단일SID입력받아 SID정보 출력
    void displaySMinfo(vector<int>&);               // 여러개의 쇼핑ID입력받아 출력
    void displaySinfoAll_Cid(int);                  // Cid 입력받아 고객이 사용한 쇼핑정보 전부 출력
    void displaySinfoAll();                         // 등록된 쇼핑 전체목록 출력
    void displayIDinforA(int);                      // 쇼핑검색 -> ID로검색 -> 각 부분별 ID목록 중복제거후 출력

    void addShopList(ShopList*);                    // ShopList* 타입의 value를 입력받으면 shopList에 저장
    void deleteShopList(int);                       // 선택된 단일 쇼핑ID 입력받아 삭제            
    int makeSid();                                  // 0번부터 시작하여 ID 생성용 함수

    void modifyShopList(int);                       // 입력된 쇼핑ID를받아 구매량만 수정되도록하는 멤버함수
    const string CurrentTime();                     // 현재 컴퓨터 내부 설정된 날짜/시간 가져와 출력
    void wordjudgeS(int);                           // 입력값 예외처리용 함수
    vector<string> parseCSV(istream&, char);        // 함수 파일입출력시 parsing용 함수

private:
    map<int, ShopList*> shopList;                   // 입력받은 쇼핑리스트key 및 value 저장용 map컨테이너
};