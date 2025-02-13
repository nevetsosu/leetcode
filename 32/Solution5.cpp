#include <string>
#include <iostream>

using namespace std;

class Solution {
  enum Mode {
    Add,
    Compare,
  };

  string s;
  uint index;
  uint max;
  Mode mode;
  
  uint counter = 0;

private:
  int recurse(int prevLength = 0, int nest = 0) {
    bool state = (nest > 0); 
    int length = 0;

    while (this->index < this->s.length()) {
      // '('
      if (this->s[this->index] == '(') {
        if (state == true) {
          index++;
          length += recurse(prevLength + length, nest + 1);
        }
        else {
          state = true;
        }
      }
      // ')'
      else {
        if (nest > 0) {
          state = false;

          length += 2;
          break;
        }
        else if (state == true) {
          state = false; 
          length += 2;
          index++;
          length += recurse(prevLength + length, nest);
        }
        else {
          index++;
          int l = recurse(0, 0);
          return (max > l) ? max : l;
        }
      }
      index++;
    }
    
    this->max = (this->max > (prevLength + length)) ? this->max : (prevLength + length);
    return state ? 0 : length;
  }

public:
  int longestValidParentheses(string s) {
    this->index = 0;
    this->max = 0;
    this->mode = Mode::Add;
    this->s = s;

    int l = recurse();
    this->max = this->max > l ? this->max : l;

    return max; 
  }
  
};

int main() {
  int length = Solution().longestValidParentheses(")()())())())");
  cout << length << endl;
}
