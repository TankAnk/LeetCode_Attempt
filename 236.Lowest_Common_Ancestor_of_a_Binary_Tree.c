typedef struct TreeNode Node;

/* For a root with p and q are valid, different and exist:
- If the root is either NULL, p or q -> return root.
- If the root is different from both q and q:
  + Recursively search for p and q in the left and right subtree.
  + If both searches return valid node -> This root is the LCA.
  + If only 1 of the search return a valid node, return it.
  + If both search return NULL, return NULL.
*/
Node *lowestCommonAncestor(Node *root, Node *p, Node *q)
{
  if (!root || root == p || root == q)
    return root;

  Node *left = lowestCommonAncestor(root->left, p, q);
  Node *right = lowestCommonAncestor(root->right, p, q);

  if (left && right)
    return root;

  return (left ? left : right);
}
