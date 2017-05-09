#include "Students.h"

int Student::GetID()
{
	return this->id;
}

//int Student::GetID const()
//{
//	return this->id;
//}

int Student::GetGrade()
{
	return this->grade;
}

int Student::GetPower()
{
	return this->power;
}

void Student::IncreasePower(int power_increase)
{
	this->power += power_increase;
}

Team* Student::GetTeam()
{
	return this->team;
}

void Student::SwitchTeam(MyTeam* new_team)
{
	if (this->team != NULL) {
		this->team->RemoveStudent(this);
	}
	
	new_team->AddStudent(this);
	this->team = new_team;
	
}

Students::Students(): by_id(), by_power(), strongest_student(-1,-1)
{ }
	
bool Students::AddStudent(Student* student)
{
	if (student == NULL) {
		return false;
	}
	
	PowerIDPair pair(student->GetID(), student->GetPower());
	
	if (!this->by_id.insert(student->GetID(), student)) {
		return false;
	}
	// if the insertion to the first tree is successfull, 
	//this will be successfull as well
	this->by_power.insert(pair, student);
	if (pair > this->strongest_student) {
		this->strongest_student = pair;
	}
}

bool Students::RemoveStudent(int student_id)
{
	if (student_id < 0) {
		return false;
	}
	
	try {
		Student * s = this->by_id.searchInTree(student_id);
	}
	catch (const DataNotFound&) {
		return false;
	}
	
	return this->RemoveStudent(s);
}

bool Students::RemoveStudent(Student* student)
{
	if (student == NULL) {
		return false;
	}
	
	
}

Student* Students::GetStudent(int student_id)
{
	return this->by_id.searchInTree(student_id);
}

Team::Team(int id) : id(id), students()
{ }

bool Team::AddStudent(Student* s)
{
	return this->students.AddStudent(s);
}

bool Team::RemoveStudent(Student* s)
{
	return this->students.RemoveStudent(s);
}