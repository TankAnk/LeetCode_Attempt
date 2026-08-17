typedef struct TreeNode Node;

/*Trivial Solution with stack call
void solve(Node *root, int **result, int *returnSize, int *capacity)
{
  if (!root)
    return;

  if (*returnSize == *capacity)
  {
    *capacity *= 2;
    *result = realloc(*result, *capacity * sizeof(*result));
  }

  (*result)[(*returnSize)++] = (*root).val;
  solve((*root).left, result, returnSize, capacity);
  solve((*root).right, result, returnSize, capacity);
}

int *preorderTraversal(Node *root, int *returnSize)
{
  *returnSize = 0;
  int capacity = 128;
  int *result = malloc(capacity * sizeof(*result));
  solve(root, &result, returnSize, &capacity);

  return result;
}
*/

/*Morris Traversal
- Predecessor: Rightmost node in the current node's left subtree
- Preorder: Find predecessor if left -> create thread -> visit -> move left and keep going -> when done, clear thread -> move right
- Inorder: Find predecessor if left -> create thread -> move left and keep going -> when done, clear thread -> visit -> move right
*/

int *preorderTraversal(Node *root, int *returnSize)
{
  *returnSize = 0;
  int *result = malloc(101 * sizeof(*result));

  Node *curr = root;
  while (curr)
  {
    //No left child, visit and go right
    if (!(*curr).left)
    {
      result[(*returnSize)++] = (*curr).val;
      curr = (*curr).right;
    }

    else
    {
      //Find predecessor
      Node *pre = (*curr).left;
      while ((*pre).right && (*pre).right != curr)
        pre = (*pre).right;

      //No thread yet aka 1st time see curr
      if (!(*pre).right)
      {
        //Create thread
        (*pre).right = curr;
        //Visit
        result[(*returnSize)++] = (*curr).val;
        //Go left
        curr = (*curr).left;
      }

      //Already seen curr
      else
      {
        //Remove thread
        (*pre).right = NULL;
        //Go right
        curr = (*curr).right;
      }
    }
  }

  return result;
}
