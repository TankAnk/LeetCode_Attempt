/*
- You are given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes).
- Return true if these edges make up a valid tree, and false otherwise.

Example 1:
Input: n = 5, edges = [[0,1],[0,2],[0,3],[1,4]]
Output: true

Example 2:
Input: n = 5, edges = [[0,1],[1,2],[2,3],[1,3],[1,4]]
Output: false

Constraints:
- 1 <= n <= 2000
- 0 < edges.length < 5000
- edges[i].length == 2
- 0 <= ai, bi <= n
- ai != bi
- There are no duplicate edges
*/

// Find the very last child / representative of a node.
int find_last(int *children, int node)
{
  if (children[node] != node)
    return find_last(children, children[node]);

  return children[node];
}

/*
No cycle: n = 5; edges = [[0,1], [0,2], [0,3], [1,4]]
Initially: [0, 1, 2, 3, 4]

For [0,1]: children[0] = 0 != children[1] = 1
-> children[0] = 1
-> children = [1, 1, 2, 3, 4]

For [0,2]: children[0] = 1 != children[2] = 2
-> children[1] = 2
-> children = [1, 2, 2, 3, 4]

For [0,3]: children[0] = 2 != children[3] = 3
-> children[2] = 3
-> children = [1, 2, 3, 3, 4]

For [1,4]: children[1] = 3 != children[4] = 4
-> children[3] = 4
-> children = [1, 2, 3, 4, 4]

=========================================================

Cycle: n = 5; edges = [[0,1], [1,2], [2,3], [1,3], [1,4]]
Initially: children = [0, 1, 2, 3, 4]

For [0,1]: children[0] = 0 != children[1] = 1
-> children[0] = 1
-> children = [1, 1, 2, 3, 4]

For [1,2]: children[1] = 1 != children[2] = 2
-> children[1] = 2
-> children = [1, 2, 2, 3, 4]

For [2,3]: children[2] = 2 != children[3] = 3
-> children[2] = 3
-> children = [1, 2, 3, 3, 4]

For [1,3]: children[1] = 3 == children[3] = 3
-> Cycle detected.
*/
bool has_cycle(int n, int **edges, int edgesSize)
{
  int children[n];
  for (int i = 0; i < n; i++)
    children[i] = i;

  for (int i = 0; i < edgesSize; i++)
  {
    int child1 = find_last(children, edges[i][0]);
    int child2 = find_last(children, edges[i][1]);

    if (child1 == child2)
      return true;

    children[child1] = child2;
  }

  return false;
}

/*
An undirected graph is w/ n nodes is a tree when: A && B or A && C
- A: It has exactly n - 1 edges.
- B: Every node is reachable (Connected).
- C: It has no cycle (Acyclic).
*/
bool validTree(int n, int **edges, int edgesSize, int *edgesColSize)
{
  // A tree must have exactly n - 1 edges.
  if (n - 1 != edgesSize)
    return false;

  /*
    If an undirected graph w/ n vertices already has exactly n - 1 edges:
    - If it contains a cycle, it must be disconnected.
    - If it is connected, it cannot contain a cycle.
    -> Check for cycle in the graph.
  */
  return !has_cycle(n, edges, edgesSize);
}
