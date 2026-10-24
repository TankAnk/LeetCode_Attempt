typedef struct TreeNode Node;

Node *invertTree(Node *root)
{
  if (!root)
    return NULL;

  root->left = invertTree(root->left);
  root->right = invertTree(root->right);

  Node *tmp = root->left;
  root->left = root->right;
  root->right = tmp;

  return root;
}
