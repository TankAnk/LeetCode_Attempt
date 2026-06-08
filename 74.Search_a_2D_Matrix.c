/*
2D index --> flat index: row * colSize + col
flat index --> 2D index: row = index / colSize; col = index % colSize

Matrix size: 4x3
00 01 02 03
04 05 06 07
08 09 10 11

2 * 4 + 1 = 9
9 / 4 = 2
9 % 4 = 1

1 * 4 + 2 = 6
6 / 4 = 1
6 % 4 = 2

2 * 4 + 3 = 11
11 / 4 = 2
11 % 4 = 3
*/

bool searchMatrix(int** matrix, int matrixSize, int* matrixColSize, int target)
{
  int left = 0;
  int right = matrixSize * matrixColSize[0] - 1;
  int mid, row, col;
  while (left <= right)
  {
    mid = left + (right - left) / 2;
    //Convert flat index to 2D index
    row = mid / matrixColSize[0];
    col = mid % matrixColSize[0];
    if (matrix[row][col] == target)
      return true;
    else if (matrix[row][col] > target)
      right = mid - 1;
    else
      left = mid + 1;
  }

  return false;
}
