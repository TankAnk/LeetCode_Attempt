typedef struct TreeNode Node;

bool check(Node *root, Node *min, Node *max)
{
  if (!root)
    return true;

  //Check if root itself are allowed
  if (min && (*root).val <= (*min).val)
    return false;
  if (max && (*root).val >= (*max).val)
    return false;

  bool result = true;
  //Check left with new upper bound = root
  if ((*root).left)
    result = result && check((*root).left, min, root);
  //Check right with the new lower bound = root
  if ((*root).right)
    result = result && check((*root).right, root, max);

  return result;
}

bool isValidBST(Node *root)
{
  return check(root, NULL, NULL);
}
