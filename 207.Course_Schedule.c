typedef struct Vertex Vertex;
typedef struct VertexListNode VertexListNode;

typedef struct Vertex
{
  short val;

  // Singly linked list to other vertices.
  struct VertexListNode *depend;
} Vertex;

// Singly linked list node for graph vertex.
typedef struct VertexListNode
{
  struct Vertex *curr;
  struct VertexListNode *next;
} VertexListNode;

Vertex *create_vertex(int val)
{
  Vertex *v = malloc(sizeof(*v));
  v->val = val;
  v->depend = NULL;

  return v;
}

VertexListNode *create_vertex_list_node(Vertex *v)
{
  VertexListNode *n = malloc(sizeof(*n));
  n->curr = v;
  n->next = NULL;

  return n;
}

bool has_cycle(Vertex *v, bool *visited, bool *in_path)
{
  /*
  If this vertex is already in the current DFS path
  -> already reached it again through its own chain of dependencies.
  -> the graph contains a cycle.
  */
  if (in_path[v->val])
    return true;

  /*
  This vertex was completely explored during an earlier DFS path.
  Since it is not currently in our path, encountering it again does not mean there is a cycle.
  */
  if (visited[v->val])
    return false;

  // Mark this vertex as visited so we know it has been explored.
  visited[v->val] = true;

  // Mark this vertex as part of the current DFS path.
  in_path[v->val] = true;

  // Traverse every prerequisite/dependency of the current vertex.
  VertexListNode *traverse = v->depend;
  while (traverse)
  {
    // Recursively check whether this dependency leads to a cycle.
    if (has_cycle(traverse->curr, visited, in_path))
      return true;

    traverse = traverse->next;
  }

  /*
  We have finished exploring this vertex and everything reachable from it.
  It is no longer part of the current DFS path.
  visited remains true because this vertex has already been completely explored.
  */
  in_path[v->val] = false;

  return false;
}

bool canFinish(int numCourses, int **prerequisites, int prerequisitesSize, int *prerequisitesColSize)
{
  // 1. Build the graph
  Vertex **courses = malloc(numCourses * sizeof(*courses));

  // Create all vertices without link first.
  for (int i = 0; i < numCourses; i++)
    courses[i] = create_vertex(i);

  // Link vertices.
  for (int i = 0; i < prerequisitesSize; i++)
  {
    Vertex *curr_course = courses[prerequisites[i][0]];
    Vertex *need = courses[prerequisites[i][1]];

    // Insert the prerequisite course (as a VertexListNode) to the head of the depend linked list.
    VertexListNode *new_node = create_vertex_list_node(need);
    new_node->next = curr_course->depend;
    curr_course->depend = new_node;
  }

  // 2. Detect cycle

  // Have I seen this vertex before?
  bool visited[numCourses];
  memset(visited, 0, numCourses * sizeof(*visited));

  // Is this vertex a part of the path I'm exploring?
  bool in_path[numCourses];
  memset(in_path, 0, numCourses * sizeof(*in_path));

  // Traverse graph
  for (int i = 0; i < numCourses; i++)
    if (has_cycle(courses[i], visited, in_path))
      return false;

  free(courses);

  return true;
}
