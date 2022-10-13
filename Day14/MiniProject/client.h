#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <iostream>

using namespace std;

class Client {
public:
	// Client 클래스 생성자
	Client(int id, string name, string phonenumber, string address, string email, int totalprice=0, string gradeInfo="");

	string getName() const;					// 이름을 얻기위한 getter
	void setName(string&);					// 이름 등록위한 setter
	string getPhoneNumber() const;			// 전화번호 얻기위한 getter
	void setPhoneNumber(string&);			// 전화번호 등록위한 setter
	string getAddress() const;				// 주소 얻기위한 getter
	void setAddress(string&);				// 주소 등록위한 setter
	string getEmail() const;				// 이메일 얻기위한 getter
	void setEmail(string&);					// 이메일 등록위한 setter
	int getTotalPrice() const;				// 총액 얻기위한 getter
	void setTotalPrice(int&);				// 총액 등록위한 setter
	string getGrade();						// 등급 얻기위한 getter
	void setGrade(string&);					// 등급 등록위한 setter
	int getCid() const;						// 고객ID 얻기위한 getter

	//used in STL Find function
	bool operator==(int) const;			    // int용 ==연산자 오퍼레이터 생성
	bool operator==(string) const;		    // string용 == 연산자 오퍼레이터 생성

private:
	int m_id;					// 고객ID 멤버변수
	string m_name;				// 고객이름 멤버변수
	string m_phoneNumber;		// 고객번호 멤버변수
	string m_address;			// 고객주소 멤버변수
	string m_email;				// 고객이메일 멤버변수
	int m_totalprice;			// 고객총액 멤버변수
	string m_grade;				// 고객등급 멤버변수
};
#endif          // __CLIENT_H__