/*2D Top-down: Intuitive, TLE
int solve(int **triangle, int row_size, int row, int col, int **memo)
{
  if (row >= row_size)
    return 0;

  if (memo[row][col] != -1)
    return memo[row][col];

  int c1 = solve(triangle, row_size, row + 1, col, memo);
  int c2 = solve(triangle, row_size, row + 1, col + 1, memo);
  memo[row][col] = (c1 < c2) ? c1 + triangle[row][col] : c2 + triangle[row][col];

  return memo[row][col];
}

int minimumTotal(int **triangle, int triangleSize, int *triangleColSize)
{
  int **memo = malloc(triangleSize * sizeof(*memo));
  for(int i = 0; i < triangleSize; i++)
  {
    memo[i] = malloc((i + 1) * sizeof(**memo));
    for(int j = 0; j <= i; j++)
      memo[i][j] = -1;
  }

  int result = solve(triangle, triangleSize, 0, 0, memo);

  for (int i = 0; i < triangleSize; i++)
    free(memo[i]);
  free(memo);

 return result;
}
*/

/*2D Bottom-up
int minimumTotal(int **triangle, int triangleSize, int *triangleColSize)
{
  //triangle[i][j] = min(triangle[i + 1][j], triangle[i + 1][j + 1])
  //Keep it general assuming int **triangle is not allowed to be modified
  int **memo = malloc(triangleSize * sizeof(*memo));
  for (int i = 0; i < triangleSize; i++)
  {
    memo[i] = malloc((i + 1) * sizeof(**memo));
    memcpy(memo[i], triangle[i], (i + 1) * sizeof(**memo));
  }

  for (int row = triangleSize - 2; row >= 0; row--)
  {
    for (int col = 0; col <= row; col++)
    {
      memo[row][col] += (memo[row + 1][col] < memo[row + 1][col + 1] ? memo[row + 1][col] : memo[row + 1][col + 1]);
    }
  }

  int result = memo[0][0];
  for (int i = 0; i < triangleSize; i++)
    free(memo[i]);
  free(memo);

  return result;
}
*/

//1D Bottom-up
int minimumTotal(int **triangle, int triangleSize, int *triangleColSize)
{
  int memo[triangleSize];
  memcpy(memo, triangle[triangleSize - 1], triangleSize * sizeof(*memo));

  for (int row = triangleSize - 2; row >= 0; row--)
  {
    for (int col = 0; col <= row; col++)
      memo[col] = triangle[row][col] + (memo[col] < memo[col + 1] ? memo[col] : memo[col + 1]);
  }

  return memo[0];
}

/*
  0 1 2 3 4
0 2
1 3 4
2 6 5 7
3 4 8 1 3
4 7 1 5 9 6

m=7 1 5 9 6
*/
