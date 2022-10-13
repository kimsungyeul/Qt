#include "clientmanager.h"

ClientManager::ClientManager(){                                         // ������ ������ clientlist.txt�� ������ ��������
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

ClientManager::~ClientManager()                                         // �Ҹ��ڰ� �ҷ����� clientlist.txt�� ������ �Է��ϱ�
{
    ofstream file;
    file.open("clientList.txt");
    if (!file.fail()) {
        for (const auto& v : clientList) {                              // map�����̳ʷ� �ۼ��� ��ü clientList ������ file�� ����
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

void ClientManager::inputClient() {                         // �� ��Ͽ� �Լ�
    string name, number, address, email;
    cout << "name : "; cin >> name;                         // �̸� �Է�
    cout << "number : "; cin >> number;                     // ��ȭ��ȣ �Է�
    cout << "address : "; cin >> address;                   // �ּ� �Է�
    cout << "email : "; cin >> email;                       // �̸��� �Է�
    cout << endl;
   
    int id = makeId();                                      // key�� ����
    Client* c = new Client(id, name, number, address, email);
    clientList.insert({ id, c });                           // ������ key���� Client*Ÿ���� value���� clientList������ 
}

Client* ClientManager::search(int cid)                       // ��ID �Է½� Client*Ÿ�Կ� ��ü�� ���
{
    return clientList[cid];
}

int ClientManager::PriceSearch(int cid) {                    // ��ID�Է¹޾� ���̻���� �� �ݾװ����
    return clientList[cid]->getTotalPrice();    
}

float ClientManager::PriceClient_All() {                     // ��ü���� �Ҹ��� ��ü�ݾ� ���
    float TotPrice=0;
    for (const auto& v : clientList) {
        Client* c = v.second;
        TotPrice += c->getTotalPrice();
    }
    return TotPrice;
}

set<int> ClientManager::findCidList() {                     // ���ΰ��� -> ���ΰ˻� -> ID��ü��� �˻��� set�����̳ʿ� ������ �ߺ������� ��� 
    set<int> setC;
    for (const auto& v : clientList) {
        int c = v.first;
        setC.insert(c);
    }
    return setC;
}

int ClientManager::findbyId(int id) {                                                       // �����̵� �Է¹޾� ������Ʈ�� ������ id��ȯ / ������ 0��ȯ
   
    if (!cin || (clientList.find(id) != clientList.end())) {
        return id;
    }
    else {
        return 0;
    }
}

vector<int> ClientManager::findbyMulId(int id) {                                            // ��id�� �Է¹޾� ������Ʈ�� �ִ��� Ȯ�ο� �Լ�(�ִٸ� vec�� ������ ��ȯ)
    vector<int> vec;
    cout << endl << "     ID  |     Name     |  Phone Number " << endl;                     // �ڼ��� ������ ����� �����˰��� �˻��ϱ����� ���
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

void ClientManager::findbyMulName(vector<int>& vecN, string name) {                        // findClientByName (������ �̸� �˻�)
    int cnt = 0;                                                                           // vector�� �̸����� �̾Ƴ� ������ ��ID����
    cout << endl << "     ID  |     Name     |  Phone Number " << endl;
    for (const auto& v : clientList) {
        Client* c = v.second;
        if (c->getName() == name) {                                                         //�̸��� �Է¹޾� ������Ʈ�������̸��� �ִٸ� ��ID��
            vecN.emplace_back(c->getCid());                                                 //vector�� ������ referece�� ��ȯ
            cout << ++cnt << ". ";
            cout << setw(5) << setfill('0') << right << c->getCid() << " | " << left;
            cout << setw(12) << setfill(' ') << c->getName() << " | ";
            cout << setw(12) << c->getPhoneNumber() << endl;
        }
    }
}   

int ClientManager::findbyMulCID_Sel(vector<int>& vec) {                          // findClientByName�� ���(�̸� ���ÿ�)
    unsigned int name_sel;                                                       // ���ӵ� �̸����� ��µ� ��ȣ�� ����( ex 1,2,3,4 ..)
    
    while (1) {
        try {
            cout << "**��ȣ����**" << endl;                                      // �տ��� ��ȣ������ ��µȰͿ��� �̸��� ��ȣ�������� �� ���
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

void ClientManager::reference() {                                       // ��ϵ� ���˻���

    int ID_check = 0;               // ���̵� ���翩�� Ȯ�ο� ����
    int select = 0;                 // Ui���ÿ� ����
    int select_ID = 0;              // ID ����/����/����ȭ��/ó��ȭ��� ����
    int find_id = 0;                // �� ID ã��� ����
    string find_name;               // �̸����� ã��� ����
    vector<int> vec;                // �̸��Է¹޾� �����ι�ID ����� vector

    while (select != 9) {
        cout << "Find Name(����ȭ�� : 9) : ";
        cin >> find_name;
        if (find_name == "9") {
END:
            return;
        }
        findbyMulName(vec,find_name);

        if (vec.size() == 0) {
            cout << "�˻� ����� �����ϴ�." << endl << endl;
        }
        else {
            cout << "�� " << vec.size() << "�� �˻�" << endl << endl;
            do{
                try {
                    cout << "ID�˻�/��ȸ/���� : 1 /  �ٽð˻� : 2 / ����ȭ�� : 3 : ";
                    cin >> select;
                    if (select != 1 && select != 2 && select != 3) {
                        throw select;
                    }
                    if (select == 1) {
                        while (1) {
                            cout << endl;
                            cout << "Find Client ID(����ȭ�� : 9) : ";
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
                                        cout << "���� : 1 / ���� : 2 / �ٽð˻� : 3 / ����ȭ�� : 4 : ";
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

void ClientManager::displayInfo(int key){                                                                                // ���ϰ����̵� �Է½� Ui���
    Client* c = search(key);
    cout << endl << "  ID  |     Name     | Phone Number  |    Address    |       E-Mail       |" << endl;
    cout << setw(5) << setfill('0') << right << c->getCid() << " | " << left;
    cout << setw(12) << setfill(' ') << c->getName() << " | ";
    cout << setw(12) << c->getPhoneNumber() << " | ";
    cout << setw(13) << setfill(' ') << c->getAddress() << " | ";
    cout << c->getEmail() << endl << endl;
}

void ClientManager::displayInfoAll_ID() {                                                                               // �����̵�/�̸�/��ȭ��ȣ�� �������
    cout << endl << "  ID  |     Name     | Phone Number  |    Address    |       E-Mail       |" << endl;              // �ߺ��̸��� �������
    for (const auto& v : clientList) {                                                                                  // �������ε� �־ �ڼ��� ��������( �ּ����� ���п� )
        Client* c = v.second;
        cout << setw(5) << setfill('0') << right << c->getCid() << " | " << left;
        cout << setw(12) << setfill(' ') << c->getName() << " | ";
        cout << setw(12) << c->getPhoneNumber() << " | " << endl;
    }
    cout << endl;
}
void ClientManager::displayInfoAll(){                                                                                   // ��ϵ� �� ��ü��� ���
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

void ClientManager::addClient(Client* c){                                       // Client* Ÿ���� value�� �Է¹����� clientList�� ����
    clientList.insert({ c->getCid(), c });
}

void ClientManager::deleteClient(int key){                                      // ���õ� ���� ��ID �Է¹޾� ����
    clientList.erase(key);
    cout << "��ID : " << setw(5) << setfill('0') << right << key << " �� ���� �Ϸ�" << endl << endl;
}

int ClientManager::makeId(){                                                    // 10000������ �����Ͽ� ID ������ �Լ�
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

void ClientManager::modifyClient(int key){                                      // ���� �� ID�Է¹޾� ������ ����Լ�
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

    cout << endl << "  ID  |     Name     | Phone Number  |    Address    |       E-Mail       |" << endl;   // ���� �� Ȯ�ο� ���Ui
    cout << setw(5) << setfill('0') << right << c->getCid() << " | " << left;
    cout << setw(12) << setfill(' ') << c->getName() << " | ";
    cout << setw(12) << c->getPhoneNumber() << " | ";
    cout << setw(13) << setfill(' ') << c->getAddress() << " | ";
    cout << c->getEmail() << endl;
}

void ClientManager::updateClientTotalprice(vector<int>& vec,int totprice) {                 // ���� ���Կ� ����� �� �ݾ� ����
    //vec.at[0] = cid , vec.at[1] = pid , vec.at[2] = productstock , vec.at[3] = price      // �Է¹��� vector ���� ���ڰ� Ȱ�뼳��
    Client* c = search(vec[0]);                                                             
    int getTot = c->getTotalPrice() + totprice;

    c->setTotalPrice(getTot);
}

void ClientManager::wordjudge(int expn) {                                                   // �Է°� ����ó���� �Լ�
    cout << "�߸��� ��ȣ �Է�: " << expn << '\n';
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

vector<string> ClientManager::parseCSV(istream& file, char delimiter)                       // �Լ� ��������½� parsing�� �Լ�
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
            if (c != delimiter) break;                          // ���� ���ǹ� or �������� ���й��ڰ� �ƴ϶�� ����
        }
        else {
            ss << c;
        }
    }
    return row;
}