typedef struct TreeNode Node;
bool isSameTree(Node *p, Node *q)
{
  if (!p && q || p && !q || (p && q && (*p).val != (*q).val))
    return false;

  if (!p && !q)
    return true;

  bool result = isSameTree((*p).left, (*q).left);
  if (result)
    result = isSameTree((*p).right, (*q).right);

  return result;
}
