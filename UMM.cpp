// UMM.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
using namespace std;

void clear(void) {
	system("pause");
	system("cls");
}

bool go_on(void) {
	cout << "Do you want to continue (Y / N) ? [Case Insensitive]" << endl;
	char c;
	cin >> c;
	if (c == 'Y' || c == 'y') {
		return true;
	}
	else {
		return false;
	}
}

class People {
private:
	string name;
	unsigned short age;
public:
	People(string str, unsigned short num);
	void setName(string str);
	void setAge(unsigned short num);
	string getName(void);
	unsigned short getAge(void);
};

People::People(string str, unsigned short num) {
	this->name = str;
	this->age = num;
}

void People::setName(string str) {
	this->name = str;
}

void People::setAge(unsigned short num) {
	this->age = num;
}

string People::getName(void) {
	return name;
}

unsigned short People::getAge(void) {
	return age;
}

class Student :public People {
private:
	unsigned short chnMark, mathMark, sumMark;
public:
	void SUM(void);
	Student(string str_s, unsigned short num_s, unsigned short num_1, unsigned short num_2);
	void setChn(unsigned short num1);
	void setMath(unsigned short num2);
	unsigned short getChn(void);
	unsigned short getMath(void);
	unsigned short getSum(void);
};

void Student::SUM(void) {
	this->sumMark = this->chnMark + this->mathMark;
}

Student::Student(string str_s, unsigned short num_s, unsigned short num_1, unsigned short num_2) :People(str_s, num_s) {
	this->chnMark = num_1;
	this->mathMark = num_2;
	SUM();
}

void Student::setChn(unsigned short num1) {
	this->chnMark = num1;
	SUM();
}

void Student::setMath(unsigned short num2) {
	this->mathMark = num2;
	SUM();
}

unsigned short Student::getChn(void) {
	return chnMark;
}

unsigned short Student::getMath(void) {
	return mathMark;
}

unsigned short Student::getSum(void) {
	return sumMark;
}

class Worker :virtual public People {
private:
	double wage;
public:
	Worker(string str_w, unsigned short num_w, double flt);
	void setWage(double flt);
	double getWage(void);
};

Worker::Worker(string str_w, unsigned short num_w, double flt) :People(str_w, num_w) {
	this->wage = flt;
}

void Worker::setWage(double flt) {
	this->wage = flt;
}

double Worker::getWage(void) {
	return wage;
}

class Teacher :virtual public Worker {
private:
	string title;
public:
	Teacher(string str_t, unsigned short num1_t, unsigned short num2_t);
	double PaidT(unsigned short num);
	void setTitle(unsigned short switch_on);
	string getTitle(void);
};

Teacher::Teacher(string str_t, unsigned short num1_t, unsigned short num2_t) :Worker(str_t, num1_t, PaidT(num2_t)), People(str_t, num1_t) {}

double Teacher::PaidT(unsigned short num) {
	switch (num) {
	case 1:
		return 4000;
		break;
	case 2:
		return 5000;
		break;
	case 3:
		return 6000;
		break;
	default:
		return -4001;
	}
}

void Teacher::setTitle(unsigned short switch_on) {
	switch (switch_on) {
	case '1':
		this->title = "Lecturer";
		break;
	case '2':
		this->title = "Associate Professor";
		break;
	case '3':
		this->title = "Professor";
		break;
	default:
		return;
	}
}

string Teacher::getTitle(void) {
	return title;
}

class Executive :virtual public Worker {
private:
	unsigned short level;
public:
	double PaidE(unsigned short num);
	Executive(string str_e, unsigned short num1_e, unsigned short num2_e);
	void setLevel(unsigned short num);
	unsigned short getLevel(void);
};

double Executive::PaidE(unsigned short num) {
	switch (num)
	{
	case 1:
		return 2000;
	case 2:
		return 3000;
	case 3:
		return 4000;
	default:
		return -6001;
	}
}

