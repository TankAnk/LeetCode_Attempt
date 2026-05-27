int** generateMatrix(int n, int* returnSize, int** returnColumnSizes) {
  *returnSize = n;
  *returnColumnSizes = malloc(n * sizeof(**returnColumnSizes));
  for (int i = 0; i < n; i++)
    (*returnColumnSizes)[i] = n;

  int **result = malloc(*returnSize * sizeof(*result));
  for (int i = 0; i < *returnSize; i++)
    result[i] = malloc(*returnSize * sizeof(**result));
  int offset = 0, curr = 1, max = (n + 1)/ 2, top, right, bottom, left;
  while (offset < max)
  {
    //Set boundaries
    top = offset;
    right = n - 1 - offset;
    bottom = n - 1 - offset;
    left = offset;


    //Travers top: left to right
    for (int i = left; i <= right; i++)
      result[top][i] = curr++;

    //Traverse right size: top to bottom
    for (int i = top + 1; i <= bottom; i++)
      result[i][right] = curr++;

    //Traverse bottom: right to left
    for (int i = right - 1; i >= left; i--)
      result[bottom][i] = curr++;

    //Traverse left side: bottom to top
    for (int i = bottom - 1; i > top; i--)
      result[i][left] = curr++;

    offset++;
  }

  return result;
}
