typedef struct TreeNode Node;

int minDepth(Node *root)
{
  if (!root)
    return 0;

  int left_size = minDepth((*root).left);
  int right_size = minDepth((*root).right);

  if (!left_size)
    return 1 + right_size;

  if (!right_size)
    return 1 + left_size;

  return 1 + (left_size < right_size ? left_size : right_size);
}
