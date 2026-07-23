/*
9C5 = 9.8.7.6.5.4.3.2.1 / (5.4.3.2.1 * 4.3.2.1)
    = 9.8.7.6 / 4.3.2.1
nCk = n! / k!(n - k)!;
*/

int combination(int n, int k)
{
  if (n < k || n < 0 || k < 0)
    return -1;

  if (n == 0 || k == 0 || n == k)
    return 1;

  if (k > n / 2)
    k = n - k;

  long long result = 1;

  for (int i = n, j = 1; i > k && j <= k;  i--, j++)
    result = result * i / j;

  return (int)result;
}

/*
row 9
0 1 2  3  4   5   6  7  8 9
1 9 36 84 126 126 84 36 9 1

row 10
0 1  2  3   4   5   6   7   8  9  10
1 10 45 120 210 252 210 120 45 10 1
*/

int *getRow(int rowIndex, int *returnSize)
{
  *returnSize = rowIndex + 1;
  int *result = malloc(*returnSize * sizeof(*result));

  for (int i = 0; i < *returnSize; i++)
    result[i] = combination(rowIndex, i);

  return result;
}
