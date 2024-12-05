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

    std::cout << line << "\n";
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
    }

    // check if page update is good
    for (size_t i = page_update.size() - 1; i >= 0; i--) {
      int page = page_update[i];
      auto nums_after = page_dict[page];
      std::cout << page;
      for (auto t : nums_after) {
        std::cout << " " << t;
      }
      std::cout << std::endl;
    }
  }
}
