#ifndef __SHOPLIST_H__
#define __SHOPLIST_H__

#include <iostream>

using namespace std;

class ShopList {
public:
	// ShopList Ŭ���� ������ �̴ϼȶ�����
	ShopList(int sid, string purchasedate, int cid, int pid, int purchaseamount, int purchaseprice, string discountinfo = "");
	
	string getPurchaseDate() const;		// ���γ�¥ ������� getter
	void setPurchaseDate(string&);		// ���γ�¥ ������� setter

	int getPurchaseAmount() const;		// ���ż��� ������� getter
	void setPurchaseAmount(int&);		// ���ż��� ������� setter
	int getPurchasePrice() const;		// ���Ű��� ������� getter
	void setPurchasePrice(int&);		// ���Ű��� ������� setter
	string getDiscountInfo() const;		// �������� ������� getter
	void setDiscountInfo(string&);		// �������� ������� setter
	int getCid() const;					// ���ο���ϵ� Cid������� getter
	int getPid() const;					// ���ο���ϵ� Pid������� getter
	int getSid() const;					// ����ID ������� getter
private:
	int m_sid;					// ����ID �������
	string m_purchasedate;		// ���ų�¥ �������
	int m_cid;					// ���ο���ϵ� ��ID �������
	int m_pid;					// ���ο���ϵ� ��ǰ ID �������
	int m_purchaseamount;		// ���ż��� �������
	int m_purchaseprice;		// ���Ű��� �������
	string m_discountinfo;		// �������� �������
};
#endif          // __SHOPLIST_H__