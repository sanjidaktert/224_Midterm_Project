// drone_project_224.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include "depot.h"

// Reads each drone one by one from input file
static bool readOneDrone(std::istream& in, Drone& outD) {
    std::string line;

    // Read name
    if (!std::getline(in, line)) return false;
    while (line.empty() && std::getline(in, line));  // skip blanks
    if (line.empty()) return false;
    outD.setName(line);

    // Read ID
    if (!std::getline(in, line)) return false;
    {
        std::istringstream iss(line);
        int id;
        if (!(iss >> id)) return false;
        outD.setID(id);
    }

    // Init position
    if (!std::getline(in, line)) return false;
    {
        std::istringstream iss(line);
        int x, y;
        if (!(iss >> x >> y)) return false;
        outD.setInitPosition(x, y);
    }

    for (int i = 0; i < 5; ++i) {
        if (!std::getline(in, line)) return false;
        if (line.empty()) { --i; continue; }
        std::istringstream iss(line);
        std::string task;
        int tx, ty;
        if (!(iss >> task >> tx >> ty)) return false;
        outD.setTaskAndPosition(i, task, tx, ty);
    }
}

// Loads drones from file into Depot
static void loadInitial(const std::string& filename, Depot& depot) {
    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "Could not open " << filename << ". Starting empty.\n";
        return;
    }

    int count = 0;
    while (count < 10) {  // Amount of drones 
        Drone d;
        if (!readOneDrone(fin, d)) break;
        depot.addDrone(d);
        ++count;
    }

    std::cout << "Loaded " << count << " drone(s) from " << filename << ".\n";
}
#include <fstream>
#include <sstream>
#include <vector>
#include <cctype>
#include "Depot.h"

// Reads each drone one by one from input file
static bool readOneDrone(std::istream& in, Drone& outD) {
    std::string line;

    // Read name
    if (!std::getline(in, line)) return false;
    while (line.empty() && std::getline(in, line));  // skip blanks
    if (line.empty()) return false;
    outD.setName(line);

    // Read ID
    if (!std::getline(in, line)) return false;
    {
        std::istringstream iss(line);
        int id;
        if (!(iss >> id)) return false;
        outD.setID(id);
    }

    // Init position
    if (!std::getline(in, line)) return false;
    {
        std::istringstream iss(line);
        int x, y;
        if (!(iss >> x >> y)) return false;
        outD.setInitPosition(x, y);
    }

    for (int i = 0; i < 5; ++i) {
        if (!std::getline(in, line)) return false;
        if (line.empty()) { --i; continue; }
        std::istringstream iss(line);
        std::string task;
        int tx, ty;
        if (!(iss >> task >> tx >> ty)) return false;
        outD.setTaskAndPosition(i, task, tx, ty);
    }
}

// Loads drones from file into Depot
static void loadInitial(const std::string& filename, Depot& depot) {
    std::ifstream fin(filename);
    if (!fin) {
        std::cerr << "Could not open " << filename << ". Starting empty.\n";
        return;
    }

    int count = 0;
    while (count < 10) {  // Amount of drones 
        Drone d;
        if (!readOneDrone(fin, d)) break;
        depot.addDrone(d);
        ++count;
    }

    std::cout << "Loaded " << count << " drone(s) from " << filename << ".\n";
}

static void showMenu() {
std::cout <<
"\nMenu:\n"
"1. Sort Drones By Name\n"
"2. Sort Drones By ID\n"
"3. Sort Drones By Position\n"
"4. Randomize Drone Order\n"
"5. Add a drone\n"
"6. Retrieve a drone\n"
"7. Search Drone By Name\n"
"8. Search Drone By ID\n"
"9. Write Depot to File\n"
"10. Swap Drone Data\n"
"11. Insert Drone Task\n"
"12. Copy-Paste Drone\n"
"13. Display All Drones’ names\n"
"14. SortDroneDataAscending (per-drone tasks)\n"
"15. SortDroneDataDescending (per-drone tasks)\n"
"16. Quit\n"
"17. Export Local-Opt Routes (Nearest-Neighbor)\n"
"18. Export Global-Opt Routes (Exact)\n";
}

