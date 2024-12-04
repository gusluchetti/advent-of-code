#include <iostream>
#include <ostream>
#include <string>
#include <vector>

int count_x_mas_occurrences(std::vector<std::vector<char>> &ws, int x, int y) {
  int count = 0;
  int max_y = ws.size();
  int max_x = ws[0].size();
  // check 4 possible directions, assuming ltr checks if possible
  // 1. Ms on TOP, first M on left
  if (y <= max_y - 4 && x <= max_x - 4) {
    std::string mas_1 = {ws[y][x], ws[y + 1][x + 1], ws[y + 2][x + 2]};
    std::string mas_2 = {ws[y][x + 2], ws[y + 1][x + 1], ws[y + 2][x]};
    if (mas_1 == "MAS" && mas_2 == "MAS") {
      count++;
    }
  }
  // 2. Ms on RIGHT, first M on top
  if (y <= max_y - 4 && x >= 3) {
    std::string mas_1 = {ws[y][x], ws[y + 1][x - 1], ws[y + 2][x - 2]};
    std::string mas_2 = {ws[y + 2][x], ws[y + 1][x - 1], ws[y][x - 2]};
    if (mas_1 == "MAS" && mas_2 == "MAS") {
      count++;
    }
  }
  // 3. Ms on DOWN, first M on left
  if (y >= 3 && x <= max_x - 4) {
    std::string mas_1 = {ws[y][x], ws[y - 1][x + 1], ws[y - 2][x + 2]};
    std::string mas_2 = {ws[y][x + 2], ws[y - 1][x + 1], ws[y - 2][x]};
    if (mas_1 == "MAS" && mas_2 == "MAS") {
      count++;
    }
  }
  // 4. Ms on LEFT, first M on top
  if (y <= max_y - 4 && x <= max_x - 4) {
    std::string mas_1 = {ws[y][x], ws[y + 1][x + 1], ws[y + 2][x + 2]};
    std::string mas_2 = {ws[y + 2][x], ws[y + 1][x + 1], ws[y][x + 2]};
    if (mas_1 == "MAS" && mas_2 == "MAS") {
      count++;
    }
  }

  return count;
}

int count_xmas_occurrences(std::vector<std::vector<char>> &ws, int x, int y) {
  int count = 0;
  int max_y = ws.size();
  int max_x = ws[0].size();
  // check 8 possible directions clockwise
  // 1. vertical inverted xmas
  if (y >= 3) {
    std::string word = {'X', ws[y - 1][x], ws[y - 2][x], ws[y - 3][x]};
    if (word == "XMAS") {
      count++;
    }
  }
  // 2. right inverted diagonal
  if (y >= 3 && x <= max_x - 4) {
    std::string word = {'X', ws[y - 1][x + 1], ws[y - 2][x + 2],
                        ws[y - 3][x + 3]};
    if (word == "XMAS") {
      count++;
    }
  }
  // 3. normal ltr
  if (x <= max_x - 4) {
    std::string word = {'X', ws[y][x + 1], ws[y][x + 2], ws[y][x + 3]};
    if (word == "XMAS") {
      count++;
    }
  }
  // 4. normal right diagonal
  if (y <= max_y - 4 && x <= max_x - 4) {
    std::string word = {'X', ws[y + 1][x + 1], ws[y + 2][x + 2],
                        ws[y + 3][x + 3]};
    if (word == "XMAS") {
      count++;
    }
  }
  // 5. normal vertical
  if (y <= max_y - 4) {
    std::string word = {'X', ws[y + 1][x], ws[y + 2][x], ws[y + 3][x]};
    if (word == "XMAS") {
      count++;
    }
  }
  // 6. inverted left diagonal
  if (y <= max_y - 4 && x >= 3) {
    std::string word = {'X', ws[y + 1][x - 1], ws[y + 2][x - 2],
                        ws[y + 3][x - 3]};
    if (word == "XMAS") {
      count++;
    }
  }
  // 7. normal rtl
  if (x >= 3) {
    std::string word = {'X', ws[y][x - 1], ws[y][x - 2], ws[y][x - 3]};
    if (word == "XMAS") {
      count++;
    }
  }
  // 8.inverted left diagonal
  if (x >= 3 && y >= 3) {
    std::string word = {'X', ws[y - 1][x - 1], ws[y - 2][x - 2],
                        ws[y - 3][x - 3]};
    if (word == "XMAS") {
      count++;
    }
  }

  return count;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  std::string line;
  int count_xmas = 0;
  int count_x_mas = 0;
  std::vector<std::vector<char>> ws;

  while (std::cin) {
    getline(std::cin, line);
    if (line.empty()) {
      break;
    }

    std::vector<char> ws_line;
    for (char c : line) {
      ws_line.push_back(c);
    }
    ws.push_back(ws_line);
  }

  for (size_t y = 0; y < ws.size(); y++) {
    std::vector<char> ws_line = ws[y];
    for (size_t x = 0; x < ws_line.size(); x++) {
      char c = ws_line[x];
      std::cout << "at: " << x << "," << y;
      std::cout << " | " << c << "\n";
      if (c == 'X') {
        int found = count_xmas_occurrences(ws, x, y);
        if (found >= 1) {
          count_xmas += found;
          std::cout << "found " << found << " occurrences of XMAS, "
                    << count_xmas << "\n";
        }
      }

      if (c == 'M') {
        int found = count_x_mas_occurrences(ws, x, y);
        if (found >= 1) {
          count_x_mas += found;
          std::cout << "found " << found << " occurrences of X-MAS, "
                    << count_x_mas << "\n";
        }
      }
    }
    std::cout << std::endl;
  }

  std::cout << count_xmas << ", " << count_x_mas << "\n";
}
