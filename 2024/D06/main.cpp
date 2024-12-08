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

bool done = false;
std::vector<std::pair<int, int>> path = {};
std::set<std::pair<int, int>> seen_locations = {};

struct Guard {
  int dir_index = 0;
  std::pair<int, int> pos;

  char &dir() { return guard_directions[dir_index]; }
};

void print_grid(Guard guard) {
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

  path.push_back(guard.pos);

  while (!done) {
    print_grid(guard);
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
    std::pair<int, int> right_pos = {
        guard.pos.first + blocked_next_pos[guard.dir_index].first,
        guard.pos.second + blocked_next_pos[guard.dir_index].second};
    // GOING RIGHT
    if (grid_char == '#') {
      guard.pos = right_pos;
      guard.dir_index++;
      if (guard.dir_index >= 4) {
        guard.dir_index = 0;
      }
      // GOING FORWARD
    } else {
      guard.pos = next_pos;
    }
    grid[guard.pos.first][guard.pos.second] = guard.dir();

    path.push_back(guard.pos);
  }

  seen_locations = {path.begin(), path.end()};
  std::cout << "\n";
  std::cout << "path: \n";
  for (auto p : path) {
    std::cout << "(" << p.first << "," << p.second << ")";
  }
  std::cout << "\nunique locations: \n";
  for (auto s : seen_locations) {
    std::cout << "(" << s.first << "," << s.second << ")";
  }
  std::cout << "\n" << seen_locations.size() << "\n";
}
