typedef struct TreeNode Node;

void solve(Node *root, int ***result, int **returnColumnSizes, int *returnSize, int *capacity)
{
  if (!root)
    return;

  int front = 0, rear = 0, q_cap = 128;
  Node **queue = malloc(q_cap * sizeof(*queue));
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
    (*result)[*returnSize] = malloc(level_size * sizeof(***result));
    (*returnColumnSizes)[*returnSize] = level_size;

    for (int i = 0; i < level_size; i++)
    {
      Node *curr = queue[front++];
      (*result)[*returnSize][i] = (*curr).val;

      if (q_cap - rear < 2)
      {
        q_cap *= 2;
        queue = realloc(queue, q_cap * sizeof(*queue));
      }

      if ((*curr).left)
        queue[rear++] = (*curr).left;
      if ((*curr).right)
        queue[rear++] = (*curr).right;
    }

    (*returnSize)++;
  }

  free(queue);
}

int **levelOrder(Node *root, int *returnSize, int **returnColumnSizes)
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
