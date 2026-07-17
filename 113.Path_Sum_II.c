typedef struct TreeNode Node;
void solve(Node *root, int ***result, int **returnColumnSizes, int *returnSize, int *capacity, int targetSum, int curr_sum, int **curr_arr, int idx, int *size)
{
  if (!root)
    return;

  if (idx == *size)
  {
    *size *= 2;
    *curr_arr = realloc(*curr_arr, *size * sizeof(**curr_arr));
  }
  (*curr_arr)[idx] = (*root).val;

  if (!(*root).left && !(*root).right && (*curr_arr)[idx] + curr_sum == targetSum)
  {
    if (*returnSize == *capacity)
    {
      *capacity *= 2;
      *result = realloc(*result, *capacity * sizeof(**result));
      *returnColumnSizes = realloc(*returnColumnSizes, *capacity * sizeof(**returnColumnSizes));
    }

    (*returnColumnSizes)[*returnSize] = idx + 1;
    (*result)[*returnSize] = malloc((idx + 1) * sizeof(***result));
    memcpy((*result)[(*returnSize)++], *curr_arr, (idx + 1) * sizeof(***result));
    return;
  }

  solve((*root).left, result, returnColumnSizes, returnSize, capacity, targetSum, curr_sum + (*curr_arr)[idx], curr_arr, idx + 1, size);

  solve((*root).right, result, returnColumnSizes, returnSize, capacity, targetSum, curr_sum + (*curr_arr)[idx], curr_arr, idx + 1, size);
}

int **pathSum(Node *root, int targetSum, int *returnSize, int **returnColumnSizes)
{
  *returnSize = 0;
  if (!root)
    return NULL;

  int capacity = 128;
  int **result = malloc(capacity * sizeof(*result));
  *returnColumnSizes = malloc(capacity * sizeof(**returnColumnSizes));

  int size = 128;
  int *curr_arr = malloc(size * sizeof(*curr_arr));

  solve(root, &result, returnColumnSizes, returnSize, &capacity, targetSum, 0, &curr_arr, 0, &size);

  free(curr_arr);

  return result;
}
