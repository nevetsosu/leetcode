#include <string>
#include <iostream>

using namespace std;

class Parenthesis {
private:
  string s;
  
  int recurse(char prev = '0', int index = 0, int nest = 0) {
    if (index >= s.length()) return 0;

    if (index == 0) {
      if (s[index] == '(') {
        return recurse(s[index], index + 1, nest + 1)
      }
      else return recurse(s[index], index + 1, 0);
    }
public:
  Parenthesis(string s) {
    this->s = s;
  }

  int longestValidParenthesis() {
    solve();
    return max_found;
  }
};

class Solution {
public:
  int longestValidParentheses(string s) {
    Parenthesis p(s);
    return p.longestValidParenthesis();
  }
};

int main() {
  Solution solution;
  // string s("(()())");
  string s("(()(((()");
 
  /*
  // get and validate input string
  cout << "Enter parenthesis string:" << endl;
  cin >> s;
  if (!Solution::validate(s)) {
    cerr << "String should only contain parenthesis!" << endl;
    return 1;
  }
  */
  cout << solution.longestValidParentheses(s) << endl;
}
