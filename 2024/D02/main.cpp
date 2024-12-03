#include <cstdlib>
#include <ios>
#include <iostream>
#include <sstream>
#include <vector>

bool is_safe(int first, int second, bool is_asc) {
  int diff = abs(first - second);
  bool diff_ok = (diff >= 1 && diff <= 3);

  if (is_asc && first > second)
    return false;
  if (!is_asc && first < second)
    return false;

  return diff_ok;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;
  std::vector<int> report;

  int safe_levels = 0;

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

    bool is_basic_safe = true;
    bool is_dampened_safe = true;
    std::vector<int> bad_indexes = {};

    bool last_is_asc = (report[0] < report[1]);
    int last = report[0];
    for (int i = 1; i < report.size(); i++) {
      int curr = report[i];
      bool is_asc = (last <= curr);

      bool safe = is_safe(last, curr, last_is_asc);
      if (!safe) {
        is_basic_safe = false;
        bad_indexes.push_back(i);
        bad_indexes.push_back(i - 1);
      }

      last = curr;
      last_is_asc = is_asc;
    }
    std::cout << line << " | " << is_basic_safe << "\n";

    if (is_basic_safe) {
      safe_levels++;
    }
  }

  std::cout << "basic safe: " << safe_levels << "\n";
}
