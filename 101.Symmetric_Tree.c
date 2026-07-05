typedef struct TreeNode Node;
bool check(Node *left_root, Node *right_root)
{
  if (!left_root && !right_root)
    return true;

  if (!left_root || !right_root || (*left_root).val != (*right_root).val)
    return false;

  bool result = check((*left_root).left, (*right_root).right);
  if (result)
    result = check((*left_root).right, (*right_root).left);

  return result;
}

bool isSymmetric(Node *root)
{
  return check((*root).left, (*root).right);
}
