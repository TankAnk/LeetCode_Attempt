typedef struct TreeNode Node;

int inorder_traverse(Node *root, int *count, int k)
{
  if (!root)
    return -1;

  int result = inorder_traverse(root->left, count, k);
  if (result != -1)
    return result;

  // printf ("%d, V: %d, K: %d\n", *count, root->val, k);
  (*count)++;
  if (*count == k)
    return root->val;

  result = inorder_traverse(root->right, count, k);

  return result;
}

int kthSmallest(Node *root, int k)
{
  int count = 0;
  return inorder_traverse(root, &count, k);
}
