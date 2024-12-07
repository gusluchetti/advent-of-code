#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

std::vector<std::vector<char>> grid;
char guard_directions[4] = {'^', '>', 'v', '<'};
std::pair<int, int> normal_next_pos[4] = {{-1, 0}, {0, +1}, {+1, 0}, {0, -1}};
std::pair<int, int> blocked_next_pos[4] = {{0, +1}, {+1, 0}, {0, -1}, {-1, 0}};

struct Guard {
  int dir_index = 0;
  std::pair<int, int> pos;

  char &dir() { return guard_directions[dir_index]; }
};

void print_grid() {
  for (size_t y = 0; y < grid.size(); y++) {
    for (size_t x = 0; x < grid[0].size(); x++) {
      std::cout << grid[y][x];
    }
    std::cout << "\n";
  }
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;
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
      for (size_t d = 0; d < sizeof(guard_directions) - 1; d++) {
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
    // print_grid();
    std::pair<int, int> next_pos = {
        guard.pos.first + normal_next_pos[guard.dir_index].first,
        guard.pos.second + normal_next_pos[guard.dir_index].second};

    char grid_char = '.';
    try {
      grid_char = grid.at(next_pos.first).at(next_pos.second);
    } catch (const std::out_of_range &e) {
      done = true;
      continue;
    }

    grid[guard.pos.first][guard.pos.second] = '.';
    if (grid_char == '#') {
      guard.pos = {guard.pos.first + blocked_next_pos[guard.dir_index].first,
                   guard.pos.second + blocked_next_pos[guard.dir_index].second};
      guard.dir_index++;
      if (guard.dir_index >= 4) {
        guard.dir_index = 0;
      }
      std::cout << "\n" << guard.dir_index << " " << guard.dir() << "\n";
    } else {
      guard.pos = next_pos;
    }
    grid[guard.pos.first][guard.pos.second] = guard.dir();

    auto res = seen_locations.insert(guard.pos);
    if (res.second == true) {
      std::cout << "new pos added: " << guard.pos.first << ","
                << guard.pos.second << "\n";
    }
    if (res.second == false) {
      std::cout << "already seen" << "\n";
    }
  }

  std::cout << seen_locations.size() << "/n";
}
