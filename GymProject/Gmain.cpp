#include "gym.h"


/* 회원정보가 담겨 있는 전역 벡터 m과 iterator*/
vector<memberInfo>m;
vector<memberInfo>::iterator iter;

/* trainer class에 내용을 담고 있는 vector*/
vector<Trainer>trainer;

/*트레이너의 성과의 top을 판별하기 위한 우선순위큐*/
priority_queue<Trainer>trainerPQ;

/*동의 대한 정보가 담겨 있는 전역 벡터 dong과 iterator*/
map<string,int>dong;
map<string, int>::iterator d_iter;


/*트레이너에 대한 정보가 담겨 있는 전역벡터 trainer_map와 iterator */
map<string, int>trainer_map;
map<string, int>::iterator t_iter;

/* map을 value로 정렬하기 위한 template함수 비교해서 true/false를 반환*/
template<template <typename> class P = less >
struct compare_pair_second {

	template<class T1, class T2> bool operator()(const pair<T1, T2>&left, 
		const pair<T1, T2>&right) {

		return P<T2>()(left.second, right.second);

	}

};

/*1~12월에 해당하는 전역배열 선언*/
int month[12];

/*등록일이 가장 많은 달 우선순위 큐.*/
priority_queue<int, vector<int>, less<int>> max_monthPQ;

/*등록일이 가장 적은 달 우선순위 큐.*/
priority_queue<int, vector<int>, greater<int>>min_monthPQ;

/*가장 오랫동안 오지 않은 회원에 대한 정보를 담을 vector*/
vector<recentEX>recentex;

/*가장 오랫동안 오지 않은 회원을 Max_heap을 만들기 위한 heap*/
priority_queue<recentEX>latememMinH;

/*운동 목표가 높은 회원을 Max_heap을 만들기 위한 heap*/
priority_queue<memberInfo>bmiMaxH;

/*Q1 를 해결하기 위해 map을 활용해서 사용*/
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
	cout << "Q1. 가장 회원을 많이 확보한 트레이너는?\n\n";
	string temp = vec.back().first;
	string except = "-";
	if (temp == except) {
		vec.pop_back();
		cout << "Answer : " << "가장 회원을 많이 확보한 트레이너는? : " << vec.back().first << "   회원수: " << vec.back().second << endl;
	}
	else {
		cout << "Answer : " << "가장 회원을 많이 확보한 트레이너는? : " << vec.back().first << "   회원수: " << vec.back().second << endl;
	}
}


/* Q2
trainer vector에 성취여부를 판별하여 데이터 삽입하는 함수 
1. PT를 받는 회원인지를 구별
2.vector가 empty일때는 처음 들어오는 데이터를 성취여부를 판단하여 삽입
// linear Search를 사용하여 vector를 탐색한다.
2.트레이너가 vector에 없다면 성취한 회원이 있는 지 판별하여 achiMemCount를 1증가시키고 트레이너 이름을 vector에 삽입
3.이미 vector에 있는 트레이너이고 회원이 목표를 달성했다면 achiMemCount만 1증가 시킨다.*/
void put_trainer_vector(memberInfo temp) {
	if (temp.isPT == "Y") {
		if (trainer.empty()) {//트레이너 벡터가 엠티이면
			Trainer t;
			t.trainerName = temp.trainerName;
			t.achiMemCount = 0;
			if (temp.achieved() == true) {
				t.achiMemCount++;
			}
			//새로 채워주기
			trainer.push_back(t);
		}
		else {//엠티가 아니면
			bool check = false;
			for (int i = 0; i < trainer.size(); i++) {//linear search로 내 트레이너와 이름이 같은 트레이너가 있는지 찾는다.
				if (trainer[i].trainerName == temp.trainerName) {//이름이 같은 트레이너가 있으면
					check = true;
					if (temp.achieved() == true) {//내가 목표를 성취했으면 트레이너의 성과에 +1을하여 보탬을 준다.
						trainer[i].achiMemCount++;
					}
				}
			}
			if (!check) {//내 트레이너와 이름이 같은 트레이너가 없으면
				Trainer t;
				t.trainerName = temp.trainerName;
				t.achiMemCount = 0;
				if (temp.achieved() == true) {//성취여부 판단하고
					t.achiMemCount++;
				}
				trainer.push_back(t);//트레이너 벡터에 넣어준다.
			}
		}
	}
}

