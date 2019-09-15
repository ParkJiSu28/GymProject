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
	bool achieved(); /*Q2 �Լ�*/
	double diffBMI;//��ǥ BMI ù BMI�� ����.

};

/*trainer class Q2�� Ȱ��*/
class Trainer
{
public:
	string trainerName;
	int achiMemCount;  //��ǥ�޼�ȸ��

};

/*
ȸ�� �������, �̸� ���� class
Q17�� Ȱ��
*/
class memBirthday
{
public:
	int memeberId;
	string name;
	string birthday;
	int birthday_i;
};
/* �������� ���� ���� ȸ���� ���ϱ� ���� class
Q13�� Ȱ��*/
class recentEX {
public:
	string name;
	int recentday;
	int memberId;
};



/*Q2.ȸ���� ��ǥ�� �����ߴ��� �Ǵ��Ͽ� bool������ ��ȯ���ִ� �Լ�*/
bool memberInfo::achieved() {
	if (firstBMI < goalBMI) {//��ü��
		if (goalBMI - currBMI > 0.5) {
			return true;
		}
	}
	else {//��ü��
		if (currBMI - goalBMI > 0.5) {
			return true;
		}
	}
	return false;
}