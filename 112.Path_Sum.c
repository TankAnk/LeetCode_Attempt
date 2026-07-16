typedef struct TreeNode Node;

bool solve(Node *root, int target, int curr)
{
  if (!root)
    return false;

  bool left_check = solve((*root).left, target, curr + (*root).val);
  if (left_check)
    return true;

  bool right_check = solve((*root).right, target, curr + (*root).val);
  if (right_check)
    return true;

  return ((target == curr + (*root).val) && !(*root).left && !(*root).right);
}

bool hasPathSum(Node* root, int targetSum)
{
  return solve(root, targetSum, 0);
}
