#include <cstdlib>
#include <ios>
#include <iostream>
#include <pstl/glue_algorithm_defs.h>
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

bool is_report_safe(std::vector<int> report) {
  bool is_basic_safe = true;

  bool last_is_asc = (report[0] < report[1]);
  int curr = report[0];
  for (int i = 0; i < (report.size() - 1); i++) {
    int next = report[i + 1];
    bool is_asc = (curr < next);

    bool safe = is_safe(curr, next, last_is_asc);
    if (!safe) {
      is_basic_safe = false;
      break;
    }

    curr = next;
    last_is_asc = is_asc;
  }

  return is_basic_safe;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;
  std::vector<int> report;

  int safe_levels = 0;
  int adv_safe_levels = 0;

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

    bool is_basic_safe = is_report_safe(report);
    bool is_adv_safe = true;
    if (!is_basic_safe) {
      is_adv_safe = false;
      std::vector<int> temp = {};
      for (int i = 0; i < report.size(); i++) {
        temp = report;
        temp.erase(temp.begin() + i);

        if (is_report_safe(temp)) {
          is_adv_safe = true;
          std::cout << "\n";
          for (int t : temp) {
            std::cout << t;
          }
          std::cout << "\n";
        }
      }
    }

    std::cout << line << " | " << is_basic_safe << ", " << is_adv_safe << "\n";

    if (is_basic_safe) {
      safe_levels++;
    }

    if (is_adv_safe) {
      adv_safe_levels++;
    }
  }

  std::cout << "\nbasic safe: " << safe_levels << "\n";
  std::cout << "dampened safe: " << adv_safe_levels << "\n";
}
