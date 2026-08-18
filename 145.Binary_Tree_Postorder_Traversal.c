/*Morris Traversal
Predecessor: Rightmost node of the left subtree of the current node
Successor: Left most node of the right subtree of the current node
1. Preorder:
- No left subtree: visit, move right
- 1st encounter: find predecessor, visit, create thread, move left
- 2nd encounter: detach thread, move right

2. Inorder:
- No left subtree: visit, move right
- 1st encounter: find predecessor, create thread, move left
- 2nd encounter: visit, detach thread, move right

3. Postorder (Modified Preorder: Root->Right->Left and Reverse)
- No right subtree: visit, move left
- 1st encounter: find successor, visit, create thread, move right
- 2nd encounter: detach thread, move left
- Reverse result array
*/

typedef struct TreeNode Node;
int *postorderTraversal(Node *root, int *returnSize)
{
  *returnSize = 0;
  int *result = malloc(101 * sizeof(*result));

  Node *curr = root;
  while (curr)
  {
    //No right subtree, visit, move left
    if (!(*curr).right)
    {
      result[(*returnSize)++] = (*curr).val;
      curr = (*curr).left;
    }

    else
    {
      //Find sucessor
      Node *suc = (*curr).right;
      while ((*suc).left && (*suc).left != curr)
        suc = (*suc).left;

      //1st time encounter curr
      if (!(*suc).left)
      {
        //Create thread
        (*suc).left = curr;
        //Visit
        result[(*returnSize)++] = (*curr).val;
        //Move right
        curr = (*curr).right;
      }

      //2nd time encounter curr
      else
      {
        //Detach thread
        (*suc).left = NULL;
        //Move left
        curr = (*curr).left;
      }
    }
  }

  //Reverse array
  for (int i = 0; i < *returnSize / 2; i++)
  {
    int tmp = result[i];
    result[i] = result[*returnSize - 1 - i];
    result[*returnSize - 1 - i] = tmp;
  }

  return result;
}
