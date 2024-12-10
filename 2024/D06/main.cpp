#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

std::vector<std::vector<char>> grid;
char guard_directions[4] = {'^', '>', 'v', '<'};
std::pair<int, int> straight_next_pos[4] = {{-1, 0}, {0, +1}, {+1, 0}, {0, -1}};
std::pair<int, int> right_next_pos[4] = {{0, +1}, {+1, 0}, {0, -1}, {-1, 0}};

bool done_p1 = false;
bool done_p2 = false;
bool add_obstacle = false;
std::vector<std::pair<std::pair<int, int>, int>> path = {};
std::set<std::pair<int, int>> unique_locations = {};
std::set<std::pair<int, int>> obstacles = {};

struct Guard {
  int dir_index = 0;
  std::pair<int, int> pos;

  char &dir() { return guard_directions[dir_index]; }
  void rotate() {
    dir_index++;
    if (dir_index >= 4) {
      dir_index = 0;
    }
  }
};

void print_grid(Guard &guard) {
  for (size_t y = 0; y < grid.size(); y++) {
    for (size_t x = 0; x < grid[0].size(); x++) {
      std::cout << grid[y][x];
    }
    std::cout << "\n";
  }
  std::cout << guard.pos.first << "," << guard.pos.second << "\n";
  std::cout << guard.dir_index << " " << guard.dir() << "\n";
  std::cout << "\n";
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;
  Guard guard;

  int count = 0;

  // read grid
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

  while (!done_p1) {
    path.push_back(std::make_pair(
        std::make_pair(guard.pos.first, guard.pos.second), guard.dir_index));
    unique_locations.insert({guard.pos.first, guard.pos.second});
    print_grid(guard);
    try {
      std::pair<int, int> next = {
          guard.pos.first + straight_next_pos[guard.dir_index].first,
          guard.pos.second + straight_next_pos[guard.dir_index].second};
      auto grid_char = grid.at(next.first).at(next.second);
      while (grid_char == '#') {
        guard.rotate();
        next = {guard.pos.first + straight_next_pos[guard.dir_index].first,
                guard.pos.second + straight_next_pos[guard.dir_index].second};
        grid_char = grid.at(next.first).at(next.second);
      }

      grid[guard.pos.first][guard.pos.second] = '.';
      guard.pos = next;
      grid[next.first][next.second] = guard.dir();

    } catch (const std::out_of_range &e) {
      done_p1 = true;
      continue;
    }
  }

  std::cout << "\n\n";
  std::cout << "path: " << path.size() << " \n";
  std::cout << "unique locations: " << unique_locations.size() << " \n";
  std::cout << "num loops: " << obstacles.size() << " \n";
}
