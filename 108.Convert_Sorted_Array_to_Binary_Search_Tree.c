typedef struct TreeNode Node;
Node *solve(int *nums, int start, int end)
{
  if (start > end)
    return NULL;
  Node *root = malloc(sizeof(*root));
  int curr_idx = start + (end - start + 1) / 2;
  (*root).val = nums[curr_idx];
  (*root).left = solve(nums, start, curr_idx - 1);
  (*root).right = solve(nums, curr_idx + 1, end);
  return root;
}

Node *sortedArrayToBST(int *nums, int numsSize)
{
  return solve(nums, 0, numsSize - 1);
}
