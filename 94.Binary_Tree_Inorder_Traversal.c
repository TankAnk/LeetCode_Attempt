/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
/*
Pre-order: Root-Left-Right
In-order: Left-Root-Right
Post-order: Left-Right-Root
*/
typedef struct TreeNode Node;

void inorder_traverse(Node *root, int *returnSize, int **result, int *capacity)
{
  if (!root)
    return;

  inorder_traverse((*root).left, returnSize, result, capacity);

  if (*returnSize == *capacity)
  {
    *capacity *= 2;
    *result = realloc(*result, *capacity * sizeof(**result));
  }
  (*result)[(*returnSize)++] = (*root).val;

  inorder_traverse((*root).right, returnSize, result, capacity);
}

int *inorderTraversal(Node *root, int *returnSize)
{
  *returnSize = 0;
  if (!root)
    return NULL;

  int capacity = 128;
  int *result = malloc(capacity * sizeof(*result));

  inorder_traverse(root, returnSize, &result, &capacity);
  return result;
}
