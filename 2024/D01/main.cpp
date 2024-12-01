#include <iostream>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  std::string line;
  while (std::cin) {
    getline(std::cin, line);
    std::cout << line << "\n";
  }
}
