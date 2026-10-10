typedef struct Vertex Vertex;
typedef struct GraphListNode GraphListNode;

typedef struct Vertex
{
  int val;
  struct GraphListNode *depend;
} Vertex;

typedef struct GraphListNode
{
  Vertex *curr;
  struct GraphListNode *next;

} GraphListNode;

GraphListNode *createGraphListNode(Vertex *v)
{
  GraphListNode *n = malloc(sizeof(*n));
  n->curr = v;
  n->next = NULL;

  return n;
}

Vertex *createVertex(int value)
{
  Vertex *v = malloc(sizeof(*v));
  v->val = value;
  v->depend = NULL;

  return v;
}

bool hasCycle(bool *visited, bool *inPath, Vertex *v, int *result, int *idx)
{
  if (inPath[v->val])
    return true;

  if (visited[v->val])
    return false;

  visited[v->val] = true;
  inPath[v->val] = true;

  GraphListNode *traverse = v->depend;
  while (traverse)
  {
    if (hasCycle(visited, inPath, traverse->curr, result, idx))
      return true;

    traverse = traverse->next;
  }

  inPath[v->val] = false;
  result[(*idx)++] = v->val;

  return false;
}

int *findOrder(int numCourses, int **prerequisites, int prerequisitesSize, int *prerequisitesColSize, int *returnSize) {
  Vertex **graph = malloc(numCourses * sizeof(*graph));
  for (int i = 0; i < numCourses; i++)
    graph[i] = createVertex(i);

  for (int i = 0; i < prerequisitesSize; i++)
  {
    Vertex *course = graph[prerequisites[i][0]];
    Vertex *need = graph[prerequisites[i][1]];

    GraphListNode *node = createGraphListNode(need);
    node->next = course->depend;
    course->depend = node;
  }

  bool visited[numCourses];
  memset(visited, 0, numCourses * sizeof(*visited));
  bool inPath[numCourses];
  memset(inPath, 0, numCourses * sizeof(*inPath));

  *returnSize = 0;
  int *result = malloc(numCourses * sizeof(*result));
  int idx = 0;
  for (int i = 0; i < numCourses; i++)
    if (hasCycle(visited, inPath, graph[i], result, &idx))
    {
      free(result);
      return NULL;
    }


  *returnSize = idx;
  return result;
}
