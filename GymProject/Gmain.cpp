#include "gym.h"


/* ȸ�������� ��� �ִ� ���� ���� m�� iterator*/
vector<memberInfo>m;
vector<memberInfo>::iterator iter;

/* trainer class�� ������ ��� �ִ� vector*/
vector<Trainer>trainer;

/*Ʈ���̳��� ������ top�� �Ǻ��ϱ� ���� �켱����ť*/
priority_queue<Trainer>trainerPQ;

/*���� ���� ������ ��� �ִ� ���� ���� dong�� iterator*/
map<string,int>dong;
map<string, int>::iterator d_iter;


/*Ʈ���̳ʿ� ���� ������ ��� �ִ� �������� trainer_map�� iterator */
map<string, int>trainer_map;
map<string, int>::iterator t_iter;

/* map�� value�� �����ϱ� ���� template�Լ� ���ؼ� true/false�� ��ȯ*/
template<template <typename> class P = less >
struct compare_pair_second {

	template<class T1, class T2> bool operator()(const pair<T1, T2>&left, 
		const pair<T1, T2>&right) {

		return P<T2>()(left.second, right.second);

	}

};

/*1~12���� �ش��ϴ� �����迭 ����*/
int month[12];

/*������� ���� ���� �� �켱���� ť.*/
priority_queue<int, vector<int>, less<int>> max_monthPQ;

/*������� ���� ���� �� �켱���� ť.*/
priority_queue<int, vector<int>, greater<int>>min_monthPQ;

/*���� �������� ���� ���� ȸ���� ���� ������ ���� vector*/
vector<recentEX>recentex;

/*���� �������� ���� ���� ȸ���� Max_heap�� ����� ���� heap*/
priority_queue<recentEX>latememMinH;

/*� ��ǥ�� ���� ȸ���� Max_heap�� ����� ���� heap*/
priority_queue<memberInfo>bmiMaxH;

/*Q1 �� �ذ��ϱ� ���� map�� Ȱ���ؼ� ���*/
void max_trainer() {
	for (iter = m.begin(); iter != m.end(); iter++) {
		if (trainer_map.find(iter->trainerName) == trainer_map.end())
			trainer_map.insert(make_pair(iter->trainerName, 1));
		else {
			trainer_map[iter->trainerName]++;
		}
	}
	vector<pair<string, int> > vec(trainer_map.begin(), trainer_map.end());
	sort(vec.begin(), vec.end(), compare_pair_second<less>());
	cout << "Q1. ���� ȸ���� ���� Ȯ���� Ʈ���̳ʴ�?\n\n";
	string temp = vec.back().first;
	string except = "-";
	if (temp == except) {
		vec.pop_back();
		cout << "Answer : " << "���� ȸ���� ���� Ȯ���� Ʈ���̳ʴ�? : " << vec.back().first << "   ȸ����: " << vec.back().second << endl;
	}
	else {
		cout << "Answer : " << "���� ȸ���� ���� Ȯ���� Ʈ���̳ʴ�? : " << vec.back().first << "   ȸ����: " << vec.back().second << endl;
	}
}


/* Q2
trainer vector�� ���뿩�θ� �Ǻ��Ͽ� ������ �����ϴ� �Լ� 
1. PT�� �޴� ȸ�������� ����
2.vector�� empty�϶��� ó�� ������ �����͸� ���뿩�θ� �Ǵ��Ͽ� ����
// linear Search�� ����Ͽ� vector�� Ž���Ѵ�.
2.Ʈ���̳ʰ� vector�� ���ٸ� ������ ȸ���� �ִ� �� �Ǻ��Ͽ� achiMemCount�� 1������Ű�� Ʈ���̳� �̸��� vector�� ����
3.�̹� vector�� �ִ� Ʈ���̳��̰� ȸ���� ��ǥ�� �޼��ߴٸ� achiMemCount�� 1���� ��Ų��.*/
void put_trainer_vector(memberInfo temp) {
	if (temp.isPT == "Y") {
		if (trainer.empty()) {//Ʈ���̳� ���Ͱ� ��Ƽ�̸�
			Trainer t;
			t.trainerName = temp.trainerName;
			t.achiMemCount = 0;
			if (temp.achieved() == true) {
				t.achiMemCount++;
			}
			//���� ä���ֱ�
			trainer.push_back(t);
		}
		else {//��Ƽ�� �ƴϸ�
			bool check = false;
			for (int i = 0; i < trainer.size(); i++) {//linear search�� �� Ʈ���̳ʿ� �̸��� ���� Ʈ���̳ʰ� �ִ��� ã�´�.
				if (trainer[i].trainerName == temp.trainerName) {//�̸��� ���� Ʈ���̳ʰ� ������
					check = true;
					if (temp.achieved() == true) {//���� ��ǥ�� ���������� Ʈ���̳��� ������ +1���Ͽ� ������ �ش�.
						trainer[i].achiMemCount++;
					}
				}
			}
			if (!check) {//�� Ʈ���̳ʿ� �̸��� ���� Ʈ���̳ʰ� ������
				Trainer t;
				t.trainerName = temp.trainerName;
				t.achiMemCount = 0;
				if (temp.achieved() == true) {//���뿩�� �Ǵ��ϰ�
					t.achiMemCount++;
				}
				trainer.push_back(t);//Ʈ���̳� ���Ϳ� �־��ش�.
			}
		}
	}
}