/*우선순위큐를 성과에 따라 히피파이 하게 하는 operator*/
bool operator<(Trainer a, Trainer b) {
	return a.achiMemCount < b.achiMemCount;
}


/*trainerPQ에 인서트 하는 함수->자동 히피파이*/
void heapSort_trainer(vector<Trainer>&trainer) {
	for (int i = 0; i < trainer.size(); i++) {
		trainerPQ.push(trainer[i]);
	}
	cout << "Q2. 가장 훈련 성과가 좋은 트레이너는?\n\n";   
	cout << "Answer : " << "가장 훈련성과가 좋은 트레이너는? : " << trainerPQ.top().trainerName <<"  목표를 달성한 회원수 : "<< trainerPQ.top().achiMemCount <<endl;
}



/*Q4 를 해결하기 위해 map을 활용해서 사용*/
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
	cout << "Q4. 가장 많은/적은 회원이 사는 동은?\n\n";
	cout << "Answer : " << "가장 많은 회원이 사는 동은: " << vec.back().first<<"   회원수: "<< vec.back().second <<endl;
	cout << "Answer : " << "가장 적은 회원이 사는 동은: " << vec.front().first<<"   회원수: "<<vec.front().second <<endl ;
}
/*Q5*/

/* MaxHeap에 삽입하기 위한 함수*/
void heapSort_MaxRegMonth()
{
	for (int i = 0; i < 12; i++)
	{
		max_monthPQ.push(month[i]);
	}

}
/* MinHeap에 삽입하기 위한 함수*/
void heapSort_MinRegMonth()
{
	for (int i = 0; i < 12; i++)
	{
		min_monthPQ.push(month[i]);
	}
}

/*월 전연배열 초기화*/
void initMonthArr()
{
	for (int i = 0; i < 12; i++)
	{
		month[i] = 0;
	}
}
/*등록이 가장 많고 적은 달을 찾기 위한 함수.
매 년도마다 가장 많고 적은 달이 아닌 년도를 통틀어서 가장 많은 달과 적은 달을 구한다.
1. 0으로 전역배열 초기화
2. string인 자료 타입을 int로 변환(공백 제거)
3.월에 해당하면 그 월에 값을 1씩 증가
4.그 후 priority Queue를 사용하여 sorting후 TOP을 반환한다.*/

