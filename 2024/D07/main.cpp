#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;
  std::vector<std::vector<long>> equations;

  // read grid
  while (std::cin) {
    std::vector<long> curr;
    getline(std::cin, line);
    if (std::cin.eof()) {
      std::cout << "eof" << "\n";
      break;
    }

    auto res = line.find(':');
    std::cout << res;
    long result = std::stol(line.substr(0, res));
    curr.push_back(result);
    std::stringstream ss(line.substr(res + 2));
    long num;
    while (ss >> num) {
      curr.push_back(num);
    }

    equations.push_back(curr);
  }

  // 28_729_823_246_578, too low
  long p1 = 0;
  std::list<char> opts = {'+', '*'};

  for (auto e : equations) {
    for (auto x : e) {
      std::cout << x << " ";
    }

    long test_value = e[0];
    std::vector<long> valid_subsets = {e[1]};
    bool finished = false;

    int initial_size;
    std::vector<long> new_subsets;
    while (valid_subsets.size() > 0 && !finished) {
      for (size_t n = 2; n < e.size(); n++) {
        initial_size = valid_subsets.size();
        new_subsets = {};

        for (size_t i = 0; i < valid_subsets.size(); i++) {
          long v = valid_subsets[i];
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

        std::cout << "\ncurr w/ pos " << n << " ";
        for (auto vs : valid_subsets) {
          std::cout << vs << " ";
        }
      }

      finished = true;
    }
    std::cout << "\nfound " << valid_subsets.size() << " valid subsets\n\n";
    if (valid_subsets.size() >= 1) {
      p1 += e[0];
    }
  }

  std::cout << "\n\ntotal calibration result: " << p1;
  std::cout << "\n";
}
