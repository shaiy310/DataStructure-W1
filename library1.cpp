#include "library1.h"
#include "School.h"

void* Init()
{
	School * DS = new School();
	return (void*)DS;
}

StatusType AddStudent(void *DS, int StudentID, int Grade, int Power)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	return ((School*)DS)->AddStudent(StudentID, Grade, Power);
}

StatusType AddTeam(void *DS, int TeamID)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	
	return ((School*)DS)->AddTeam(TeamID);
}

StatusType MoveStudentToTeam(void *DS, int StudentID, int TeamID)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	
	return ((School*)DS)->MoveStudentToTeam(StudentID, TeamID);
}

StatusType GetMostPowerful(void *DS, int TeamID, int *StudentID)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	
	return ((School*)DS)->GetMostPowerful(TeamID, StudentID);
}

StatusType RemoveStudent(void *DS, int StudentID)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	
	return ((School*)DS)->RemoveStudent(StudentID);
}

StatusType GetAllStudentsByPower(void *DS, int TeamID, int **Students, 
	int *numOfStudents)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	
	return ((School*)DS)->GetAllStudentsByPower(TeamID, Students, numOfStudents);
}

StatusType IncreaseLevel(void *DS, int Grade, int PowerIncrease)
{
	if (DS == NULL) {
		return INVALID_INPUT;
	}
	
	return ((School*)DS)->IncreaseLevel(Grade, PowerIncrease);
}

void Quit(void** DS)
{
	if (*DS != NULL) {
		delete *((School**)DS);
	}
	*DS = NULL;
}