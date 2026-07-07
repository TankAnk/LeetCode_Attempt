typedef struct TreeNode Node;
void solve(Node *root, int ***result, int **returnColumnSizes, int *returnSize, int *capacity)
{
  Node *queue[2000];
  int front = 0, rear = 0;
  queue[rear++] = root;
  while (front != rear)
  {
    int level_size = rear - front;
    if (*returnSize == *capacity)
    {
      *capacity *= 2;
      *result = realloc(*result, *capacity * sizeof(**result));
      *returnColumnSizes = realloc(*returnColumnSizes, *capacity * sizeof(**returnColumnSizes));
    }
    (*returnColumnSizes)[*returnSize] = level_size;
    (*result)[*returnSize] = malloc(level_size * sizeof(***result));

    for (int i = 0; i < level_size; i++)
    {
      Node *curr = queue[front++];
      int idx = (*returnSize % 2 == 0) ? i : level_size - 1 - i;
      (*result)[*returnSize][idx] = (*curr).val;

      if ((*curr).left)
        queue[rear++] = (*curr).left;
      if ((*curr).right)
        queue[rear++] = (*curr).right;
    }

    (*returnSize)++;
  }
}

int **zigzagLevelOrder(Node *root, int *returnSize, int **returnColumnSizes)
{
  *returnSize = 0;
  if (!root)
    return NULL;

  int capacity = 128;
  int **result = malloc(capacity * sizeof(*result));
  *returnColumnSizes = malloc(capacity * sizeof(**returnColumnSizes));

  solve(root, &result, returnColumnSizes, returnSize, &capacity);

  return result;
}
