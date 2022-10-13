#include "productmanager.h"

ProductManager::ProductManager() {                                                // ������ ������ productList.txt�� ������ ��������
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

ProductManager::~ProductManager()                                                   // �Ҹ��ڰ� �ҷ����� productList.txt�� ������ �Է��ϱ�
{
    ofstream file;
    file.open("productList.txt");                                                   // map�����̳ʷ� �ۼ��� ��ü productList ������ file�� ����
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

void ProductManager::inputProduct() {                                               // ��ǰ��Ͽ� ����Լ�
    string productcategory,productname;
    int price, productstuck;

    cout << "category : "; cin >> productcategory;                                  // ��ǰ ī�װ��Է�
    cout << "name : "; cin >> productname;                                          // ��ǰ �̸��Է�
    cout << "price : "; cin >> price;                                               // ��ǰ �����Է�
    cout << "productstuck : "; cin >> productstuck;                                 // ��ǰ ����Է�
    cout << endl;

    int pid = makePid();                                                            // key�� ����
    Product* p = new Product(pid, productcategory,productname,price,productstuck);
    productList.insert({ pid, p });                                                 // ������ key���� Product*Ÿ���� value���� productList������ 
}

Product* ProductManager::Psearch(int pid)                                           // ��ǰID �Է½� Product*Ÿ�Կ� ��ü�� ���
{
    return productList[pid];
}

set<int> ProductManager::findPidList() {                                            // ��ǰid�� �Է¹޾� ��ǰ����Ʈ�� ������ id��ȯ / ������ 0��ȯ
    set<int> setP;
    for (const auto& v : productList) {
        int p = v.first;
        setP.insert(p);
    }
    return setP;
}

int ProductManager::findbyPid(int pid) {                                            // ��ǰID�� �Է¹޾� ��ϵ��ִ��� Ȯ�ο� ����Լ�
    if (!cin || (productList.find(pid) != productList.end())) {
        return pid;
    }
    else {
        return 0;
    }
}

vector<int> ProductManager::findbyMulPid(int pid) {                                 // ��ǰid�� �Է¹޾� ��ǰ����Ʈ�� �ִ��� Ȯ�ο� �Լ�(�ִٸ� vec�� ������ ��ȯ)
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

void ProductManager::findbyMulPname(vector<int>& vec, string name) {                // selectProductList,find_Shop_Product_ByName�Լ� �� ������ǰã��
    int cnt = 0;                                                                    // ��ǰ�����ϱ����� ��ǰ�̸��� ���
    cout << endl << "    PID  |   Category   |     Name     |" << endl;             // ������ �ߺ��̸� ���� ���
    for (const auto& v : productList) {
        Product* p = v.second;
        if (p->getProductName() == name) {                                          // �˻��̸��� �����ϸ�
            vec.emplace_back(p->getPid());                                          // vec�� PID���� �� ������� ������
            cout << ++cnt << ". ";
            cout << setw(5) << setfill('0') << right << p->getPid() << " | " << left;
            cout << setw(12) << setfill(' ') << p->getProductCategory() << " | ";
            cout << setw(12) << p->getProductName() << endl;
        }
    }
}

int ProductManager::findStockbyPid(int pid) {                       // ��ǰ ID �Է¹޾� productList �� ��ǰ����ϵ� ��� ��¿� �Լ�
    return productList[pid]->getProductStock();
}

int ProductManager::findPricebyPid(int pid) {                       // ��ǰ ID �Է¹޾� productList �� ��ǰ����ϵ� ���� ��¿� �Լ�
    return productList[pid]->getPrice();
}

void ProductManager::referenceP() {                                 // ��ϵ� ��ǰ�˻�/����/������ ����Լ�

    int select = 0;                     // Ui���ÿ� ���� 
    int select_ID = 0;                  // ID ����/����/����ȭ��/ó��ȭ��� ����
    int find_id = 0;                    // ��ǰ ID ã��� ����
    string find_name;                   // �̸����� ã��� ����
    vector<int> vec;                    // �̸��Է¹޾� ������ǰID ����� vector

    while (select != 9) {
        cout << "1.��ǰ�̸��˻�(����ȭ�� : 9) : ";
        cin >> find_name;
        if (find_name == "9") {
END:
            return;
        }
        findbyMulPname(vec,find_name);
        if (vec.size() == 0) {
            cout << "�˻� ����� �����ϴ�." << endl << endl;
        }
        else {
            cout << "�� " << vec.size() << "���� �˻�" << endl << endl;
            do {
                try {
                    cout << "ID�˻�/����/���� : 1 / �ٽð˻� : 2 / ����ȭ�� : 3 : ";
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
                        while (1) {                             // ��ǰ ID�� �Է¹ޱ��
                            try {
                                cout << endl;
                                cout << "Find Product ID(����ȭ�� : 9) : ";
                                cin >> find_id;
                                if (find_id == 9) {
                                    return;
                                }
                                if (!cin || productList.find(find_id) == productList.end()) {
                                    throw find_id;
                                }
                                displayPinfo(find_id);
                                while (1) {                     // ����/����/�ٽð˻�/����ȭ�� ����
                                    try {
                                        cout << "���� : 1 / ���� : 2 / �ٽð˻� : 3 / ����ȭ�� : 4 : ";
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

void ProductManager::displayPinfo(int key) {                        // ������ǰID �Է¹޾� ������ǰ������� Ui
    Product* p = Psearch(key);
    cout << endl << "  PID |   Category   |     Name     |     Price    |     Stuck     |" << endl;
    cout << setw(5) << p->getPid() << " | " << left;
    cout << setw(12) << setfill(' ') << p->getProductCategory() << " | ";
    cout << setw(12) << setfill(' ') << p->getProductName() << " | ";
    cout << setw(12) << p->getPrice() << " | ";
    cout << p->getProductStock() << endl << endl;
}

void ProductManager::displayPinfoAll() {                            // ��� ��ǰ ��¿� Ui
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

void ProductManager::addProduct(Product* p) {                       // Product* Ÿ���� value�� �Է¹����� productList�� ����
    productList.insert({ p->getPid(), p });
}

void ProductManager::deleteProduct(int key) {                       // ���õ� ���� ��ǰID �Է¹޾� ����
    productList.erase(key);
    cout << "��ǰID : " << setw(5) << setfill('0') << right << key << " �� ���� �Ϸ�" << endl << endl;
}

int ProductManager::makePid() {                                     // 50000������ �����Ͽ� ��ǰID ������ �Լ�
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

void ProductManager::modifyProduct(int key) {                                           // ���� �� ID�Է¹޾� ������ ����Լ�
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

    cout << endl << "  PID |   Category   |     Name     |     Price    |     Stuck     |" << endl;     // ���� �� Ȯ�ο� ���Ui
    cout << setw(5) <<  p->getPid() << " | " << left;
    cout << setw(12) << setfill(' ') << p->getProductCategory() << " | ";
    cout << setw(12) << setfill(' ') << p->getProductName() << " | ";
    cout << setw(12) << p->getPrice() << " | ";
    cout << p->getProductStock() << endl;
}

void ProductManager::updateProductStock(vector<int>& vec) {                                 // ������ ��� ������Ʈ�� �Լ�
    //vec.at[0] = cid , vec.at[1] = pid , vec.at[2] = productstock , vec.at[3] = price      // �Է¹��� vector ���� ���ڰ� Ȱ�뼳��
    Product* p = Psearch(vec[1]);

    p->setProductStock(vec[2]);
}

void ProductManager::wordjudgeP(int expn) {                             // �Է°� ����ó���� �Լ�
    cout << "�߸��� ��ȣ �Է�: " << expn << '\n';
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

vector<string> ProductManager::parseCSV(istream& file, char delimiter)  // �Լ� ��������½� parsing�� �Լ�
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while (!file.eof()) {
        char c = file.get();                                // ���ϳ��� �ѱ��ھ� ������
        if (c == delimiter || c == '\r' || c == '\n') {     // �����Ǻ���
            if (file.peek() == '\n') file.get();            // ���� ����� �Է¹ް� 
            string s = ss.str();                            // stringstreamȰ���� ���ڿ��ޱ�
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break;                      // ���� ���ǹ� or �������� ���й��ڰ� �ƴ϶�� ����
        }
        else {
            ss << c;
        }
    }
    return row;
}