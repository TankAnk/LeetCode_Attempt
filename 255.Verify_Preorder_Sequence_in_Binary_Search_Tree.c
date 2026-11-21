/*
Given an array of unique integers preorder, return true if it is the correct preorder traversal sequence of a binary search tree.

Example 1:
Input: preorder = [5,2,1,3,6]
Output: true

Example 2:
Input: preorder = [5,2,6,1,3]
Output: false

Constraints:
- 1 <= preorder.length <= 10^4
- 1 <= preorder[i] <= 10^4
- All the elements of preorder are unique.

Follow-up: Could you do it using only constant space complexity?
*/

/*
- Pre-order traversal in BST results in the pattern:
root - [Nodes < root (left subtree)] - [Node > root (right subtree)]
- Once encounter a value larger top of the stack, pop all the smaller values from the stack because theirs left subtrees were traversed.
*/
bool verifyPreorder(int *preorder, int preorderSize)
{
  int stack[preorderSize];
  int top = -1;
  int lower_bound = -10001;

  for (int i = 0; i < preorderSize; i++)
  {
    if (preorder[i] <= lower_bound)
      return false;

    while (top >= 0 && preorder[i] > stack[top])
      lower_bound = stack[top--];

    stack[++top] = preorder[i];
  }

  return true;
}
