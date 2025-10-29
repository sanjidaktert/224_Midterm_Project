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
