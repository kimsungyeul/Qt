#include "productmanager.h"

ProductManager::ProductManager() {                                                // 생성자 생성시 productList.txt안 데이터 가져오기
    ifstream file;
    file.open("productList.txt");
    if (!file.fail()) {
        while (!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if (row.size()) {
                //int id = atoi(row[0].c_str());
                int pid = stoi(row[0]);
                int price = stoi(row[3]);
                int stock = stoi(row[4]);
                Product* p = new Product(pid, row[1], row[2], price, stock);
                productList.insert({ pid, p });
            }
        }
    }
    file.close();
}

ProductManager::~ProductManager()                                                   // 소멸자가 불려지면 productList.txt안 데이터 입력하기
{
    ofstream file;
    file.open("productList.txt");                                                   // map컨테이너로 작성된 전체 productList 내용을 file에 저장
    if (!file.fail()) {
        for (const auto& v : productList) {
            Product* p = v.second;
            file << p->getPid() << ", " << p->getProductCategory() << ", ";
            file << p->getProductName() << ", ";
            file << p->getPrice() << ", ";
            file << p->getProductStock() << endl;
        }
    }
    file.close();
}

void ProductManager::inputProduct() {                                               // 제품등록용 멤버함수
    string productcategory,productname;
    int price, productstuck;

    cout << "category : "; cin >> productcategory;                                  // 제품 카테고리입력
    cout << "name : "; cin >> productname;                                          // 제품 이름입력
    cout << "price : "; cin >> price;                                               // 제품 가격입력
    cout << "productstuck : "; cin >> productstuck;                                 // 제품 재고입력
    cout << endl;

    int pid = makePid();                                                            // key값 생성
    Product* p = new Product(pid, productcategory,productname,price,productstuck);
    productList.insert({ pid, p });                                                 // 생성된 key값과 Product*타입의 value들을 productList에저장 
}

Product* ProductManager::Psearch(int pid)                                           // 제품ID 입력시 Product*타입에 객체를 출력
{
    return productList[pid];
}

set<int> ProductManager::findPidList() {                                            // 제품id를 입력받아 제품리스트에 있으면 id반환 / 없으면 0반환
    set<int> setP;
    for (const auto& v : productList) {
        int p = v.first;
        setP.insert(p);
    }
    return setP;
}

int ProductManager::findbyPid(int pid) {                                            // 제품ID를 입력받아 등록되있는지 확인용 멤버함수
    if (!cin || (productList.find(pid) != productList.end())) {
        return pid;
    }
    else {
        return 0;
    }
}

vector<int> ProductManager::findbyMulPid(int pid) {                                 // 제품id를 입력받아 제품리스트에 있는지 확인용 함수(있다면 vec에 저장후 반환)
    int cnt = 0;
    vector<int> vec;
    cout << endl << "   PID  |   Category   |     Name     |" << endl;
    for (const auto& v : productList) {
        Product* p = v.second;
        if (p->getPid() == pid) {
            vec.emplace_back(pid);
            cout << ++cnt << ". ";
            cout << setw(5) << setfill('0') << right << p->getPid() << " | " << left;
            cout << setw(12) << setfill(' ') << p->getProductCategory() << " | ";
            cout << setw(12) << p->getProductName() << endl;
        }
    }

    return vec;
}

void ProductManager::findbyMulPname(vector<int>& vec, string name) {                // selectProductList,find_Shop_Product_ByName함수 내 여러제품찾기
    int cnt = 0;                                                                    // 제품선택하기위해 제품이름만 출력
    cout << endl << "    PID  |   Category   |     Name     |" << endl;             // 종류별 중복이름 전부 출력
    for (const auto& v : productList) {
        Product* p = v.second;
        if (p->getProductName() == name) {                                          // 검색이름과 동일하면
            vec.emplace_back(p->getPid());                                          // vec에 PID수집 및 순서대로 목록출력
            cout << ++cnt << ". ";
            cout << setw(5) << setfill('0') << right << p->getPid() << " | " << left;
            cout << setw(12) << setfill(' ') << p->getProductCategory() << " | ";
            cout << setw(12) << p->getProductName() << endl;
        }
    }
}

int ProductManager::findStockbyPid(int pid) {                       // 제품 ID 입력받아 productList 에 제품에등록된 재고 출력용 함수
    return productList[pid]->getProductStock();
}

int ProductManager::findPricebyPid(int pid) {                       // 제품 ID 입력받아 productList 에 제품에등록된 가격 출력용 함수
    return productList[pid]->getPrice();
}

