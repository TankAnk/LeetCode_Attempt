typedef struct TreeNode Node;

int maxDepth(Node *root)
{
  if (!root)
    return 0;
  int left_count = 1 + maxDepth((*root).left);
  int right_count = 1 + maxDepth((*root).right);

  return (left_count > right_count) ? left_count : right_count;
}
