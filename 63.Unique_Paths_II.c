int solve(int** grid, int row_size, int col_size, int *memo, int row, int col)
{
  if (row >= row_size || col >= col_size)
    return 0;

  int idx = row * col_size + col;
  if (memo[idx] != -1)
    return memo[idx];

  if (grid[row][col] == 1)
    return memo[idx] = 0;

  if (row == row_size - 1 && col == col_size - 1)
    return memo[idx] = 1;

  memo[idx] = solve(grid, row_size, col_size, memo, row + 1, col) + solve(grid, row_size, col_size, memo, row, col + 1);
  return memo[idx];
}

/*
0,0
0,1
*/

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridSize, int* obstacleGridColSize)
{
  int memo[obstacleGridSize * obstacleGridColSize[0]];
  memset(memo, -1, obstacleGridSize * obstacleGridColSize[0] * sizeof(*memo));
  return solve(obstacleGrid, obstacleGridSize, obstacleGridColSize[0], memo, 0, 0);
}