/*�켱����ť�� ������ ���� �������� �ϰ� �ϴ� operator*/
bool operator<(Trainer a, Trainer b) {
	return a.achiMemCount < b.achiMemCount;
}


/*trainerPQ�� �μ�Ʈ �ϴ� �Լ�->�ڵ� ��������*/
void heapSort_trainer(vector<Trainer>&trainer) {
	for (int i = 0; i < trainer.size(); i++) {
		trainerPQ.push(trainer[i]);
	}
	cout << "Q2. ���� �Ʒ� ������ ���� Ʈ���̳ʴ�?\n\n";   
	cout << "Answer : " << "���� �Ʒü����� ���� Ʈ���̳ʴ�? : " << trainerPQ.top().trainerName <<"  ��ǥ�� �޼��� ȸ���� : "<< trainerPQ.top().achiMemCount <<endl;
}



/*Q4 �� �ذ��ϱ� ���� map�� Ȱ���ؼ� ���*/
void max_min_dong() {
	for (iter = m.begin(); iter != m.end(); iter++) {
		if (dong.find(iter->address) == dong.end())
			dong.insert(make_pair(iter->address, 1));
		else {
			dong[iter->address]++;
		}
	}
	vector<pair<string, int> > vec(dong.begin(), dong.end());
	sort(vec.begin(), vec.end(), compare_pair_second<less>());
	cout << "Q4. ���� ����/���� ȸ���� ��� ����?\n\n";
	cout << "Answer : " << "���� ���� ȸ���� ��� ����: " << vec.back().first<<"   ȸ����: "<< vec.back().second <<endl;
	cout << "Answer : " << "���� ���� ȸ���� ��� ����: " << vec.front().first<<"   ȸ����: "<<vec.front().second <<endl ;
}
/*Q5*/

/* MaxHeap�� �����ϱ� ���� �Լ�*/
void heapSort_MaxRegMonth()
{
	for (int i = 0; i < 12; i++)
	{
		max_monthPQ.push(month[i]);
	}

}
/* MinHeap�� �����ϱ� ���� �Լ�*/
void heapSort_MinRegMonth()
{
	for (int i = 0; i < 12; i++)
	{
		min_monthPQ.push(month[i]);
	}
}

/*�� �����迭 �ʱ�ȭ*/
void initMonthArr()
{
	for (int i = 0; i < 12; i++)
	{
		month[i] = 0;
	}
}
/*����� ���� ���� ���� ���� ã�� ���� �Լ�.
�� �⵵���� ���� ���� ���� ���� �ƴ� �⵵�� ��Ʋ� ���� ���� �ް� ���� ���� ���Ѵ�.
1. 0���� �����迭 �ʱ�ȭ
2. string�� �ڷ� Ÿ���� int�� ��ȯ(���� ����)
3.���� �ش��ϸ� �� ���� ���� 1�� ����
4.�� �� priority Queue�� ����Ͽ� sorting�� TOP�� ��ȯ�Ѵ�.*/

