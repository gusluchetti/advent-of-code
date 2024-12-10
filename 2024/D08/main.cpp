#include <iostream>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;

  // read grid
  while (std::cin) {
    getline(std::cin, line);
    if (std::cin.eof()) {
      std::cout << "eof" << "\n";
      break;
    }

    std::cout << line << "\n";
  }

  std::cout << "\n";
}
