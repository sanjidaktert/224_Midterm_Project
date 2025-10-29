#include "depot.h"
#include <iostream>
#include <fstream>
#include <algorithm> // Only for swap
#include <cmath>
#include <random>

Depot::Depot() {}

void Depot::addDrone(const Drone& d1) {
    drones.push_back(d1);
}

Drone Depot::getDrone(int index) const {
    return drones.at(index);
}

void Depot::sortByName() {
    for (size_t i = 0; i < drones.size(); ++i) {
        for (size_t j = i + 1; j < drones.size(); ++j) {
            if (drones[i].getName() > drones[j].getName() ||
               (drones[i].getName() == drones[j].getName() && drones[i].getId() > drones[j].getId())) {
                std::swap(drones[i], drones[j]);
            }
        }
    }
}

void Depot::sortByID() {
    for (size_t i = 0; i < drones.size(); ++i) {
        for (size_t j = i + 1; j < drones.size(); ++j) {
            if (drones[i].getId() > drones[j].getId()) {
                std::swap(drones[i], drones[j]);
            }
        }
    }
}

void Depot::sortByPosition() {
    auto distance = [](const Drone& d) {
        int x = d.getInit()[0];
        int y = d.getInit()[1];
        return std::sqrt(x*x + y*y);
    };
    for (size_t i = 0; i < drones.size(); ++i) {
        for (size_t j = i + 1; j < drones.size(); ++j) {
            if (distance(drones[i]) > distance(drones[j])) {
                std::swap(drones[i], drones[j]);
            }
        }
    }
}

void Depot::copyDrone(int index1, int index2) {
	// check if the indexes are valid (not less than 0 or too big)
	if (index1 < 0 || index1 >= (int)drones.size()) {
		cout << "bad first index\n";
		return;
	}
	if (index2 < 0 || index2 >= (int)drones.size()) { 
		cout << "bad second index\n";
		return;
	}
	drones[index2] = drones[index1]; // copy all info from one drone to another
	cout << "Drone " << index2 << " copied from drone " << index1 << endl; //output 
}


void Depot::printAllNames() const {
	if (drones.empty()) { //checks if there are even any drones 
		cout << "There are no drones";
		return;
	}
	cout << "Drones: ";
	for (size_t i = 0; i < drones.size(); ++i) { // go through each drone and show its name
		cout << i << ". " << drones[i].getName() << endl;
	}
	// print how many total drones there are
	cout << "total: " << drones.size() << " drone(s)\n";
}

void sortDroneDataAscending(int idx) {
	int idx;
	cout << "drone index? "; //asks which drone to sort
	cin >> idx;
	cin.ignore(); //clears the input

	if (idx < 0 || idx >= (int)drones.size()) { //checks for a valid input
		cout << "This is not a index\n";
		return;
	}

	Drone& d = drones[idx]; //get a reference to that drone to get the drone we want
	// bubble sort
	for (int i = 0; i < 5 - 1; ++i) {       // outer loop for passes
		for (int j = 0; j < 5 - i - 1; ++j) { //goes through the tasks
			if (d.getTask(j) > d.getTask(j + 1)) { //checks the order
				string temp = d.getTask(j); //saves the current task and its position
				int x = d.getTaskPos(j)[0];
				int y = d.getTaskPos(j)[1];
				d.setTask(j, d.getTask(j + 1)); // move the next task up
				d.setTaskPos(j, d.getTaskPos(j + 1)[0], d.getTaskPos(j + 1)[1]);
				d.setTask(j + 1, temp); //put the stored task one down 
				d.setTaskPos(j + 1, x, y);
			}
		}
	}
	cout << "sorted";
}

void sortDroneDataDescending(int idx) { //does the same thing but descending
	int idx;
	cout << "drone index? ";
	cin >> idx;
	cin.ignore();

	if (idx < 0 || idx >= (int)drones.size()) {
		cout << "Not a index\n";
		return;
	}

	Drone& d = drones[idx];
	for (int i = 0; i < 5 - 1; ++i) {
		for (int j = 0; j < 5 - i - 1; ++j) {
			if (d.getTask(j) < d.getTask(j + 1)) { //if the next task should come first 
				string temp = d.getTask(j); //stores the current task into a temp int
				int x = d.getTaskPos(j)[0]; //save the x and y position
				int y = d.getTaskPos(j)[1];
				d.setTask(j, d.getTask(j + 1)); //replace the current tasks with the ones after
				d.setTaskPos(j, d.getTaskPos(j + 1)[0], d.getTaskPos(j + 1)[1]);
				d.setTask(j + 1, temp); //put the stored task into the next position 
				d.setTaskPos(j + 1, x, y);
			}
		}
	}
	cout << "sorted\n";
}

