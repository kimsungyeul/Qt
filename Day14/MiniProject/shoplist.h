#ifndef __SHOPLIST_H__
#define __SHOPLIST_H__

#include <iostream>

using namespace std;

class ShopList {
public:
	// ShopList 클래스 생성자 이니셜라이저
	ShopList(int sid, string purchasedate, int cid, int pid, int purchaseamount, int purchaseprice, string discountinfo = "");
	
	string getPurchaseDate() const;		// 쇼핑날짜 얻기위한 getter
	void setPurchaseDate(string&);		// 쇼핑날짜 등록위한 setter

	int getPurchaseAmount() const;		// 구매수량 얻기위한 getter
	void setPurchaseAmount(int&);		// 구매수량 등록위한 setter
	int getPurchasePrice() const;		// 구매가격 얻기위한 getter
	void setPurchasePrice(int&);		// 구매가격 등록위한 setter
	string getDiscountInfo() const;		// 할인정보 얻기위한 getter
	void setDiscountInfo(string&);		// 할인정보 등록위한 setter
	int getCid() const;					// 쇼핑에등록된 Cid얻기위한 getter
	int getPid() const;					// 쇼핑에등록된 Pid얻기위한 getter
	int getSid() const;					// 쇼핑ID 얻기위한 getter
private:
	int m_sid;					// 쇼핑ID 멤버변수
	string m_purchasedate;		// 구매날짜 멤버변수
	int m_cid;					// 쇼핑에등록된 고객ID 멤버변수
	int m_pid;					// 쇼핑에등록된 제품 ID 멤버변수
	int m_purchaseamount;		// 구매수량 멤버변수
	int m_purchaseprice;		// 구매가격 멤버변수
	string m_discountinfo;		// 할인정보 멤버변수
};
#endif          // __SHOPLIST_H__