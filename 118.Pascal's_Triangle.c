int **generate(int numRows, int *returnSize, int **returnColumnSizes)
{
  *returnSize = numRows;
  *returnColumnSizes = malloc(numRows * sizeof(**returnColumnSizes));
  for (int i = 0; i < numRows; i++)
    (*returnColumnSizes)[i] = i + 1;

  int **result = malloc(numRows * sizeof(*result));
  for (int i = 0; i < numRows; i++)
    result[i] = malloc((i + 1) * sizeof(**result));

  for (int i = 0; i < numRows; i++)
  {
    for (int j = 0; j < i + 1; j++)
    {
      if (j == 0 || j == i)
        result[i][j] = 1;

      else
        result[i][j] = result[i - 1][j - 1] + result[i - 1][j];
    }
  }

  return result;
}
