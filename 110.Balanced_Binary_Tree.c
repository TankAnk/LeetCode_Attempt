typedef struct TreeNode Node;
int depth(Node *root)
{
  if (!root)
    return 0;

  int left_depth = 1 + depth((*root).left);
  int right_depth = 1 + depth((*root).right);

  return (left_depth > right_depth) ? left_depth : right_depth;
}

bool isBalanced(Node *root)
{
  if (!root)
    return true;

  bool result;

  int left_depth = depth((*root).left);
  int right_depth = depth((*root).right);
  if (left_depth - right_depth > 1 && left_depth - right_depth < -1)
    return false;
  bool result = isBalanced((*root).left);
  if (result)
    return isBalanced((*root).right);
  return result;
}
