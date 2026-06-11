/*
C(3,7) = 7! / 3!4! = 7x6x5 x 4x3x2 / 3x2 x 4x3x2
C(4,9) = 9! / 4!5! = 9x8x7x6 x 5x4x3x2 / 4x3x2 x 5x4x3x2
*/
/*
unsigned long long combination(int n, int k)
{
  if (k > n)
    return 0;

  if (k == n || k == 0)
    return 1;

  if (k == 1)
    return n;

  k = (n - k < k) ? n - k : k;

  unsigned long long result = 1;
  for (int i = 1; i <= k; i++)
    result = result * (n - i + 1) / i;

  return result;
}
*/

void solve(int n, int k, int* returnSize, int ***result, int *curr_arr, int curr_idx, int curr_val, int *capacity)
{
  if (curr_idx == k)
  {
    if (*returnSize == *capacity)
    {
      *capacity *= 2;
      *result = realloc(*result, *capacity * sizeof(**result));
    }

    (*result)[*returnSize] = malloc(k * sizeof(***result));
    memcpy((*result)[*returnSize], curr_arr, k * sizeof(***result));
    (*returnSize)++;
    return;
  }

  for (int i = curr_val; i <= n; i++)
  {
    curr_arr[curr_idx] = i;
    solve(n, k, returnSize, result, curr_arr, curr_idx + 1, i + 1, capacity);
  }
}

int** combine(int n, int k, int* returnSize, int** returnColumnSizes)
{
  *returnSize = 0;
  int capacity = 128;
  int **result = malloc(capacity * sizeof(*result));
  int *curr_arr = malloc(k * sizeof(*curr_arr));
  solve(n, k, returnSize, &result, curr_arr, 0, 1, &capacity);

  *returnColumnSizes = malloc(*returnSize * sizeof(**returnColumnSizes));
  for (int i = 0; i < *returnSize; i++)
    (*returnColumnSizes)[i] = k;

  free(curr_arr);
  return result;
}
