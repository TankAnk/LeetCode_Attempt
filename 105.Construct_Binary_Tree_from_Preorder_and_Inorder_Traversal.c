typedef struct TreeNode Node;
#define SIZE 6001

Node *solve(int *preorder, int pre_start, int pre_end, int *inorder, int in_start, int in_end, int *val_to_idx)
{
  if (pre_start > pre_end || in_start > in_end)
    return NULL;

  Node *root = malloc(sizeof(*root));
  (*root).val = preorder[pre_start];
  int k = val_to_idx[(*root).val + 3000];
  int left_size = k - in_start;

  (*root).left = solve(preorder, pre_start + 1, pre_start + left_size, inorder, in_start, k - 1, val_to_idx);
  (*root).right = solve(preorder, pre_start + left_size + 1, pre_end, inorder, k + 1, in_end, val_to_idx);

  return root;
}

/*
root = preorder[pre_start];
left_size = k - in_start;
left preorder: pre_start + 1 -> pre_start + left_size
left inorder: in_start -> k - 1

right_size = in_end - k;
right preorder: pre_start + left_size + 1 -> pre_end
right inorder: k + 1 -> in_end
*/

Node *buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize)
{
  int val_to_idx[SIZE];
  for (int i = 0; i < inorderSize; i++)
    val_to_idx[inorder[i] + 3000] = i;

  return solve(preorder, 0, preorderSize - 1, inorder, 0, inorderSize - 1, val_to_idx);
}
