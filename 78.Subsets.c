void solve(int* nums, int numsSize, int* returnSize, int** returnColumnSizes, int ***result, int *curr_arr, int curr_idx, int nums_idx, int *capacity)
{
  if (nums_idx >= numsSize || curr_idx >= numsSize)
    return;

  for (int i = nums_idx; i < numsSize; i++)
  {
    if (*returnSize == *capacity)
    {
      *capacity *= 2;
      *result = realloc(*result, *capacity * sizeof(**result));
      *returnColumnSizes = realloc(*returnColumnSizes, *capacity * sizeof(**returnColumnSizes));
    }

    curr_arr[curr_idx] = nums[i];
    (*result)[*returnSize] = malloc((curr_idx + 1) * sizeof(***result));
    memcpy((*result)[*returnSize], curr_arr, (curr_idx + 1) * sizeof(***result));
    (*returnColumnSizes)[*returnSize] = curr_idx + 1;
    (*returnSize)++;
    solve(nums, numsSize, returnSize, returnColumnSizes, result, curr_arr, curr_idx + 1, i + 1, capacity);
  }
}

/*1 2 3
empty
1 12 13 123
2 23
3
*/

int** subsets(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
  *returnSize = 1;
  int capacity = 128;
  int **result = malloc(capacity * sizeof(*result));
  result[0] = NULL;
  *returnColumnSizes = malloc(capacity * sizeof(**returnColumnSizes));
  (*returnColumnSizes)[0] = 0;
  int *curr_arr = malloc(numsSize * sizeof(*curr_arr));
  solve(nums, numsSize, returnSize, returnColumnSizes, &result, curr_arr, 0, 0, &capacity);
  free(curr_arr);
  return result;
}
