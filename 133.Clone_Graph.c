typedef struct Node Node;

typedef struct Entry
{
  Node *origin;
  Node *clone;
} Entry;

#define MAX_SIZE 101

Node *solve(Node *src, Entry *entry, int *idx)
{
  if (!src)
    return NULL;

  for (int i = 0; i < *idx; i++)
    if (entry[i].origin == src)
      return entry[i].clone;

  Node *dest = malloc(sizeof(*dest));
  (*dest).val = (*src).val;
  (*dest).numNeighbors = (*src).numNeighbors;
  (*dest).neighbors = malloc((*src).numNeighbors * sizeof(Node*));

  entry[*idx].origin = src;
  entry[*idx].clone = dest;
  (*idx)++;

  for (int i = 0; i < (*src).numNeighbors; i++)
    ((*dest).neighbors)[i] = solve(((*src).neighbors)[i], entry, idx);

  return dest;
}

Node *cloneGraph(Node *s)
{
  Entry *entry = malloc(MAX_SIZE * sizeof(*entry));
  int idx = 0;

  Node *result = solve(s, entry, &idx);
  free(entry);
  return result;
}

/*
Given pointer to a SINGLE Node 1:
  val = 1;
  numNeighbors = 2;
  Node **neighbors = [&Node 2, &Node4];
*/

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numNeighbors;
 *     struct Node** neighbors;
 * };
 */
