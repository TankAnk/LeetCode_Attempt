/*
- Given the root of a binary tree, return the number of univalue subtrees.
- A univalue subtree is a subtree in which all nodes have the same value.
- A subtree consists of a node and all of its descendants.

Ex1:
Input: root = [5,1,5,5,5,null,5]
Output: 4

    5
   / \
  1   5
 / \   \
5   5   5

Ex2:
Input = [5,5,5,5,5,5,2,5,null,null,null,null,5,null,2,5]
Output: 9

         5
       /   \
      5     5
     / \   / \
    5   5  5  2
   /       \   \
  5         5   2
 /           \
5             2

Ex3:Input: [8,8,8,8,3,8,8,8,8,null,null,8,null,8,2,null,null,null,null,null,null,null,null,null,2]
Output: 10

          8
       /     \
      8       8
     / \     / \
    8   3   8   8
   / \     /   / \
  8   8   8   8   2
 /                 \
8                   2
*/

#include <stdio.h>
#include <stdlib.h>

struct TreeNode
{
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

typedef struct TreeNode Node;

/*
- Traverse the tree in post-order.
- Return:
+ 1 if this node is a univalue tree.
+ 0 if this node is not a univalue tree.
+ -1 if this node is NULL.
*/
int traverse(Node *root, int *result)
{
  if (!root)
    return -1;

  int left_val = traverse(root->left, result);
  int right_val = traverse(root->right, result);

  /*
    For a node to be a univalue tree, either:
    - It has no child (leaf node).
    - It has 2 children & 2 children are univalue trees & they have the same value.
    - It has 1 child & the child is a univalue tree & they have the same value.
  */
  if (
    (left_val == -1 && right_val == -1) ||
    (left_val == 1 && right_val == 1 && root->val == root->left->val && root->val == root->right->val) ||
    (left_val == -1 && right_val == 1 && root->val == root->right->val) ||
    (right_val == -1 && left_val == 1 && root->val == root->left->val)
    )
  {
    (*result)++;
    return 1;
  }

  return 0;
}

int countUnivalSubtrees(Node *root)
{
  int result = 0;
  traverse(root, &result);
  return result;
}

// Helper function to create a new node
Node *createNode(int val)
{
  Node *node = malloc(sizeof(*node));

  node->val = val;
  node->left = NULL;
  node->right = NULL;

  return node;
}

int main(void)
{
  /*
  Node* root = createNode(7);
  root->left = createNode(7);
  root->right = createNode(7);

  root->left->left = createNode(7);
  root->left->right = createNode(3);
  root->right->left = createNode(7);
  root->right->right = createNode(7);

  root->left->left->left = createNode(7);
  root->left->left->right = createNode(7);
  root->right->left->left = createNode(7);
  root->right->right->left = createNode(7);
  root->right->right->right = createNode(2);

  root->left->left->left->left = createNode(7);
  root->right->right->right->right = createNode(2);
  printf("%d\n", countUnivalSubtrees(root));
  */

  Node *root = createNode(8);

  // Level 1
  root->left = createNode(8);
  root->right = createNode(8);

  // Level 2
  root->left->left = createNode(8);
  root->left->right = createNode(4);

  root->right->left = createNode(8);
  root->right->right = createNode(3);

  // Level 3
  root->left->left->left = createNode(8);
  root->left->left->right = createNode(8);

  root->left->right->left = createNode(4);
  root->left->right->right = createNode(4);

  root->right->left->left = createNode(8);
  root->right->left->right = createNode(6);

  root->right->right->left = createNode(3);
  root->right->right->right = createNode(3);

  // Level 4
  root->left->left->left->left = createNode(8);
  root->left->left->left->right = createNode(8);

  root->left->right->left->left = createNode(4);

  root->right->left->left->left = createNode(8);

  root->right->right->right->right = createNode(3);

  // Run test
  int result = countUnivalSubtrees(root);

  printf("Expected: 16\n");
  printf("Actual:   %d\n", result);

  if (result == 16) {
    printf("Test passed!\n");
  } else {
    printf("Test failed!\n");
  }

  return 0;
}
