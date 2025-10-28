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