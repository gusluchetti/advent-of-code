#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;
  std::vector<std::vector<char>> grid;

  while (std::cin) {
    getline(std::cin, line);
    if (std::cin.eof()) {
      std::cout << "eof" << "\n";
      break;
    }

    grid.push_back(std::vector<char>(line.begin(), line.end()));
  }

  for (size_t y = 0; y < grid.size() - 1; y++) {
    for (size_t x = 0; x < grid[0].size() - 1; x++) {
      std::cout << grid[y][x];
    }
    std::cout << "\n";
  }
}