Executive::Executive(string str_e, unsigned short num1_e, unsigned short num2_e) :Worker(str_e, num1_e, PaidE(num2_e)), People(str_e, num1_e) {
	this->level = num2_e;
}

void Executive::setLevel(unsigned short num) {
	this->level = num;
}

unsigned short Executive::getLevel(void) {
	return level;
}

class Head :public Teacher, public Executive {
public:
	double Wages(unsigned short num1, unsigned short num2);
	Head(string str_h, unsigned short num1_h, unsigned short num2_h, unsigned short num3_h);
	void setWages(unsigned short num1, unsigned short num2);
	double getWages(void);
};

double Head::Wages(unsigned short num1, unsigned short num2) {
	return PaidT(num1) + PaidE(num2) / 2;
}

Head::Head(string str_h, unsigned short num1_h, unsigned short num2_h, unsigned short num3_h) :People(str_h, num1_h), Worker(str_h, num1_h, Wages(num2_h, num3_h)), Teacher(str_h, num1_h, num2_h), Executive(str_h, num1_h, num3_h) {}

void Head::setWages(unsigned short num1, unsigned short num2) {
	setTitle(num1);
	setLevel(num2);
	setWage(Wages(num1, num2));
}

double Head::getWages(void) {
	return getWage();
}

struct StudentArguments
{
	string name;
	unsigned short age;
	unsigned short Chinese;
	unsigned short Mathematics;
};

struct TeacherArguments
{
	string name;
	unsigned short age;
	unsigned short title_num;
};

struct ExecutiveArguments
{
	string name;
	unsigned short age;
	unsigned short level;
};

struct HeadArguments
{
	string name;
	unsigned short age;
	unsigned short title_num;
	unsigned short level;
};

Student SNULL("-1", 0, 0, 0);
Teacher TNULL("-1", 0, 0);
Executive ENULL("-1", 0, 0);
Head HNULL("-1", 0, 0, 0);

class System {
private:
	vector<Student> students;
	vector<Teacher> teachers;
	vector<Executive> executives;
	vector<Head> heads;
	bool success = false;
	unsigned short past_size;
public:
	void menu(void);
	~System();
protected:
	void isSuccessful(int now);
	bool studentInitial(void);
	bool teacherInitial(void);
	bool executiveInitial(void);
	bool headInitial(void);
	bool allInitial(void);
	void addStudent(void);
	unsigned short getTitleNum(void);
	void addTeacher(void);
	void addExecutive(void);
	void addHead(void);
	void printOptions_ofPosition(void);
	void choosePosition(void);
	void addNew(void);
	void addNew_Loop(void);
	void listStudents(void);
	void listTeachers(void);
	void listExecutives(void);
	void listHeads(void);
	void listAll(void);
	unsigned short Push_backPosition_num(void);
	string inputName(void);
	void targetizing(bool doDelete);
	vector<Student>::iterator SearchStudent(string strS);
	vector<Teacher>::iterator SearchTeacher(string strT);
	vector<Executive>::iterator SearchExecutive(string strE);
	vector<Head>::iterator SearchHead(string strH);
	void StudentTargetized(string sName, bool doDelete);
	void TeacherTargetized(string tName, bool doDelete);
	void ExecutiveTargetized(string eName, bool doDelete);
	void HeadTargetized(string hName, bool doDelete);
	void CheckItOut(void);
	void Delete();
	void printOptions_ofMenu(void);
	void process(void);
};

void System::isSuccessful(int now) {
	if (past_size < now) {
		success = true;
	}
	else {
		success = false;
	}
	past_size = 0;
}

bool System::studentInitial(void) {
	if (students.size() != 0) {
		return false;
	}
	else {
		return true;
	}
}

bool System::teacherInitial(void) {
	if (teachers.size() != 0) {
		return false;
	}
	else {
		return true;
	}
}

bool System::executiveInitial(void) {
	if (executives.size() != 0) {
		return false;
	}
	else {
		return true;
	}
}

