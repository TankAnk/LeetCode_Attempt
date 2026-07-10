typedef struct TreeNode Node;

Node *solve(int *inorder, int in_start, int in_end, int *postorder, int post_start, int post_end, int *table)
{
  if (in_start > in_end || post_start > post_end)
    return NULL;

  Node *root = malloc(sizeof(*root));
  (*root).val = postorder[post_end];
  int k = table[(*root).val + 3000];
  int left_size = k - in_start;
  (*root).left = solve(inorder, in_start, k - 1, postorder, post_start, post_start + left_size - 1, table);
  (*root).right = solve(inorder, k + 1, in_end, postorder, post_start + left_size, post_end - 1, table);

  return root;
}

/*
in = 1,2,3,4,5,6,7
po = 1,3,2,5,7,6,4
root = post[post_end]
k = index of the value "post[post_end]" in inorder array
left_size = k - in_start, right_size = in_end - k
left sub tree:
po: post_start -> post_start + left_size - 1
in: in_start -> k - 1

right sub tree:
po: post_start + left_size -> post_end - 1
in: k + 1 -> in_end
*/

Node *buildTree(int *inorder, int inorderSize, int *postorder, int postorderSize)
{
  int table[6001];
  for (int i = 0; i < inorderSize; i++)
    table[inorder[i] + 3000] = i;
  return solve(inorder, 0, inorderSize - 1, postorder, 0, postorderSize - 1, table);
}
