#include "depot.h"
#include <iostream>
#include <fstream>
#include <limits>
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

int Depot::searchDroneByName(std::string name) {
    int low = 0;
    int high = static_cast<int>(drones.size()) - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (name < drones[mid].getName()) {
            high = mid - 1;
        } else if (name > drones[mid].getName()) {
            low = mid + 1;
        } else {
            std::cout << "Drone with name \"" << name << "\" found at index "
                      << mid << std::endl;
            return mid;
        }
    }
    std::cout << "Drone with name \"" << name << "\" not found.\n";
    return -1;
}

int Depot::searchDroneByID(int id) {
    int low = 0;
    int high = static_cast<int>(drones.size()) - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (id < drones[mid].getID()) {
            high = mid - 1;
        } else if (id > drones[mid].getID()) {
            low = mid + 1;
        } else {
            std::cout << "Drone with ID " << id << " found at index "
                      << mid << std::endl;
            return mid;
        }
    }
    std::cout << "Drone with ID " << id << " not found.\n";
    return -1;
}

void Depot::writeDepotToFile(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cout << "Error opening file: " << filename << std::endl;
        return;
    }
    for (const auto& d : drones) {
        int init[2];
        d.getInitPosition(init);
        ofs << d.getName() << "," << d.getID()
            << ",(" << init[0] << "," << init[1] << ")\n";
        for (int i = 0; i < 5; ++i) {
            std::string t;
            int p[2];
            d.getTask(i, t);
            d.getTaskPosition(i, p);
            ofs << "  " << t << " (" << p[0] << "," << p[1] << ")\n";
        }
        ofs << "\n";
    }
    std::cout << "Depot successfully written to " << filename << "\n";
}

void Depot::swapDroneData(int i, int j) {
    if (i < 0 || j < 0 || i >= (int)drones.size() || j >= (int)drones.size()) {
        std::cout << "Invalid indices.\n";
        return;
    }
    drones[i] - drones[j];  // uses Drone::operator- to swap tasks
    std::cout << "Swapped task data between drones " << i << " and " << j << ".\n";
}

void Depot::insertDroneTask(int droneIdx, int taskIdx, const std::string& task, const int pos[2]) {
    if (droneIdx < 0 || droneIdx >= (int)drones.size() ||
        taskIdx < 0 || taskIdx >= 5) {
        std::cout << "Invalid indices.\n";
        return;
    }
    drones[droneIdx].setTask(taskIdx, task);
    drones[droneIdx].setTaskPosition(taskIdx, pos);
    std::cout << "Inserted task \"" << task << "\" at index "
              << taskIdx << " for drone " << droneIdx << ".\n";
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

static double dist2d(int ax, int ay, int bx, int by) {
    double dx = double(ax - bx), dy = double(ay - by);
    return std::sqrt(dx*dx + dy*dy);
}

void Depot::exportLocalOptRoutes(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cout << "Error opening " << filename << "\n";
        return;
    }

    for (int dIdx = 0; dIdx < (int)drones.size(); ++dIdx) {
        const Drone& d = drones[dIdx];

        // grab start and the 5 tasks
        int start[2]; d.getInitPosition(start);
        int tpos[5][2];
        std::string tname[5];
        for (int i = 0; i < 5; ++i) {
            d.getTask(i, tname[i]);
            d.getTaskPosition(i, tpos[i]);
        }

        bool used[5] = {false,false,false,false,false};
        int order[5];
        int cx = start[0], cy = start[1];
        double total = 0.0;

        for (int step = 0; step < 5; ++step) {
            int best = -1;
            double bestd = std::numeric_limits<double>::infinity();
            for (int k = 0; k < 5; ++k) if (!used[k]) {
                double dd = dist2d(cx, cy, tpos[k][0], tpos[k][1]);
                if (dd < bestd) { bestd = dd; best = k; }
            }
            used[best] = true;
            order[step] = best;
            total += bestd;
            cx = tpos[best][0]; cy = tpos[best][1];
        }
        total += dist2d(cx, cy, start[0], start[1]);

        ofs << "Drone " << dIdx << " (" << d.getName() << ")\n";
        ofs << "  Route (Nearest-Neighbor): ";
        for (int i = 0; i < 5; ++i) {
            ofs << tname[order[i]];
            if (i < 4) ofs << " -> ";
        }
        ofs << " -> START\n";
        ofs << "  Total Distance: " << total << "\n\n";
    }

    std::cout << "Wrote local-opt routes to " << filename << "\n";
}

void Depot::exportGlobalOptRoutes(const std::string& filename) const {
    std::ofstream ofs(filename);
    if (!ofs) {
        std::cout << "Error opening " << filename << "\n";
        return;
    }

    for (int dIdx = 0; dIdx < (int)drones.size(); ++dIdx) {
        const Drone& d = drones[dIdx];

        int start[2]; d.getInitPosition(start);
        int tpos[5][2]; std::string tname[5];
        for (int i = 0; i < 5; ++i) {
            d.getTask(i, tname[i]);
            d.getTaskPosition(i, tpos[i]);
        }

        int perm[5] = {0,1,2,3,4};
        int bestPerm[5] = {0,1,2,3,4};
        double bestDist = std::numeric_limits<double>::infinity();

        do {
            double cur = 0.0;
            int cx = start[0], cy = start[1];
            for (int i = 0; i < 5; ++i) {
                int k = perm[i];
                cur += dist2d(cx, cy, tpos[k][0], tpos[k][1]);
                cx = tpos[k][0]; cy = tpos[k][1];
            }
            cur += dist2d(cx, cy, start[0], start[1]); // return to start

            if (cur < bestDist) {
                bestDist = cur;
                for (int i = 0; i < 5; ++i) bestPerm[i] = perm[i];
            }
        } while (std::next_permutation(perm, perm+5));

        ofs << "Drone " << dIdx << " (" << d.getName() << ")\n";
        ofs << "  Route (Exact Shortest): ";
        for (int i = 0; i < 5; ++i) {
            ofs << tname[bestPerm[i]];
            if (i < 4) ofs << " -> ";
        }
        ofs << " -> START\n";
        ofs << "  Total Distance: " << bestDist << "\n\n";
    }

    std::cout << "Wrote global-opt routes to " << filename << "\n";
}
