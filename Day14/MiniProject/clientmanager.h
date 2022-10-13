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
    ClientManager();                                        // ������ ������ clientlist.txt�� ������ ��������
    ~ClientManager();                                       // �Ҹ��ڰ� �ҷ����� clientlist.txt�� ������ �Է��ϱ�

    void inputClient();                                     // �� ��Ͽ� �Լ�
    Client* search(int);                                    // ��ID �Է½� Client*Ÿ�Կ� ��ü�� ���
    int PriceSearch(int);                                   // ��ID�Է¹޾� ���̻���� �� �ݾװ����
    float PriceClient_All();                                  // ��ü���� �Ҹ��� ��ü�ݾ� ���
    set<int> findCidList();                                 // ���ΰ��� -> ���ΰ˻� -> ID��ü��� �˻��� set�����̳ʿ� ������ �ߺ������� ��� 

    int findbyId(int);                                      // �����̵� �Է¹޾� ������Ʈ�� ������ id��ȯ / ������ 0��ȯ
    vector<int> findbyMulId(int);                           // ��id�� �Է¹޾� ������Ʈ�� �ִ��� Ȯ�ο� �Լ�(�ִٸ� vec�� ������ ��ȯ)
    void findbyMulName(vector<int>&,string);                // findClientByName (������ �̸� �˻�)
    int findbyMulCID_Sel(vector<int>&);                     // findClientByName�� ���(�̸� ���ÿ�)

    void reference();                                       // ��ϵ� ���˻���
    void displayInfo(int);                                  // ���ϰ����̵� �Է½� Ui���
    void displayInfoAll_ID();                               // �����̵�/�̸�/��ȭ��ȣ�� �������
    void displayInfoAll();                                  // ��ϵ� �� ��ü��� ���

    void addClient(Client*);                                // Client* Ÿ���� value�� �Է¹����� clientList�� ����
    void deleteClient(int);                                 // ���õ� ���� ��ID �Է¹޾� ����
    int makeId();                                           // 10000������ �����Ͽ� ID ������ �Լ�
    void modifyClient(int);                                 // ���� �� ID�Է¹޾� ������ ����Լ�
    void updateClientTotalprice(vector<int>&,int);          // ���� ���Կ� ����� �� �ݾ� ����

    void wordjudge(int);                                    // �Է°� ����ó���� �Լ�
    vector<string> parseCSV(istream&, char);                // �Լ� ��������½� parsing�� �Լ�

private:
    map<int, Client*> clientList;                           // �Է¹��� ������Ʈkey �� value ����� map�����̳�                           
};