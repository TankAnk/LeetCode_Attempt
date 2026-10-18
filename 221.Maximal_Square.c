/*
Find the largest area starting at this cell.
*/
int solve(char **matrix, int row, int col, int row_size, int col_size, int **memo, int *best_side)
{
  // If this cell is 0 (never happen with this implementation), return 0.
  if (matrix[row][col] == '0')
    return 0;

  // Find the longest possible width of this row.
  int width = memo[row][col];

  // If the longest width is 1, the largest square area can only be 1.
  if (width == 1)
  {
    *best_side = (*best_side < 1) ? 1 : *best_side;
    return 1;
  }

  // Square area. At first as height is 1, its area is only 1.
  int area = 1;

  /*
  - Height of the current square.
  - Height - 1 act as offset to traverse row.
  */
  int height = 2;
  // Traverse to the next row as long as it starts with 1.
  while (row + height - 1 < row_size && matrix[row + height - 1][col] == '1')
  {
    int curr_width = memo[row + height - 1][col];

    // If this row has width 1 or width < current height, it can no longer form a larger square.
    if (curr_width == 1 || curr_width < height)
      return area;

    /*
    - Update minimum width.
    - To continue forming a square along the original cell, the length of the square cannot exceed this width.
    */
    if (width > curr_width)
      width = curr_width;

    /*
    If the global minimum width cannot exceed best side, we cannot form a larger square from here.
    */
    if (width <= *best_side)
      return area;

    // Square length is min(current height, min width) as long as min width >= current height.
    int len = (height < width) ? height : width;

    // Update area and best side if needed.
    if (area < len * len)
    {
      area = len * len;
      *best_side = len;
    }

    // Increment to next height.
    height++;
  }

  return area;
}

int maximalSquare(char **matrix, int matrixSize, int *matrixColSize)
{
  int result = 0;

  // Global side of the largest squar found.
  int best_side = 0;

  // Pre-compute the maximum width of 1 in each cell.
  int **memo = malloc(matrixSize * sizeof(*memo));
  for (int i = 0; i < matrixSize; i++)
    memo[i] = malloc(matrixColSize[0] * sizeof(**memo));

  for (int row = 0; row < matrixSize; row++)
  {
    for (int col = matrixColSize[0] - 1; col >= 0; col--)
    {
      if (matrix[row][col] == '0')
        memo[row][col] = 0;
      else if (col == matrixColSize[0] - 1)
        memo[row][col] = 1;
      else
        memo[row][col] = memo[row][col + 1] + 1;
    }
  }

  for (int row = 0; row < matrixSize; row++)
  {
    for (int col = 0; col < matrixColSize[0]; col++)
    {
      /*
      Skip if:
        - Current cell is 0.
        - The remaining rows cannot beat the global best side.
        - The remaining columns cnnot beat the global best side.
      */
      if (matrix[row][col] == '0'
        || matrixSize - row <= best_side
        || matrixColSize[0] - col <= best_side)
        continue;

      int area = solve(matrix, row, col, matrixSize, matrixColSize[0], memo, &best_side);

      if (result < area)
        result = area;
    }
  }

  for (int i = 0; i < matrixSize; i++)
    free(memo[i]);
  free(memo);

  return result;
}
