#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <utility>

using namespace std;

int loop(bool repeat_location) {
  typedef pair<int, int> coords;
  coords last_coords = {0, 0};
  coords cur_coords = {0, 0};
  int distance;
  string input;
  int cur_dir = 0; // 0N, 1W, 2S, 3E

  pair<set<coords>::iterator, bool> ret;
  set<coords> coord_set = {};

  while (getline(cin, input, ' ')) {
    char dir = input[0];
    string::size_type comma = input.find(',');
    string::size_type end_line = input.find('\n');
    int blocks = -1;
    if (comma != string::npos) {
      blocks = stoi(input.substr(1, comma - 1));
    } else if (end_line != string::npos) {
      blocks = stoi(input.substr(1, end_line - 1));
    }

    if (dir == 'L') {
      cur_dir =
          (cur_dir - 1 + 8) % 4; // 8 = 2 * 4 (all possible direction states)
    } else if (dir == 'R') {
      cur_dir = (cur_dir + 1) % 4;
    }

    last_coords = cur_coords;
    switch (cur_dir) {
    case 0:
      cur_coords.second += blocks;
      break;
    case 1:
      cur_coords.first += blocks;
      break;
    case 2:
      cur_coords.second -= blocks;
      break;
    case 3:
      cur_coords.first -= blocks;
      break;
    default:
      cout << "not possible";
      return -1;
    }
    distance = abs(cur_coords.first) + abs(cur_coords.second);

    if (repeat_location == true) {
      cout << last_coords.first << "," << last_coords.second << "\n";
      cout << cur_coords.first << "," << cur_coords.second << "\n";

      int diff = cur_coords.first - last_coords.first;
      if (diff != 0) {
        for (int i = cur_coords.first; i < cur_coords.first + diff; i++) {
          
        }
        cout << 'x';
      } else {
        diff = cur_coords.second - last_coords.second;
        cout << 'y';
      }

      ret = coord_set.insert(cur_coords);
      if (ret.second == false) {
        cout << distance << "\n";
        break;
      }
    }
  }

  cout << distance << "\n";
  return 0;
}

int part1() { return loop(false); }

int part2() { return loop(true); }

int main() {
  // part1();
  part2();
}
