#include <iostream>
#include <string>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;

  while (std::cin) {
    getline(std::cin, line);
    if (std::cin.eof()) {
      break;
    }
    std::cout << line << "\n";
  }
}
