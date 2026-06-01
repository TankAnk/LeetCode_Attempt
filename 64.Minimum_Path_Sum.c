#define BOUND 798001 // (m + n - 1) * 200 + 1

int solve(int** grid, int row_size, int col_size, int row, int col, int **memo)
{
  if (row >= row_size || col >= col_size)
    return BOUND;

  if (row == row_size - 1 && col == col_size - 1)
    return memo[row][col] = grid[row][col];

  if (memo[row][col] != -1)
    return memo[row][col];

  int right = solve(grid, row_size, col_size, row, col + 1, memo);
  int down = solve(grid, row_size, col_size, row + 1, col, memo);
  memo[row][col] = (right < down) ? grid[row][col] + right : grid[row][col] + down;
  return memo[row][col];
}

int minPathSum(int** grid, int gridSize, int* gridColSize)
{
  int **memo = malloc(gridSize * sizeof(*memo));
  for (int i = 0; i < gridSize; i++)
  {
    memo[i] = malloc(gridColSize[0] * sizeof(**memo));
    memset(memo[i], -1, gridColSize[0] * sizeof(**memo));
  }

  int result = solve(grid, gridSize, gridColSize[0], 0, 0, memo);
  for (int i = 0; i < gridSize; i++)
    free(memo[i]);
  free(memo);
  return result;
}
