#include "School.h"

School::School() : students(), teams()
{
}

StatusType School::AddStudent(int StudentID, int Grade, int Power)
{
	if ((StudentID < 1) ||
		(Grade < 0) ||
		(Power < 1)) {
		return INVALID_INPUT;
	}
	
	Student * s = new Student(StudentID, Grade, Power);
	if (s == NULL) {
		return ALLOCATION_ERROR;
	}
	
	if (!this->students.AddStudent(s)) {
		delete s;
		return FAILURE;
	}
	
	return SUCCESS;
}

StatusType School::AddTeam(int TeamID)
{
	if (TeamID < 1) {
		return INVALID_INPUT;
	}
	
	Team * t = new Team(TeamID);
	if (t == NULL) {
		return ALLOCATION_ERROR;
	}
	
	if (!this->teams.insert(TeamID, t)) {
		delete t;
		return FAILURE;
	}
	
	return SUCCESS;
}

StatusType School::MoveStudentToTeam(int StudentID, int TeamID)
{
	if ((StudentID < 1) ||
		(TeamID < 1)) {
		return INVALID_INPUT;
	}
	
	Student * s = NULL;
	Team * t = NULL;
	try {
		s = this->students.GetStudent(StudentID);
		t = this->teams.searchInTree(TeamID);
	}
	catch (DataNotFound) {
		return FAILURE;
	}
	
	s->SwitchTeam(t);
	
	return SUCCESS;
}

StatusType School::GetMostPowerful(int TeamID, int *StudentID)
{
	if ((TeamID == 0) ||
		(StudentID == NULL)) {
		return INVALID_INPUT;
	}
	
	if (TeamID < 0) {
		*StudentID = this->students.GetStrongestStudentID();
	} else {
		Team * t = NULL;
		try {
			t = this->teams.searchInTree(TeamID);
		}
		catch (DataNotFound) {
			return FAILURE;
		}
		*StudentID = t->GetStrongestStudentID();
	}
	
	return SUCCESS;
}

StatusType School::RemoveStudent(int StudentID)
{
	if (StudentID < 1) {
		return INVALID_INPUT;
	}
	
	Student * s = this->students.GetStudent(StudentID);
	if (s == NULL) {
		return FAILURE;
	}
	
	s->GetTeam()->RemoveStudent(s);
	this->students.RemoveStudent(s);
	
	delete s;
	
	return SUCCESS;
}

//StatusType School::GetAllStudentsByPower(int TeamID, int **Students, int *numOfStudents);
StatusType School::IncreaseLevel(int Grade, int PowerIncrease)
{
	if ((Grade < 0) ||
		(PowerIncrease < 1)) {
		return INVALID_INPUT;
	}
	
	int length = 0;
	Student * s = this->students.GetAllStudents(&length);
	if (length == -1) {
		return ALLOCATION_ERROR;
	}
	
	for (int i = 0; i < length; ++i) {
		if (s->GetGrade() == Grade) {
			s->IncreasePower(PowerIncrease);
		}
	}
	
	delete[] s;
	
	return SUCCESS;
}