typedef struct TreeNode Node;

int solve(Node *root, int curr)
{
  if (!root)
    return 0;

  curr = curr * 10 + (*root).val;
  if (!(*root).left && !(*root).right)
    return curr;
  int left_num = solve((*root).left, curr);
  int right_num = solve((*root).right, curr);

  return left_num + right_num;
}

int sumNumbers(Node *root)
{
  return solve(root, 0);
}
