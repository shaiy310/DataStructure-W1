#ifndef __SCHOOL_H__
#define __SCHOOL_H__

#include "library1.h"
#include "Students.h"
#include "AVLTree.h"

class School
{
	public:
		School();
		~School() = default;
		
		StatusType AddStudent(int StudentID, int Grade, int Power);
		StatusType AddTeam(int TeamID);
		StatusType MoveStudentToTeam(int StudentID, int TeamID);
		StatusType GetMostPowerful(int TeamID, int *StudentID);
		StatusType RemoveStudent(int StudentID);
		StatusType GetAllStudentsByPower(int TeamID, int **Students, int *numOfStudents);
		StatusType IncreaseLevel(int Grade, int PowerIncrease);

	private:
		Students students;
		AVLTree<int, Team*> teams;
};

#endif