#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include<map>
#include<queue>
#include<algorithm>
#include<time.h>
#include <functional>
#include<cmath>
#pragma warning(disable:4996)
using namespace std;


class memberInfo
{
public:
	int memberId;
	string name;
	string address;
	string phoneNum;
	string recMember;
	string birthDay;
	string package;
	string isPT;
	string trainerName;
	double firstBMI;
	double currBMI;
	double goalBMI;
	string lockNum;
	string first_Register;
	int totalExCount;
	int totalPTCount;
	string recentExDay;
	string expiredDate;
	bool achieved(); /*Q2 함수*/
	double diffBMI;//목표 BMI 첫 BMI차 절댓값.

};

/*trainer class Q2에 활용*/
class Trainer
{
public:
	string trainerName;
	int achiMemCount;  //목표달성회원

};

/*
회원 생년월일, 이름 저장 class
Q17의 활용
*/
class memBirthday
{
public:
	int memeberId;
	string name;
	string birthday;
	int birthday_i;
};
/* 오랫동안 오지 않은 회원을 구하기 위한 class
Q13에 활용*/
class recentEX {
public:
	string name;
	int recentday;
	int memberId;
};



/*Q2.회원이 목표를 성취했는지 판단하여 bool형으로 반환해주는 함수*/
bool memberInfo::achieved() {
	if (firstBMI < goalBMI) {//저체중
		if (goalBMI - currBMI > 0.5) {
			return true;
		}
	}
	else {//과체중
		if (currBMI - goalBMI > 0.5) {
			return true;
		}
	}
	return false;
}