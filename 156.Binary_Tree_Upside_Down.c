typedef struct TreeNode Node;

#define MAX_SIZE 10

Node *upsideDownBinaryTree(Node *root)
{
  if (!root || !(*root).left)
    return root;

  Node *stack[MAX_SIZE];
  int top = -1;
  stack[++top] = root;

  //Find left most node aka new root
  Node *traverse = root;
  while ((*traverse).left)
  {
    stack[++top] = (*traverse).right;
    stack[++top] = (*traverse).left;
    traverse = (*traverse).left;
  }

  while (top >= 0)
  {
    Node *curr = stack[top--];

    //Empty stack, curr is the original root
    if (top == -1)
    {
      (*curr).left = NULL;
      (*curr).right = NULL;
    }

    else
    {
      (*curr).left = stack[top--];
      (*curr).right = stack[top];
    }
  }

  return traverse;
}