bool System::headInitial(void) {
	if (heads.size() != 0)
	{
		return false;
	}
	else {
		return true;
	}
}

bool System::allInitial(void) {
	if (!studentInitial()) {
		return false;
	}
	else if (!teacherInitial()) {
		return false;
	}
	else if (!executiveInitial()) {
		return false;
	}
	else if (!headInitial())
	{
		return false;
	}
	else
	{
		return true;
	}
}

void System::addStudent(void) {
	past_size = students.size();
	StudentArguments student;
	cout << "Name Age Chinese Maths: ";
	cin >> student.name >> student.age >> student.Chinese >> student.Mathematics;
	Student temp(student.name, student.age, student.Chinese, student.Mathematics);
	students.push_back(temp);
	isSuccessful(students.size());
}

unsigned short System::getTitleNum(void) {
	cout << "Select the Title of the Teacher" << endl;
	cout << "1> Lecturer" << endl;
	cout << "2> Associate Professor" << endl;
	cout << "3> Professor" << endl;
	unsigned short num;
	cin >> num;
	return num;
}

void System::addTeacher(void) {
	past_size = teachers.size();
	TeacherArguments teacher;
	cout << "Name Age: ";
	cin >> teacher.name >> teacher.age;
	teacher.title_num = getTitleNum();
	Teacher temp(teacher.name, teacher.age, teacher.title_num);
	teachers.push_back(temp);
	isSuccessful(teachers.size());
}

void System::addExecutive(void) {
	past_size = executives.size();
	ExecutiveArguments executive;
	cout << "Name Age Level: ";
	cin >> executive.name >> executive.age >> executive.level;
	Executive temp(executive.name, executive.age, executive.level);
	executives.push_back(temp);
	isSuccessful(executives.size());
}

void System::addHead(void) {
	past_size = heads.size();
	HeadArguments head;
	cout << "Name Age Level: ";
	cin >> head.name >> head.age >> head.level;
	head.title_num = getTitleNum();
	Head temp(head.name, head.age, head.title_num, head.level);
	heads.push_back(temp);
	isSuccessful(heads.size());
}

void System::printOptions_ofPosition(void) {
	cout << "Position: " << endl;
	cout << "1> Student" << endl;
	cout << "2> Teacher" << endl;
	cout << "3> Administrative Staff" << endl;
	cout << "4> University Administration" << endl;
}

void System::choosePosition(void) {
	switch (Push_backPosition_num())
	{
	case 1:
		addStudent();
		break;
	case 2:
		addTeacher();
		break;
	case 3:
		addExecutive();
		break;
	case 4:
		addHead();
		break;
	default:
		break;
	}
}

void System::addNew(void) {
	printOptions_ofPosition();
	choosePosition();
	if (success) {
		cout << "Success!!!" << endl;
	}
	else {
		cout << "Failed!!!" << endl;
	}
}

void System::addNew_Loop(void) {
	do
	{
		addNew();
		system("pause");
	} while (go_on());
	cout << "<---End of Add Function--->" << endl;
}

void System::listStudents(void) {
	int count = 1;
	for (vector<Student>::iterator iter = students.begin(); iter != students.end(); ++iter) {
		cout << iter->getName();
		if (count % 5 == 0 && iter != students.end()) {
			cout << endl;
		}
		else if (iter != students.end()-1)
		{
			cout << ", ";
		}
		else {
			cout << ".";
		}
		++count;
	}
	cout << endl;
}

void System::listTeachers(void) {
	int count = 1;
	for (vector<Teacher>::iterator iter = teachers.begin(); iter != teachers.end(); ++iter) {
		cout << iter->getName();
		if (count % 5 == 0 && iter != teachers.end()) {
			cout << endl;
		}
		else if (iter != teachers.end())
		{
			cout << ", ";
		}
		else {
			cout << ".";
		}
		++count;
	}
	cout << endl;
}

