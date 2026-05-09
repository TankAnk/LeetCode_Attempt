#define MIN_CANDIDATE_VAL 1
#define MAX_TARGET_VAL 30

void merge(int *arr, int left, int mid, int right)
{
  int i = 0, j = 0, k = left;
  int left_len = mid - left + 1, right_len = right - mid;
  int L[left_len], R[right_len];
  for (int z = 0; z < left_len; z++)
    L[z] = arr[left + z];
  
  for (int z = 0; z < right_len; z++)
    R[z] = arr[mid + z + 1];

  while (i < left_len && j < right_len)
  {
    if (L[i] < R[j])
      arr[k++] = L[i++];
    else
      arr[k++] = R[j++];
  }

  while (i < left_len)
    arr[k++] = L[i++];
  while (j < right_len)
    arr[k++] = R[j++];
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

void solve(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes, int ***result, int sum, int *curr, int *curr_size, int candidate_idx, int *capacity)
{
  if (sum == target)
  {
    if (*returnSize == *capacity)
    {
      (*capacity) *= 2;
      *result = realloc(*result, *capacity * sizeof(**result));
      *returnColumnSizes = realloc(*returnColumnSizes, *capacity * sizeof(**returnColumnSizes));
    }

    (*returnSize)++;
    (*returnColumnSizes)[*returnSize - 1] = *curr_size;
    (*result)[*returnSize - 1] = malloc(*curr_size * sizeof(***result));
    memcpy((*result)[*returnSize - 1], curr, *curr_size * sizeof(***result));

    return;
  }

  else if (sum < target)
  {
    for (int i = candidate_idx + 1; i < candidatesSize; i++)
    {
      if (i > candidate_idx + 1 && candidates[i] == candidates[i - 1])
        continue;
      if (sum + candidates[i] > target)
        break;
      sum += candidates[i];
      (*curr_size)++;
      curr[*curr_size - 1] = candidates[i];
      
      solve(candidates, candidatesSize, target, returnSize, returnColumnSizes, result, sum, curr, curr_size, i, capacity);
      sum -= candidates[i];
      (*curr_size)--;  
    }
  }

    if (*curr_size >= (MAX_TARGET_VAL / MIN_CANDIDATE_VAL) || candidate_idx >= candidatesSize)
      return;
}

int** combinationSum2(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
  merge_sort(candidates, 0, candidatesSize - 1);
  int capacity = 150, curr_size = 0;
  *returnSize = 0;
  *returnColumnSizes = malloc(capacity * sizeof(**returnColumnSizes));
  int *curr = malloc((MAX_TARGET_VAL / MIN_CANDIDATE_VAL) * sizeof(*curr));
  int **result = malloc(capacity * sizeof(*result));
  solve(candidates, candidatesSize, target, returnSize, returnColumnSizes, &result, 0, curr,  &curr_size, -1, &capacity);

  free(curr);
  return result;
}
