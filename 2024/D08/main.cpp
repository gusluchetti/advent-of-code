#include <iostream>
#include <map>
#include <set>
#include <utility>
#include <vector>

std::map<char, std::vector<std::pair<int, int>>> antennas = {};
std::vector<std::vector<char>> grid = {};
std::set<std::pair<int, int>> p1_antinodes = {};
std::set<std::pair<int, int>> p2_antinodes = {};

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  // read grid
  std::string line;
  while (std::cin) {
    std::vector<char> curr;
    getline(std::cin, line);
    if (std::cin.eof()) {
      std::cout << "eof" << "\n";
      break;
    }

    for (char c : line) {
      curr.push_back(c);
    }
    grid.push_back(curr);
  }

  size_t max_y = grid.size();
  size_t max_x = grid[0].size();

  for (size_t y = 0; y < max_y; y++) {
    std::vector<char> char_list = grid[y];
    for (size_t x = 0; x < max_x; x++) {
      char c = char_list[x];
      if (c != '.') {
        auto found = antennas.find(c);
        if (found != antennas.end()) {
          found->second.push_back({y, x});
        } else {
          antennas.insert({c, {{y, x}}});
        }
      }
    }
    std::cout << "\n";
  }

  for (auto a : antennas) {
    std::cout << a.first << " | ";
    for (size_t i = 0; i < a.second.size(); ++i) {
      std::pair<int, int> one = a.second[i];
      for (size_t j = i + 1; j < a.second.size(); ++j) {
        std::pair<int, int> another = a.second[j];

        std::cout << one.first << "," << one.second << " ";
        std::cout << another.first << "," << another.second << "\n";

        std::pair<int, int> diff = {one.first - another.first,
                                    one.second - another.second};
        std::cout << "\ndiff: " << diff.first << "," << diff.second << "\n";

        std::pair<int, int> p1_nodes[2] = {
            {one.first + diff.first, one.second + diff.second},
            {another.first - diff.first, another.second - diff.second}};

        for (auto n : p1_nodes) {
          if ((n.first >= 0 && n.first < max_y) &&
              (n.second >= 0 && n.second < max_x)) {
            p1_antinodes.insert(n);
            // if (grid[n.first][n.second] == '.') {
            //   grid[n.first][n.second] = '#';
            // }
          }
        }

        std::vector<std::pair<int, int>> one_extended = {
            {one.first + diff.first, one.second + diff.second}};
        bool one_ok = true;
        while (one_ok) {
          std::pair<int, int> last = one_extended.back();
          std::cout << last.first << "," << last.second << "\n";
          std::pair<int, int> new_pair = {last.first + diff.first,
                                          last.second + diff.second};
          if ((new_pair.first >= 0 && new_pair.first < max_y) &&
              (new_pair.second >= 0 && new_pair.second < max_x)) {
            one_extended.push_back(new_pair);
          } else {
            one_ok = false;
          }
        }
        std::cout << "\ndone first side\n";

        bool another_ok = true;
        std::vector<std::pair<int, int>> another_extended = {
            {another.first - diff.first, another.second - diff.second}};
        while (another_ok) {
          std::pair<int, int> last = another_extended.back();
          std::cout << last.first << "," << last.second << "\n";
          std::pair<int, int> new_pair = {last.first - diff.first,
                                          last.second - diff.second};
          if ((new_pair.first >= 0 && new_pair.first < max_y) &&
              (new_pair.second >= 0 && new_pair.second < max_x)) {
            another_extended.push_back(new_pair);
          } else {
            another_ok = false;
          }
        }
        std::cout << "\ndone second side\n";

        std::vector<std::pair<int, int>> p2_nodes;
        p2_nodes.insert(p2_nodes.end(), one_extended.begin(),
                        one_extended.end());
        p2_nodes.insert(p2_nodes.end(), another_extended.begin(),
                        another_extended.end());

        p2_antinodes.insert({one.first, one.second});
        p2_antinodes.insert({another.first, another.second});

        for (auto n : p2_nodes) {
          std::cout << "\n";
          for (auto y : grid) {
            for (auto x : y) {
              std::cout << x;
            }
            std::cout << "\n";
          }
          if ((n.first >= 0 && n.first < max_y) &&
              (n.second >= 0 && n.second < max_x)) {
            p2_antinodes.insert(n);
            if (grid[n.first][n.second] == '.') {
              grid[n.first][n.second] = '#';
            }
          }
        }
      }
    }
    std::cout << "\n";
  }

  std::cout << "num. antennas: " << antennas.size() << "\n";

  std::cout << "p1 antinodes: " << p1_antinodes.size() << "\n";
  for (auto an : p1_antinodes) {
    std::cout << an.first << "," << an.second << " ";
  }
  std::cout << "\n";

  std::cout << "p2 antinodes: " << p2_antinodes.size() << "\n";
  for (auto an : p2_antinodes) {
    std::cout << an.first << "," << an.second << " ";
  }
  std::cout << "\n";
}
