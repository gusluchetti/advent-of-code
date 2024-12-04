#include <iostream>
#include <sstream>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;

  while (std::cin) {
    getline(std::cin, line);
    std::stringstream ss(line);

    std::cout << line << "\n";
  }
}