void findMaxMonth()
{
	//�޷� �迭 ��� 0���� ���. �ʱ�ȭ 
	initMonthArr();

	//string���� ���ڸ� �Ľ��ϱ� ���� �ʿ��� ����
	int index1, index2, index3;

	//string���� --> int��ȯ
	int year_i, month_i, day_i;


	for (int i = 0; i < m.size(); i++)
	{
		string date = m[i].first_Register;

		//���� ���� :: 2019�� 08�� 14�� ->2019��08��14��
		date.erase(std::remove(date.begin(), date.end(), ' '), date.end());


		index1 = date.find("��");
		string year = date.substr(0, index1);
		year_i = stoi(year);

		index2 = date.find("��");
		string months = date.substr(index1 + 2, 2);
		month_i = stoi(months);


		index3 = date.find("��");
		string day = date.substr(index2 + 2, 2);
		day_i = stoi(day);


		//month�迭�� ���� ��ġ�� �� ����
		switch (month_i)
		{
		case 1:
			month[0]++;
			break;
		case 2:
			month[1]++;
			break;
		case 3:
			month[2]++;
			break;
		case 4:
			month[3]++;
			break;
		case 5:
			month[4]++;
			break;
		case 6:
			month[5]++;
			break;
		case 7:
			month[6]++;
			break;
		case 8:
			month[7]++;
			break;
		case 9:
			month[8]++;
			break;
		case 10:
			month[9]++;
			break;
		case 11:
			month[10]++;
			break;
		case 12:
			month[11]++;
			break;
		default:
			cout << "�߸��� ���Դϴ�" << endl;
			break;
		}
	}

	heapSort_MaxRegMonth();
	heapSort_MinRegMonth();

	int i, j;
	for (i = 0; i < 12; i++)
	{
		if (month[i] == max_monthPQ.top())
			break;
	}
	for (j = 0; j < 12; j++)
	{
		if (month[j] == min_monthPQ.top())
			break;
	}

	cout << "Q5. ���� ����ο��� ����/���� ����?\n\n";
	cout << "Answer : " << "���� ����ο��� ���� ���� : " << i+1 << "��\n" << "Answer : " <<"���� ����ο��� ���� ���� : " << j+1 << "��\n";
}

/*Q6
����ð��� �����ϴ� ����ü tm�� ����ؼ� ��¥�� ����.
1.���� �ð� ���ؼ� string���� ���� �� ���ᳯ¥�� ���Ͽ� ��ȿ���θ� ���Ѵ�.
memberinfo���� ���ᳯ¥�� nowdate�� ���ؼ� ��ȿ���θ� ����
2.ù ������ڸ� ȸ������ �� ���� ������ ȸ���� �ε����� �����ϰ� ù ������ڸ� �����ؼ� ��.
��ó�� ���Ҷ��� 999999�Ͱ��� ū ���� �����ؼ� ��.

*/

void longRegistered() {

	int count = 0; //���� ȸ���� �ε��� ���� ���� ����
	string date = "99999999"; //���� ��

	time_t nowtime;
	struct tm* d;
	nowtime = time(NULL);
	d = localtime(&nowtime);
	int thisyear = d->tm_year; //119
	int thismonth = d->tm_mon; //0~11��
	int thisday = d->tm_mday;

	thisyear += 1900;
	thismonth += 1;

	string thisyear_s = to_string(thisyear);
	string thismonth_s = to_string(thismonth);
	string thisday_s = to_string(thisday);
	string thismonth_zero = "0";

	if (thismonth < 10) {
		thismonth_s = thismonth_zero + thismonth_s;
	}

	//���� ��¥ string (��,��,�� ��)
	string nowdate = thisyear_s + "�� " + thismonth_s + "�� " + thisday_s + "�� ";

	for (int i = 0; i < m.size(); i++) {
		//��ȿȸ�� �Ÿ���	
		if ((m[i].expiredDate).compare(nowdate) > 0) {

			if ((m[i].first_Register).compare(date) < 0) {
				date = m[i].first_Register;
				count = i;
			}
		}
	}		

	cout << "Q6. ���� ������ ȸ����?\n\n";
	cout << "Answer : " << "���� ������ ȸ���� �̸� : " << m[count].name << "  ȸ����ȣ : "<< m[count].memberId << "  ù �����: "<< m[count].first_Register <<endl;
}
/*Q9*/
typedef class node *nptr;
class node {
	string personName;
	int nchilds;
	nptr *childs;
public:
	string get_personName() {
		return personName;
	}
	void set_personName(string name) {
		personName = name;
	}
	int get_nchilds() {
		return nchilds;
	}
	void set_nchilds(int n) {
		nchilds = n;
	}
	nptr* get_childs() {
		return childs;
	}
	void set_childs(nptr *c) {
		childs = c;
	}

