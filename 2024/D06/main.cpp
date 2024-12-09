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
bool add_obstacle = false;
std::vector<std::pair<int, int>> path = {};
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

// 1896 too low | 1922, 2013 incorrect
bool check_path_collision(Guard guard_cp,
                          std::vector<std::vector<char>> grid_cp) {
  bool should_quit = false;

  std::vector<std::pair<int, int>> curr_path = {
      {guard_cp.pos.first + right_next_pos[guard_cp.dir_index].first,
       guard_cp.pos.second + right_next_pos[guard_cp.dir_index].second}};
  guard_cp.rotate();

  while (!should_quit) {
    int dupe_count = 0;

    std::pair<int, int> next = {
        curr_path.back().first + straight_next_pos[guard_cp.dir_index].first,
        curr_path.back().second + straight_next_pos[guard_cp.dir_index].second};

    try {
      auto on_grid = grid_cp.at(next.first).at(next.second);
      if (on_grid == '#') {
        next = {
            curr_path.back().first + right_next_pos[guard_cp.dir_index].first,
            curr_path.back().second + right_next_pos[guard_cp.dir_index].second,
        };
        guard_cp.rotate();
      }
    } catch (const std::out_of_range &e) {
      should_quit = true;
      continue;
    }

    curr_path.push_back(next);

    auto penultimate = curr_path[curr_path.size() - 2];
    auto last = curr_path[curr_path.size() - 1];
    for (size_t j = 0; j < curr_path.size() - 1; j++) {
      if (curr_path[j] == penultimate && curr_path[j + 1] == last) {
        dupe_count++;
        if (dupe_count >= 2) {
          return true;
        }
      }
    }
  }

  return false;
}

bool move_guard(Guard &guard) {
  path.push_back(guard.pos);
  if (add_obstacle) {
    std::cout << "LOOPED at " << guard.pos.first << "," << guard.pos.second
              << "\n";
    obstacles.insert(guard.pos);
    add_obstacle = false;
  }
  // if (path.size() >= 27) {
  //   return true;
  // }
  auto res = unique_locations.insert(guard.pos);
  std::pair<int, int> straight_pos = {
      guard.pos.first + straight_next_pos[guard.dir_index].first,
      guard.pos.second + straight_next_pos[guard.dir_index].second};

  std::cout << path.size() << " | try " << guard.pos.first << ","
            << guard.pos.second;
  std::cout << " to " << straight_pos.first << "," << straight_pos.second;

  char grid_char = '.';
  try {
    grid_char = grid.at(straight_pos.first).at(straight_pos.second);
  } catch (const std::out_of_range &e) {
    return true;
  }

  grid[guard.pos.first][guard.pos.second] = '.';
  std::pair<int, int> right_pos = {
      guard.pos.first + right_next_pos[guard.dir_index].first,
      guard.pos.second + right_next_pos[guard.dir_index].second};

  auto cp_grid = grid;
  cp_grid[straight_pos.first][straight_pos.second] = '#';
  bool is_loop = check_path_collision(guard, cp_grid);
  if (is_loop) {
    add_obstacle = true;
  }
  std::cout << "\n";

  if (grid_char == '#') { // GOING RIGHT
    guard.pos = right_pos;
    guard.rotate();
  } else { // GOING FORWARD
    guard.pos = straight_pos;
  }
  grid[guard.pos.first][guard.pos.second] = guard.dir();

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
    // print_grid(guard);
    done = move_guard(guard);
  }

  std::cout << "\n\n";
  std::cout << "path: " << path.size() << " \n";
  // for (auto p : path) {
  //   std::cout << "(" << p.first << "," << p.second << ")";
  // }
  std::cout << "unique locations: " << unique_locations.size() << " \n";
  // for (auto u : unique_locations) {
  //   std::cout << "(" << s.first << "," << s.second << ")";
  // }
  std::cout << "num loops: " << obstacles.size() << " \n";
  // for (auto o : obstacles) {
  //   std::cout << "(" << o.first << "," << o.second << ")";
  // }
}
