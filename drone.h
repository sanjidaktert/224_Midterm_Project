#pragma once
#ifndef DRONE_H
#define DRONE_H
#include <string>
using namespace std;

class drone {
private:
	string name; //name of the drone
	int id; //id of the drone
	string tasks[5]; //last 5 delivery task names
	int init_position[2]; //(x,y) location
	int task_positions[5][2]; //delivery position for each delivery task

public:
	//Constructors
	drone();
	drone(const string& name, int id, const string& tasks, int init_position[2], int task_positions[5][2]);

	//Getters
	string getName();
	int getId();
	string getTasks();
	int getInit();
	int taskPos();

	//Setters
	void setName(const string& n);
	void setId(int id);
	void setTasks(const string t[5]);
	void setInit(const int pos[2]);
	void setTaskPos(const int pos[5][2]);

	//Index setters
	//maps a task name to tasks[]
	void setTasks(int index, const string& task); 
	//sets the initial (x,y) position
	void setInit(int x, int y);
	//sets the drone's position for a specific task
	void setTaskPos(int index, int x, int y);

	//Sorting 
	//void sortByAscending();
	//void sortByDescending();
	void sortByName();
	void sortById();
	void sortByTasks();
	void sortByInit();
	void sortByTaskPos();

	//Operator overloads
	void operator<<(drone& d2); //copies all attributes
	void operator-(drone& d2); //swaps the tasks and their positions

	//Display
	void displayDrone(); //displays all the attributes 
};
#endif 