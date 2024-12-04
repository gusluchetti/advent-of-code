#include <iostream>
#include <regex>
#include <sstream>
#include <string>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;
  int sum = 0;

  while (std::cin) {
    getline(std::cin, line);
    if (line.empty()) {
      break;
    }
    std::stringstream ss(line);
    std::cout << line << "\n";

    std::regex e("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    std::regex_iterator<std::string::iterator> rit(line.begin(), line.end(), e);
    std::regex_iterator<std::string::iterator> rend;

    while (rit != rend) {
      auto match = *rit;
      int first = std::stoi(match[1]);
      int second = std::stoi(match[2]);
      // std::cout << first << "*" << second << "\n";
      sum += (first * second);

      rit++;
    }

    std::cout << "\n" << sum << "\n";
  }
}
