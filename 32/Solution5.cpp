#include <string>
#include <iostream>

using namespace std;

class Solution {
  string s;
  uint index;
  uint max;
  
private:
  int recurse(int nest = 0, int prevLength = 0) {
    bool state = (nest > 0); 
    int length = 0;

    while (this->index < this->s.length()) {
      // '('
      if (this->s[this->index] == '(') {
        if (state) {
          index++;
          int L = recurse(nest + 1, 0);
          length += L;
          
          this->max = (this->max > length) ? this->max : length;

          if (L == 0) {
            return 0;
          } 
        }
        else {
          state = true;
        }
      }
      else if (state) {
        state = false; 
        length += 2;
        
        if (nest > 0) {
          break;
        } else {
          index++;

          int L = recurse(nest, prevLength + length);
          length += L;

          this->max = ((length + prevLength) > this->max) ? (length + prevLength) : this->max;
          if (L == 0) {
            return 0;
          }
          
        }
      }
      else {
        break;
      }
      index++;
    }
    
    if (nest == 0 && !state) {
      this->max = (length + prevLength)  > this->max ? (length + prevLength) : this->max;
    }
    else {
      this->max = (length > this->max) ? length : this->max;
    }
    
    return state ? 0 : length;
  }

public:
  int longestValidParentheses(string s) {
    this->index = 0;
    this->max = 0;
    this->s = s;

    while (this->index < this->s.length()) {
      recurse();
      this->index++;
    }

    return max; 
  }
  
};

int main() {
  cout << "A: " << Solution().longestValidParentheses(")()())()()(") << " = 4"<< endl;
  cout << "B: " << Solution().longestValidParentheses("()(()") << " = 2" << endl;
  cout << "C: " << Solution().longestValidParentheses("()(())") << " = 6" << endl;
  cout << "D: " << Solution().longestValidParentheses(")(()()()()())()(()()()((()()()))))))") << " = 32" << endl;
  cout << "E.2: " << Solution().longestValidParentheses("(())") << " = 4" << endl;
  cout << "E: " << Solution().longestValidParentheses("(())(") << " = 4" << endl; 
  cout << "F.2: " << Solution().longestValidParentheses("()()(())((") << " = 8" << endl; 
  cout << "F: " << Solution().longestValidParentheses("(()()(())((") << " = 8" << endl;
 }
