#define MIN_CANDIDATE_VAL 2
#define MAX_TARGET_VAL 40
#define MAX_COMBINATION 150

void solve(int **result, int *curr, int *curr_size, int *curr_sum, int candidate_idx, int *candidates, int candidatesSize, int target, int *returnSize, int **returnColumnSizes)
{
  if (candidate_idx >= candidatesSize || *curr_sum > target)
    return;
  
  else if (*curr_sum == target)
  {
    (*returnSize)++;
    *returnColumnSizes = realloc(*returnColumnSizes, sizeof(**returnColumnSizes) * (*returnSize));
    (*returnColumnSizes)[*returnSize - 1] = *curr_size;
    result[*returnSize - 1] = malloc(sizeof(**result) * (*curr_size));
    memcpy(result[*returnSize - 1], curr, sizeof(**result) * (*curr_size));
  }

  else if (*curr_sum < target)
  {
    for (int i = candidate_idx; i < candidatesSize; i++)
    {
      (*curr_size)++;
      curr[*curr_size - 1] = candidates[i];
      int next_sum = *curr_sum + candidates[i];

      solve(result, curr, curr_size, &next_sum, i, candidates, candidatesSize, target, returnSize, returnColumnSizes);
      (*curr_size)--;
  }
}

  return;
}

int** combinationSum(int* candidates, int candidatesSize, int target, int* returnSize, int** returnColumnSizes) {
  *returnSize = 0;
  int curr_size = 0, curr_sum = 0;
  int *curr = malloc(sizeof(*curr) * (MAX_TARGET_VAL / MIN_CANDIDATE_VAL));
  int **result = malloc(sizeof(*result) * MAX_COMBINATION);
  *returnColumnSizes = NULL;
  solve(result, curr, &curr_size, &curr_sum, 0, candidates, candidatesSize, target, returnSize, returnColumnSizes);

  return result;
}
