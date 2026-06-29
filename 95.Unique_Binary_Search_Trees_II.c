/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
typedef struct TreeNode Node;

Node **solve(int low, int high, int *size)
{
  Node **result;
  if (low > high)
  {
    *size = 1;
    result = malloc(*size * sizeof(*result));
    result[0] = NULL;
    return result;
  }

  *size = 0;
  int capacity = 128;
  result = malloc(capacity * sizeof(*result));
  for (int i = low; i <= high; i++)
  {
    int left_size = 0, right_size = 0;
    Node **left_tree = solve(low, i - 1, &left_size);
    Node **right_tree = solve(i + 1, high, &right_size);

    for (int l = 0; l < left_size; l++)
    {
      for (int r = 0; r < right_size; r++)
      {
        if (*size == capacity)
        {
          capacity *= 2;
          result = realloc(result, capacity * sizeof(*result));
        }

        result[*size] = malloc(sizeof(**result));
        (*result[*size]).val = i;
        (*result[*size]).left = left_tree[l];
        (*result[*size]).right = right_tree[r];
        (*size)++;
      }
    }

    free(left_tree);
    free(right_tree);
  }

  return result;
}

Node **generateTrees(int n, int *returnSize)
{
  *returnSize = 0;
  return solve(1, n, returnSize);
}