void ProductManager::referenceP() {                                 // 등록된 제품검색/수정/삭제용 멤버함수

    int select = 0;                     // Ui선택용 변수 
    int select_ID = 0;                  // ID 수정/삭제/이전화면/처음화면용 변수
    int find_id = 0;                    // 제품 ID 찾기용 변수
    string find_name;                   // 이름으로 찾기용 변수
    vector<int> vec;                    // 이름입력받아 동일제품ID 저장용 vector

    while (select != 9) {
        cout << "1.제품이름검색(이전화면 : 9) : ";
        cin >> find_name;
        if (find_name == "9") {
END:
            return;
        }
        findbyMulPname(vec,find_name);
        if (vec.size() == 0) {
            cout << "검색 결과가 없습니다." << endl << endl;
        }
        else {
            cout << "총 " << vec.size() << "종류 검색" << endl << endl;
            do {
                try {
                    cout << "ID검색/수정/삭제 : 1 / 다시검색 : 2 / 이전화면 : 3 : ";
                    cin >> select;
                    if (select != 1 && select != 2 && select != 3) {
                        throw select;
                    }
                    if (select == 2) {
                        cout << endl;
                        vec.clear();
                        break;
                    }
                    if (select == 1) {
                        while (1) {                             // 제품 ID를 입력받기용
                            try {
                                cout << endl;
                                cout << "Find Product ID(이전화면 : 9) : ";
                                cin >> find_id;
                                if (find_id == 9) {
                                    return;
                                }
                                if (!cin || productList.find(find_id) == productList.end()) {
                                    throw find_id;
                                }
                                displayPinfo(find_id);
                                while (1) {                     // 수정/삭제/다시검색/이전화면 선택
                                    try {
                                        cout << "수정 : 1 / 삭제 : 2 / 다시검색 : 3 / 이전화면 : 4 : ";
                                        cin >> select_ID;

                                        if (select != 1 && select != 2 && select != 3 && select != 4) {
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
                                            deleteProduct(find_id);
                                            break;
                                        }
                                        else if (select_ID == 1) {
                                            cout << endl;
                                            modifyProduct(find_id);
                                            break;
                                        }
                                    }
                                    catch (int expn3) {
                                        wordjudgeP(expn3);
                                    }
                                }
                            }
                            catch (int expn2) {
                                wordjudgeP(expn2);
                            }
                        }
                    }
                    else if (select == 3) {
                        return;
                    }
                }
                catch (int expn1) {
                    wordjudgeP(expn1);
                }

            } while (select != 1 && select != 2 && select != 3);
        }
    }
}

void ProductManager::displayPinfo(int key) {                        // 단일제품ID 입력받아 단일제품내용출력 Ui
    Product* p = Psearch(key);
    cout << endl << "  PID |   Category   |     Name     |     Price    |     Stuck     |" << endl;
    cout << setw(5) << p->getPid() << " | " << left;
    cout << setw(12) << setfill(' ') << p->getProductCategory() << " | ";
    cout << setw(12) << setfill(' ') << p->getProductName() << " | ";
    cout << setw(12) << p->getPrice() << " | ";
    cout << p->getProductStock() << endl << endl;
}

void ProductManager::displayPinfoAll() {                            // 모든 제품 출력용 Ui
    cout << endl << "  PID |   Category   |     Name     |     Price    |     Stuck     |" << endl;
    for (const auto& v : productList) {
        Product* p = v.second;
        cout << p->getPid() << " | " << left;
        cout << setw(12) << setfill(' ') << p->getProductCategory() << " | ";
        cout << setw(12) << setfill(' ') << p->getProductName() << " | ";
        cout << setw(12) << p->getPrice() << " | ";
        cout << p->getProductStock() << endl;
    }
    cout << endl;
}

void ProductManager::addProduct(Product* p) {                       // Product* 타입의 value를 입력받으면 productList에 저장
    productList.insert({ p->getPid(), p });
}

void ProductManager::deleteProduct(int key) {                       // 선택된 단일 제품ID 입력받아 삭제
    productList.erase(key);
    cout << "제품ID : " << setw(5) << setfill('0') << right << key << " 번 삭제 완료" << endl << endl;
}

int ProductManager::makePid() {                                     // 50000번부터 시작하여 제품ID 생성용 함수
    int Productkey_start = 50000;
    auto key = productList.end();
    if (productList.size() == 0) {
        return Productkey_start;
    }
    else {
        Productkey_start = (--key)->first;
        return ++Productkey_start;
    }
}

void ProductManager::modifyProduct(int key) {                                           // 단일 고객 ID입력받아 수정용 멤버함수
    Product* p = Psearch(key);
    string productcategory,productname;
    int price, productstock;
    cout << "productcategory : "; cin.ignore(); getline(cin, productcategory, '\n');    // cin >> productcategory;
    cout << "productname : "; cin.ignore(); getline(cin, productname, '\n');            // cin >> productname;
    cout << "price : "; cin >> price;
    cout << "productstuck : "; cin >> productstock;

    p->setProductCategory(productcategory);
    p->setProductName(productname);
    p->setPrice(price);
    p->setProductStock(productstock);

    productList[key] = p;

    cout << endl << "  PID |   Category   |     Name     |     Price    |     Stuck     |" << endl;     // 수정 후 확인용 출력Ui
    cout << setw(5) <<  p->getPid() << " | " << left;
    cout << setw(12) << setfill(' ') << p->getProductCategory() << " | ";
    cout << setw(12) << setfill(' ') << p->getProductName() << " | ";
    cout << setw(12) << p->getPrice() << " | ";
    cout << p->getProductStock() << endl;
}

void ProductManager::updateProductStock(vector<int>& vec) {                                 // 수정된 재고 업데이트용 함수
    //vec.at[0] = cid , vec.at[1] = pid , vec.at[2] = productstock , vec.at[3] = price      // 입력받은 vector 내부 인자값 활용설명
    Product* p = Psearch(vec[1]);

    p->setProductStock(vec[2]);
}

void ProductManager::wordjudgeP(int expn) {                             // 입력값 예외처리용 함수
    cout << "잘못된 번호 입력: " << expn << '\n';
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

vector<string> ProductManager::parseCSV(istream& file, char delimiter)  // 함수 파일입출력시 parsing용 함수
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while (!file.eof()) {
        char c = file.get();                                // 파일내용 한글자씩 가져옴
        if (c == delimiter || c == '\r' || c == '\n') {     // 글자판별용
            if (file.peek() == '\n') file.get();            // 만일 개행시 입력받고 
            string s = ss.str();                            // stringstream활용해 문자열받기
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break;                      // 위에 조건문 or 마무리로 구분문자가 아니라면 종료
        }
        else {
            ss << c;
        }
    }
    return row;
}