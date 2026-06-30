int solve(int low, int high, int **memo)
{
  if (low > high)
    return 1;

  if (memo[low][high] != -1)
    return memo[low][high];

  int left_size, right_size;
  memo[low][high] = 0;
  for (int i = low; i <= high; i++)
  {
    left_size = solve(low, i - 1, memo);
    right_size = solve(i + 1, high, memo);
    memo[low][high] += left_size * right_size;
  }

  return memo[low][high];
}

int numTrees(int n)
{
  int **memo = malloc((n + 1) * sizeof(*memo));
  for (int i = 0; i <= n; i++)
  {
    memo[i] = malloc((n + 1) * sizeof(**memo));
    for (int j = 0; j <= n; j++)
      memo[i][j] = -1;
  }

  int result = solve(1, n, memo);
  for (int i = 0; i <= n; i++)
    free(memo[i]);
  free(memo);
  return result;
}
