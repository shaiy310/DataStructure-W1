#ifndef __STUDENTS_H__
#define __STUDENTS_H__

#include "AVLTree.h"

typedef class Team MyTeam;
class Student
{
	public:
		Student(int StudentID, int Grade, int Power);
		
		const int GetID() const;
		int GetID();
		const int GetGrade() const;
		int GetGrade();
		const int GetPower() const;
		int GetPower();
		void IncreasePower(int power_increase);
		MyTeam* GetTeam();
		void SwitchTeam(MyTeam* new_team);
		
	private:
		int id;
		int grade;
		int power;
		MyTeam* team;
};

class Students
{
	public:
		Students();
		~Students() = default;
		
		bool AddStudent(Student* student);
		bool RemoveStudent(int student_id);
		bool RemoveStudent(Student* student);
		Student* GetStudent(int student_id);
		int GetStrongestStudentID();
		
	private:
	
		class PowerIDPair {
			public:
				PowerIDPair(int id, int power) : id(id), power(power)
				{ }
				PowerIDPair(PowerIDPair& other) = default;
				~PowerIDPair() = default;
				PowerIDPair& operator=(const PowerIDPair& other) = default;
				
				bool operator>(const PowerIDPair& other)
				{
					if (this->power == other.power) {
						return (this->id < other.id);
					} else {
						return (this->power > other.power);
					}
				}
			private:
				int power;
				int id;
		};
		AVLTree<int, Student*> by_id;
		AVLTree<PowerIDPair, Student*> by_power;
		PowerIDPair strongest_student;
};

class Team
{
	public:
		Team(int id);
		~Team() = default;
		
		bool AddStudent(Student* s);
		bool RemoveStudent(Student* s);
		
	private:
		int id;
		Students students;
};
#endif