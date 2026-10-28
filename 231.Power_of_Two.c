/*
bool isPowerOfTwo(int n)
{
  if (n <= 0 || n == INT_MAX)
      return false;

  int cnt = 0;
  while (n > 0)
  {
    if ((1 & n) == 1)
      cnt++;

    if (cnt > 1)
      return false;

    n >>= 1;
  }

  return true;
}
*/

bool isPowerOfTwo(int n)
{
  return n > 0 && (n & (n - 1)) == 0;
}
