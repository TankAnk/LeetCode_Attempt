/*
This is just a Fibonnaci sequence because:
  - At any stair: the last move either 1 or 2
  - The number of moves to get to n - 1 is f(n - 1)
  - The number of moves to get to n - 2 is f(n - 2)
  --> Total f(n - 1) + f(n - 2)

01 02 03 04 05 06 07
01 02 03 05 08 13 21
*/

int climbStairs(int n) {
  if (n <= 3)
    return n;

  int left = 3, right = 5, tmp;
  for (int i = 4; i < n; i++)
  {
    tmp = left + right;
    left = right;
    right = tmp;
  }
  return right;
}
