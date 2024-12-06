#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

char guard_directions[4] = {'^', '>', 'v', '<'};
std::pair<int, int> normal_next_pos[4] = {{-1, 0}, {0, +1}, {+1, 0}, {0, -1}};
std::pair<int, int> blocked_next_pos[4] = {{0, +1}, {+1, 0}, {0, -1}, {-1, 0}};

struct Guard {
  int dir_index = 0;
  char &dir = guard_directions[dir_index];
  std::pair<int, int> pos;
};

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;
  std::vector<std::vector<char>> grid;
  Guard guard;

  bool done = false;
  std::set<std::pair<int, int>> seen_locations = {};

  int count = 0;
  while (std::cin) {
    getline(std::cin, line);
    if (std::cin.eof()) {
      std::cout << "eof" << "\n";
      break;
    }

    for (size_t i = 0; i < line.size() - 1; i++) {
      char c = line[i];
      for (int d = 0; d < sizeof(guard_directions) - 1; d++) {
        if (c == guard_directions[d]) {
          guard.pos = {count, i};
          guard.dir_index = d;
        }
      }
    }
    grid.push_back(std::vector<char>(line.begin(), line.end()));
    count++;
  }

  seen_locations.insert(guard.pos);
  std::cout << guard.pos.first << "," << guard.pos.second << "\n";

  while (!done) {
    for (size_t y = 0; y < grid.size() - 1; y++) {
      for (size_t x = 0; x < grid[0].size() - 1; x++) {
        std::cout << grid[y][x];
      }
      std::cout << "\n";
    }

    std::pair<int, int> next_pos = {
        guard.pos.first + normal_next_pos[guard.dir_index].first,
        guard.pos.second + normal_next_pos[guard.dir_index].second};
    std::cout << "new pos: " << guard.pos.first << "," << guard.pos.second
              << "\n";

    if (grid[next_pos.first][next_pos.second] == '#') {
      guard.pos = {guard.pos.first + blocked_next_pos[guard.dir_index].first,
                   guard.pos.second + blocked_next_pos[guard.dir_index].second};
      guard.dir_index++;
    } else {
      guard.pos = next_pos;
    }

    try {
      char new_location = grid.at(next_pos.first).at(next_pos.second);
    } catch (const std::out_of_range &e) {
      done = true;
    }

    auto res = seen_locations.insert(next_pos);
    if (res.second == true) {
      std::cout << "new pos";
    }
    if (res.second == false) {
      std::cout << "already seen";
    }
  }

  std::cout << seen_locations.size() << "/n";
}
