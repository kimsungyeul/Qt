#include "product.h"

#include <iostream>

using namespace std;
// Product 클래스 생성자 이니셜라이저
Product::Product(int pid, string category, string productname, int price, int productstock)
    : m_pid(pid),m_category(category), m_productname(productname), m_price(price), m_productstock(productstock) {
}

int Product::getPid() const {                           // 제품ID 얻기위한 getter
    return this->m_pid;
}

string Product::getProductCategory() const {            // 제품카테고리 얻기위한 getter
    return this->m_category;
}

void Product::setProductCategory(string& category) {    // 제품카테고리 등록위한 setter
    this->m_category = category;
}

string Product::getProductName() const {                // 제품이름 얻기위한 getter
    return this->m_productname;
}

void Product::setProductName(string& productname) {     // 제품이름 등록위한 setter
    this->m_productname=productname;
}

int Product::getPrice() const {                         // 제품가격 얻기위한 getter
    return this->m_price;
}

void Product::setPrice(int& price) {                     // 제품가격 등록위한 setter
    this->m_price = price;
}

int Product::getProductStock() const {                   // 제품재고 얻기위한 getter
    return this->m_productstock;
}

void Product::setProductStock(int& productstuck) {       // 제품재고 등록위한 setter
    this->m_productstock = productstuck;
}