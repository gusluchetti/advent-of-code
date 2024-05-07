#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <utility>

using namespace std;

typedef pair<int, int> coords;
set<coords> coord_set = {};
int total_blocks;
bool repeat_location = false;

int update_coords(int pos, int start, int end, int other) {
  if (repeat_location == true) {
    pair<set<coords>::iterator, bool> ins_return;
    vector<pair<int, int>> vec;
    for (int i = start; i <= end; i++) {
      pair<int, int> new_pair;
      if (pos == 1 || pos == 3) {
        new_pair = make_pair(i, other);
      } else if (pos == 2 || pos == 4) {
        new_pair = make_pair(other, i);
      }
      vec.push_back(new_pair);
    }

    if (pos == 3 || pos == 4) {
      reverse(vec.begin(), vec.end());
    }

    for (auto v : vec) {
      cout << v.first << "," << v.second << "\n";
      ins_return = coord_set.insert(v);
      if (ins_return.second == false) {
        cout << total_blocks << "\n";
        exit(0);
      }
    }
  }

  return -1;
}

int loop() {
  coords last_coords = {0, 0};
  coords cur_coords = {0, 0};
  string input;
  int cur_dir = 0; // 0N, 1W, 2S, 3E

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

    cout << "\n\n" << dir << blocks << "\n";
    last_coords = cur_coords;
    switch (cur_dir) {
    case 0:
      cur_coords.second += blocks;
      update_coords(2, last_coords.second, cur_coords.second,
                    last_coords.first);
      break;
    case 1:
      cur_coords.first += blocks;
      update_coords(1, last_coords.first, cur_coords.first, last_coords.second);
      break;
    case 2:
      cur_coords.second -= blocks;
      update_coords(4, cur_coords.second, last_coords.second,
                    last_coords.first);
      break;
    case 3:
      cur_coords.first -= blocks;
      update_coords(3, cur_coords.first, last_coords.first, last_coords.second);
      break;
    default:
      cout << "not possible";
      return -1;
    }
    total_blocks = abs(cur_coords.first) + abs(cur_coords.second);
  }

  cout << total_blocks << "\n";
  return 0;
}

int part1() { return loop(); }

int part2() {
  repeat_location = true;
  return loop();
}

int main() {
  // part1();
  part2();
}
