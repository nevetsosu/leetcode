#include <string>
#include <iostream>

using namespace std;

class Parenthesis {
private:
  string s;
  int max_found = 0;
  int cur_found = 0;
  int index = 0;
  bool continous = true;

  int findNest() {
    cerr << "Entered findNest() at index " << this->index << endl;

    int nest = 0;
    int length = 0;

    // enter nest
    do {
      if (this->index < s.length() && s[this->index] == '(') {
        nest++;
      }
      else {
        break;
      }
      index++;
    } while (true);
  
    // exit nests
    do {
      if (this->index >= s.length()) {
        break;
      }
      else if (s[this->index] == ')') {
        nest--;
        if (nest == 0) length += 2;
      }
      else if (s[this->index] == '(') {
        nest++;
      }
      index++;
    } while (nest != 0);
    if (nest > 0) this->continous = false;

    return length;
  }

  // returns true if continous
  // returns false is non-continous (a ')' was found)
  void nextNest() {
    cerr << "entered nextNest() at index " << index << endl;
    while (this->index < s.length()) {
      if (s[this->index] == ')') {
        this->continous = false;
      }
      else break;
      index++;
    }
    cerr << (this->continous ? "no additional closing braces" : "additional close found") << endl;
  }
 
public:
  Parenthesis(string s) {
    this->s = string(s);
  }

  int longestValidParentheses() {
    while (this->index < s.length()) {
      this->continous = true;
      nextNest();
      int length = findNest();
      cerr << "findNest returned " << length << endl;

      if (this->continous) {
        cerr << "continous" << endl;
        this->cur_found += length;
        cerr << "Grew cur_found to " << cur_found << endl;
      } else {
        cerr << "discontinous" << endl;
        this->max_found = this->cur_found > this->max_found ? this->cur_found : this->max_found;
        this->cur_found = length;
        cerr << "new max_found is " << max_found << endl;
        cerr << "new cur_found is " << cur_found << endl;
      }
    }
    max_found = cur_found > max_found ? cur_found : max_found;

    return max_found;
  }
};

class Solution {
public:
  int longestValidParentheses(string s) {
    Parenthesis p(s);
    return p.longestValidParentheses();
  }
    
  static bool validate(string s) {
    int index = 0;
    while (index <= s.length()) {
      if (s[index] != '(' && s[index] != ')') {
        return false;
      }
    }
    return true;
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
