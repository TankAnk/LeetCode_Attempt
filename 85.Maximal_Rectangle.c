int largest_area_in_histogram(int *arr, int size)
{
  int result = 0, stack_idx = -1, arr_idx = 0;
  int stack[size];

  while (arr_idx < size)
  {
    if (stack_idx < 0 || arr[arr_idx] >= arr[stack[stack_idx]])
      stack[++stack_idx] = arr_idx++;

    else
    {
      int top = stack[stack_idx--];
      int width = (stack_idx < 0) ? arr_idx : arr_idx - stack[stack_idx] - 1;
      int area = width * arr[top];
      if (result < area)
        result = area;
    }
  }

  while (stack_idx >= 0)
  {
    int top = stack[stack_idx--];
    int width = (stack_idx < 0) ? arr_idx : arr_idx - stack[stack_idx] - 1;
    int area = width * arr[top];
    if (result < area)
      result = area;
  }

  return result;
}

int maximalRectangle(char** matrix, int matrixSize, int* matrixColSize)
{
  int histogram[matrixColSize[0]];
  memset(histogram, 0, matrixColSize[0] * sizeof(*histogram));
  int result = 0;
  for (int i = 0; i < matrixSize; i++)
  {
    for (int j = 0; j < matrixColSize[0]; j++)
    {
      if (matrix[i][j] == '0')
        histogram[j] = 0;

      else
        histogram[j]++;
    }
    int tmp = largest_area_in_histogram(histogram, matrixColSize[0]);
    if (tmp > result)
      result = tmp;
  }

  return result;
}
