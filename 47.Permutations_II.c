void merge(int *arr, int left, int mid, int right)
{
  int i = 0, j = 0, k = left;
  int sl = mid - left + 1, sr = right - mid;
  int l[sl], r[sr];
  for (int z = 0; z < sl; z++)
    l[z] = arr[left + z];
  for (int z = 0; z < sr; z++)
    r[z] = arr[mid + z + 1];

  while (i < sl && j < sr)
  {
    if (l[i] <= r[j])
      arr[k++] = l[i++];
    else
      arr[k++] = r[j++]; 
  }

  while (i < sl)
    arr[k++] = l[i++];

  while (j < sr)
    arr[k++] = r[j++];
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
    if (used[i] || i > 0 && nums[i] == nums[i - 1] && !used[i - 1])
      continue;
      
    curr[curr_idx] = nums[i];
    used[i] = 1;
    solve(nums, numsSize, returnSize, result, result_idx, curr, curr_idx + 1, used);
    used[i] = 0;
  }
}

int** permuteUnique(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
  *returnSize = 1;
  merge_sort(nums, 0, numsSize - 1);
  for (int i = numsSize; i > 1; i--)
    *returnSize *= i;  
  for (int i = 0; i < numsSize - 1; i++)
  {
    int count = 1;
    while (i < numsSize - 1 && nums[i] == nums[i + 1])
    {
      count++;
      *returnSize /= count;
      i++;
    }
  }

  *returnColumnSizes = malloc(*returnSize * sizeof(**returnColumnSizes));
  for (int i = 0; i < *returnSize; i++)
    (*returnColumnSizes)[i] = numsSize;
  int **result = malloc(*returnSize * sizeof(*result));
  for (int i = 0; i < *returnSize; i++)
    result[i] = malloc(numsSize * sizeof(**result));

  int result_idx = 0;
  int *curr = malloc(numsSize * sizeof(*curr));
  int *used = calloc(numsSize, sizeof(*used));

  solve(nums, numsSize, returnSize, &result, &result_idx, curr, 0, used);

  free(curr);
  free(used);
  return result;
}