	void make_node(string recName);
	void insert(node *myNode);
	bool traverse(string str, node *foundNode);
};

void node::make_node(string recName) {
	this->personName = recName;
	this->nchilds = 0;
	this->childs = NULL;
}

//�� �ڽ��� Ʈ���� �Ǵ� ���
//�� �ڽ��� ��� �ϳ��� �Ǵ� ���
void node::insert(node *myNode) {
	this->childs = (nptr *)realloc(this->childs, sizeof(nptr)*(this->nchilds + 1));
	this->childs[this->nchilds] = (nptr)malloc(sizeof(node));
	this->childs[this->nchilds] = myNode;
	this->nchilds++;
}

bool node::traverse(string str, node *foundNode) {//��Ʈ��� ���� ������ ���ϴ� ��尡 ������ true ��ȯ �ݴ�� false ��ȯ

	for (int i = 0; i < nchilds; i++) {
		if (this->childs[i] != NULL) {
			if (this->childs[i]->get_personName() == str) {
				foundNode = this->childs[i];
				return true;
			}
			this->childs[i]->traverse(str, foundNode);
		}
	}
	return false;
}


vector<node>tree_array;//���⿡�� ��� ����°� ��� ����
vector<node>temp;//���� ������ ����ϴ� node �迭 �ӽ������

void refresh_tree_array() {//tree_array���� ���� �����ϰ� ���� �����Ҷ� ����ϴ� �Լ�
	tree_array.clear();
	for (int i = 0; i < temp.size(); i++) {
		tree_array[i] = temp[i];
	}
}


void insertAll() {//forest ����� �Լ�
	for (int i = 0; i < m.size(); i++) {

		if (m[i].recMember != "-" && (m[i].name != m[i].recMember)) {//���� ��õ�� ��õ���� ���� ��
																	 //my.make_node(m[i].name);//�� ��� ����->���� �� �ִٰ� �ٲ㺸��

			if (tree_array.empty()) {
				node my;
				my.make_node(m[i].name);
				//���ο� ��� �����ؼ� ��õ���� ��Ʈ��
				//���� �ڽ����� �ִ´�.
				node recommender;//��õ�� ��� ����

				recommender.make_node(m[i].recMember);//��õ�� ��� �ʱ�ȭ

				recommender.insert(&my);//��õ�� ��忡 ���� �ڽ����� �ִ´�.

				tree_array.push_back(recommender);//�ڷᱸ���� �߰�
				continue;
			}//ok
			else {//�迭�� ������� ���� ���
				node my;
				my.make_node(m[i].name);
				bool check = false;
				for (int k = 0; k < tree_array.size(); k++) {//1) ���� ��õ�� ��õ���� tree_array�� �ִ��� Ȯ���Ѵ�.
					if (tree_array[k].get_personName() == m[i].recMember) {//-���� ��õ�� ��õ���� tree_array�� �ִٸ� 
						check = true;
						//�� ��õ�� �ؿ� ���� �ڽ����� �ִ´�.
						tree_array[k].insert(&my);
						break;
					}
				}

				if (!check) {//-���� ��õ�� ��õ���� tree_array�� ���ٸ�
					bool my_recMembere = false;
					node found_recMember;
					for (int k = 0; k < tree_array.size(); k++) {//tree_array ��ü�� for�� ������ ����ִ� ���(��Ʈ)���� �ϳ��ϳ� traverse�� ������.
																 //���� ��õ���� �ִ��� ã�´�.
						if (tree_array[k].traverse(m[i].recMember, &found_recMember)) {//traverse�� ������ �� ��õ���� ��򰡿� �����Ѵٸ� �ű⿡ ���̰� for���� �����.
							found_recMember.insert(&my);//ã�� ��õ�� ��忡 ���� �߰��Ѵ�.
							my_recMembere = true;
							break;
						}
					}
					if (!my_recMembere) {//���� ��õ�� ��õ���� tree_array�� ���� ��ü�� ������ ���ٸ� ���� �߰��Ѵ�.
						node recommender;//��õ�� ��� ����

						recommender.make_node(m[i].recMember);//��õ�� ��� �ʱ�ȭ

						recommender.insert(&my);//��õ�� ��忡 ���� �ڽ����� �ִ´�.

						tree_array.push_back(recommender);//�ڷᱸ���� �߰�

					}
				}
			}
		}
	}
}



