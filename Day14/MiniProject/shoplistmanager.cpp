#include "shoplistmanager.h"

ShopListManager::ShopListManager()                                       // 생성자 생성시 clientlist.txt안 데이터 가져오기
{
    ifstream file;
    file.open("shopList.txt");
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                int sid = stoi(row[0]);
                int cid = stoi(row[2]);
                int pid = stoi(row[3]);
                int purchaseamount = stoi(row[4]);
                int purchaseprice = stoi(row[5]);
                ShopList* s = new ShopList(sid, row[1], cid, pid, purchaseamount, purchaseprice, row[6]);
                shopList.insert({ sid, s });
            }
        }
    }
    file.close();
}

ShopListManager::~ShopListManager()                                     // 소멸자가 불려지면 shopList.txt안 데이터 입력하기
{
    ofstream file;
    file.open("shopList.txt");
    if (!file.fail()) {
        for (const auto& v : shopList) {                                // map컨테이너로 작성된 전체 shopList 내용을 file에 저장
            ShopList* s = v.second;
            file << s->getSid() << ", " << s->getPurchaseDate() << ", ";
            file << s->getCid() << ", ";
            file << s->getPid() << ", ";
            file << s->getPurchaseAmount() << ", ";
            file << s->getPurchasePrice() << ", ";
            file << s->getDiscountInfo() << endl;
        }
    }
    file.close();

}
int ShopListManager::inputShopList(vector<int>& vec)                    // 고객이 제품을 쇼핑한 기록 입력
{
    //vec.at[0] = cid , vec.at[1] = pid , vec.at[2] = productstock , vec.at[3] = productprice
    string Cur_time = CurrentTime();
    string discountinfo;
    int purchaseamount, purchaseprice;
    vector<int> vector;
    //구매액 = 물품금액 x 수량(자동 계산)
    while (1) {
        try {
            cout << "Purchase Amount? : ";
            cin >> purchaseamount;
            if (purchaseamount > vec[2]) {
                throw vec[2];
            }
            vec[2] -= purchaseamount;
            purchaseprice = vec[3] * purchaseamount;
            break;
        }
        catch(int expn){ 
            cout << "재고량 부족 : " << expn << endl << endl;
        }
    }

    int sid = makeSid();
    ShopList* s = new ShopList(sid, Cur_time, vec[0], vec[1], purchaseamount, purchaseprice);
    shopList.insert({ sid, s });
    return purchaseprice;
}

ShopList* ShopListManager::Ssearch(int sid){                        // 쇼핑ID를 받아 ShopList타입에 쇼핑value 출력
    return shopList[sid];
}

vector<int> ShopListManager::SCsearch(int cid) {                    // 단일고객아이디 이용 쇼핑내 쇼핑한고객목록 가져오기
    vector<int> vec;
    for (const auto& v : shopList) {
        ShopList* s = v.second;
        if (s->getCid() == cid) {
            vec.emplace_back(s->getSid());
        }
    }
    return vec;
}

vector<int> ShopListManager::SPsearch(int pid) {                    // 제품아이디 이용 쇼핑내 쇼핑한 고객목록 가져오기
    vector<int> vec;
    for (const auto& v : shopList) {
        ShopList* s = v.second;
        if (s->getPid() == pid) {
            vec.emplace_back(s->getSid());
        }
    }
    return vec;
}

int ShopListManager::findbySid(int id) {                            // 쇼핑목록 내 단일 SID 검색
    try {
        if (!cin || shopList.find(id) == shopList.end()) {
            throw id;
        }
        return id;
    }
    catch (...) {
        return 0;
    }
}

vector<int> ShopListManager::findMulSLbyCid(int cid) {                               // 고객입력받아 고객이쇼핑한 SID출력
    int cnt = 0;                                                                     // 선택하기위한 일부공개
    vector<int> vec;                                                                 
    cout << endl << "    ShopID |     CID      |     PID      |" << endl;
    for (const auto& v : shopList) {
        ShopList* s = v.second;
        if (s->getCid() == cid) {
            vec.emplace_back(s->getSid());
            cout << ++cnt << ". ";
            cout << setw(5) << setfill('0') << right << s->getSid() << " | " << left;
            cout << setw(12) << setfill(' ') << s->getCid() << " | ";
            cout << setw(12) << s->getPid() << endl;
        }
    }
    cout << endl;
    return vec;
}

vector<int> ShopListManager::findMulSLbyPid(int pid) {                               // 쇼핑목록 내 여러개 제품아이디 검색
    int cnt = 0;
    vector<int> vec;                                                                 // 단일제품id 입력받아 쇼핑목록에있는 제품ID와 같다면 vector에 삽입
    cout << endl << "    ShopID |     CID      |     PID      |" << endl;
    for (const auto& v : shopList) {
        ShopList* s = v.second;
        if (s->getPid() == pid) {
            vec.emplace_back(pid);
            cout << ++cnt << ". ";
            cout << setw(5) << setfill('0') << right << s->getSid() << " | " << left;
            cout << setw(12) << setfill(' ') << s->getCid() << " | ";
            cout << setw(12) << s->getPid() << endl;
        }
    }
    cout << endl;
    return vec;
}

