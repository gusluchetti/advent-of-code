#include <cstdlib>
#include <ios>
#include <iostream>
#include <sstream>
#include <vector>

int main() {
  std::cout << "\n";
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;
  std::vector<int> report;

  int safe_levels = 0;
  int safe_levels_w_dampener = 0;

  while (std::cin) {
    getline(std::cin, line);
    std::stringstream ss(line);

    report = {};
    int item;
    while (ss >> item) {
      report.push_back(item);
    }

    if (report.size() == 0) {
      continue;
    }

    bool last_is_asc = (report[0] <= report[1]);
    int last = report[0];
    bool is_basic_safe = true;
    int bad_levels = 0;
    for (int i = 1; i < report.size(); i++) {
      int curr = report[i];
      bool is_asc = (last <= curr);
      int diff = abs(last - curr);

      if (last_is_asc != is_asc || (diff < 1 || diff > 3)) {
        is_basic_safe = false;
        bad_levels++;
      }

      last = curr;
      last_is_asc = is_asc;
    }

    std::cout << line << "\n";
    if (is_basic_safe) {
      safe_levels++;
    }
    if (bad_levels <= 1) {
      safe_levels_w_dampener++;
    }
  }

  std::cout << "basic safe: " << safe_levels << "\n";
  std::cout << "safe w/ dampener: " << safe_levels_w_dampener << "\n";
}
