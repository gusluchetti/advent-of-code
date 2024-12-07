#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

// TODO:
// add test obstable to field! and save its position so we can reset it later

std::vector<std::vector<char>> grid;
char guard_directions[4] = {'^', '>', 'v', '<'};
std::pair<int, int> normal_next_pos[4] = {{-1, 0}, {0, +1}, {+1, 0}, {0, -1}};
std::pair<int, int> blocked_next_pos[4] = {{0, +1}, {+1, 0}, {0, -1}, {-1, 0}};

// part 1
bool done = false;
std::set<std::pair<int, int>> seen_locations = {};

// part 2
bool is_testing_loop = false;
int blocked_count = 0;
int possible_loops = 0;
std::pair<int, int> safe_pos;
int safe_dir_index;

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

void reset(Guard &guard) {
  is_testing_loop = false;
  blocked_count = 0;
  std::cout << "STOPPED TESTING\n";

  grid[guard.pos.first][guard.pos.second] = '.';

  guard.pos = safe_pos;
  guard.dir_index = safe_dir_index;
  grid[guard.pos.first][guard.pos.second] = guard.dir();
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

  seen_locations.insert(guard.pos);

  while (!done) {
    count++;
    if (count >= 150) {
      break;
    }
    print_grid(guard);
    if (!is_testing_loop) {
      safe_pos = {guard.pos.first, guard.pos.second};
      safe_dir_index = guard.dir_index;
    }
    std::pair<int, int> next_pos = {
        guard.pos.first + normal_next_pos[guard.dir_index].first,
        guard.pos.second + normal_next_pos[guard.dir_index].second};

    char grid_char = '.';
    try {
      grid_char = grid.at(next_pos.first).at(next_pos.second);
    } catch (const std::out_of_range &e) {
      if (!is_testing_loop) {
        done = true;
        continue;
      }

      reset(guard);
      continue;
    }

    grid[guard.pos.first][guard.pos.second] = '.';
    std::pair<int, int> right_pos = {
        guard.pos.first + blocked_next_pos[guard.dir_index].first,
        guard.pos.second + blocked_next_pos[guard.dir_index].second};
    // GOING RIGHT
    if (grid_char == '#') {
      if (is_testing_loop) {
        blocked_count++;
        if (blocked_count == 4 && safe_pos == next_pos) {
          reset(guard);
          continue;
        }
      }
      guard.pos = right_pos;
      guard.dir_index++;
      if (guard.dir_index >= 4) {
        guard.dir_index = 0;
      }
      // GOING FORWARD
    } else {
      if (!is_testing_loop && grid[right_pos.first][right_pos.second] != '#') {
        safe_pos = next_pos;
        is_testing_loop = true;
        std::cout << "STARTED TESTING\n\n";
        blocked_count++;
        guard.pos = right_pos;
        guard.dir_index++;
        if (guard.dir_index >= 4) {
          guard.dir_index = 0;
        }
      } else {
        guard.pos = next_pos;
      }
    }
    grid[guard.pos.first][guard.pos.second] = guard.dir();

    if (!is_testing_loop) {
      auto res = seen_locations.insert(guard.pos);
      if (res.second == true) {
        // new location
      }
      if (res.second == false) {
        // already seen
      }
    }
  }

  std::cout << "\n";
  std::cout << seen_locations.size() << "\n";
  std::cout << possible_loops << "\n";
}
