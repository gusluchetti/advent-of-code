#include <algorithm>
#include <iostream>
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
  // 28_730_327_770_375
  long p1 = 0;

  for (int a = 0; a < equations.size(); a++) {
    // if (a >= 10) {
    //   break;
    // }
    std::vector<long> e = equations[a];
    for (auto x : e) {
      std::cout << x << " ";
    }

    long test_value = e[0];
    std::vector<long> valid_subsets = {e[1]};
    bool finished = false;

    std::vector<long> new_subsets;
    while (valid_subsets.size() > 0 && !finished) {
      for (size_t n = 2; n < e.size(); n++) {
        int initial_size = valid_subsets.size();
        new_subsets = {};

        for (size_t i = 0; i < valid_subsets.size(); i++) {
          long v = valid_subsets[i];

          // doing possible options, sum and mult
          new_subsets.push_back(v + e[n]);
          new_subsets.push_back(v * e[n]);
        }

        for (auto ns : new_subsets) {
          if (ns <= test_value) {
            valid_subsets.push_back(ns);
          }
        }
        valid_subsets.erase(valid_subsets.begin(),
                            valid_subsets.begin() + initial_size);
      }

      finished = true;
    }

    // NOTE: prune in case something went bad
    valid_subsets.erase(
        std::remove_if(valid_subsets.begin(), valid_subsets.end(),
                       [test_value](long vs) { return vs != test_value; }),
        valid_subsets.end());

    std::cout << "\nvalid subsets: ";
    for (auto vs : valid_subsets) {
      std::cout << vs << " ";
    }
    std::cout << "\nfound " << valid_subsets.size() << " valid subsets\n\n";
    if (valid_subsets.size() >= 1) {
      p1 += e[0];
    }
  }

  std::cout << "\n\ntotal calibration result: " << p1;
  std::cout << "\n";
}
