#include <iostream>
#include <string>

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

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
    }
  }

  int temp[disk_size];
  for (size_t i = 0; i < sizeof(temp); i++) {
    int x = temp[i];
  }
}
