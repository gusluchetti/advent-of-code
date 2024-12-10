#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

bool done_p1 = false;
bool done_p2 = false;
bool add_obstacle = false;

std::vector<std::vector<char>> g_grid;
std::vector<std::pair<std::pair<int, int>, int>> g_path = {};
std::set<std::pair<std::pair<int, int>, int>> loop_path = {};
std::set<std::pair<int, int>> g_unique_locations = {};
int num_loops = 0;

char guard_directions[4] = {'^', '>', 'v', '<'};
std::pair<int, int> straight_next_pos[4] = {{-1, 0}, {0, +1}, {+1, 0}, {0, -1}};

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

void print_grid(Guard guard, std::vector<std::vector<char>> grid) {
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

void p1(Guard guard, std::vector<std::vector<char>> grid,
        bool check_loop = false) {
  loop_path = {};
  while (!done_p1) {
    g_path.push_back(std::make_pair(
        std::make_pair(guard.pos.first, guard.pos.second), guard.dir_index));
    if (check_loop) {
      auto res = loop_path.insert(std::make_pair(
          std::make_pair(guard.pos.first, guard.pos.second), guard.dir_index));
      if (res.second == false) {
        num_loops++;
        std::cout << "\nGOT LOOP! " << num_loops << "\n";
        done_p1 = true;
      }
    }
    g_unique_locations.insert({guard.pos.first, guard.pos.second});
    // print_grid(guard, grid);
    try {
      std::pair<int, int> next = {
          guard.pos.first + straight_next_pos[guard.dir_index].first,
          guard.pos.second + straight_next_pos[guard.dir_index].second};
      auto grid_char = grid.at(next.first).at(next.second);
      while (grid_char == '#' || (grid_char == 'O' && check_loop)) {
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
}

void p2(Guard guard, std::vector<std::vector<char>> grid) {
  auto init_pos = g_path[0];
  std::vector<std::pair<int, int>> obstacles = {};
  for (auto it = g_unique_locations.begin(); it != g_unique_locations.end();
       it++) {
    auto coord = *it;
    if (coord.first == init_pos.first.first &&
        coord.second == init_pos.first.second) {
      // do nothing
    } else {
      obstacles.push_back(coord);
    }
  }

  done_p1 = false;
  while (!done_p2) {
    for (size_t i = 0; i < obstacles.size(); i++) {
      auto obstacle = obstacles[i];
      std::cout << obstacle.first << "," << obstacle.second << " ";

      grid[obstacle.first][obstacle.second] = 'O';
      std::cout << "\nNEW TEST!\n";
      p1(guard, grid, true);
      done_p1 = false;
      grid[obstacle.first][obstacle.second] = '.';
    }
    done_p2 = true;
  }
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
    g_grid.push_back(std::vector<char>(line.begin(), line.end()));
    count++;
  }

  p1(guard, g_grid);
  std::cout << "\npath: " << g_path.size() << " \n";
  std::cout << "unique locations: " << g_unique_locations.size() << " \n";

  p2(guard, g_grid);
  std::cout << "\nnum loops: " << num_loops << " \n";
}
