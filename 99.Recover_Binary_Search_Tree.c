typedef struct TreeNode Node;
void inorder_traverse_check(Node *root, Node **last_visited, Node **first, Node **second)
{
  if (!root)
    return;

  inorder_traverse_check((*root).left, last_visited, first, second);

  if (*last_visited && (*root).val < (*(*last_visited)).val)
  {
    if (!(*first))
      *first = *last_visited;
    *second = root;
  }
  *last_visited = root;

  inorder_traverse_check((*root).right, last_visited, first, second);
}

void recoverTree(Node *root)
{
  Node *first = NULL, *second = NULL, *last_visited = NULL;
  inorder_traverse_check(root, &last_visited, &first, &second);
  int tmp = (*first).val;
  (*first).val = (*second).val;
  (*second).val = tmp;
}
