#define MAX_KEY 10001

typedef struct Node
{
  int key;
  int val;
  struct Node *prev;
  struct Node *next;
} Node;

void del_node(Node *node)
{
  Node *next_node = (*node).next;
  Node *prev_node = (*node).prev;

  (*prev_node).next = next_node;
  (*next_node).prev = prev_node;
}

//Head = MRU. Tail = LRU
//Add to the head
void add_node(Node *head, Node *node)
{
  Node *start = (*head).next;
  (*node).prev = head;
  (*node).next = start;
  (*head).next = node;
  (*start).prev = node;
}

typedef struct LRUCache {
  int capacity;
  int size;
  Node *head;
  Node *tail;
  Node *table[MAX_KEY];
} LRUCache;

LRUCache *lRUCacheCreate(int capacity)
{
  LRUCache *cache = malloc(sizeof(*cache));
  (*cache).capacity = capacity;
  (*cache).size = 0;

  (*cache).head = malloc(sizeof(Node));
  (*cache).tail = malloc(sizeof(Node));
  (*(*cache).head).prev = NULL;
  (*(*cache).head).next = (*cache).tail;
  (*(*cache).tail).next = NULL;
  (*(*cache).tail).prev = (*cache).head;

  memset((*cache).table, 0, MAX_KEY * sizeof(Node *));

  return cache;
}

int lRUCacheGet(LRUCache *obj, int key)
{
  Node *node = (*obj).table[key];
  if (!node)
    return -1;

  //Update node to MRU
  del_node(node);
  add_node((*obj).head, node);
  return (*node).val;
}

void lRUCachePut(LRUCache *obj, int key, int value)
{
   Node *node = ((*obj).table)[key];
  //Node already exist, update
  if (node)
  {
    (*node).val = value;
    del_node(node);
    add_node((*obj).head, node);
    return;
  }

  //New key
  Node *new_node = malloc(sizeof(*new_node));
  (*new_node).key = key;
  (*new_node).val = value;

  ((*obj).table)[key] = new_node;
  add_node((*obj).head, new_node);
  (*obj).size++;

  if ((*obj).size > (*obj).capacity)
  {
    Node *lru = (*(*obj).tail).prev;
    del_node(lru);
    (*obj).table[(*lru).key] = NULL;
    free(lru);
    (*obj).size--;
  }
}

void lRUCacheFree(LRUCache *obj)
{
  Node *curr = (*obj).head;
  while (curr)
  {
    Node *nxt = (*curr).next;
    free(curr);
    curr = nxt;
  }

  free(obj);
}
