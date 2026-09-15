/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

typedef struct TreeNode Node;

typedef struct BSTIterator
{
  unsigned int capacity;
  int top;
  Node **stack;
  Node *curr;

} BSTIterator;


BSTIterator *bSTIteratorCreate(Node *root)
{
  BSTIterator *iterator = malloc(sizeof(*iterator));
  iterator->capacity = 128;
  iterator->top = -1;
  iterator->stack = malloc(iterator->capacity * sizeof(Node *));
  iterator->curr = root;

  return iterator;
}

int bSTIteratorNext(BSTIterator *obj)
{
  while (obj->curr)
  {
    if (obj->top + 1 == obj->capacity)
    {
      obj->capacity *= 2;
      obj->stack = realloc(obj->stack, obj->capacity * sizeof(Node *));
    }

    obj->stack[++(obj->top)] = obj->curr;
    obj->curr = obj->curr->left;
  }

  Node *popped = obj->stack[(obj->top)--];
  int result = popped->val;
  obj->curr = popped->right;

  return result;
}

bool bSTIteratorHasNext(BSTIterator *obj)
{
  return (obj->top >= 0 || obj->curr);
}

void bSTIteratorFree(BSTIterator *obj)
{
  if (!obj)
    return;

  free(obj->stack);
  free(obj);
}

/**
 * Your BSTIterator struct will be instantiated and called as such:
 * BSTIterator* obj = bSTIteratorCreate(root);
 * int param_1 = bSTIteratorNext(obj);

 * bool param_2 = bSTIteratorHasNext(obj);

 * bSTIteratorFree(obj);
*/
