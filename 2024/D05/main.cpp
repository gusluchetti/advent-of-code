#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;
  int sum_middle_valid = 0;
  bool at_rules = true;
  std::map<int, std::vector<int>> page_dict;
  std::vector<int> page_update;

  while (std::cin) {
    getline(std::cin, line);
    if (std::cin.eof()) {
      std::cout << "eof" << "\n";
      break;
    }

    if (line.empty()) {
      std::cout << "now reading page updates..." << "\n";
      at_rules = false;
      continue;
    }

    page_update = {};
    if (at_rules) {
      const size_t delimiter = line.find("|");
      int before = stoi(line.substr(0, delimiter));
      int after = stoi(line.substr(delimiter + 1));
      page_dict[before].push_back(after);
    } else {
      std::istringstream iss(line);
      int num;
      while (iss >> num) {
        page_update.push_back(num);
        iss.ignore();
      }
      for (auto p : page_update) {
        std::cout << p << "\n";
      }

      bool correct = true;
      int max = page_update.size() - 1;
      for (int i = max; i >= 0; i--) {
        int page = page_update[i];
        std::map<int, std::vector<int>>::iterator rule_iter =
            page_dict.find(page);
        if (rule_iter == page_dict.end()) {
          continue;
        }

        std::vector<int> rule_after = rule_iter->second;
        for (auto a : rule_after) {
          int count =
              std::count(page_update.begin(), page_update.begin() + i + 1, a);
          if (count > 0) {
            std::cout << a << " is bad! at " << page << "\n";
            correct = false;
            break;
          }
        }

        if (correct == false) {
          break;
        }
      }
      std::cout << "\n";

      if (correct) {
        int middle_index = (page_update.size() / 2);
        int middle_value = page_update.at(middle_index);
        sum_middle_valid += middle_value;
        std::cout << middle_value << " " << sum_middle_valid << "\n";
      }
    }
  }

  std::cout << sum_middle_valid;
}