vector<int> ShopListManager::findbyMulSLSid(int sid) {                               // 쇼핑목록 내 여러개 쇼핑아이디 검색(여러개X)
    int cnt = 0;                                                                     // 단일검색
    vector<int> vec;
    cout << endl << "     ShopID |     CID      |     PID      |" << endl;
    for (const auto& v : shopList) {
        ShopList* s = v.second;
        if (s->getSid() == sid) {
            vec.emplace_back(sid);
            cout << ++cnt << ". ";
            cout << setw(5) << setfill('0') << right << s->getSid() << " | " << left;
            cout << setw(12) << setfill(' ') << s->getCid() << " | ";
            cout << setw(12) << s->getPid() << endl;
        }
    }
    cout << endl;
    return vec;
}

int ShopListManager::findbyMulSLID_Sel(vector<int>& vec) {                          // 선택된 SID벡터를 입력받아 번호(1,2,3,4...)로 선택후 출력
    unsigned int ID_sel;
    while (1) {
        try {
            cout << "**번호선택**" << endl;
            cin >> ID_sel;
            if (!cin || (ID_sel > vec.size()) || ID_sel == 0) {
                throw ID_sel;
            }
            return vec[ID_sel - 1];
        }
        catch (int expn) {
            wordjudgeS(expn);
        }
    }
}

void ShopListManager::displaySinfoSingle(int key) {                                 // 단일SID입력받아 SID정보 출력
    cout << endl << "ShopID|         Date        |     CID      |     PID      |    Amount    |" << endl;
    ShopList* s = shopList[key];
    cout << setw(5) << setfill('0') << right << s->getSid() << " | " << left;
    cout << setw(12) << setfill(' ') << s->getPurchaseDate() << " | ";
    cout << setw(12) << setfill(' ') << s->getCid() << " | " << left;
    cout << setw(12) << setfill(' ') << s->getPid() << " | " << left;
    cout << setw(12) << s->getPurchaseAmount() << endl;
    //cout << setw(13) << setfill(' ') << s->getDiscountInfo() << endl << endl;
}

void ShopListManager::displaySMinfo(vector<int>& key) {                             // 여러개의 쇼핑ID입력받아 출력
    int cnt=0;                                                                      // 앞에 단일Cid 혹은 단일Pid로 검색후 그 타겟이 쇼핑한 목록 전체 출력
    cout << endl << "   ShopID|         Date        |     CID      |     PID      |    Amount    |" << endl;
    for (const auto& convK : key) {                                                 // 여러개의 쇼핑key iterator
        for (const auto& v : shopList) {
            ShopList* s = v.second;
            if (convK == s->getSid()) {                                             // 선택한 key가 shoplist에 잇다면 출력
                cout << ++cnt << ". ";
                cout << setw(5) << setfill('0') << right << s->getSid() << " | " << left;
                cout << setw(12) << setfill(' ') << s->getPurchaseDate() << " | ";
                cout << setw(12) << setfill(' ') << s->getCid() << " | " << left;
                cout << setw(12) << setfill(' ') << s->getPid() << " | " << left;
                cout << setw(12) << s->getPurchaseAmount() << endl;
                //cout << setw(13) << setfill(' ') << s->getDiscountInfo() << endl;
            }
        }
    }
    cout << endl;
}

void ShopListManager::displaySinfoAll_Cid(int cid) {                                // Cid 입력받아 고객이 사용한 쇼핑정보 전부 출력
    cout << endl << "ShopID|         Date        |     CID      |     PID      |    Amount    |" << endl;
    for (const auto& v : shopList) {
        ShopList* s = v.second;
        if (s->getCid() == cid) {
            cout << setw(5) << setfill('0') << right << s->getSid() << " | " << left;
            cout << setw(12) << setfill(' ') << s->getPurchaseDate() << " | ";
            cout << setw(12) << setfill(' ') << s->getCid() << " | " << left;
            cout << setw(12) << setfill(' ') << s->getPid() << " | " << left;
            cout << setw(12) << s->getPurchaseAmount() << endl;
            //cout << setw(13) << setfill(' ') << s->getDiscountInfo() << endl;
        }
    }
    cout << endl;
}

