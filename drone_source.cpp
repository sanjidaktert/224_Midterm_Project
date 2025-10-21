#include "drone.h"
#include <iostream>
#include <iomanip>
using namespace std;

//Default constructor
drone::drone() : name(""), id() {
	for (int i = 0; i < 5; i++) { //loop that runs 5 times since tasks[5]
		tasks[i] = ""; //i represents each element (empty strings) (each task)
		//we use 0 and 1 here because the second part of the 2D array [5][2] has [2] so 0,1
		task_positions[i][0] = 0; //x coordinate for task i 
		task_positions[i][1] = 0; //y coordinate for task i 
	}
	init_position[0] = 0; //sets the x coordinate of init_position to 0 and 1 respectively
	init_position[1] = 1; //0 is the first value and 1 is the second value x,y
}
//Parameterized constructor
drone::drone(const string& name, int id, int init_position, int task_position)
	:name(name), id(id), init_position(init_position), task_position(task_position) {
}

//Getters
string drone::getName() const {
	return name;
}
int drone::getId() {
	return id;
}
string drone::getTasks() const {
	return tasks[5];
}
int drone::getInit() {
	return init_position[2];
}
int drone::taskPos() {
	return task_positions[5][2];
}

//Setters
void setName(const string& n) {
	name = name;
}
void setId(int id) {
	id = id;
}
void setTasks(const string t[5]) {

}
void setInit(const int pos[2]) {

}
void setTaskPos(const int pos[5][2]) {

}

//Sorting algorithms
void sortByAscending() {

}
void sortByDescending() {

}


//Display outputs
void displayDrone() {

}