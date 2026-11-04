typedef struct TreeNode Node;

/*
Traverse the tree to find both node while checking if the current 2 traverse node is the same.
Tree: 0 2 3 4 5 6 7 8 9
1. LCA is the root: 3 and 7
6 2 4 3
6 8 7

2. LCA is one of the node: 2 and 4
6 2 4
6 2

3. LCA is one odinary node: 0 and 5
6 2 0
6 2 4 5
*/

Node *lowestCommonAncestor(Node *root, Node *p, Node *q)
{
  Node *result = root;
  Node *p_traverse = root;
  Node *q_traverse = root;

  while (p_traverse && q_traverse && p_traverse == q_traverse)
  {
    result = p_traverse;

    if (p_traverse != p)
      p_traverse = p_traverse->val < p->val ? p_traverse->right : p_traverse->left;

    if (q_traverse != q)
      q_traverse = q_traverse->val < q->val ? q_traverse->right : q_traverse->left;
  }

  return result;
}