void System::listExecutives(void) {
	int count = 1;
	for (vector<Executive>::iterator iter = executives.begin(); iter != executives.end(); ++iter) {
		cout << iter->getName();
		if (count % 5 == 0 && iter != executives.end()) {
			cout << endl;
		}
		else if (iter != executives.end())
		{
			cout << ", ";
		}
		else {
			cout << ".";
		}
		++count;
	}
	cout << endl;
}

void System::listHeads(void) {
	int count = 1;
	for (vector<Head>::iterator iter = heads.begin(); iter != heads.end(); ++iter) {
		cout << iter->getName();
		if (count % 5 == 0 && iter != heads.end()) {
			cout << endl;
		}
		else if (iter != heads.end())
		{
			cout << ", ";
		}
		else {
			cout << ".";
		}
		++count;
	}
	cout << endl;
}

void System::listAll(void) {
	cout << "-----< Student Names >-----" << endl;
	listStudents();
	cout << "-----< Teacher Names >-----" << endl;
	listTeachers();
	cout << "-----< Administrative Staff Names >-----" << endl;
	listExecutives();
	cout << "-----< University Administration >-----" << endl;
	listHeads();
	cout << "End of List Function" << endl;
}

unsigned short System::Push_backPosition_num(void) {
	unsigned short num;
	cin >> num;
	return num;
}

string System::inputName(void) {
	string str;
	cout << "Plz input target's name: " << endl;
	cin >> str;
	return str;
}

void System::targetizing(bool doDelete) {
	switch (Push_backPosition_num())
	{
	case 1:
		StudentTargetized(inputName(), doDelete);
		break;
	case 2:
		TeacherTargetized(inputName(), doDelete);
		break;
	case 3:
		ExecutiveTargetized(inputName(), doDelete);
		break;
	case 4:
		HeadTargetized(inputName(), doDelete);
		break;
	default:
		break;
	}
}

vector<Student>::iterator System::SearchStudent(string strS) {
	for (vector<Student>::iterator iter = students.begin(); iter != students.end(); ++iter) {
		if (iter->getName() == strS) {
			return iter;
		}
	}
	students.push_back(SNULL);
	return students.end();
}

vector<Teacher>::iterator System::SearchTeacher(string strT) {
	for (vector<Teacher>::iterator iter = teachers.begin(); iter != teachers.end(); ++iter) {
		if (iter->getName() == strT) {
			return iter;
		}
	}
	teachers.push_back(TNULL);
	return teachers.end();
}

vector<Executive>::iterator System::SearchExecutive(string strE) {
	for (vector<Executive>::iterator iter = executives.begin(); iter != executives.end(); ++iter) {
		if (iter->getName() == strE) {
			return iter;
		}
	}
	executives.push_back(ENULL);
	return executives.end();
}

vector<Head>::iterator System::SearchHead(string strH) {
	for (vector<Head>::iterator iter = heads.begin(); iter != heads.end(); ++iter) {
		if (iter->getName() == strH) {
			return iter;
		}
	}
	heads.push_back(HNULL);
	return heads.end();
}

void System::StudentTargetized(string sName, bool doDelete) {
	if (students.size() > 1) {
		vector<Student>::iterator iter = SearchStudent(sName);
		if (iter->getAge() == 0) {
			cout << sName << " Not Found!!!" << endl;
			students.pop_back();
			return;
		}
		else
		{
			if (doDelete) {
				students.erase(iter);
			}
			else {
				cout << "The score is " << iter->getSum() << "." << endl;
			}
		}
	}
	else if (students.size() == 1) {
		if (students.at(0).getName() == sName) {
			if (doDelete) {
				students.erase(students.begin());
			}
			else {
				cout << "The score is " << students.at(0).getSum() << "." << endl;
			}
		}
		else {
			cout << sName << " Not Found!!!" << endl;
			return;
		}
	}
	else {
		cout << "November!!" << endl;
	}
}

