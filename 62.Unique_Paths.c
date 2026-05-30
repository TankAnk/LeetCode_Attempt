void solve(int row, int col, int m, int n, int *memo)
{
  int idx = row * n + col;
  if (memo[idx] != -1)
    return;

  if (row == m - 1|| col == n - 1)
  {
    memo[idx] = 1;
    return;
  }

  int right_idx = (row + 1) * n + col, down_idx = row * n + col + 1;
  solve(row + 1, col, m, n, memo);
  solve(row, col + 1, m, n, memo);
  memo[idx] = memo[right_idx] + memo[down_idx];
}

/* 3x4
S . . .
. . . .
. . . E
*/

int uniquePaths(int m, int n)
{
  if (m == 1 || n == 1)
    return 1;

  int *memo = malloc(m * n * sizeof(*memo));
  for (int i = 0, size = m * n; i < size; i++)
    memo[i] = -1;

  solve(0, 0, m, n, memo);
  int result = memo[0];
  free(memo);
  return result;
}
