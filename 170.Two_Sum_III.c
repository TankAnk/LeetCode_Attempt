#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Implementing binary search tree
  - left < root < right
  - duplicate value increase occur by 1
*/
typedef struct TreeNode
{
  int val;
  unsigned int occur;
  struct TreeNode *left;
  struct TreeNode *right;
} TreeNode;

TreeNode *insertTree(TreeNode *root, int n)
{
  if (!root)
  {
    root = malloc(sizeof(*root));
    (*root).val = n;
    (*root).occur = 1;
    (*root).left = NULL;
    (*root).right = NULL;

    return root;
  }

  if ((*root).val == n)
    (*root).occur++;

  else if ((*root).val < n)
    (*root).right = insertTree((*root).right, n);

  else
    (*root).left = insertTree((*root).left, n);

  return root;
}

TreeNode *searchTree(TreeNode *root, int target)
{
  if (!root)
    return NULL;

  if ((*root).val == target)
    return root;

  else if ((*root).val > target)
    return searchTree((*root).left, target);

  else
    return searchTree((*root).right, target);
}

void freeTree(TreeNode *root)
{
  if (!root)
    return;

  free((*root).left);
  free((*root).right);
  free(root);
}

void levelTraverse(TreeNode *root)
{
  TreeNode *queue[128];
  int front = 1, rear = 1, level = 0;
  queue[rear++] = root;

  while (front != rear)
  {
    printf("Level %d: ", level);
    int level_size = rear - front;

    for (int i = 0; i < level_size; i++)
    {
      TreeNode *curr = queue[front++];
      printf("%d(%d) ", (*curr).val, (*curr).occur);

      if ((*curr).left)
        queue[rear++] = (*curr).left;
      if ((*curr).right)
        queue[rear++] = (*curr).right;
    }

    level++;

    printf("\n");
  }
}

//Search the tree if there are any 2 nodes with sum == target
bool twoSumFind(TreeNode *curr_root, TreeNode *abs_root, int target)
{
  if (!curr_root)
    return false;

  int complement = target - (*curr_root).val;
  TreeNode *find = searchTree(abs_root, complement);
  if (find)
  {
    if (find != curr_root || (*curr_root).occur >= 2)
      return true;
  }

  return twoSumFind((*curr_root).left, abs_root, target) || twoSumFind((*curr_root).right, abs_root, target);
}

//API function
bool twoSum(TreeNode *root, int target)
{
  return twoSumFind(root, root, target);
}

int main()
{
  TreeNode *root = NULL;
  root = insertTree(root, 30);
  root = insertTree(root, 25);
  root = insertTree(root, 35);
  root = insertTree(root, 28);
  root = insertTree(root, 31);

  levelTraverse(root);

  TreeNode *tmp = searchTree(root, 28);
  if (tmp)
    printf("Found!\n");
  else
    printf("Not found!\n");

  tmp = searchTree(root, 99);
  if (tmp)
    printf("Found!\n");
  else
    printf("Not found!\n");

  printf("%d\n", twoSum(root, 59));

  freeTree(root);

  return 0;
}
