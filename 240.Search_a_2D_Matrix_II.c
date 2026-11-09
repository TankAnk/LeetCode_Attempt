/* First attempt: perform binary search for row and column.
int binary_search_row(int *arr, int left, int right, int target)
{
  while (left <= right)
  {
    int mid = (right - left) / 2 + left;
    if (arr[mid] == target)
      return mid;

    else if (arr[mid] > target)
      right = mid - 1;

    else
      left = mid + 1;
  }

  return -1;
}

int binary_search_col(int **arr, int col, int left, int right, int target)
{
  while (left <= right)
  {
    int mid = (right - left) / 2 + left;
    if (arr[mid][col] == target)
      return mid;

    else if (arr[mid][col] > target)
      right = mid - 1;

    else
      left = mid + 1;
  }

  return -1;
}

bool searchMatrix(int **matrix, int matrixSize, int *matrixColSize, int target)
{
  for (int i = 0; i < matrixSize; i++)
  {
    if (binary_search_row(matrix[i], i, matrixColSize[0] - 1, target) != -1)
      return true;

    // Must validate:
    // - The start row.
    // - The searching column.
    if (i + 1 < matrixSize && i < matrixColSize[0]
      && binary_search_col(matrix, i, i + 1, matrixSize - 1, target) != -1)
      return true;
  }

  return false;
}
*/

/* Optimized solution: Binary search starting at top right corner
Top right corner:
  - All elemnt to the left are smaller.
  - All element under are larger.
  -> At every step, move either left or down.
  -> Binary choice at every step that eliminate an entire row or column.
*/
bool searchMatrix(int **matrix, int matrixSize, int *matrixColSize, int target)
{
  int row = 0, col = matrixColSize[0] - 1;
  while (row < matrixSize && col >= 0)
  {
    if (matrix[row][col] == target)
      return true;

    else if (matrix[row][col] > target)
      col--;

    else
      row++;
  }

  return false;
}
