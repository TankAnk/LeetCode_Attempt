#define MAX_SIZE 1009
typedef struct Node Node;
typedef struct Pair
{
  Node *origin;
  Node *clone;
} Pair;

/*1st approach with O(n^2) time
Node *solve(Node *head, Pair *memo, int *size)
{
  if (!head)
    return NULL;

  for (int i = 0; i < *size; i++)
    if (head == memo[i].origin)
      return memo[i].clone;

  Node *result = malloc(sizeof(*result));
  memo[*size].origin = head;
  memo[(*size)++].clone = result;

  (*result).val = (*head).val;
  (*result).next = solve((*head).next, memo, size);
  (*result).random = solve((*head).random, memo, size);

  return result;
}

Node *copyRandomList(Node *head)
{
  Pair memo[1000];
  int size = 0;
  return solve(head, memo, &size);
}
*/

//Simulating hash table for Average O(1)
size_t hash(Node *node)
{
  //Convert pointer to unsigned inte capable of holding a pointer value
  uintptr_t n = (uintptr_t)node;
  n ^= n >> 16;
  n *= 0x45d9f3b;
  n ^= n >> 16;

  return n % MAX_SIZE;
}

Node *solve(Node *head, Pair *memo)
{
  if (!head)
    return NULL;

  size_t idx = hash(head);
  //If this slot is occupied, search until find corresponding origin OR empty slot
  while(memo[idx].origin)
  {
    if (memo[idx].origin == head)
      return memo[idx].clone;

    idx = (idx + 1) % MAX_SIZE;
  }

  //If a the slot is already empty OR search not found (land on next empty slot)
  Node *result = malloc(sizeof(*result));
  //Insert
  memo[idx].origin = head;
  memo[idx].clone = result;

  (*result).val = (*head).val;
  (*result).next = solve((*head).next, memo);
  (*result).random = solve((*head).random, memo);

  return result;
}

Node *copyRandomList(Node *head)
{
  Pair memo[MAX_SIZE];
  return solve(head, memo);
}
