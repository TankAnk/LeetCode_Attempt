typedef struct TreeNode Node;

int solve(Node *root, int *bound)
{
  if (!root)
    return 0;

  int left_sum = solve((*root).left, bound);
  if (left_sum < 0)
    left_sum = 0;

  int right_sum = solve((*root).right, bound);
  if (right_sum < 0)
    right_sum = 0;

  if ((*root).val + left_sum + right_sum > *bound)
    *bound = (*root).val + left_sum + right_sum;

  return (*root).val + (left_sum > right_sum ? left_sum : right_sum);
}

int maxPathSum(Node *root)
{
  int bound = -3001;
  solve(root, &bound);
  return bound;
}
