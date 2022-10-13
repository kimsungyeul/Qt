#include "clientmanager.h"

ClientManager::ClientManager(){                                         // 생성자 생성시 clientlist.txt안 데이터 가져오기
    ifstream file;
    file.open("clientList.txt");
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int id = stoi(row[0]);
                int totalprice = stoi(row[5]);
                Client* c = new Client(id, row[1], row[2], row[3], row[4], totalprice, row[6]);
                clientList.insert({ id, c });
            }
        }
    }
    file.close();
}

ClientManager::~ClientManager()                                         // 소멸자가 불려지면 clientlist.txt안 데이터 입력하기
{
    ofstream file;
    file.open("clientList.txt");
    if (!file.fail()) {
        for (const auto& v : clientList) {                              // map컨테이너로 작성된 전체 clientList 내용을 file에 저장
            Client* c = v.second;
            file << c->getCid() << ", " << c->getName() << ", ";
            file << c->getPhoneNumber() << ", ";
            file << c->getAddress() << ", ";
            file << c->getEmail() << ", ";
            file << c->getTotalPrice() << ", ";
            file << c->getGrade() << endl;
        }
    }
    file.close();
}

void ClientManager::inputClient() {                         // 고객 등록용 함수
    string name, number, address, email;
    cout << "name : "; cin >> name;                         // 이름 입력
    cout << "number : "; cin >> number;                     // 전화번호 입력
    cout << "address : "; cin >> address;                   // 주소 입력
    cout << "email : "; cin >> email;                       // 이메일 입력
    cout << endl;
   
    int id = makeId();                                      // key값 생성
    Client* c = new Client(id, name, number, address, email);
    clientList.insert({ id, c });                           // 생성된 key값과 Client*타입의 value들을 clientList에저장 
}

Client* ClientManager::search(int cid)                       // 고객ID 입력시 Client*타입에 객체를 출력
{
    return clientList[cid];
}

int ClientManager::PriceSearch(int cid) {                    // 고객ID입력받아 고객이사용한 총 금액값출력
    return clientList[cid]->getTotalPrice();    
}

float ClientManager::PriceClient_All() {                     // 전체고객이 소모한 전체금액 계산
    float TotPrice=0;
    for (const auto& v : clientList) {
        Client* c = v.second;
        TotPrice += c->getTotalPrice();
    }
    return TotPrice;
}

set<int> ClientManager::findCidList() {                     // 쇼핑관리 -> 쇼핑검색 -> ID전체목록 검색후 set컨테이너에 저장해 중복제거후 출력 
    set<int> setC;
    for (const auto& v : clientList) {
        int c = v.first;
        setC.insert(c);
    }
    return setC;
}

int ClientManager::findbyId(int id) {                                                       // 고객아이디를 입력받아 고객리스트에 있으면 id반환 / 없으면 0반환
   
    if (!cin || (clientList.find(id) != clientList.end())) {
        return id;
    }
    else {
        return 0;
    }
}

vector<int> ClientManager::findbyMulId(int id) {                                            // 고객id를 입력받아 고객리스트에 있는지 확인용 함수(있다면 vec에 저장후 반환)
    vector<int> vec;
    cout << endl << "     ID  |     Name     |  Phone Number " << endl;                     // 자세한 내용은 지우고 다음알고리즘에 검색하기위한 출력
    for (const auto& v : clientList) {
        Client* c = v.second;
        if (c->getCid() == id) {
            vec.emplace_back(id);
            cout << setw(5) << setfill('0') << right << c->getCid() << " | " << left;
            cout << setw(12) << setfill(' ') << c->getName() << " | ";
            cout << setw(12) << c->getPhoneNumber() << endl;
        }
    }
    cout << endl;
    return vec;
}

void ClientManager::findbyMulName(vector<int>& vecN, string name) {                        // findClientByName (여러개 이름 검색)
    int cnt = 0;                                                                           // vector에 이름에서 뽑아낸 여러개 고객ID있음
    cout << endl << "     ID  |     Name     |  Phone Number " << endl;
    for (const auto& v : clientList) {
        Client* c = v.second;
        if (c->getName() == name) {                                                         //이름을 입력받아 고객리스트에동일이름이 있다면 고객ID를
            vecN.emplace_back(c->getCid());                                                 //vector에 저장후 referece로 반환
            cout << ++cnt << ". ";
            cout << setw(5) << setfill('0') << right << c->getCid() << " | " << left;
            cout << setw(12) << setfill(' ') << c->getName() << " | ";
            cout << setw(12) << c->getPhoneNumber() << endl;
        }
    }
}   

