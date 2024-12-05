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
  int sum_middle_invalid = 0;
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
      std::cout << line << "\n";

      bool correct = true;
      int max = page_update.size() - 1;
      int middle = page_update[(page_update.size() / 2)];
      for (int i = max; i >= 0; i--) {
        int page = page_update[i];
        std::map<int, std::vector<int>>::iterator rule_iter =
            page_dict.find(page);
        if (rule_iter == page_dict.end()) {
          continue;
        }

        std::vector<int> rule_after = rule_iter->second;
        for (auto a : rule_after) {
          std::cout << a << "\n";
          std::cout << i << "\n";
          auto found = std::find(page_update.begin(), page_update.end(), a);
          if (found != page_update.end()) {
            std::cout << *found << "\n";
            std::cout << a << " is bad, should be after " << page << "\n";
            correct = false;
            page_update.erase(found);
            page_update.insert(page_update.begin() + i, a);
            for (auto p : page_update) {
              std::cout << p << " ";
            }
          }
        }
      }

      int middle_invalid = page_update[(page_update.size() / 2)];
      if (correct) {
        sum_middle_valid += middle;
      }
      if (!correct) {
        sum_middle_invalid += middle_invalid;
      }

      std::cout << "\n\n";
      std::cout << middle << " " << sum_middle_valid << "\n";
      std::cout << middle_invalid << " " << sum_middle_invalid << "\n";
    }
  }

  std::cout << sum_middle_valid;
}
