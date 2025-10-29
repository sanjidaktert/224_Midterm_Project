#pragma once
#ifndef DEPOT_H
#define DEPOT_H

#include <vector>
#include "drone.h"
#include <string>

class Depot {
private:
    std::vector<Drone> drones;

public:
    Depot();

    void addDrone(const Drone& d1);
    Drone getDrone(int index) const;

    void sortByName();
    void sortByID();
    void sortByPosition();

    int searchDroneByName(const std::string& name);
    int searchDroneByID(int id);

    void swapDroneData(int index1, int index2);
    void copyDrone(int index1, int index2);
    void writeDepottoFile(const std::string& filename) const;

    void insertDroneTask(int droneIdx, int taskIdx, const std::string& task, int taskPosX, int taskPosY);

    void sortDroneDataAscending(int idx);
    void sortDroneDataDescending(int idx);

    void randomizeOrder();
    void printAllNames() const;
    void writeDepotToFile(const std::string& filename) const;
};

#endif // DEPOT_H
