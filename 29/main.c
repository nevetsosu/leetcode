// https://leetcode.com/problems/divide-two-integers/

#include "stdio.h"

unsigned int positiveDivide(unsigned int dividend, unsigned int divisor) {
     unsigned int solution = 0;
     unsigned int currentDividend = (dividend >> 31) & 1;

     // ignore sign bit and keep zero index
     for (unsigned int i = sizeof(int) * 8 - 1; i > 0; i--) {
          if (currentDividend >= divisor) {
               currentDividend -= divisor;
               solution |= 1u << i;
          }
          currentDividend = (currentDividend << 1) | ((dividend >> (i - 1)) & 1);
     }

     // final bit doesn't carry
     if (currentDividend >= divisor) solution |= 1;
     return solution;
}

int divide(int dividend, int divisor) {
     // handle common 0 or 1 cases
     if (dividend == 0) return 0;
     else if (divisor == 1) return dividend;
     else if (divisor == 0) {
          fprintf(stderr, "WARNING: Divided by 0, returning max signed int!\n");
          return 0x7FFFFFFF;
     }

     int pDividendBool = dividend >= 0;
     int pDivisorBool = divisor >= 0;
     unsigned int positiveDividend;
     unsigned int positiveDivisor;

     if (dividend == -2147483648) positiveDividend = 2147483648u;
     else positiveDividend = pDividendBool ? dividend : -dividend;

     if (divisor == -2147483648) positiveDivisor = 2147483648u;
     else positiveDivisor = pDivisorBool ? divisor : -divisor;

     unsigned int answer = positiveDivide(positiveDividend, positiveDivisor);

     if (answer > 2147483647u) return 2147483647;

     if (pDividendBool ^ pDivisorBool) return -answer;
     return answer;
}


int main() {
     // printf("10 / 3 = %d\n", divide(10, 3));
     // printf("-10 / 3 = %d\n", divide(-10, 3));
     // printf("10 / -3 = %d\n", divide(10, -3));
     // printf("-10 / -3 = %d\n", divide(-10, -3));

     // printf("0x7FFFFFFF / -3 = %d\n", divide(0x7FFFFFFF, -3));
     // printf("0x7FFFFFFF / 0x7FFFFFFF = %d\n", divide(0x7FFFFFFF, 0x7FFFFFFF));

     // printf("0x80000000 / -1 = %d\n", divide(-2147483648, -1)); // 0x7FFFFFFF
     // printf("0x7FFFFFFF / -1 = %d\n\n", divide(2147483647, -1)); // 0x80000000

     // printf("0x80000000 / 1 = %d\n", divide(-2147483648, 1)); // 0x7FFFFFFF
     // printf("0x7FFFFFFF / 1 = %d\n", divide(2147483647, 1)); // 0x80000000

     printf("0x80000000 / 2 = %d\n", divide(-2147483648, 2)); // 0x7FFFFFFF

     return 0;
}
