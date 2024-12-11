#include <iostream>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  // read grid
  std::string line;
  while (std::cin) {
    getline(std::cin, line);
    if (std::cin.eof()) {
      std::cout << "eof" << "\n";
      break;
    }

    std::cout << line << "\n";
  }
}
