void merge(int *arr, int left, int mid, int right)
{
  int s1 = mid - left + 1, s2 = right - mid;
  int l_arr[s1], r_arr[s2];
  for (int i = 0; i < s1; i++)
    l_arr[i] = arr[left + i];
  for (int j = 0; j < s2; j++)
    r_arr[j] = arr[mid + 1 + j];

  int i = 0, j = 0, k = left;
  while (i < s1 && j < s2)
  {
    if (l_arr[i] <= r_arr[j])
      arr[k++] = l_arr[i++];
    else
      arr[k++] = r_arr[j++];
  }

  while (i < s1)
    arr[k++] = l_arr[i++];

  while (j < s2)
    arr[k++] = r_arr[j++];
}

void merge_sort(int *arr, int left, int right)
{
  if (left < right)
  {
    int mid = left + (right - left) / 2;
    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

void solve(int *nums, int numsSize, int *returnSize, int **returnColumnSizes, int ***result, int *curr, int nums_idx, int curr_idx, int *capacity)
{
  if (curr_idx == numsSize|| nums_idx == numsSize)
    return;

  for (int i = nums_idx; i < numsSize; i++)
  {
    if (i > nums_idx && nums[i] == nums[i - 1])
      continue;

    if (*returnSize == *capacity)
    {
      (*capacity) *= 2;
      *result = realloc(*result, *capacity * sizeof(**result));
      *returnColumnSizes = realloc(*returnColumnSizes, *capacity * sizeof(**returnColumnSizes));
    }

    curr[curr_idx] = nums[i];
    (*result)[*returnSize] = malloc((curr_idx + 1) * sizeof(***result));
    memcpy((*result)[*returnSize], curr, (curr_idx + 1) * sizeof(***result));
    (*returnColumnSizes)[(*returnSize)++] = curr_idx + 1;
    solve(nums, numsSize, returnSize, returnColumnSizes, result, curr, i + 1, curr_idx + 1, capacity);
  }
}

int** subsetsWithDup(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
  merge_sort(nums, 0, numsSize - 1);

  *returnSize = 1;
  int capacity = 128;
  int **result = malloc(capacity * sizeof(*result));
  result[0] = NULL;

  *returnColumnSizes = malloc(capacity * sizeof(**returnColumnSizes));
  (*returnColumnSizes)[0] = 0;

  int *curr = malloc(numsSize * sizeof(*curr));

  solve(nums, numsSize, returnSize, returnColumnSizes, &result, curr, 0, 0, &capacity);
  free(curr);
  return result;
}
