#include <iostream>
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

  for (auto e : equations) {
    for (auto x : e) {
      std::cout << x << " ";
    }
    std::cout << "\n";
  }
}