void ShopListManager::displaySinfoAll() {                                           // 등록된 쇼핑 전체목록 출력
    cout << endl << "ShopID|         Date        |     CID      |     PID      |    Amount    |" << endl;
    for (const auto& v : shopList) {
        ShopList* s = v.second;
        cout << setw(5) << setfill('0') << right << s->getSid() << " | " << left;
        cout << setw(12) << setfill(' ') << s->getPurchaseDate() << " | ";
        cout << setw(12) << setfill(' ') << s->getCid() << " | " << left;
        cout << setw(12) << setfill(' ') << s->getPid() << " | " << left;
        cout << setw(12) << s->getPurchaseAmount() << endl;
        //cout << setw(13) << setfill(' ') << s->getDiscountInfo() << endl;
    }
    cout << endl;
}

void ShopListManager::displayIDinforA(int num) {                                    // 쇼핑검색 -> ID로검색 -> 각 부분별 ID목록 중복제거후 출력
    set<int> setSCid,setSPid,setSSid;                                               // set 메쏘드 사용해 중복제거 후 정렬해 ID 선택지 출력
    int cnt = 0;
    if (num == 1) {
        for (const auto& v : shopList) {                                            // shopList에 저장된 고객아이디를 set에 iterator로 저장 
            ShopList* s = v.second;
            setSCid.insert(s->getCid());
        }
        cout << endl << "     CID |" << endl;
        for_each(setSCid.begin(), setSCid.end(), [&](const int& n) {
            ++cnt;
            cout << cnt << ". " << n << " | " << left << endl;
            });
        cout << "총 " << cnt << "개 검색" << endl;
    }
    else if (num == 2) {
        for (const auto& v : shopList) {                                            // shopList에 저장된 제품아이디를 set에 iterator로 저장 
            ShopList* s = v.second;
            setSPid.insert(s->getPid());
        }
        cout << endl << "     PID |" << endl;
        for_each(setSPid.begin(), setSPid.end(), [&](const int& n) {
            ++cnt;
            cout << cnt << ". " << n << " | " << left << endl;
            });
        cout << "총 " << cnt << "개 검색" << endl;
    }
    else if (num == 3) {
        for (const auto& v : shopList) {                                            // shopList에 저장된 쇼핑아이디를 set에 iterator로 저장 
            ShopList* s = v.second;
            setSSid.insert(s->getSid());
        }
        cout << endl << "  SID |" << endl;
        for_each(setSSid.begin(), setSSid.end(), [&](const int& n) {
            ++cnt;
            cout << cnt << ". " << setw(5) << setfill('0') << right << n << " | " << left << endl;
        });
        cout << "총 " << cnt << "개 검색" << endl;
    }
}

void ShopListManager::addShopList(ShopList* c) {                                    // ShopList* 타입의 value를 입력받으면 shopList에 저장
    shopList.insert({ c->getCid(), c });
}

void ShopListManager::deleteShopList(int key) {                                     // 선택된 단일 쇼핑ID 입력받아 삭제                        
    shopList.erase(key);
    cout << "ID : " << setw(5) << setfill('0') << right << key << " 번 삭제 완료" << endl << endl;
}

int ShopListManager::makeSid() {                                                    // 0번부터 시작하여 ID 생성용 함수
    auto key = shopList.end();
    if (shopList.size() == 0) {
        return 0;
    }
    else {
        int id = (--key)->first;
        return ++id;
    }
}

void ShopListManager::modifyShopList(int key) {                                     // 입력된 쇼핑ID를받아 구매량만 수정되도록하는 멤버함수
    ShopList* s = Ssearch(key);
    int amount;
    string discountinfo;
    cout << "Amount : "; cin >> amount;                                             

    s->setPurchaseAmount(amount);

    shopList[key] = s;

    cout << endl << "ShopID|         Date        |     CID      |     PID      |    Amount    |  DiscountInfo  |" << endl;      // 수정 후 확인용 출력Ui
    cout << setw(5) << setfill('0') << right << s->getSid() << " | " << left;
    cout << setw(12) << setfill(' ') << s->getPurchaseDate() << " | ";
    cout << setw(12) << setfill(' ') << s->getCid() << " | " << left;
    cout << setw(12) << setfill(' ') << s->getPid() << " | " << left;
    cout << setw(12) << s->getPurchaseAmount() << " | ";
    cout << setw(13) << setfill(' ') << s->getDiscountInfo() << endl << endl;
}

const string ShopListManager::CurrentTime() {                                       // 현재 컴퓨터 내부 설정된 날짜/시간 가져와 출력                 
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    char buffer[30];
    strftime(buffer, sizeof(buffer), "%m-%d-%Y %X", now);
    return buffer;                                                                  // 날짜 및 시간을 char타입 버퍼에 담아 출력
}

void ShopListManager::wordjudgeS(int expn) {                                        // 입력값 예외처리용 함수
    cout << "잘못된 번호 입력: " << expn << '\n';
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

vector<string> ShopListManager::parseCSV(istream& file, char delimiter)              // 함수 파일입출력시 parsing용 함수
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
            if (c != delimiter) break;                           // 위에 조건문 or 마무리로 구분문자가 아니라면 종료
        }
        else {
            ss << c;
        }
    }
    return row;
}