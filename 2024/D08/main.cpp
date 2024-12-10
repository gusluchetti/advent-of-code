#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

std::map<char, std::set<std::pair<int, int>>> antennas = {};
std::vector<std::vector<char>> grid = {};
std::vector<std::vector<char>> antinode_grid = {};

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  // read grid
  std::string line;
  while (std::cin) {
    std::vector<char> curr;
    getline(std::cin, line);
    if (std::cin.eof()) {
      std::cout << "eof" << "\n";
      break;
    }

    for (char c : line) {
      curr.push_back(c);
    }
    grid.push_back(curr);
  }

  size_t max_y = grid.size();
  size_t max_x = grid[0].size();

  for (size_t y = 0; y < max_y; y++) {
    std::vector<char> char_list = grid[y];
    for (size_t x = 0; x < max_x; x++) {
      char c = char_list[x];
      std::cout << c;
      if (c != '.') {
        auto found = antennas.find(c);
        if (found != antennas.end()) {
          found->second.insert({y, x});
        } else {
          antennas.insert({c, {{y, x}}});
        }
      }
    }
    std::cout << "\n";
  }

  for (auto a : antennas) {
    std::cout << a.first << " | ";
    for (auto s : a.second) {
      std::cout << s.first << "," << s.second << " ";
    }
    std::cout << "\n";
  }
  std::cout << antennas.size() << "\n";
}
