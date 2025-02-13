#include <iostream>
#include <string>

using namespace std;

class Solution {
  enum Mode { Add, Compare };

  string s;
  int index;
  int counter;
  int nest;
  Mode mode;

public:
  int longestValidParentheses(string s) {
    this->s = s;
    this->index = 0;
    this->mode = Add;
    this->counter = 0;
    this->nest = 0;

    return recurse();
  }

private:
  int recurse() {
    int length = 0;
    auto updateLength = [&length, this](int l) {
      switch (this->mode) {
      case Mode::Add:
        length += l;
        break;
      case Mode::Compare:
        length = (l > length) ? l : length;
        break;
      }
    };

    // Base Condition
    if (this->index >= s.length()) {
      this->mode = Mode::Add; // mode doesn't matter here but adding is faster
      return 0;
    }

    // '(' just increments nest level
    if (this->s[this->index] == '(') {
      index++;
      nest++;
      int l = recurse();
      updateLength(l);
    }
    // ')' depends on nest level
    else if (nest > 0) {
      length += 2;
      nest--;
      int l = recurse();
      updateLength(l);

      this->mode = Mode::Add;
      return length;
    }

    index++;
    int l = recurse();
    updateLength(l);

    this->mode = (nest == 0) ? Mode::Add : Mode::Compare;
    return length;
  }
};

int main() {
  Solution s;
  //())
  int solution = s.longestValidParentheses(")()())()()(");
  // ()())((()))

  cout << solution << endl;
}
