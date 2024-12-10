#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

std::map<char, std::vector<std::pair<int, int>>> antennas = {};
std::vector<std::vector<char>> grid = {};
std::set<std::pair<int, int>> antinode_grid = {};

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

  size_t max_y = grid.size() - 1;
  size_t max_x = grid[0].size() - 1;

  for (size_t y = 0; y < max_y; y++) {
    std::vector<char> char_list = grid[y];
    for (size_t x = 0; x < max_x; x++) {
      char c = char_list[x];
      std::cout << c;
      if (c != '.') {
        auto found = antennas.find(c);
        if (found != antennas.end()) {
          found->second.push_back({y, x});
        } else {
          antennas.insert({c, {{y, x}}});
        }
      }
    }
    std::cout << "\n";
  }

  for (auto a : antennas) {
    std::cout << a.first << " | ";

    for (size_t i = 0; i < a.second.size(); ++i) {
      std::pair<int, int> one = a.second[i];
      std::cout << one.first << "," << one.second << " ";
      for (size_t j = i + 1; j < a.second.size(); ++j) {
        std::pair<int, int> another = a.second[j];

        std::pair<int, int> diff = {one.first - another.first,
                                    one.second - another.second};

        std::pair<int, int> nodes[2] = {
            {one.first + diff.first, one.second + diff.second},
            {another.first - diff.first, another.second - diff.second}};

        for (auto n : nodes) {
          if ((n.first >= 0 && n.first <= max_y) &&
              (n.second >= 0 && n.second <= max_x)) {
            antinode_grid.insert(n);
            if (grid[n.first][n.second] == '.') {
              grid[n.first][n.second] = '#';
            }
          }
        }
      }
    }

    std::cout << "\n";
  }

  std::cout << "num. antennas: " << antennas.size() << "\n";

  std::cout << "antinodes: " << antinode_grid.size() << "\n";
  for (auto an : antinode_grid) {
    std::cout << an.first << "," << an.second << " ";
  }
  std::cout << "\n";
}
