#include "product.h"

#include <iostream>

using namespace std;
// Product Ŭ���� ������ �̴ϼȶ�����
Product::Product(int pid, string category, string productname, int price, int productstock)
    : m_pid(pid),m_category(category), m_productname(productname), m_price(price), m_productstock(productstock) {
}

int Product::getPid() const {                           // ��ǰID ������� getter
    return this->m_pid;
}

string Product::getProductCategory() const {            // ��ǰī�װ� ������� getter
    return this->m_category;
}

void Product::setProductCategory(string& category) {    // ��ǰī�װ� ������� setter
    this->m_category = category;
}

string Product::getProductName() const {                // ��ǰ�̸� ������� getter
    return this->m_productname;
}

void Product::setProductName(string& productname) {     // ��ǰ�̸� ������� setter
    this->m_productname=productname;
}

int Product::getPrice() const {                         // ��ǰ���� ������� getter
    return this->m_price;
}

void Product::setPrice(int& price) {                     // ��ǰ���� ������� setter
    this->m_price = price;
}

int Product::getProductStock() const {                   // ��ǰ��� ������� getter
    return this->m_productstock;
}

void Product::setProductStock(int& productstuck) {       // ��ǰ��� ������� setter
    this->m_productstock = productstuck;
}