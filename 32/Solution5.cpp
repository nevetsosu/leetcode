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
  Mode mode;
  
  uint counter = 0;

private:
  int recurse(int nest = 0) {
    cerr << this->counter++ << endl;
    int length = 0;
    bool state = false;

    auto update = [&length, this](int l) {
      switch (this->mode) { 
        case Mode::Add:
          length += 2;
          break;
        case Mode::Compare:
          length = length > l ? length : l;
          break;
      }
    };

    while (this->index < this->s.length()) {
      cerr << "index: " << this->index << ", char: " << this->s[this->index] << endl;

      if (this->s[this->index] == '(') {
        if (state == false) {
          cerr << "setting state" << endl;
          state = true;
        }
        else {
          cerr << "recursing forward" << endl;
          index++;
          update(recurse(nest + 1));
        }
      }

      // match ')'
      else {
        if (state == true) {
          cerr << "adding 2 to length" << endl;
          length += 2;
          state = false;
        }
        else if (nest > 0) {
          cerr << "stopping unnest" << endl;
          index++;
          break;
        } else {
          cerr << "passing forward" << endl;
          index++;
          int l = recurse(0);
          length = length > l ? length : l;
          break; 
        }
      }
      
      index++;
    }
    
    this->mode = state ? Mode::Compare : Mode::Add;
    return length;
  }

public:
  int longestValidParentheses(string s) {
    this->index = 0;
    this->mode = Mode::Add;
    this->s = s;

    return recurse(); 
  }
  
};

int main() {
  int length = Solution().longestValidParentheses("()(())");
  cout << length << endl;
}
