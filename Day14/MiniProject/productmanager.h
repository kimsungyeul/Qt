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
    ProductManager();                                   // ������ ������ productList.txt�� ������ ��������
    ~ProductManager();                                  // �Ҹ��ڰ� �ҷ����� productList.txt�� ������ �Է��ϱ�

    void inputProduct();                                // ��ǰ��Ͽ� ����Լ�
    Product* Psearch(int);                              // ��ǰID �Է½� Product*Ÿ�Կ� ��ü�� ���
    set<int> findPidList();                             // ��ǰID�� �Է¹޾� ��ǰ����Ʈ�� ������ id��ȯ / ������ 0��ȯ
    int findbyPid(int);                                 // ��ǰID�� �Է¹޾� ��ϵ��ִ��� Ȯ�ο� ����Լ�
    vector<int> findbyMulPid(int);                      // ��ǰID�� �Է¹޾� ��ǰ����Ʈ�� �ִ��� Ȯ�ο� �Լ�(�ִٸ� vec�� ������ ��ȯ)
    void findbyMulPname(vector<int>&, string);          // selectProductList,find_Shop_Product_ByName�Լ� �� ������ǰã��

    int findStockbyPid(int);                            // ��ǰ ID �Է¹޾� productList �� ��ǰ����ϵ� ��� ��¿� �Լ�
    int findPricebyPid(int);                            // ��ǰ ID �Է¹޾� productList �� ��ǰ����ϵ� ���� ��¿� �Լ�

    void referenceP();                                  // ��ϵ� ��ǰ�˻�/����/������ ����Լ�
    void displayPinfo(int);                             // ������ǰID �Է¹޾� ������ǰ������� Ui
    void displayPinfoAll();                             // ��� ��ǰ ��¿� Ui

    void addProduct(Product*);                          // Product* Ÿ���� value�� �Է¹����� productList�� ����
    void deleteProduct(int);                            // ���õ� ���� ��ǰID �Է¹޾� ����
    int makePid();                                      // 50000������ �����Ͽ� ��ǰID ������ �Լ�
    
    void modifyProduct(int);                            // ���� �� ID�Է¹޾� ������ ����Լ�
    void updateProductStock(vector<int>&);              // ������ ��� ������Ʈ�� �Լ�

    void wordjudgeP(int);                               // �Է°� ����ó���� �Լ�
    vector<string> parseCSV(istream&, char);            // �Լ� ��������½� parsing�� �Լ�
private:
    map<int, Product*> productList;                     // �Է¹��� ��ǰ����Ʈkey �� value ����� map�����̳�
};