#include<iostream>
#include<stdio.h>
#include<cstring>
#include<string>
#include<string.h>

using namespace std;

class Student {

private:

	char Sname[20];

	int age = 0;

	char id[20];

	int scores[4];

public:
		void set_student_scores(){

			int i = 0;

			char k;

			for (i = 0; i< 3; ++i) { cin >> scores[i] >> k; }

			cin >> scores[3];
	
		}

		void set_student_age(int stAge){ stAge = age;}

		void set_student_id(char* ID){ strcpy(id, ID); }

		void set_student_name(char* name){ strcpy(Sname, name); }

		int get_student_average_scores(){

			int avg = int((scores[0] + scores[1] + scores[2] + scores[3]) / 4);

			return avg;
		}


};

int main() {

	Student *student = new Student;

	char* name_ = new char[20];

	char* id_ = new char[20];

	int age = 0;

	char k;

	cin.getline(name_, 20, ',');

	cin >> age >> k;

	cin.getline(id_, 20, ',');

	student->set_student_name(name_);

	student->set_student_age(age);

	student->set_student_id(id_);

	student->set_student_scores();

	cout << name_ << ',' << age << ',' << id_ << ',' << student->get_student_average_scores();

	delete[] name_;

	delete[] id_;

	delete student;

	return 0;
}