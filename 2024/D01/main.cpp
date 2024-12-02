#include <algorithm>
#include <cstdlib>
#include <ios>
#include <iostream>
#include <sstream>
#include <vector>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;
  std::vector<int> left_list;
  std::vector<int> right_list;
  while (std::cin) {
    getline(std::cin, line);
    std::stringstream ss(line);

    int number;
    while (ss >> number) {
      left_list.push_back(number);
      ss >> number;
      right_list.push_back(number);
    }
  }

  std::sort(left_list.begin(), left_list.end());
  std::sort(right_list.begin(), right_list.end());

  int sum = 0;
  int size = left_list.size();
  for (int i = 0; i < size; i++) {
    sum += abs(left_list[i] - right_list[i]);
  }

  int similarity = 0;
  for (int a = 0; a < size; a++) {
    int target = left_list[a];
    int freq = std::count(right_list.begin(), right_list.end(), target);
    similarity += (target * freq);
  }

  std::cout << sum << "\n" << similarity;
}
