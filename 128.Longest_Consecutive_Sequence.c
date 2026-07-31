/*
 For any number x:
  - If x - 1 exists: x cannot be the start, skip
  - Else: x can be the start, count forward
 */
#define MAX_SIZE 100003

typedef struct Node
{
  int val;
  struct Node *next;
} Node;

/*TLE
unsigned int hash(int val)
{
  int idx = val % MAX_SIZE;

  if (idx < 0)
    idx += MAX_SIZE;

  return idx;
}

bool contain(Node **set, int val)
{
  int idx = hash(val);

  Node *curr = set[idx];
  while (curr)
  {
    if ((*curr).val == val)
      return true;
    curr = (*curr).next;
  }

  return false;
}

void free_set(Node **set)
{
  for (int i = 0; i < MAX_SIZE; i++)
  {
    Node *curr = set[i];
    while (curr)
    {
      Node *tmp = curr;
      curr = (*curr).next;
      free(tmp);
    }
  }
}

void insert(Node **set, int val)
{
  if (contain(set, val))
    return;

  int idx = hash(val);
  Node *new = malloc(sizeof(*new));

  (*new).val = val;
  (*new).next = set[idx];

  set[idx] = new;
}

int longestConsecutive(int *nums, int numsSize)
{
  Node *set[MAX_SIZE];
  memset(set, 0, MAX_SIZE * sizeof(*set));

  for (int i = 0; i < numsSize; i++)
    insert(set, nums[i]);

  int result = 0;
  for (int i = 0; i < numsSize; i++)
  {
    if (contain(set, nums[i] - 1))
      continue;

    int cnt = 1, n = nums[i];
    while (contain(set, n + 1))
    {
      cnt++;
      n++;
    }

    if (result < cnt)
      result = cnt;
  }

  free_set(set);

  return result;
}
*/

unsigned int hash(int val)
{
  unsigned int x = val;
  x ^= x >> 16;
  x *= 0x45d9f3b;
  x ^= x >> 16;

  return x % MAX_SIZE;
}

bool contain(Node **set, int val)
{
  int idx = hash(val);
  Node *curr = set[idx];
  while (curr)
  {
    if ((curr).val == val)
      return true;

    curr = (*curr).next;
  }

  return false;
}

void insert(Node **set, int val)
{
  int idx = hash(val);
  Node *curr = set[idx];
  while (curr)
  {
    if ((*curr).val == val)
      return;

    curr = (*curr).next;
  }

  Node *new = malloc(sizeof(*new));
  (*new).val = val;
  (*new).next = set[idx];

  set[idx] = new;
}

void free_set(Node **set)
{
  for (int i = 0; i < MAX_SIZE; i++)
  {
    Node *curr = set[i];

    while (curr)
    {
      Node *tmp = curr;
      curr = (*curr).next;
      free(tmp);
    }
  }
}

int longestConsecutive(int *nums, int numsSize)
{
  Node *set[MAX_SIZE] = {0};

  for (int i = 0; i < numsSize; i++)
    insert(set, nums[i]);

  int result = 0;

  for (int i = 0; i < numsSize; i++)
  {
    if (contain(set, nums[i] - 1))
      continue;

    int cnt = 1;
    int n = nums[i];

    while (contain(set, n + 1))
    {
      cnt++;
      n++;
    }

    if (result < cnt)
      result = cnt;
  }

  free_set(set);

  return result;
}
