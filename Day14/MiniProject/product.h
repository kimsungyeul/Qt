#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <iostream>

using namespace std;

class Product {
public:
	// Product 클래스 생성자
	Product(int pid, string category, string productname, int price, int stock);

	int getPid() const;						// 제품ID 얻기위한 getter
	string getProductCategory() const;		// 제품카테고리 얻기위한 getter
	void setProductCategory(string&);		// 제품카테고리 등록위한 setter
	string getProductName() const;			// 제품이름 얻기위한 getter
	void setProductName(string&);			// 제품이름 등록위한 setter
	int getPrice() const;					// 제품가격 얻기위한 getter
	void setPrice(int&);					// 제품가격 등록위한 setter
	int getProductStock() const;			// 제품재고 얻기위한 getter
	void setProductStock(int&);				// 제품재고 등록위한 setter

private:
	int m_pid;					// 제품ID 멤버변수
	string m_category;			// 제품카테고리 멤버변수
	string m_productname;		// 제품이름 멤버변수
	int m_price;				// 제품가격 멤버변수
	int m_productstock;			// 제품재고 멤버변수
};
#endif          // __PRODUCT_H__