/*Q12 
1.2000��� ������ ���ĸ� ����
2.2000��� ���Ķ�� 100�� �����༭ �񱳸� �� 
-> ��������� 99-05-28 �� ����Ǿ� �ֱ⿡ 00-02-28�ϰ� ���Ҷ� ������ ���ϱ� ���ؼ�
3.���� �⵵�� ���ؼ� ���� �ȿ� �ش�ȴٸ� 20���� ī���͸� ���������ش�.
4.���糯¥�� ���ϱ� ������ �ð��� ������ 20���� ������ ��µȴ�.
*/
void find20() {

	time_t nowtime;
	struct tm* d;
	nowtime = time(NULL);
	d = localtime(&nowtime);
	int thisyear = d->tm_year; //���� ���� 2019=>119
	int millchild = 0;

	int counttwenty = 1; //20�� �� ������ count;

	if (thisyear >= 119) { //00��� ���� ����� �񱳸� ���� ���Ѵ�.
		millchild = 100;
	}

	for (int i = 0; i < m.size(); i++) {
		const char* year = (m[i].birthDay).c_str();
		int byear = atoi(year);//�ش����� ź������;
		if (byear < 20) { //00��� ���� ���
			byear += millchild;
		}
		if ((thisyear - 29 < byear) && (thisyear - 18>byear)) {
			//cout << i <<"   "<<thisyear << m[i].name <<" ������ " << byear << '\n';
			counttwenty++;
		}
	}

	double ratio = ((double)counttwenty / (double)m.size());

	cout << "Q12. ȸ�� �� ���̰� 20���� ȸ���� ������?\n\n";
	cout << "Answer : " << "20���� ������ : " << ratio*100<<"%"<< "  20�� �� : " << counttwenty  << endl;

}

/*Q13 */

/* ��¥Ÿ���� int�� ��ȯ�ϱ� ���� �Լ�
ex)1996�� 09�� 08�� -> 19960908
*/
int changeTime(string a) {
	int year, month, day;
	string temp1 = a.substr(0, 5);
	string temp2 = a.substr(6, 9);
	string temp3 = a.substr(11, 13);
	year = stoi(temp1);
	month = stoi(temp2);
	day = stoi(temp3);
	int currdate = year * 10000 + month * 100 + day;

	return currdate;
}
/*LOAD�� 
���� �ñⰡ ������ ���� ȸ���� �����Ͽ� vector�� ����*/
void put_recentEX_mem(memberInfo temp) {
	struct tm* datatime;
	time_t t;
	t = time(NULL);
	datatime = localtime(&t);
	int currtime = (datatime->tm_year + 1900) * 10000 + (datatime->tm_mon + 1) * 100 + datatime->tm_mday;//���糯¥ ��ȯ �Լ�

	if (changeTime(temp.expiredDate) < currtime)//�������� ������ �����̶�� return
		return;
	else {
		recentEX re;
		re.name = temp.name;
		re.recentday = changeTime(temp.recentExDay);
		re.memberId = temp.memberId;
		recentex.push_back(re);
	}
}

/*MaxHeap�� ������ ���� operator�Լ�*/
bool operator<(recentEX a, recentEX b) {//min heap�� ���� operator
	return a.recentday > b.recentday;
}
/*HeapSort�� TOP��ȯ*/

void haep_sort_recentexmem(vector<recentEX>&recentex) {
	for (int i = 0; i < recentex.size(); i++)
		latememMinH.push(recentex[i]);
	int day = latememMinH.top().recentday;
	int year = day / 10000;
	day = day % 10000;
	int month = day / 100;
	int date = day % 100;
	cout << "Q13. ���� �������� ���� ���� ȸ����?\n\n";
	cout << "Answer : " << "���� �������� ���� ���� ȸ�� : " << latememMinH.top().name <<"  ȸ����ȣ : "<<latememMinH.top().memberId<<"  ���� �ֱ� ���: : " << year << "�� " << month << "�� " << date << "��\n";

}
/*Q15*/
/*diffBMI�� ���� �������� �ϴ� operator*/
bool operator<(memberInfo a, memberInfo b) {
	return a.diffBMI < b.diffBMI;
}
/*diffBMI�� ���ؼ� Max_heap �ǽ�*/
void heap_sort_biggoal(vector<memberInfo>&m) {
	for (int i = 0; i < m.size(); i++)//bmiPQ�� diffBMI�� ���� max heap �ǽ�
		bmiMaxH.push(m[i]);
	cout << "Q15. � ��ǥ�� ���� ���� ȸ����?\n\n";
	cout << "Answer : " << "� ��ǥ�� ���� ���� ȸ���� : " << bmiMaxH.top().name <<"  ȸ����ȣ : "<< bmiMaxH.top().memberId <<"  ó�� BMI : "<< bmiMaxH.top().firstBMI<<"  ��ǥ BMI : "<<bmiMaxH.top().goalBMI<<endl;
}



