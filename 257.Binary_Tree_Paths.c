/*
600 =
- 100 maximum nodes * 4 digits/node = 400 (-100 needs 4 slots)
- 99 maximum arrows * 2 chars/arrow = 198
- 1 for \0
- 1 because I'm insecured and 600 looks better than 599
*/
#define MAX_SIZE 600

typedef struct TreeNode Node;

void solve(Node *root, int *returnSize, char ***result, int *capacity, char *path, int path_idx)
{
  if (!root)
    return;

  // path_idx always points to the NEXT EMPTY slot in this implementation.
  if (path_idx != 0)
  {
    path[path_idx++] = '-';
    path[path_idx++] = '>';
  }

  // int snprintf(char *str, size_t size, const char *format, number).
  // snprintf returns the number of chars that WOULD HAVE BEEN WRITTEN (excluding \0) if the buffer size is large enough.
  int increment = snprintf(path + path_idx, MAX_SIZE - path_idx, "%d", root->val);
  path_idx += increment;

  // If this is a leaf node.
  if (!root->left && !root->right)
  {
    if (*returnSize == *capacity)
    {
      *capacity *= 2;
      *result = realloc(*result, *capacity * sizeof(**result));
    }

    (*result)[*returnSize] = malloc((path_idx + 1) * sizeof(***result));
    // snprintf already inserted \0.
    memcpy((*result)[*returnSize], path, (path_idx + 1) * sizeof(***result));
    (*returnSize)++;

    return;
  }

  if (root->left)
    solve(root->left, returnSize, result, capacity, path, path_idx);

  if (root->right)
    solve(root->right, returnSize, result, capacity, path, path_idx);
}

char **binaryTreePaths(Node *root, int *returnSize)
{
  *returnSize = 0;
  if (!root)
    return NULL;

  int capacity = 64;
  char **result = malloc(capacity * sizeof(*result));
  char path[MAX_SIZE];

  solve(root, returnSize, &result, &capacity, path, 0);

  return result;
}
