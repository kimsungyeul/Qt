#include<string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include<iomanip>
#include <map>
#include <set>
#include "client.h"

using namespace std;

class ClientManager {
public:
    ClientManager();                                        // 생성자 생성시 clientlist.txt안 데이터 가져오기
    ~ClientManager();                                       // 소멸자가 불려지면 clientlist.txt안 데이터 입력하기

    void inputClient();                                     // 고객 등록용 함수
    Client* search(int);                                    // 고객ID 입력시 Client*타입에 객체를 출력
    int PriceSearch(int);                                   // 고객ID입력받아 고객이사용한 총 금액값출력
    float PriceClient_All();                                  // 전체고객이 소모한 전체금액 계산
    set<int> findCidList();                                 // 쇼핑관리 -> 쇼핑검색 -> ID전체목록 검색후 set컨테이너에 저장해 중복제거후 출력 

    int findbyId(int);                                      // 고객아이디를 입력받아 고객리스트에 있으면 id반환 / 없으면 0반환
    vector<int> findbyMulId(int);                           // 고객id를 입력받아 고객리스트에 있는지 확인용 함수(있다면 vec에 저장후 반환)
    void findbyMulName(vector<int>&,string);                // findClientByName (여러개 이름 검색)
    int findbyMulCID_Sel(vector<int>&);                     // findClientByName에 사용(이름 선택용)

    void reference();                                       // 등록된 고객검색용
    void displayInfo(int);                                  // 단일고객아이디 입력시 Ui출력
    void displayInfoAll_ID();                               // 고객아이디/이름/전화번호만 전부출력
    void displayInfoAll();                                  // 등록된 고객 전체목록 출력

    void addClient(Client*);                                // Client* 타입의 value를 입력받으면 clientList에 저장
    void deleteClient(int);                                 // 선택된 단일 고객ID 입력받아 삭제
    int makeId();                                           // 10000번부터 시작하여 ID 생성용 함수
    void modifyClient(int);                                 // 단일 고객 ID입력받아 수정용 멤버함수
    void updateClientTotalprice(vector<int>&,int);          // 고객이 가게에 사용한 총 금액 누적

    void wordjudge(int);                                    // 입력값 예외처리용 함수
    vector<string> parseCSV(istream&, char);                // 함수 파일입출력시 parsing용 함수

private:
    map<int, Client*> clientList;                           // 입력받은 고객리스트key 및 value 저장용 map컨테이너                           
};