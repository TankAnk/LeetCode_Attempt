int occur(int *arr, int size, int val)
{
  for (int i = 0; i < size; i++)
    if (arr[i] == val)
      return i;

  return -1;
}

void solve(int* nums, int numsSize, int* returnSize, int ***result, int *result_idx, int *curr, int curr_idx, int *used)
{
  if (*result_idx >= *returnSize)
    return;
  
  if (curr_idx >= numsSize)
  {
    memcpy((*result)[(*result_idx)++], curr, numsSize * sizeof(*curr));
    return;
  }
      
  for (int i = 0; i < numsSize; i++)
  {
    if (occur(used, curr_idx, nums[i]) == -1)
    {
      curr[curr_idx] = nums[i];    
      used[curr_idx++] = nums[i];
      solve(nums, numsSize, returnSize, result, result_idx, curr, curr_idx, used);
      
      curr_idx--;
    }
  }
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
  *returnSize = 1;
  for (int i = numsSize; i > 1; i--)
    *returnSize *= i;
  *returnColumnSizes = malloc(*returnSize * sizeof(**returnColumnSizes));
  for (int i = 0; i < *returnSize; i++)
    (*returnColumnSizes)[i] = numsSize;
  
  int **result = malloc(*returnSize * sizeof(*result));
  for(int i = 0; i < *returnSize; i++)
    result[i] = malloc(numsSize * sizeof(**result));

  int *curr = malloc(numsSize * sizeof(*curr));
  int result_idx = 0;
  int *used = malloc(numsSize * sizeof(*used));

  solve(nums, numsSize, returnSize, &result, &result_idx, curr, 0, used);
  
  free(curr);
  free(used);
  return result;
}
