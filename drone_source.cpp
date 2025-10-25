#include "drone.h"
#include <iostream>
using namespace std;

//Default constructor
drone::drone() : name(""), id()
{
	for (int i = 0; i < 5; i++) { //loop that runs 5 times since tasks[5]
		tasks[i] = ""; //i represents each element (empty strings) (each task)
		//we use 0 and 1 here because the second part of the 2D array [5][2] has [2] so 0,1
		task_positions[i][0] = 0; //x coordinate for task i 
		task_positions[i][1] = 0; //y coordinate for task i 
	}
	init_position[0] = 0; //sets the x coordinate of init_position to 0 and 1 respectively
	init_position[1] = 1; //0 is the first value and 1 is the second value x,y
}

//Getters
string drone::getName() const {
	return name;
}
int drone::getId() const {
	return id;
}
string drone::getTasks(int index) const {
	return tasks[index];
}
int drone::getInitX() const {
	return init_position[0];
}
int drone::getInitY() const {
	return init_position[1];
}
int drone::getTaskPosX(int index) const {
	return task_positions[index][0];
}
int drone::getTaskPosY(int index) const {
	return task_positions[index][1];
}

//Setters
void drone::setName(const string& n) {
	name = n;
}
void drone::setId(int id) {
	id = id;
}
void drone::setTasks(int index, const string& t) {
	tasks[index] = t;
}
void drone::setInitPos(int x, int y) {
	init_position[0] = x;
	init_position[1] = y;
}
void drone::setTaskPos(int index, int x, int y) {
	task_positions[index][0] = x;
	task_positions[index][1] = y;
}


//Sorting algorithms
void drone::sortByAscending() {
	for (int i = 0; i < 4; i++) { //repeat for all the tasks
		for (int j = 0; j < 4 - i; j++) {
			if (tasks[j] > tasks[j + 1]) { //checks if the task is in order, if not, swap
				string temp = tasks[j]; //bubble sort used to swap the task names
				tasks[j] = tasks[j + 1];
				tasks[j + 1] = temp;
				//Swaps their task positions so that they match
				int tempX = task_positions[j][0]; //matching the x,y positions
				int tempY = task_positions[j][1];
				//Moves the coordinates of another task a spot up from the array
				int tempX = task_positions[j][0] = task_positions[j + 1][0];
				int tempX = task_positions[j][1] = task_positions[j + 1][1];
				//Restore the original x,y coordinate in tempX,Y 
				task_positions[j + 1][0] = tempX;
				task_positions[j + 1][1] = tempY;
			}
		}
	}
}
void drone::sortByDescending() { //bascially does the same thing as ascend but reversed
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4 - i; j++) {
			if (tasks[j] > tasks[j + 1]) { //this logic makes it so it's descending
				string temp = tasks[j];
				tasks[j] = tasks[j + 1];
				tasks[j + 1] = temp;

				int tempX = task_positions[j][0];
				int tempY = task_positions[j][1];
				int tempX = task_positions[j][0] = task_positions[j + 1][0];
				int tempX = task_positions[j][1] = task_positions[j + 1][1];
				task_positions[j + 1][0] = tempX;
				task_positions[j + 1][1] = tempY;
			}
		}
	}
}


//Display outputs
void drone::displayDrone() {
	cout << "This is the drone's name: " << name << endl;
	cout << "This is the drone's ID: " << id << endl;
	cout << "Initial position: (" << init_position[0] << ", " << init_position[1] << ")" << endl;
	cout << "Tasks and positions: " << endl;
	for (int i = 0; i < 5; i++) {
		cout << "Task" << i + 1 << ": " << tasks[i] << endl;
		cout << " -> (" << task_positions[i][0] << ", " << task_positions[i][1] << ")" << endl;
	}
}

//Op << 
//This copies all the data from another drone
void drone::operator<<(drone& d2) {
	name = d2.name; //copies the name from d2 into drone and does the same for the ID
	id = d2.id;
	for (int i = 0; i < 5; i++) { //goes through all 5 tasks and copies name and pos
		tasks[i] = d2.tasks[i];	  //copies name
		task_positions[i][0] = 0; //x coordinate for task i 
		task_positions[i][1] = 0; //y coordinate for task i
	}
	init_position[0] = d2.init_position[0]; //copies the initial x,y 
	init_position[1] = d2.init_position[1];
}

//Op -
//This swaps the tasks and task positions between drones
void drone::operator-(drone& d2) {
	for (int i = 0; i < 5; i++) {
		string temp = tasks[i]; //bubble sort used to store the tasks
		tasks[i] = d2.tasks[i];
		d2.tasks[i] = temp;
		int tempX = task_positions[i][0]; //temp stores the x and y positions of drone
		int tempY = task_positions[i][1];
		task_positions[i][0] = task_positions[i][0]; //copies the d2's (x,y) pos into this drone
		task_positions[i][1] = task_positions[i][1];
		d2.task_positions[i][0] = tempX; //copy stored x,y position into d2
		d2.task_positions[i][1] = tempY;
	}
}