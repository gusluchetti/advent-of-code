#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// NOTE:
// possible obstacle for infinite loop HAS to be on the path
// obstacle placement (on path) leads to infinite line to the right
// if line reaches path + another position (to check direction) = loop

std::vector<std::vector<char>> grid;
char guard_directions[4] = {'^', '>', 'v', '<'};
std::pair<int, int> straight_next_pos[4] = {{-1, 0}, {0, +1}, {+1, 0}, {0, -1}};
std::pair<int, int> right_next_pos[4] = {{0, +1}, {+1, 0}, {0, -1}, {-1, 0}};

bool done = false;
std::vector<std::pair<int, int>> path = {};
std::set<std::pair<int, int>> seen_locations = {};

bool should_check = false;
int num_loops = 0;

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

// 863 too low
bool check_path_collision(std::vector<std::pair<int, int>> &path, Guard guard) {
  bool should_quit = false;
  std::vector<std::pair<int, int>> line = {
      {guard.pos.first + right_next_pos[guard.dir_index].first,
       guard.pos.second + right_next_pos[guard.dir_index].second}};
  guard.rotate();

  while (!should_quit) {
    std::pair<int, int> next = {
        line.back().first + straight_next_pos[guard.dir_index].first,
        line.back().second + straight_next_pos[guard.dir_index].second};

    try {
      auto on_grid = grid.at(next.first).at(next.second);
      if (on_grid == '#') {
        guard.rotate();
        next = {
            line.back().first + straight_next_pos[guard.dir_index].first,
            line.back().second + straight_next_pos[guard.dir_index].second,
        };
      }
    } catch (const std::out_of_range &e) {
      should_quit = true;
      continue;
    }

    line.push_back(next);
  }

  for (size_t j = 0; j < line.size() - 1; j++) {
    std::cout << line[j].first << "," << line[j].second << " ";
    for (size_t i = 0; i < path.size() - 1; i++) {
      if (line[j] == path[i] && line[j + 1] == path[i + 1]) {
        std::cout << "LOOPED!!\n";
        num_loops++;
        return true;
      }
    }
  }
  std::cout << "\n";

  return false;
}

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

  while (!done) {
    path.push_back(guard.pos);
    auto res = seen_locations.insert(guard.pos);
    if (res.second == false) {
      should_check = true;
    }

    // print_grid(guard);
    std::pair<int, int> next_pos = {
        guard.pos.first + straight_next_pos[guard.dir_index].first,
        guard.pos.second + straight_next_pos[guard.dir_index].second};

    char grid_char = '.';
    try {
      grid_char = grid.at(next_pos.first).at(next_pos.second);
    } catch (const std::out_of_range &e) {
      done = true;
      continue;
    }

    grid[guard.pos.first][guard.pos.second] = '.';
    std::pair<int, int> right_pos = {
        guard.pos.first + right_next_pos[guard.dir_index].first,
        guard.pos.second + right_next_pos[guard.dir_index].second};

    if (should_check) {
      bool is_loop = check_path_collision(path, guard);
    }
    // GOING RIGHT
    if (grid_char == '#') {
      guard.pos = right_pos;
      guard.rotate();
      // GOING FORWARD
    } else {
      guard.pos = next_pos;
    }
    grid[guard.pos.first][guard.pos.second] = guard.dir();
  }

  std::cout << "\n";
  std::cout << "path: " << path.size() << " \n";
  ;
  for (auto p : path) {
    std::cout << "(" << p.first << "," << p.second << ")";
  }
  std::cout << "\nunique locations: " << seen_locations.size() << " \n";
  for (auto s : seen_locations) {
    std::cout << "(" << s.first << "," << s.second << ")";
  }
  std::cout << "\nnum loops: " << num_loops << " \n";
}