int ClientManager::findbyMulCID_Sel(vector<int>& vec) {                          // findClientByName에 사용(이름 선택용)
    unsigned int name_sel;                                                       // 연속된 이름에서 출력된 번호로 선택( ex 1,2,3,4 ..)
    
    while (1) {
        try {
            cout << "**번호선택**" << endl;                                      // 앞에서 번호순으로 출력된것에서 이름을 번호선택으로 값 출력
            cin >> name_sel;
            if (!cin || name_sel > vec.size() || name_sel == 0 ) {
                throw name_sel;
            }
            return vec.at(name_sel - 1);
        }
        catch (int expn) {
            wordjudge(expn);
        }
    }
}

void ClientManager::reference() {                                       // 등록된 고객검색용

    int ID_check = 0;               // 아이디 존재여부 확인용 변수
    int select = 0;                 // Ui선택용 변수
    int select_ID = 0;              // ID 수정/삭제/이전화면/처음화면용 변수
    int find_id = 0;                // 고객 ID 찾기용 변수
    string find_name;               // 이름으로 찾기용 변수
    vector<int> vec;                // 이름입력받아 동일인물ID 저장용 vector

    while (select != 9) {
        cout << "Find Name(이전화면 : 9) : ";
        cin >> find_name;
        if (find_name == "9") {
END:
            return;
        }
        findbyMulName(vec,find_name);

        if (vec.size() == 0) {
            cout << "검색 결과가 없습니다." << endl << endl;
        }
        else {
            cout << "총 " << vec.size() << "명 검색" << endl << endl;
            do{
                try {
                    cout << "ID검색/조회/수정 : 1 /  다시검색 : 2 / 이전화면 : 3 : ";
                    cin >> select;
                    if (select != 1 && select != 2 && select != 3) {
                        throw select;
                    }
                    if (select == 1) {
                        while (1) {
                            cout << endl;
                            cout << "Find Client ID(이전화면 : 9) : ";
                            cin >> find_id;
                            if (find_id == 9) {
                                return;
                            }
                            ID_check = findbyId(find_id);
                            if (ID_check == 0) {
                                wordjudge(find_id);
                            }
                            else {
                                displayInfo(find_id);
                                while (1) {
                                    try {
                                        cout << "수정 : 1 / 삭제 : 2 / 다시검색 : 3 / 이전화면 : 4 : ";
                                        cin >> select_ID;

                                        if (select_ID != 1 && select_ID != 2 && select_ID != 3 && select_ID != 4) {
                                            throw select_ID;
                                        }

                                        if (select_ID == 4) {
                                            cout << endl;
                                            goto END;
                                        }
                                        else if (select_ID == 3) {
                                            cout << endl;
                                            break;
                                        }
                                        else if (select_ID == 2) {
                                            cout << endl;
                                            deleteClient(find_id);
                                            break;
                                        }
                                        else if (select_ID == 1) {
                                            cout << endl;
                                            modifyClient(find_id);
                                            break;
                                        }
                                    }
                                    catch (int expn2) {
                                        wordjudge(expn2);
                                    }
                                }
                            }
                        }
                    }
                    else if (select == 3) {
                        return;
                    }
                }
                catch (int expn1) {
                    wordjudge(expn1);
                }
            } while (select != 1 && select != 2 && select != 3);
        }
    }
}

void ClientManager::displayInfo(int key){                                                                                // 단일고객아이디 입력시 Ui출력
    Client* c = search(key);
    cout << endl << "  ID  |     Name     | Phone Number  |    Address    |       E-Mail       |" << endl;
    cout << setw(5) << setfill('0') << right << c->getCid() << " | " << left;
    cout << setw(12) << setfill(' ') << c->getName() << " | ";
    cout << setw(12) << c->getPhoneNumber() << " | ";
    cout << setw(13) << setfill(' ') << c->getAddress() << " | ";
    cout << c->getEmail() << endl << endl;
}

