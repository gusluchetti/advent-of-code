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

  std::list<char> opts = {'+', '*'};
  int spaces = 0;
  int sum = 0;
  int initial_size = 0;
  for (auto e : equations) {
    int test_value = e[0];
    bool finished = false;
    std::vector<int> valid_subsets = {e[1]};
    spaces = e.size() - 2;
    while (valid_subsets.size() > 0) {
      initial_size = valid_subsets.size();
      for (int i = 0; i < valid_subsets.size(); i++) {
        int v = valid_subsets[i];
        for (int s = 2; s <= spaces + 1; s++) {
          for (char o : opts) {
            if (o == '+') {
              v += e[s];
            } else if (o == '*') {
              v *= e[s];
            }

            if (v < test_value || (v == test_value && s == spaces + 1)) {
              valid_subsets.push_back(v);
            }
          }
        }
      }
      valid_subsets.erase(valid_subsets.begin(),
                          valid_subsets.begin() + initial_size);
    }
  }
  std::cout << "\n";
}
