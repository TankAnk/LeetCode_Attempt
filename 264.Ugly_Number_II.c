// ==================== MIN HEAP ====================
typedef struct MinHeap
{
  int64_t *array;
  int capacity;
  int size;
} MinHeap;

MinHeap *create(int capacity)
{
  MinHeap *heap = malloc(sizeof(*heap));

  if (heap == NULL)
    return NULL;

  heap->array = malloc(capacity * sizeof(*heap->array));

  if (heap->array == NULL)
  {
    free(heap);
    return NULL;
  }

  heap->capacity = capacity;
  heap->size = 0;

  return heap;
}

void fix_up(MinHeap *heap, int current)
{
  while (current > 0 &&
         heap->array[(current - 1) / 2] > heap->array[current])
  {
    int parent = (current - 1) / 2;

    int64_t temp = heap->array[parent];
    heap->array[parent] = heap->array[current];
    heap->array[current] = temp;

    current = parent;
  }
}

void push(MinHeap *heap, int64_t value)
{
  if (heap->size == heap->capacity)
    return;

  heap->array[heap->size] = value;

  int current = heap->size;
  heap->size++;

  fix_up(heap, current);
}

void fix_down(MinHeap *heap)
{
  int current = 0;

  while (1)
  {
    int leftChild = 2 * current + 1;
    int rightChild = 2 * current + 2;
    int smallest = current;

    if (leftChild < heap->size &&
        heap->array[leftChild] < heap->array[smallest])
      smallest = leftChild;

    if (rightChild < heap->size &&
        heap->array[rightChild] < heap->array[smallest])
      smallest = rightChild;

    if (smallest == current)
      break;

    int64_t temp = heap->array[current];
    heap->array[current] = heap->array[smallest];
    heap->array[smallest] = temp;

    current = smallest;
  }
}

int64_t pop(MinHeap *heap)
{
  if (heap->size == 0)
    return -1;

  int64_t top = heap->array[0];

  heap->array[0] = heap->array[heap->size - 1];
  heap->size--;

  fix_down(heap);

  return top;
}

void destroy_heap(MinHeap *heap)
{
  if (heap == NULL)
    return;

  free(heap->array);
  free(heap);
}

// ==================== HASH SET ====================

typedef struct HashSet
{
  int64_t *table;
  size_t capacity;
  size_t size;
} HashSet;

size_t hash(int64_t key, size_t capacity)
{
  uint64_t x = (uint64_t)key;

  x += 0x9e3779b97f4a7c15ULL;
  x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
  x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
  x ^= x >> 31;

  return x & (capacity - 1);
}

HashSet *create_set(size_t capacity)
{
  HashSet *set = malloc(sizeof(*set));

  if (set == NULL)
    return NULL;

  set->table = calloc(capacity, sizeof(*set->table));

  if (set->table == NULL)
  {
    free(set);
    return NULL;
  }

  set->capacity = capacity;
  set->size = 0;

  return set;
}

int insert(HashSet *set, int64_t value)
{
  size_t index = hash(value, set->capacity);

  for (size_t i = 0; i < set->capacity; i++)
  {
    if (set->table[index] == value)
      return false;

    if (set->table[index] == 0)
    {
      set->table[index] = value;
      set->size++;
      return 1;
    }

    index = (index + 1) & (set->capacity - 1);
  }

  return -1;
}

void destroy_set(HashSet *set)
{
  if (set == NULL)
    return;

  free(set->table);
  free(set);
}

// ==================== LEETCODE 264 ====================

int nthUglyNumber(int n)
{
  MinHeap *heap = create(2 * n);
  HashSet *visited = create_set(16384);

  if (heap == NULL || visited == NULL)
  {
    destroy_heap(heap);
    destroy_set(visited);
    return 0;
  }

  push(heap, 1);
  insert(visited, 1);

  int64_t result = 1;

  for (int i = 0; i < n; i++)
  {
    result = pop(heap);

    int64_t candidates[] = {result * 2, result * 3, result * 5};

    for (int j = 0; j < 3; j++)
      (insert(visited, candidates[j]) == 1) ? (void)push(heap, candidates[j]) : (void)0;
  }

  destroy_heap(heap);
  destroy_set(visited);

  return (int)result;
}
