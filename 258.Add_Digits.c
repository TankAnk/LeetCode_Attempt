/*
- abc = a * 100 + b *10 + c
- 10^k % 9 = 1, k >= 0
-> abc % 9 = (a + b + c) % 9
-> Every time a number replaced w/ the sum of its digits, the result of % 9 remains.

Ex: 583
5 + 8 + 3 = 16
1 + 6 = 7

583 = 5 * 100 + 8 * 10 + 3
583 % 9 = (5 + 8 + 3) % 9
        = 16 % 9
        = (1 + 6) % 9
        = 7
*/

int addDigits(int num)
{
  if (num == 0)
    return 0;

  if (num % 9 == 0)
    return 9;

  return num % 9;
}