/*Q17
1.Merge ���� 
-> ��������� ���Ͽ� �պ�.
2.�������� ����
*/
void merge(memBirthday* mb, int left, int mid, int right)
{

	int i, j, k;
	i = left;
	j = mid + 1;
	k = left;

	memBirthday* temp = new memBirthday[m.size()];

	//left~mid���� & mid+1 ~ right���� ������� ��.
	while (i <= mid && j <= right)
	{
		if (mb[i].birthday_i >= mb[j].birthday_i)
		{
			temp[k].name = mb[i].name;
			temp[k].memeberId = mb[i].memeberId;
			temp[k].birthday = mb[i].birthday;
			temp[k].birthday_i = mb[i].birthday_i;

			i++;
		}
		else
		{
			temp[k].name = mb[j].name;
			temp[k].memeberId = mb[j].memeberId;
			temp[k].birthday = mb[j].birthday;
			temp[k].birthday_i = mb[j].birthday_i;
			j++;
		}
		k++;
	}

	//left ������ ���� ��� ó�� �Ǿ�����, right ������ index�� �����ִ� ���
	//right������ ���� �κ��� temp�� ����.
	if (i > mid)
	{


		for (int m = j; m <= right; m++)
		{
			temp[k].name = mb[m].name;
			temp[k].memeberId = mb[m].memeberId;
			temp[k].birthday = mb[m].birthday;
			temp[k].birthday_i = mb[m].birthday_i;
			k++;
		}
	}
	//�� �ݴ��� ��� ó��
	else
	{
		for (int m = i; m <= mid; m++)
		{
			temp[k].name = mb[m].name;
			temp[k].memeberId = mb[m].memeberId;
			temp[k].birthday = mb[m].birthday;
			temp[k].birthday_i = mb[m].birthday_i;
			k++;
		}
	}
	//���� �迭�� ����.
	for (int m = left; m <= right; m++)
	{
		mb[m].name = temp[m].name;
		mb[m].memeberId = temp[m].memeberId;
		mb[m].birthday = temp[m].birthday;
		mb[m].birthday_i = temp[m].birthday_i;
	}

}

void merge_sort(memBirthday* mb, int left, int right)
{
	int mid;

	if (left < right)
	{
		mid = (left + right) / 2;

		//����
		merge_sort(mb, left, mid);
		merge_sort(mb, mid + 1, right);

		//�պ�
		merge(mb, left, mid, right);
	}

}
/* 
1.������ϰ� �̸��� �����ϴ� class�� List�������� ���
2. 00��� ���Ŀ� ������ �����ϱ� ���� 1�� �߰��Ѵ�.
3. �� �� ������� LIst�� ����� Merge Sort�� �����Ѵ�.*/
void findYoungOldMember()
{
	//�������, �̸� �����ϴ� LIST
	memBirthday* memBirth = new memBirthday[m.size()];

	//00��� �̻��� ��� �տ� 1�� �߰��Ѵ�. 00����̻� ������� �ӽ� ���� ����
	string birthday;

	for (int i = 0; i < m.size(); i++)
	{
		memBirth[i].name = m[i].name;
		memBirth[i].memeberId = m[i].memberId;
		memBirth[i].birthday = m[i].birthDay;
		memBirth[i].birthday.erase(std::remove(memBirth[i].birthday.begin(), memBirth[i].birthday.end(), '.'), memBirth[i].birthday.end());

		//00��� �̻��� ��� �� ���ڸ� 1 �߰� 
		if (memBirth[i].birthday.at(0) == '0')
		{
			birthday = memBirth[i].birthday;
			birthday.insert(0, 1, '1');

			//int�� ��ȯ 060708 --> 1060708
			memBirth[i].birthday_i = stoi(birthday);
		}

		//90��� ���� �׳� int�� ��ȯ.
		else
			memBirth[i].birthday_i = stoi(memBirth[i].birthday);
	}

	//List�� ���Ͽ� mergeSort����.
	merge_sort(memBirth, 0, m.size() - 1);

	cout << "Q17. ���� ���̰� ����/���� ȸ����?\n\n";   
	cout << "Answer : " << "���� ���̰� ���� ȸ���� : " << memBirth[m.size() - 1].name <<"  ȸ����ȣ : "<<memBirth[m.size()-1].memeberId<< "  ������� : " << memBirth[m.size()-1].birthday << endl;
	cout << "Answer : " << "���� ���̰� ���� ȸ���� : " << memBirth[0].name<< "  ȸ����ȣ : " << memBirth[0].memeberId << "  ������� : " << memBirth[0].birthday << endl;

}


