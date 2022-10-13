#if 1
#include "client.h"

#include <iostream>

using namespace std;

// Client 클래스 생성자 이니셜라이저
Client::Client(int id, string name, string phoneNumber, string address, string email, int totalprice, string grade)
    : m_id(id), m_name(name), m_phoneNumber(phoneNumber), m_address(address), m_email(email), m_totalprice(totalprice), m_grade(grade){
}

string Client::getName() const                       // 이름을 얻기위한 getter
{
    return this->m_name;
}

void Client::setName(string& name)                  // 이름 등록위한 setter
{
    this->m_name = name;
}

string Client::getPhoneNumber() const               // 전화번호 얻기위한 getter
{
    return this->m_phoneNumber;
}

void Client::setPhoneNumber(string& phoneNumber)    // 전화번호 등록위한 setter
{
   this-> m_phoneNumber = phoneNumber;
}

string Client::getAddress() const                   // 주소 얻기위한 getter
{
    return this->m_address;
}

void Client::setAddress(string& address)            // 주소 등록위한 setter
{
    this->m_address = address;
}

string Client::getEmail() const                     // 이메일 얻기위한 getter
{
    return this->m_email;
}

void Client::setEmail(string& email)                // 이메일 등록위한 setter
{
    this->m_email = email;
}

int Client::getTotalPrice() const {                 // 총액 얻기위한 getter
    return this->m_totalprice;
}

void Client::setTotalPrice(int& totalprice) {       // 총액 등록위한 setter
    this->m_totalprice = totalprice;
}

string Client::getGrade() {                         // 등급 얻기위한 getter
    return this->m_grade;
}

void Client::setGrade(string& grade) {              // 등급 등록위한 setter
    this->m_grade = grade;
}

int Client::getCid() const                          // 고객ID 얻기위한 getter
{
    return this->m_id;
}

bool Client::operator==(int id) const               // int용 ==연산자 오퍼레이터 생성
{
    return (this->m_id == id);
}

bool Client::operator==(string str) const           // string용 == 연산자 오퍼레이터 생성
{
    return (this->m_name == str);
}
#endif