int main()
Depot depot;
loadInitial("Droneinput.txt", depot);
        int choice = 0;
        while (true) {
Depot depot;
loadInitial("Droneinput.txt", depot);
        int choice = 0;
        while (true) {
        showMenu();
        std::cout << "Enter choice: ";
        if (!(std::cin >> choice)) break;

        if (choice == 1) {
            depot.sortByName();
            std::cout << "Sorted by name.\n";

        } else if (choice == 2) {
            depot.sortByID();
            std::cout << "Sorted by ID.\n";

        } else if (choice == 3) {
            depot.sortByPosition();
            std::cout << "Sorted by position.\n";

        } else if (choice == 4) {
            depot.randomizeOrder();
            std::cout << "Order randomized.\n";

        } else if (choice == 5) {  // add a drone interactively
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Header (Name,ID,(x,y)):\n";
            std::string header; std::getline(std::cin, header);

            std::stringstream hs(header);
            std::string name, idStr, coordStr;
            if (!std::getline(hs, name, ',') || !std::getline(hs, idStr, ',') || !std::getline(hs, coordStr)) {
                std::cout << "Bad header format.\n"; continue;
            }

            int id = 0; int init[2];
            try { id = std::stoi(trim(idStr)); } catch (...) { std::cout << "Bad ID.\n"; continue; }
            if (!parseCoord(coordStr, init)) { std::cout << "Bad init coord.\n"; continue; }

            std::string tasks[5]; int tpos[5][2];
            for (int i = 0; i < 5; ++i) {
                std::cout << "Task " << i << " (TaskName,(x,y)):\n";
                std::string line; std::getline(std::cin, line);
                size_t comma = line.rfind(',');
                if (comma == std::string::npos) { std::cout << "Bad line.\n"; i--; continue; }
                tasks[i] = trim(line.substr(0, comma));
                std::string coord = trim(line.substr(comma+1));
                if (!parseCoord(coord, tpos[i])) { std::cout << "Bad coord.\n"; i--; continue; }
            }

            Drone d(trim(name), id, init, tasks, tpos);
            depot.addDrone(d);
            std::cout << "Drone added.\n";

        } else if (choice == 6) {
            int idx; std::cout << "Index? "; std::cin >> idx;
            try { depot.getDrone(idx).displayDrone(); }
            catch (...) { std::cout << "Bad index.\n"; }

        } else if (choice == 7) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string name; std::cout << "Name (case-sensitive): ";
            std::getline(std::cin, name);
            std::cout << "Tip: sort by name first for binary search.\n";
            depot.searchDroneByName(name);

        } else if (choice == 8) {
            int id; std::cout << "ID? "; std::cin >> id;
            std::cout << "Tip: sort by ID first for binary search.\n";
            depot.searchDroneByID(id);

        } else if (choice == 9) {
            depot.writeDepotToFile("Depot.txt");
            std::cout << "Depot written to Depot.txt\n";

        } else if (choice == 10) {
            int i, j; std::cout << "Swap data between indices i j: ";
            std::cin >> i >> j;
            depot.swapDroneData(i, j);

        } else if (choice == 11) {
            int di, ti; std::cout << "Drone index and task index (0..4): ";
            std::cin >> di >> ti;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string task; std::cout << "Task name: "; std::getline(std::cin, task);
            std::string coord; std::cout << "Coord as (x,y) or x,y: "; std::getline(std::cin, coord);
            if (!coord.empty() && coord.front() != '(') coord = "(" + coord + ")";
            int p[2];
            if (!parseCoord(coord, p)) { std::cout << "Bad coord.\n"; continue; }
            depot.insertDroneTask(di, ti, task, p);

        } else if (choice == 12) {
            int s, d; std::cout << "Copy from src index to dst index: ";
            std::cin >> s >> d;
            depot.copyDrone(s, d);

        } else if (choice == 13) {
            depot.printAllNames();

        } else if (choice == 14) {
            int idx; std::cout << "Drone index: "; std::cin >> idx;
            depot.sortDroneDataAscending(idx);

        } else if (choice == 15) {
            int idx; std::cout << "Drone index: "; std::cin >> idx;
            depot.sortDroneDataDescending(idx);

        } else if (choice == 16) {
            std::cout << "Bye!\n";
            break;

        } else if (choice == 17) {
            depot.exportLocalOptRoutes("Routes_Local.txt");
            std::cout << "Wrote Routes_Local.txt\n";

        } else if (choice == 18) {
            depot.exportGlobalOptRoutes("Routes_Global.txt");
            std::cout << "Wrote Routes_Global.txt\n";
        }
    }
return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
