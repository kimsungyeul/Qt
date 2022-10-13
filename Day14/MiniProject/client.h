#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <iostream>

using namespace std;

class Client {
public:
	// Client Ŭ���� ������
	Client(int id, string name, string phonenumber, string address, string email, int totalprice=0, string gradeInfo="");

	string getName() const;					// �̸��� ������� getter
	void setName(string&);					// �̸� ������� setter
	string getPhoneNumber() const;			// ��ȭ��ȣ ������� getter
	void setPhoneNumber(string&);			// ��ȭ��ȣ ������� setter
	string getAddress() const;				// �ּ� ������� getter
	void setAddress(string&);				// �ּ� ������� setter
	string getEmail() const;				// �̸��� ������� getter
	void setEmail(string&);					// �̸��� ������� setter
	int getTotalPrice() const;				// �Ѿ� ������� getter
	void setTotalPrice(int&);				// �Ѿ� ������� setter
	string getGrade();						// ��� ������� getter
	void setGrade(string&);					// ��� ������� setter
	int getCid() const;						// ��ID ������� getter

	//used in STL Find function
	bool operator==(int) const;			    // int�� ==������ ���۷����� ����
	bool operator==(string) const;		    // string�� == ������ ���۷����� ����

private:
	int m_id;					// ��ID �������
	string m_name;				// ���̸� �������
	string m_phoneNumber;		// ����ȣ �������
	string m_address;			// ���ּ� �������
	string m_email;				// ���̸��� �������
	int m_totalprice;			// ���Ѿ� �������
	string m_grade;				// ����� �������
};
#endif          // __CLIENT_H__