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
    ShopListManager();                              // ������ ������ clientlist.txt�� ������ ��������
    ~ShopListManager();                             // �Ҹ��ڰ� �ҷ����� shopList.txt�� ������ �Է��ϱ�
    
    int inputShopList(vector<int>&);                // ���� ��ǰ�� ������ ��� �Է�
    ShopList* Ssearch(int);                         // ����ID�� �޾� ShopListŸ�Կ� ����value ���
    vector<int> SCsearch(int);                      // ���ϰ����̵� �̿� ���γ� �����Ѱ���� ��������
    vector<int> SPsearch(int);                      // ��ǰ���̵� �̿� ���γ� ������ ����� ��������
                         
    int findbySid(int);                             // ���θ�� �� ���� SID �˻�
    vector<int> findMulSLbyCid(int);                // ���Է¹޾� ���̼����� SID���
    vector<int> findMulSLbyPid(int);                // ���θ�� �� ������ ��ǰ���̵� �˻�
    vector<int> findbyMulSLSid(int);                // ���θ�� �� ������ ���ξ��̵� �˻�(������X)
    int findbyMulSLID_Sel(vector<int>&);            // ���õ� SID���͸� �Է¹޾� ��ȣ(1,2,3,4...)�� ������ ���
    
    void displaySinfoSingle(int);                   // ����SID�Է¹޾� SID���� ���
    void displaySMinfo(vector<int>&);               // �������� ����ID�Է¹޾� ���
    void displaySinfoAll_Cid(int);                  // Cid �Է¹޾� ���� ����� �������� ���� ���
    void displaySinfoAll();                         // ��ϵ� ���� ��ü��� ���
    void displayIDinforA(int);                      // ���ΰ˻� -> ID�ΰ˻� -> �� �κк� ID��� �ߺ������� ���

    void addShopList(ShopList*);                    // ShopList* Ÿ���� value�� �Է¹����� shopList�� ����
    void deleteShopList(int);                       // ���õ� ���� ����ID �Է¹޾� ����            
    int makeSid();                                  // 0������ �����Ͽ� ID ������ �Լ�

    void modifyShopList(int);                       // �Էµ� ����ID���޾� ���ŷ��� �����ǵ����ϴ� ����Լ�
    const string CurrentTime();                     // ���� ��ǻ�� ���� ������ ��¥/�ð� ������ ���
    void wordjudgeS(int);                           // �Է°� ����ó���� �Լ�
    vector<string> parseCSV(istream&, char);        // �Լ� ��������½� parsing�� �Լ�

private:
    map<int, ShopList*> shopList;                   // �Է¹��� ���θ���Ʈkey �� value ����� map�����̳�
};