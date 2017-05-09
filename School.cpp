#include "School.h"

School::School() : students(), teams()
{
	
}

School::~School()
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
}

//StatusType School::RemoveStudent(int StudentID);
//StatusType School::GetAllStudentsByPower(int TeamID, int **Students, int *numOfStudents);
//StatusType School::IncreaseLevel(int Grade, int PowerIncrease);