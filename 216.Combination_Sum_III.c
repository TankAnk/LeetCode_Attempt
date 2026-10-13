void solve(int k, int n, int ***result, int *returnSize, int *capacity, int **returnColumnSizes, int start, int *tmp, int tmp_size, int curr_sum)
{
  if (curr_sum == n && tmp_size == k)
  {
    if (*returnSize == *capacity)
    {
      *capacity *= 2;
      *result = realloc(*result, *capacity * sizeof(**result));
      *returnColumnSizes = realloc(*returnColumnSizes, *capacity * sizeof(**returnColumnSizes));
    }

    (*returnColumnSizes)[*returnSize] = k;
    (*result)[*returnSize] = malloc(k * sizeof(***result));
    memcpy((*result)[*returnSize], tmp, k * sizeof(***result));
    (*returnSize)++;

    return;
  }

  if (tmp_size >= k || curr_sum > n || start > 9)
    return;

  /*
    Let i = start and next start = i + 1 to:
    - Ensures that each subsequent choice is greater than the previous choice
    - Avoids duplicated number selected again
    - Avoids permutations of the same combination
    */
  for (int i = start; i < 10; i++)
  {
    tmp[tmp_size] = i;
    solve(k, n, result, returnSize, capacity, returnColumnSizes, i + 1, tmp, tmp_size + 1, curr_sum + i);
  }
}

int **combinationSum3(int k, int n, int *returnSize, int **returnColumnSizes)
{
  *returnSize = 0;

  if (k > n)
    return NULL;

  *returnSize = 0;
  int capacity = 128;
  int **result = malloc(capacity * sizeof(*result));
  *returnColumnSizes = malloc(capacity * sizeof(**returnColumnSizes));

  int tmp[k];

  solve(k, n, &result, returnSize, &capacity, returnColumnSizes, 1, tmp, 0, 0);

  return result;
}
