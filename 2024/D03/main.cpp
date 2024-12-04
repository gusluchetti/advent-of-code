#include <iostream>
#include <regex>
#include <sstream>
#include <string>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;
  int sum = 0;
  int sum_toggled = 0;
  bool on = true;

  while (std::cin) {
    getline(std::cin, line);
    if (line.empty()) {
      break;
    }
    std::stringstream ss(line);
    std::cout << line << "\n";

    // std::regex e("mul\\((\\d{1,3}),(\\d{1,3})\\)");
    std::regex e2("(mul)\\((\\d{1,3}),(\\d{1,3})\\)|(do)\\(\\)|(don't)\\(\\)");

    std::regex_iterator<std::string::iterator> rit(line.begin(), line.end(),
                                                   e2);
    std::regex_iterator<std::string::iterator> rend;

    while (rit != rend) {
      auto match = *rit;

      for (int i = 0; i < match.size(); i++) {
        if (match[i] == "don't") {
          on = false;
        }
        if (match[i] == "do") {
          on = true;
        }

        if (match[i] == "mul") {
          int first = std::stoi(match[i + 1]);
          int second = std::stoi(match[i + 2]);
          sum += (first * second);
          if (on) {
            sum_toggled += (first * second);
          }
        }
      }

      rit++;
    }

    std::cout << "\n" << sum;
    std::cout << "\n" << sum_toggled << "\n";
  }
}