void System::TeacherTargetized(string tName, bool doDelete) {
	if (teachers.size() > 1) {
		vector<Teacher>::iterator iter = SearchTeacher(tName);
		if (iter->getAge() == 0) {
			cout << tName << " Not Found!!!" << endl;
			teachers.pop_back();
			return;
		}
		else
		{
			if (doDelete) {
				teachers.erase(iter);
			}
			else {
				cout << "The salary is " << iter->getWage() << "." << endl;
			}
		}
	}
	else if (teachers.size() == 1) {
		if (teachers.at(0).getName() == tName) {
			if (doDelete) {
				teachers.erase(teachers.begin());
			}
			else {
				cout << "The salary is " << teachers.at(0).getWage() << "." << endl;
			}
		}
		else {
			cout << tName << " Not Found!!!" << endl;
			return;
		}
	}
	else {
		cout << "November!!" << endl;
	}
}

void System::ExecutiveTargetized(string eName, bool doDelete) {
	if (executives.size() > 1) {
		vector<Executive>::iterator iter = SearchExecutive(eName);
		if (iter->getAge() == 0) {
			cout << eName << " Not Found!!!" << endl;
			executives.pop_back();
			return;
		}
		else
		{
			if (doDelete) {
				executives.erase(iter);
			}
			else {
				cout << "The salary is " << iter->getWage() << "." << endl;
			}
		}
	}
	else if (executives.size() == 1) {
		if (executives.at(0).getName() == eName) {
			if (doDelete) {
				executives.erase(executives.begin());
			}
			else {
				cout << "The salary is " << executives.at(0).getWage() << "." << endl;
			}
		}
		else {
			cout << eName << " Not Found!!!" << endl;
			return;
		}
	}
	else {
		cout << "November!!" << endl;
	}
}

void System::HeadTargetized(string hName, bool doDelete) {
	if (heads.size() > 1) {
		vector<Head>::iterator iter = SearchHead(hName);
		if (iter->getAge() == 0) {
			cout << hName << " Not Found!!!" << endl;
			heads.pop_back();
			return;
		}
		else
		{
			if (doDelete) {
				heads.erase(iter);
			}
			else {
				cout << "The salary is " << iter->getWage() << "." << endl;
			}
		}
	}
	else if (heads.size() == 1) {
		if (heads.at(0).getName() == hName) {
			if (doDelete) {
				heads.erase(heads.begin());
			}
			else {
				cout << "The salary is " << heads.at(0).getWage() << "." << endl;
			}
		}
		else {
			cout << hName << " Not Found!!!" << endl;
			return;
		}
	}
	else {
		cout << "November!!" << endl;
	}
}

void System::CheckItOut(void) {
	printOptions_ofPosition();
	targetizing(false);
	cout << "End of Check Function" << endl;
}

void System::Delete() {
	printOptions_ofPosition();
	targetizing(true);
	cout << "End of Delete Function" << endl;
}

void System::printOptions_ofMenu(void) {
	cout << "Campus Member Management System" << endl;
	cout << "1.Add New Members" << endl;
	cout << "2.List ALL Member Names" << endl;
	cout << "3.Check One's TOTAL Point or Salary" << endl;
	cout << "4.Delete a Member" << endl;
	cout << "0.Exit" << endl;
	cout << "Selection: " << endl;
}

void System::menu(void) {
	if (!allInitial()) {
		printOptions_ofMenu();
		process();
	}
	else {
		cout << "No one has been detected!!!" << endl;
		cout << "Starting addNew function automatically..." << endl;
		clear();
		addNew_Loop();
	}
}

void System::process(void) {
	unsigned short num;
	cin >> num;
	switch (num)
	{
	case 1:
		addNew_Loop();
		break;
	case 2:
		listAll();
		break;
	case 3:
		CheckItOut();
		break;
	case 4:
		Delete();
		break;
	case 0:
		exit(0);
		break;
	default:
		cout << "Plz check your input..." << endl;
		break;
	}
}

System::~System() {
	students.clear();
	teachers.clear();
	executives.clear();
	heads.clear();
}

int main(void)
{
	System manager;
	while (true)
	{
		manager.menu();
		clear();
	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
