#include "shoplist.h"

#include <iostream>

using namespace std;
// ShopList 클래스 생성자 이니셜라이저
ShopList::ShopList(int sid, string purchasedate, int cid, int pid, int purchaseamount,int purchaseprice, string discountinfo)
    : m_sid(sid), m_purchasedate(purchasedate), m_cid(cid), m_pid(pid), m_purchaseamount(purchaseamount), m_purchaseprice(purchaseprice), m_discountinfo(discountinfo) {
}

string ShopList::getPurchaseDate() const {                      // 쇼핑날짜 얻기위한 getter
    return this->m_purchasedate;
}

void ShopList::setPurchaseDate(string& purchasedate) {          // 쇼핑날짜 등록위한 setter
    this->m_purchasedate = purchasedate;
}

int ShopList::getPurchaseAmount() const {                       // 구매수량 얻기위한 getter
    return this->m_purchaseamount;
}

void ShopList::setPurchaseAmount(int& purchaseamount) {         // 구매수량 등록위한 setter
    this->m_purchaseamount = purchaseamount;
}

int ShopList::getPurchasePrice() const {                        // 구매가격 얻기위한 getter
    return this->m_purchaseprice;
}

void ShopList::setPurchasePrice(int& purchaseprice) {           // 구매가격 등록위한 setter
    this->m_purchaseprice = purchaseprice;
}

string ShopList::getDiscountInfo() const {                      // 할인정보 얻기위한 getter
    return this->m_discountinfo;
}

void ShopList::setDiscountInfo(string& discountinfo) {          // 할인정보 등록위한 setter
    this->m_discountinfo = discountinfo;
}

int ShopList::getCid() const                                    // 쇼핑에등록된 Cid얻기위한 getter
{
    return this->m_cid;
}

int ShopList::getPid() const                                    // 쇼핑에등록된 Pid얻기위한 getter
{
    return this->m_pid;
}

int ShopList::getSid() const                                    // 쇼핑ID 얻기위한 getter
{
    return this->m_sid;
}