#include <bits/stdc++.h>
#include <string>

using namespace std;

int main() {
  int x = 0;
  int y = 0;
  int dir; // 0 up, 1 right, 2 down, 3 left
  string input;

  while (getline(cin, input, ' ')) {
    cout << input << "\n";
    for (int i = 0; i < 3; i++) {
      if (i == 0) {
        char turn_dir = input[i];
        if (turn_dir == 'L') {
        }
        if (turn_dir == 'R') {
        }
      } else if (i == 1) {
        char blocks = input[i];
        if (dir == 0) {
          y++;
        } else if (dir == 1) {
          x++;
        } else if (dir == 2) {
          y--;
        } else if (dir == 3) {
          x--;
        }
      }
    }
  }

  return 0;
}
