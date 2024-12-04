#include <iostream>
#include <sstream>
#include <string>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;
  int count = 0;

  while (std::cin) {
    getline(std::cin, line);
    if (line.empty()) {
      break;
    }

    std::stringstream ss(line);
    for (char c : line) {
      std::cout << c << "\n";
    }
    std::cout << std::endl;
  }
}
