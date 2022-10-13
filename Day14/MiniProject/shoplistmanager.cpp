#include "shoplistmanager.h"

ShopListManager::ShopListManager()                                       // ������ ������ clientlist.txt�� ������ ��������
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

ShopListManager::~ShopListManager()                                     // �Ҹ��ڰ� �ҷ����� shopList.txt�� ������ �Է��ϱ�
{
    ofstream file;
    file.open("shopList.txt");
    if (!file.fail()) {
        for (const auto& v : shopList) {                                // map�����̳ʷ� �ۼ��� ��ü shopList ������ file�� ����
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
int ShopListManager::inputShopList(vector<int>& vec)                    // ���� ��ǰ�� ������ ��� �Է�
{
    //vec.at[0] = cid , vec.at[1] = pid , vec.at[2] = productstock , vec.at[3] = productprice
    string Cur_time = CurrentTime();
    string discountinfo;
    int purchaseamount, purchaseprice;
    vector<int> vector;
    //���ž� = ��ǰ�ݾ� x ����(�ڵ� ���)
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
            cout << "��� ���� : " << expn << endl << endl;
        }
    }

    int sid = makeSid();
    ShopList* s = new ShopList(sid, Cur_time, vec[0], vec[1], purchaseamount, purchaseprice);
    shopList.insert({ sid, s });
    return purchaseprice;
}

ShopList* ShopListManager::Ssearch(int sid){                        // ����ID�� �޾� ShopListŸ�Կ� ����value ���
    return shopList[sid];
}

vector<int> ShopListManager::SCsearch(int cid) {                    // ���ϰ����̵� �̿� ���γ� �����Ѱ���� ��������
    vector<int> vec;
    for (const auto& v : shopList) {
        ShopList* s = v.second;
        if (s->getCid() == cid) {
            vec.emplace_back(s->getSid());
        }
    }
    return vec;
}

vector<int> ShopListManager::SPsearch(int pid) {                    // ��ǰ���̵� �̿� ���γ� ������ ����� ��������
    vector<int> vec;
    for (const auto& v : shopList) {
        ShopList* s = v.second;
        if (s->getPid() == pid) {
            vec.emplace_back(s->getSid());
        }
    }
    return vec;
}

int ShopListManager::findbySid(int id) {                            // ���θ�� �� ���� SID �˻�
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

vector<int> ShopListManager::findMulSLbyCid(int cid) {                               // ���Է¹޾� ���̼����� SID���
    int cnt = 0;                                                                     // �����ϱ����� �Ϻΰ���
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

vector<int> ShopListManager::findMulSLbyPid(int pid) {                               // ���θ�� �� ������ ��ǰ���̵� �˻�
    int cnt = 0;
    vector<int> vec;                                                                 // ������ǰid �Է¹޾� ���θ�Ͽ��ִ� ��ǰID�� ���ٸ� vector�� ����
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

vector<int> ShopListManager::findbyMulSLSid(int sid) {                               // ���θ�� �� ������ ���ξ��̵� �˻�(������X)
    int cnt = 0;                                                                     // ���ϰ˻�
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

int ShopListManager::findbyMulSLID_Sel(vector<int>& vec) {                          // ���õ� SID���͸� �Է¹޾� ��ȣ(1,2,3,4...)�� ������ ���
    unsigned int ID_sel;
    while (1) {
        try {
            cout << "**��ȣ����**" << endl;
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

void ShopListManager::displaySinfoSingle(int key) {                                 // ����SID�Է¹޾� SID���� ���
    cout << endl << "ShopID|         Date        |     CID      |     PID      |    Amount    |" << endl;
    ShopList* s = shopList[key];
    cout << setw(5) << setfill('0') << right << s->getSid() << " | " << left;
    cout << setw(12) << setfill(' ') << s->getPurchaseDate() << " | ";
    cout << setw(12) << setfill(' ') << s->getCid() << " | " << left;
    cout << setw(12) << setfill(' ') << s->getPid() << " | " << left;
    cout << setw(12) << s->getPurchaseAmount() << endl;
    //cout << setw(13) << setfill(' ') << s->getDiscountInfo() << endl << endl;
}

void ShopListManager::displaySMinfo(vector<int>& key) {                             // �������� ����ID�Է¹޾� ���
    int cnt=0;                                                                      // �տ� ����Cid Ȥ�� ����Pid�� �˻��� �� Ÿ���� ������ ��� ��ü ���
    cout << endl << "   ShopID|         Date        |     CID      |     PID      |    Amount    |" << endl;
    for (const auto& convK : key) {                                                 // �������� ����key iterator
        for (const auto& v : shopList) {
            ShopList* s = v.second;
            if (convK == s->getSid()) {                                             // ������ key�� shoplist�� �մٸ� ���
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

void ShopListManager::displaySinfoAll_Cid(int cid) {                                // Cid �Է¹޾� ���� ����� �������� ���� ���
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

void ShopListManager::displaySinfoAll() {                                           // ��ϵ� ���� ��ü��� ���
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

void ShopListManager::displayIDinforA(int num) {                                    // ���ΰ˻� -> ID�ΰ˻� -> �� �κк� ID��� �ߺ������� ���
    set<int> setSCid,setSPid,setSSid;                                               // set �޽�� ����� �ߺ����� �� ������ ID ������ ���
    int cnt = 0;
    if (num == 1) {
        for (const auto& v : shopList) {                                            // shopList�� ����� �����̵� set�� iterator�� ���� 
            ShopList* s = v.second;
            setSCid.insert(s->getCid());
        }
        cout << endl << "     CID |" << endl;
        for_each(setSCid.begin(), setSCid.end(), [&](const int& n) {
            ++cnt;
            cout << cnt << ". " << n << " | " << left << endl;
            });
        cout << "�� " << cnt << "�� �˻�" << endl;
    }
    else if (num == 2) {
        for (const auto& v : shopList) {                                            // shopList�� ����� ��ǰ���̵� set�� iterator�� ���� 
            ShopList* s = v.second;
            setSPid.insert(s->getPid());
        }
        cout << endl << "     PID |" << endl;
        for_each(setSPid.begin(), setSPid.end(), [&](const int& n) {
            ++cnt;
            cout << cnt << ". " << n << " | " << left << endl;
            });
        cout << "�� " << cnt << "�� �˻�" << endl;
    }
    else if (num == 3) {
        for (const auto& v : shopList) {                                            // shopList�� ����� ���ξ��̵� set�� iterator�� ���� 
            ShopList* s = v.second;
            setSSid.insert(s->getSid());
        }
        cout << endl << "  SID |" << endl;
        for_each(setSSid.begin(), setSSid.end(), [&](const int& n) {
            ++cnt;
            cout << cnt << ". " << setw(5) << setfill('0') << right << n << " | " << left << endl;
        });
        cout << "�� " << cnt << "�� �˻�" << endl;
    }
}

void ShopListManager::addShopList(ShopList* c) {                                    // ShopList* Ÿ���� value�� �Է¹����� shopList�� ����
    shopList.insert({ c->getCid(), c });
}

void ShopListManager::deleteShopList(int key) {                                     // ���õ� ���� ����ID �Է¹޾� ����                        
    shopList.erase(key);
    cout << "ID : " << setw(5) << setfill('0') << right << key << " �� ���� �Ϸ�" << endl << endl;
}

int ShopListManager::makeSid() {                                                    // 0������ �����Ͽ� ID ������ �Լ�
    auto key = shopList.end();
    if (shopList.size() == 0) {
        return 0;
    }
    else {
        int id = (--key)->first;
        return ++id;
    }
}

void ShopListManager::modifyShopList(int key) {                                     // �Էµ� ����ID���޾� ���ŷ��� �����ǵ����ϴ� ����Լ�
    ShopList* s = Ssearch(key);
    int amount;
    string discountinfo;
    cout << "Amount : "; cin >> amount;                                             

    s->setPurchaseAmount(amount);

    shopList[key] = s;

    cout << endl << "ShopID|         Date        |     CID      |     PID      |    Amount    |  DiscountInfo  |" << endl;      // ���� �� Ȯ�ο� ���Ui
    cout << setw(5) << setfill('0') << right << s->getSid() << " | " << left;
    cout << setw(12) << setfill(' ') << s->getPurchaseDate() << " | ";
    cout << setw(12) << setfill(' ') << s->getCid() << " | " << left;
    cout << setw(12) << setfill(' ') << s->getPid() << " | " << left;
    cout << setw(12) << s->getPurchaseAmount() << " | ";
    cout << setw(13) << setfill(' ') << s->getDiscountInfo() << endl << endl;
}

const string ShopListManager::CurrentTime() {                                       // ���� ��ǻ�� ���� ������ ��¥/�ð� ������ ���                 
    time_t t = time(nullptr);
    tm* now = localtime(&t);

    char buffer[30];
    strftime(buffer, sizeof(buffer), "%m-%d-%Y %X", now);
    return buffer;                                                                  // ��¥ �� �ð��� charŸ�� ���ۿ� ��� ���
}

void ShopListManager::wordjudgeS(int expn) {                                        // �Է°� ����ó���� �Լ�
    cout << "�߸��� ��ȣ �Է�: " << expn << '\n';
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

vector<string> ShopListManager::parseCSV(istream& file, char delimiter)              // �Լ� ��������½� parsing�� �Լ�
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while (!file.eof()) {
        char c = file.get();                                    // ���ϳ��� �ѱ��ھ� ������
        if (c == delimiter || c == '\r' || c == '\n') {         // �����Ǻ���
            if (file.peek() == '\n') file.get();                // ���� ����� �Է¹ް� 
            string s = ss.str();                                // stringstreamȰ���� ���ڿ��ޱ�
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break;                           // ���� ���ǹ� or �������� ���й��ڰ� �ƴ϶�� ����
        }
        else {
            ss << c;
        }
    }
    return row;
}