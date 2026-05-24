int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
  *returnSize = matrixSize * matrixColSize[0];
  int *result = malloc(*returnSize * sizeof(*result));
  int res_idx = 0, offset = 0, top, right, bottom, left;

  while (res_idx < *returnSize)
  {
    //Set boundaries
    top = offset;
    right = matrixColSize[0] - 1 - offset;
    bottom = matrixSize - 1 - offset;
    left = offset;

    //Travers top: left to right
    for (int i = left; i <= right && res_idx < *returnSize; i++)
      result[res_idx++] = matrix[top][i];
  
    //Traverse right size: top to bottom
    for (int i = top + 1; i <= bottom && res_idx < *returnSize; i++)
      result[res_idx++] = matrix[i][right];
    
    //Traverse bottom: right to left
    for (int i = right - 1; i >= left && res_idx < *returnSize; i--)
      result[res_idx++] = matrix[bottom][i];

    //Traverse left side: bottom to top
    for (int i = bottom - 1; i > top && res_idx < *returnSize; i--)
      result[res_idx++] = matrix[i][left];
    
    offset++;
  }

  return result;
}
