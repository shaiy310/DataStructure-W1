#include "Students.h"

Student::Student(int StudentID, int Grade, int Power) : id(StudentID),
	grade(Grade), power(Power)
{ }

int Student::GetID()
{
	return this->id;
}

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
		return this->RemoveStudent(s);
	}
	catch (const DataNotFound&) {
		return false;
	}	
}

bool Students::RemoveStudent(Student * student)
{
	if (student == NULL) {
		return false;
	}
	
	// check if the student exists
	try {
		(void)this->by_id.searchInTree(student->GetID());
	}
	catch (const DataNotFound&) {
		return false;
	}

	// remove the student
	PowerIDPair pair(student->GetID(), student->GetPower());
	if (pair == this->strongest_student) {
		// in case we remove the strongest student
		Student * s = this->by_power.getPreviousInOrderSearchOfMax(
			this->strongest_student);
		this->strongest_student = PowerIDPair(s->GetID(), s->GetPower());
	}

	this->by_id.deleteKey(student->GetID());
	this->by_power.deleteKey(pair);	
	
	return true;
}

Student* Students::GetAllStudents(int * length)
{
	if (length == NULL) {
		return NULL;
	}
	
	*length = this->by_id.getSize();
	if (*length == 0) {
		return NULL;
	}
	
	Student** all = new Student*[*length];
	if (all == NULL) {
		// report error
		*length = -1;
		return NULL;
	}
	
	this->by_id.getDataInOrder(all);
	return *all;
}

//////////////////////////////////////////////////////
//					TODO: change this code
//////////////////////////////////////////////////////
Student* Students::GetAllStudentsByPower(int * length)
{
		if (length == NULL) {
		return NULL;
	}
	
	*length = this->by_power.getSize();
	if (*length == 0) {
		return NULL;
	}
	
	Student** all = new Student*[*length];
	if (all == NULL) {
		// report error
		*length = -1;
		return NULL;
	}
	
	this->by_power.getDataInOrder(all);
	return *all;

}

Student* Students::GetStudent(int student_id)
{
	return this->by_id.searchInTree(student_id);
}

int Students::GetStrongestStudentID()
{
	return this->strongest_student.GetID();
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

int Team::GetStrongestStudentID()
{
	return this->students.GetStrongestStudentID();
}