int solve(int** grid, int row_size, int col_size, int *memo, int row, int col)
{
  int idx = row * col_size + col;
  if (grid[row][col] == 1)
  {
    memo[idx] = 0;
    return memo[idx];
  }

  if (memo[idx] != -1)
    return memo[idx];

  if (row == row_size - 1)
  {
    memo[idx] = 1;
    for (int i = col + 1; i < col_size; i++)
      if (grid[row][i] == 1)
        memo[idx] = 0;

    return memo[idx];
  }

  if (col == col_size - 1)
  {
    memo[idx] = 1;
    for (int i = row + 1; i < row_size; i++)
      if (grid[i][col] == 1)
        memo[idx] = 0;

    return memo[idx];
  }

  solve(grid, row_size, col_size, memo, row + 1, col);
  solve(grid, row_size, col_size, memo, row, col + 1);
  int right_idx = idx + 1, down_idx = (row + 1) * col_size + col;
  memo[idx] = memo[right_idx] + memo[down_idx];
  return memo[idx];
}

/*
0,0,0
0,0,0
0,0,1
*/

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize)
{
  int memo[obstacleGridSize * obstacleGridColSize[0]];
  memset(memo, -1, obstacleGridSize * obstacleGridColSize[0] * sizeof(*memo));
  return solve(obstacleGrid, obstacleGridSize, obstacleGridColSize[0], memo, 0, 0);
}
