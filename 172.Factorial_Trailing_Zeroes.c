/*
  - Count multiples of 5
  - Some numbers has > 1 factor of 5 like 25 = 5 ^ 2, 50 = 2 x 5 ^ 2
*/

int trailingZeroes(int n)
{
  int result = 0;
  while (n >= 5)
  {
    n /= 5;
    result += n;
  }

  return result;
}