void ClientManager::displayInfoAll_ID() {                                                                               // 고객아이디/이름/전화번호만 전부출력
    cout << endl << "  ID  |     Name     | Phone Number  |    Address    |       E-Mail       |" << endl;              // 중복이름도 전부출력
    for (const auto& v : clientList) {                                                                                  // 동명이인도 있어서 자세한 정보생략( 최소한의 구분용 )
        Client* c = v.second;
        cout << setw(5) << setfill('0') << right << c->getCid() << " | " << left;
        cout << setw(12) << setfill(' ') << c->getName() << " | ";
        cout << setw(12) << c->getPhoneNumber() << " | " << endl;
    }
    cout << endl;
}
void ClientManager::displayInfoAll(){                                                                                   // 등록된 고객 전체목록 출력
    cout << endl << "  ID  |     Name     | Phone Number  |    Address    |       E-Mail       |" << endl;
    for (const auto& v : clientList) {
        Client* c = v.second;
        cout << setw(5) << setfill('0') << right << c->getCid() << " | " << left;
        cout << setw(12) << setfill(' ') << c->getName() << " | ";
        cout << setw(12) << c->getPhoneNumber() << " | ";
        cout << setw(13) << setfill(' ') << c->getAddress() << " | ";
        cout << c->getEmail() << endl;
    }
    cout << endl;

}

void ClientManager::addClient(Client* c){                                       // Client* 타입의 value를 입력받으면 clientList에 저장
    clientList.insert({ c->getCid(), c });
}

void ClientManager::deleteClient(int key){                                      // 선택된 단일 고객ID 입력받아 삭제
    clientList.erase(key);
    cout << "고객ID : " << setw(5) << setfill('0') << right << key << " 번 삭제 완료" << endl << endl;
}

int ClientManager::makeId(){                                                    // 10000번부터 시작하여 ID 생성용 함수
    int Clientkey_start = 10000;
    auto key = clientList.end();
    if (clientList.size() == 0) {
        return Clientkey_start;
    }
    else {
        int Clientkey_start = (--key)->first;
        return ++Clientkey_start;
    }
}

void ClientManager::modifyClient(int key){                                      // 단일 고객 ID입력받아 수정용 멤버함수
    Client* c = search(key);
    string name, number, address, email;
    cout << "name : "; cin >> name;
    cout << "number : "; cin >> number;
    cout << "address : "; cin.ignore(); getline(cin, address, '\n');            // cin >> address;
    cout << "email : "; cin.ignore(); getline(cin, email, '\n');                // cin >> email;

    c->setName(name);
    c->setPhoneNumber(number);
    c->setAddress(address);
    c->setEmail(email);

    clientList[key] = c;

    cout << endl << "  ID  |     Name     | Phone Number  |    Address    |       E-Mail       |" << endl;   // 수정 후 확인용 출력Ui
    cout << setw(5) << setfill('0') << right << c->getCid() << " | " << left;
    cout << setw(12) << setfill(' ') << c->getName() << " | ";
    cout << setw(12) << c->getPhoneNumber() << " | ";
    cout << setw(13) << setfill(' ') << c->getAddress() << " | ";
    cout << c->getEmail() << endl;
}

void ClientManager::updateClientTotalprice(vector<int>& vec,int totprice) {                 // 고객이 가게에 사용한 총 금액 누적
    //vec.at[0] = cid , vec.at[1] = pid , vec.at[2] = productstock , vec.at[3] = price      // 입력받은 vector 내부 인자값 활용설명
    Client* c = search(vec[0]);                                                             
    int getTot = c->getTotalPrice() + totprice;

    c->setTotalPrice(getTot);
}

void ClientManager::wordjudge(int expn) {                                                   // 입력값 예외처리용 함수
    cout << "잘못된 번호 입력: " << expn << '\n';
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

vector<string> ClientManager::parseCSV(istream& file, char delimiter)                       // 함수 파일입출력시 parsing용 함수
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while (!file.eof()) {
        char c = file.get();                                    // 파일내용 한글자씩 가져옴
        if (c == delimiter || c == '\r' || c == '\n') {         // 글자판별용
            if (file.peek() == '\n') file.get();                // 만일 개행시 입력받고 
            string s = ss.str();                                // stringstream활용해 문자열받기
            s.erase(0, s.find_first_not_of(t));                 
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break;                          // 위에 조건문 or 마무리로 구분문자가 아니라면 종료
        }
        else {
            ss << c;
        }
    }
    return row;
}