void findMaxMonth()
{
	//달력 배열 요소 0으로 모두. 초기화 
	initMonthArr();

	//string에서 숫자만 파싱하기 위해 필요한 변수
	int index1, index2, index3;

	//string형을 --> int변환
	int year_i, month_i, day_i;


	for (int i = 0; i < m.size(); i++)
	{
		string date = m[i].first_Register;

		//공백 제거 :: 2019년 08월 14일 ->2019년08월14일
		date.erase(std::remove(date.begin(), date.end(), ' '), date.end());


		index1 = date.find("년");
		string year = date.substr(0, index1);
		year_i = stoi(year);

		index2 = date.find("월");
		string months = date.substr(index1 + 2, 2);
		month_i = stoi(months);


		index3 = date.find("일");
		string day = date.substr(index2 + 2, 2);
		day_i = stoi(day);


		//month배열에 월에 위치한 값 증가
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
			cout << "잘못된 값입니다" << endl;
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

	cout << "Q5. 가장 등록인원이 많은/적은 달은?\n\n";
	cout << "Answer : " << "가장 등록인원이 많은 달은 : " << i+1 << "월\n" << "Answer : " <<"가장 등록인원이 적은 달은 : " << j+1 << "월\n";
}

/*Q6
현재시간을 제공하는 구조체 tm을 사용해서 날짜를 저장.
1.현재 시간 구해서 string으로 만든 후 만료날짜와 비교하여 유효여부를 구한다.
memberinfo에서 만료날짜를 nowdate와 비교해서 유효여부를 구함
2.첫 등록일자를 회원끼리 비교 가장 오래된 회원에 인덱스를 저장하고 첫 등록일자를 저장해서 비교.
맨처음 비교할때는 999999와같이 큰 값을 대입해서 비교.

*/

void longRegistered() {

	int count = 0; //최장 회원의 인덱스 값을 넣을 변수
	string date = "99999999"; //비교할 값

	time_t nowtime;
	struct tm* d;
	nowtime = time(NULL);
	d = localtime(&nowtime);
	int thisyear = d->tm_year; //119
	int thismonth = d->tm_mon; //0~11월
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

	//현재 날짜 string (연,월,일 순)
	string nowdate = thisyear_s + "년 " + thismonth_s + "월 " + thisday_s + "일 ";

	for (int i = 0; i < m.size(); i++) {
		//유효회원 거르기	
		if ((m[i].expiredDate).compare(nowdate) > 0) {

			if ((m[i].first_Register).compare(date) < 0) {
				date = m[i].first_Register;
				count = i;
			}
		}
	}		

	cout << "Q6. 가장 오래된 회원은?\n\n";
	cout << "Answer : " << "가장 오래된 회원의 이름 : " << m[count].name << "  회원번호 : "<< m[count].memberId << "  첫 등록일: "<< m[count].first_Register <<endl;
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

//내 자식이 트리가 되는 경우
//내 자식이 노드 하나가 되는 경우
void node::insert(node *myNode) {
	this->childs = (nptr *)realloc(this->childs, sizeof(nptr)*(this->nchilds + 1));
	this->childs[this->nchilds] = (nptr)malloc(sizeof(node));
	this->childs[this->nchilds] = myNode;
	this->nchilds++;
}

bool node::traverse(string str, node *foundNode) {//루트노드 부터 돌려서 원하는 노드가 나오면 true 반환 반대는 false 반환

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


vector<node>tree_array;//여기에서 멤버 지우는거 어떻게 하지
vector<node>temp;//원소 삭제시 사용하는 node 배열 임시저장소

void refresh_tree_array() {//tree_array에서 원소 삭제하고 새로 갱신할때 사용하는 함수
	tree_array.clear();
	for (int i = 0; i < temp.size(); i++) {
		tree_array[i] = temp[i];
	}
}


void insertAll() {//forest 만드는 함수
	for (int i = 0; i < m.size(); i++) {

		if (m[i].recMember != "-" && (m[i].name != m[i].recMember)) {//나를 추천한 추천인이 있을 떄
																	 //my.make_node(m[i].name);//내 노드 새성->여기 좀 있다가 바꿔보기

			if (tree_array.empty()) {
				node my;
				my.make_node(m[i].name);
				//새로운 노드 생성해서 추천인을 루트로
				//나를 자식으로 넣는다.
				node recommender;//추천인 노드 생성

				recommender.make_node(m[i].recMember);//추천인 노드 초기화

				recommender.insert(&my);//추천인 노드에 나를 자식으로 넣는다.

				tree_array.push_back(recommender);//자료구조에 추가
				continue;
			}//ok
			else {//배열이 비어있지 않은 경우
				node my;
				my.make_node(m[i].name);
				bool check = false;
				for (int k = 0; k < tree_array.size(); k++) {//1) 나를 추천한 추천인이 tree_array에 있는지 확인한다.
					if (tree_array[k].get_personName() == m[i].recMember) {//-나를 추천한 추천인이 tree_array에 있다면 
						check = true;
						//그 추천인 밑에 나를 자식으로 넣는다.
						tree_array[k].insert(&my);
						break;
					}
				}

				if (!check) {//-나를 추천한 추천인이 tree_array에 없다면
					bool my_recMembere = false;
					node found_recMember;
					for (int k = 0; k < tree_array.size(); k++) {//tree_array 전체를 for문 돌려서 들어있는 노드(루트)마다 하나하나 traverse를 돌린다.
																 //나의 추천인이 있는지 찾는다.
						if (tree_array[k].traverse(m[i].recMember, &found_recMember)) {//traverse를 돌려서 내 추천인이 어딘가에 존재한다면 거기에 붙이고 for문을 멈춘다.
							found_recMember.insert(&my);//찾은 추천인 노드에 나를 추가한다.
							my_recMembere = true;
							break;
						}
					}
					if (!my_recMembere) {//나를 추천한 추천인이 tree_array의 원소 전체를 뒤져도 없다면 새로 추가한다.
						node recommender;//추천인 노드 생성

						recommender.make_node(m[i].recMember);//추천인 노드 초기화

						recommender.insert(&my);//추천인 노드에 나를 자식으로 넣는다.

						tree_array.push_back(recommender);//자료구조에 추가

					}
				}
			}
		}
	}
}



/*Q12 
1.2000년생 이전과 이후를 구분
2.2000년생 이후라면 100을 더해줘서 비교를 함 
-> 생년월일이 99-05-28 로 저장되어 있기에 00-02-28하고 비교할때 에러를 피하기 위해서
3.현재 년도를 구해서 범위 안에 해당된다면 20대의 카운터를 증가시켜준다.
4.현재날짜와 비교하기 때문에 시간이 지나도 20대의 비율이 출력된다.
*/
void find20() {

	time_t nowtime;
	struct tm* d;
	nowtime = time(NULL);
	d = localtime(&nowtime);
	int thisyear = d->tm_year; //현재 연도 2019=>119
	int millchild = 0;

	int counttwenty = 1; //20대 몇 명인지 count;

	if (thisyear >= 119) { //00년대 이후 출생자 비교를 위해 더한다.
		millchild = 100;
	}

	for (int i = 0; i < m.size(); i++) {
		const char* year = (m[i].birthDay).c_str();
		int byear = atoi(year);//해당멤버의 탄생연도;
		if (byear < 20) { //00년대 이후 출생
			byear += millchild;
		}
		if ((thisyear - 29 < byear) && (thisyear - 18>byear)) {
			//cout << i <<"   "<<thisyear << m[i].name <<" 연도만 " << byear << '\n';
			counttwenty++;
		}
	}

	double ratio = ((double)counttwenty / (double)m.size());

	cout << "Q12. 회원 중 나이가 20대인 회원의 비율은?\n\n";
	cout << "Answer : " << "20대의 비율은 : " << ratio*100<<"%"<< "  20대 수 : " << counttwenty  << endl;

}

/*Q13 */

/* 날짜타입을 int로 변환하기 위한 함수
ex)1996년 09월 08일 -> 19960908
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
/*LOAD시 
말소 시기가 지나지 않은 회원을 구별하여 vector에 삽입*/
void put_recentEX_mem(memberInfo temp) {
	struct tm* datatime;
	time_t t;
	t = time(NULL);
	datatime = localtime(&t);
	int currtime = (datatime->tm_year + 1900) * 10000 + (datatime->tm_mon + 1) * 100 + datatime->tm_mday;//현재날짜 반환 함수

	if (changeTime(temp.expiredDate) < currtime)//만료일이 현재일 이전이라면 return
		return;
	else {
		recentEX re;
		re.name = temp.name;
		re.recentday = changeTime(temp.recentExDay);
		re.memberId = temp.memberId;
		recentex.push_back(re);
	}
}

/*MaxHeap에 삽입을 위한 operator함수*/
bool operator<(recentEX a, recentEX b) {//min heap을 위한 operator
	return a.recentday > b.recentday;
}
/*HeapSort후 TOP반환*/

void haep_sort_recentexmem(vector<recentEX>&recentex) {
	for (int i = 0; i < recentex.size(); i++)
		latememMinH.push(recentex[i]);
	int day = latememMinH.top().recentday;
	int year = day / 10000;
	day = day % 10000;
	int month = day / 100;
	int date = day % 100;
	cout << "Q13. 가장 오랫동안 오지 않은 회원은?\n\n";
	cout << "Answer : " << "가장 오랫동안 오지 않은 회원 : " << latememMinH.top().name <<"  회원번호 : "<<latememMinH.top().memberId<<"  가장 최근 운동일: : " << year << "년 " << month << "월 " << date << "일\n";

}
/*Q15*/
/*diffBMI에 대해 히피파이 하는 operator*/
bool operator<(memberInfo a, memberInfo b) {
	return a.diffBMI < b.diffBMI;
}
/*diffBMI에 대해서 Max_heap 실시*/
void heap_sort_biggoal(vector<memberInfo>&m) {
	for (int i = 0; i < m.size(); i++)//bmiPQ의 diffBMI에 대해 max heap 실시
		bmiMaxH.push(m[i]);
	cout << "Q15. 운동 목표가 가장 높은 회원은?\n\n";
	cout << "Answer : " << "운동 목표가 가장 높은 회원은 : " << bmiMaxH.top().name <<"  회원번호 : "<< bmiMaxH.top().memberId <<"  처음 BMI : "<< bmiMaxH.top().firstBMI<<"  목표 BMI : "<<bmiMaxH.top().goalBMI<<endl;
}



/*Q17
1.Merge 구현 
-> 생년월일을 비교하여 합병.
2.내림차순 정렬
*/
void merge(memBirthday* mb, int left, int mid, int right)
{

	int i, j, k;
	i = left;
	j = mid + 1;
	k = left;

	memBirthday* temp = new memBirthday[m.size()];

	//left~mid까지 & mid+1 ~ right까지 생년월일 비교.
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

	//left 구역의 값이 모두 처리 되었지만, right 구역의 index가 남아있는 경우
	//right구역의 남은 부분을 temp로 복사.
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
	//그 반대의 경우 처리
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
	//원본 배열로 복사.
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

		//분할
		merge_sort(mb, left, mid);
		merge_sort(mb, mid + 1, right);

		//합병
		merge(mb, left, mid, right);
	}

}
/* 
1.생년월일과 이름을 저장하는 class를 List형식으로 사용
2. 00년생 이후와 이전을 구별하기 위해 1을 추가한다.
3. 그 후 만들어진 LIst를 사용해 Merge Sort를 수행한다.*/
void findYoungOldMember()
{
	//생년월일, 이름 저장하는 LIST
	memBirthday* memBirth = new memBirthday[m.size()];

	//00년생 이상일 경우 앞에 1을 추가한다. 00년생이상 생년월일 임시 저장 변수
	string birthday;

	for (int i = 0; i < m.size(); i++)
	{
		memBirth[i].name = m[i].name;
		memBirth[i].memeberId = m[i].memberId;
		memBirth[i].birthday = m[i].birthDay;
		memBirth[i].birthday.erase(std::remove(memBirth[i].birthday.begin(), memBirth[i].birthday.end(), '.'), memBirth[i].birthday.end());

		//00년생 이상일 경우 맨 앞자리 1 추가 
		if (memBirth[i].birthday.at(0) == '0')
		{
			birthday = memBirth[i].birthday;
			birthday.insert(0, 1, '1');

			//int형 변환 060708 --> 1060708
			memBirth[i].birthday_i = stoi(birthday);
		}

		//90년대 생은 그냥 int로 변환.
		else
			memBirth[i].birthday_i = stoi(memBirth[i].birthday);
	}

	//List에 대하여 mergeSort수행.
	merge_sort(memBirth, 0, m.size() - 1);

	cout << "Q17. 가장 나이가 많은/적은 회원은?\n\n";   
	cout << "Answer : " << "가장 나이가 많은 회원은 : " << memBirth[m.size() - 1].name <<"  회원번호 : "<<memBirth[m.size()-1].memeberId<< "  생년월일 : " << memBirth[m.size()-1].birthday << endl;
	cout << "Answer : " << "가장 나이가 적은 회원은 : " << memBirth[0].name<< "  회원번호 : " << memBirth[0].memeberId << "  생년월일 : " << memBirth[0].birthday << endl;

}


/* cvs파일을 한줄씩 가져와 , 단위로 쪼개서 vector에 삽입*/
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
		for (int i = 0; i < m.size(); i++) {//같은 이름 있는지 검사해서 있으면 @ 붙여준다.
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
	insertAll();//forest 만드는 함수

	int max = 0;
	string max_person = "";
	for (int i = 0; i < tree_array.size(); i++) {
		if (max < tree_array[i].get_nchilds()) {
			max = tree_array[i].get_nchilds();
			max_person = tree_array[i].get_personName();
		}
	}
	cout << "Q9.가장 많은 사람을 추천한 사람은? \n\n";
	cout << "Q9. 가장 많은 사람을 추천한 사람은: " << max_person << "  추천한 회원 수 : " << max << "\n";
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