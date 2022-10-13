#include "shoplist.h"

#include <iostream>

using namespace std;
// ShopList Ŭ���� ������ �̴ϼȶ�����
ShopList::ShopList(int sid, string purchasedate, int cid, int pid, int purchaseamount,int purchaseprice, string discountinfo)
    : m_sid(sid), m_purchasedate(purchasedate), m_cid(cid), m_pid(pid), m_purchaseamount(purchaseamount), m_purchaseprice(purchaseprice), m_discountinfo(discountinfo) {
}

string ShopList::getPurchaseDate() const {                      // ���γ�¥ ������� getter
    return this->m_purchasedate;
}

void ShopList::setPurchaseDate(string& purchasedate) {          // ���γ�¥ ������� setter
    this->m_purchasedate = purchasedate;
}

int ShopList::getPurchaseAmount() const {                       // ���ż��� ������� getter
    return this->m_purchaseamount;
}

void ShopList::setPurchaseAmount(int& purchaseamount) {         // ���ż��� ������� setter
    this->m_purchaseamount = purchaseamount;
}

int ShopList::getPurchasePrice() const {                        // ���Ű��� ������� getter
    return this->m_purchaseprice;
}

void ShopList::setPurchasePrice(int& purchaseprice) {           // ���Ű��� ������� setter
    this->m_purchaseprice = purchaseprice;
}

string ShopList::getDiscountInfo() const {                      // �������� ������� getter
    return this->m_discountinfo;
}

void ShopList::setDiscountInfo(string& discountinfo) {          // �������� ������� setter
    this->m_discountinfo = discountinfo;
}

int ShopList::getCid() const                                    // ���ο���ϵ� Cid������� getter
{
    return this->m_cid;
}

int ShopList::getPid() const                                    // ���ο���ϵ� Pid������� getter
{
    return this->m_pid;
}

int ShopList::getSid() const                                    // ����ID ������� getter
{
    return this->m_sid;
}