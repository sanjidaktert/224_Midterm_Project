// copy all attributes from one drone into another (option 12)
void drone::operator<<(const drone& d2) {
name = d2.name;
id = d2.id;
init_position[0] = d2.init_position[0];
init_position[1] = d2.init_position[1];
for (int i = 0; i < 5; ++i) {
tasks[i] = d2.tasks[i];
task_positions[i][0] = d2.task_positions[i][0];
task_positions[i][1] = d2.task_positions[i][1];
}
}

// Displaying the drone (Option 13)
void drone::displayDrone() const {
std::cout << "Drone(Name=\"" << name << "\", ID=" << id << ")\n";
std::cout << "  Init Position: (" << init_position[0] << ", " << init_position[1] << ")\n";
for (int i = 0; i < 5; ++i) {
std::cout << "  Task[" << i << "]: \"" << tasks[i] << "\" at ("
          << task_positions[i][0] << ", " << task_positions[i][1] << ")\n";
}
}

// Sort by Ascending (Option 14)
void drone::sortByAscending() {
for (int i = 0; i < 5; ++i) {
int minIdx = i;
for (int j = i + 1; j < 5; ++j)
if (tasks[j] < tasks[minIdx]) minIdx = j;
if (minIdx != i) {
std::swap(tasks[i], tasks[minIdx]);
std::swap(task_positions[i][0], task_positions[minIdx][0]);
std::swap(task_positions[i][1], task_positions[minIdx][1]);
}
}
}

// Sort by Descending (Option 15)
void drone::sortByDescending() {
for (int i = 0; i < 5; ++i) {
int maxIdx = i;
for (int j = i + 1; j < 5; ++j)
if (tasks[j] > tasks[maxIdx]) maxIdx = j;
if (maxIdx != i) {
  std::swap(tasks[i], tasks[maxIdx]);
  std::swap(task_positions[i][0], task_positions[maxIdx][0]);
  std::swap(task_positions[i][1], task_positions[maxIdx][1]);
}
}
}
