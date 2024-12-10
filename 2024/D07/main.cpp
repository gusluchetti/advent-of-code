#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;
  std::vector<std::vector<int>> equations;

  // read grid
  while (std::cin) {
    std::vector<int> curr;
    getline(std::cin, line);
    if (std::cin.eof()) {
      std::cout << "eof" << "\n";
      break;
    }

    auto res = line.find(':');
    int result = std::stoi(line.substr(0, res));
    curr.push_back(result);
    std::stringstream ss(line.substr(res + 2));
    int num;
    while (ss >> num) {
      curr.push_back(num);
    }

    equations.push_back(curr);
  }

  int p1 = 0;
  std::list<char> opts = {'+', '*'};

  for (auto e : equations) {
    for (auto x : e) {
      std::cout << x << " ";
    }
    std::cout << "\n";

    int test_value = e[0];
    std::vector<int> valid_subsets = {e[1]};
    bool finished = false;

    int initial_size;
    std::vector<int> new_subsets;
    while (valid_subsets.size() > 0 || !finished) {
      for (int n = 2; n < e.size(); n++) {
        initial_size = valid_subsets.size();
        new_subsets = {};

        for (int i = 0; i < valid_subsets.size(); i++) {
          int v = valid_subsets[i];
          for (char o : opts) {
            if (o == '+') {
              new_subsets.push_back(v + e[n]);
            } else if (o == '*') {
              new_subsets.push_back(v * e[n]);
            }
          }
        }

        for (auto ns : new_subsets) {
          if ((ns < test_value && n < e.size() - 1) ||
              (ns == test_value && n == e.size() - 1)) {
            valid_subsets.push_back(ns);
          }
        }
        valid_subsets.erase(valid_subsets.begin(),
                            valid_subsets.begin() + initial_size);
      }
      finished = true;
      std::cout << "found " << valid_subsets.size() << " valid subsets\n";
      if (valid_subsets.size() >= 1) {
        p1 += e[0];
      }
    }
  }

  std::cout << "\n\ntotal calibration result: " << p1;
  std::cout << "\n";
}