/* cvs������ ���پ� ������ , ������ �ɰ��� vector�� ����*/
void load() {
	fstream file;
	file.open("gym.csv");
	string line = "";
	getline(file, line);

	while (getline(file, line, '\n')) {
		istringstream templine(line);
		string data = "";
		memberInfo temp;
		int inner_idx = 0;

		while (getline(templine, data, ',')) {
			switch (inner_idx)
			{
			case 0:
				temp.memberId = stoi(data.c_str());
				break;
			case 1:
				temp.name = data.c_str();
				break;
			case 2:
				temp.address = data.c_str();
				break;
			case 3:
				temp.phoneNum = data.c_str();
				break;
			case 4:
				temp.recMember = data.c_str();
				break;
			case 5:
				temp.birthDay = data.c_str();
				break;
			case 6:
				temp.package = data.c_str();
				break;
			case 7:
				temp.isPT = data.c_str();
				break;
			case 8:
				temp.trainerName = data.c_str();
				break;
			case 9:
				temp.firstBMI = stof(data.c_str());
				break;
			case 10:
				temp.currBMI = stof(data.c_str());
				break;
			case 11:
				temp.goalBMI = stof(data.c_str());
				break;
			case 12:
				temp.lockNum = data.c_str();
				break;
			case 13:
				temp.first_Register = data.c_str();
				break;
			case 14:
				temp.totalExCount = stoi(data.c_str());
				break;
			case 15:
				temp.totalPTCount = stoi(data.c_str());
				break;
			case 16:
				temp.recentExDay = data.c_str();
				break;
			case 17:
				temp.expiredDate = data.c_str();
				break;
			default:
				break;
			}
			inner_idx++;
		}
		for (int i = 0; i < m.size(); i++) {//���� �̸� �ִ��� �˻��ؼ� ������ @ �ٿ��ش�.
			if (temp.name == m[i].name) {
				temp.name += "@";
			}
		}
		temp.diffBMI = abs(temp.firstBMI - temp.goalBMI);
		m.push_back(temp);
		put_trainer_vector(temp);//Q2
		put_recentEX_mem(temp);//Q13
	}
	file.close();
}


int main()
{
	load();
	max_trainer();//Q1
	cout << "---------------------------------------------------------\n\n";
	heapSort_trainer(trainer);//Q2
	cout << "---------------------------------------------------------\n\n";
	max_min_dong();//Q4
	cout << "---------------------------------------------------------\n\n";
	findMaxMonth();//Q5
	cout << "---------------------------------------------------------\n\n";
	longRegistered();//Q6
	cout << "---------------------------------------------------------\n\n";
	insertAll();//forest ����� �Լ�

	int max = 0;
	string max_person = "";
	for (int i = 0; i < tree_array.size(); i++) {
		if (max < tree_array[i].get_nchilds()) {
			max = tree_array[i].get_nchilds();
			max_person = tree_array[i].get_personName();
		}
	}
	cout << "Q9.���� ���� ����� ��õ�� �����? \n\n";
	cout << "Q9. ���� ���� ����� ��õ�� �����: " << max_person << "  ��õ�� ȸ�� �� : " << max << "\n";
	cout << "---------------------------------------------------------\n\n";
	find20();//Q12
	cout << "---------------------------------------------------------\n\n";
	haep_sort_recentexmem(recentex);//Q13
	cout << "---------------------------------------------------------\n\n";
	heap_sort_biggoal(m);//Q15
	cout << "---------------------------------------------------------\n\n";
	findYoungOldMember();//Q17
	cout << "---------------------------------------------------------\n\n";

	return 0;
}