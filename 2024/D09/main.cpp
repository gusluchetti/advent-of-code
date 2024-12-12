#include <iostream>
#include <string>
#include <vector>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::vector<int> values;
  int disk_size = 0;

  // read grid
  std::string line;
  while (std::cin) {
    getline(std::cin, line);
    if (std::cin.eof()) {
      std::cout << "eof" << "\n";
      break;
    }

    for (char c : line) {
      int num = c - '0';
      std::cout << num << "\n";
      disk_size += num;
      values.push_back(num);
    }
  }

  std::vector<int> diskmap(disk_size, -1);
  for (auto num : diskmap) {
    std::cout << num << " ";
  }
  std::cout << "\n";

  std::cout << "\n";
  for (size_t i = 0; i < values.size(); i++) {
    int num = values[i];
    for (int x = 0; x < num; x++) {
      std::cout << i << "," << x << " (" << num << ") ";
      if (i % 2 == 0 || i == 0) {
        diskmap[i + x] = i;
      } else {
      }

      for (size_t i = 0; i < diskmap.size(); i++) {
        int x = diskmap[i];
        std::cout << x << " ";
      }
      std::cout << "\n";
    }
  }

  std::cout << "\n";
}
