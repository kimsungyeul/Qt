#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include <iostream>

using namespace std;

class Product {
public:
	// Product Ŭ���� ������
	Product(int pid, string category, string productname, int price, int stock);

	int getPid() const;						// ��ǰID ������� getter
	string getProductCategory() const;		// ��ǰī�װ� ������� getter
	void setProductCategory(string&);		// ��ǰī�װ� ������� setter
	string getProductName() const;			// ��ǰ�̸� ������� getter
	void setProductName(string&);			// ��ǰ�̸� ������� setter
	int getPrice() const;					// ��ǰ���� ������� getter
	void setPrice(int&);					// ��ǰ���� ������� setter
	int getProductStock() const;			// ��ǰ��� ������� getter
	void setProductStock(int&);				// ��ǰ��� ������� setter

private:
	int m_pid;					// ��ǰID �������
	string m_category;			// ��ǰī�װ� �������
	string m_productname;		// ��ǰ�̸� �������
	int m_price;				// ��ǰ���� �������
	int m_productstock;			// ��ǰ��� �������
};
#endif          // __PRODUCT_H__