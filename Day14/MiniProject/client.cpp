#if 1
#include "client.h"

#include <iostream>

using namespace std;

// Client Ŭ���� ������ �̴ϼȶ�����
Client::Client(int id, string name, string phoneNumber, string address, string email, int totalprice, string grade)
    : m_id(id), m_name(name), m_phoneNumber(phoneNumber), m_address(address), m_email(email), m_totalprice(totalprice), m_grade(grade){
}

string Client::getName() const                       // �̸��� ������� getter
{
    return this->m_name;
}

void Client::setName(string& name)                  // �̸� ������� setter
{
    this->m_name = name;
}

string Client::getPhoneNumber() const               // ��ȭ��ȣ ������� getter
{
    return this->m_phoneNumber;
}

void Client::setPhoneNumber(string& phoneNumber)    // ��ȭ��ȣ ������� setter
{
   this-> m_phoneNumber = phoneNumber;
}

string Client::getAddress() const                   // �ּ� ������� getter
{
    return this->m_address;
}

void Client::setAddress(string& address)            // �ּ� ������� setter
{
    this->m_address = address;
}

string Client::getEmail() const                     // �̸��� ������� getter
{
    return this->m_email;
}

void Client::setEmail(string& email)                // �̸��� ������� setter
{
    this->m_email = email;
}

int Client::getTotalPrice() const {                 // �Ѿ� ������� getter
    return this->m_totalprice;
}

void Client::setTotalPrice(int& totalprice) {       // �Ѿ� ������� setter
    this->m_totalprice = totalprice;
}

string Client::getGrade() {                         // ��� ������� getter
    return this->m_grade;
}

void Client::setGrade(string& grade) {              // ��� ������� setter
    this->m_grade = grade;
}

int Client::getCid() const                          // ��ID ������� getter
{
    return this->m_id;
}

bool Client::operator==(int id) const               // int�� ==������ ���۷����� ����
{
    return (this->m_id == id);
}

bool Client::operator==(string str) const           // string�� == ������ ���۷����� ����
{
    return (this->m_name == str);
}
#endif