typedef struct TreeNode Node;

void flatten(Node *root)
{
  if (!root)
    return;

  Node *tmp = (*root).right;
  (*root).right = (*root).left;
  (*root).left = NULL;
  Node *traverse = root;

  while ((*traverse).right)
    traverse = (*traverse).right;

  (*traverse).right = tmp;
  flatten((*root).right);
}
