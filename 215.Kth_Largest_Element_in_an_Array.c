/*
- Binary Heap can be represented as an array.
- Element at index i has left child at index 2*i + 1 and right child at index 2*i + 2.
*/
typedef struct MaxHeap
{
  int *arr;
  int capacity;
  int size;
} MaxHeap;

MaxHeap *create_max_heap(int n)
{
  MaxHeap *heap = malloc(sizeof(*heap));
  heap->size = 0;
  heap->capacity = n;
  heap->arr = malloc(n * sizeof(*heap->arr));

  return heap;
}

int left_child_idx(int i)
{
  return 2*i + 1;
}

int parent_idx(int i)
{
  return (i - 1) / 2;
}

void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

/*
Move this element up to its correct position in the max heap.
*/
void fix_up(MaxHeap *heap, int idx)
{
  int p_idx = parent_idx(idx);

  /* To move this value up:
  - It must have a parent AND
  - Its parent's value must be smaller than its value
  */
  while (p_idx >= 0 && heap->arr[p_idx] < heap->arr[idx])
  {
    swap(&(heap->arr[p_idx]), &(heap->arr[idx]));
    idx = p_idx;
    p_idx = parent_idx(idx);
  }
}

/*
- Insert new value at the end of the array.
- Call fix up to move new inserted value to the correct position.
*/
bool insert_max_heap(MaxHeap *heap, int val)
{
  // Won't happen in this implementation because we create
  // array of size numsSize.
  if (heap->size == heap->capacity)
  {
    heap->capacity *= 2;
    heap->arr = realloc(heap->arr, heap->capacity * sizeof(*heap->arr));
  }

  heap->arr[heap->size] = val;
  fix_up(heap, heap->size);
  (heap->size)++;

  return true;
}

/*
Move this element down to its correct position in the max heap.
*/
void fix_down(MaxHeap *heap, int idx)
{
  // Index of current element's child. For now it's the left child.
  int c_idx = left_child_idx(idx);

  /*
  To move down:
  - This element cannot be a leaf
  - This element must be smaller than either its left child or its right child
  */
  while (c_idx < heap->size)
  {
    /*
    - If this child is not the last element, also check if the right child is larger than the left child.
    - If the right child is larger than the left child, we work with right child instead.
    */
    if (c_idx != heap->size - 1 && heap->arr[c_idx] < heap->arr[c_idx + 1])
      c_idx++;

    // If this element is larger than both of its children, stop.
    if (heap->arr[idx] >= heap->arr[c_idx])
      break;

    // Else, swap this element to with its child
    swap(&(heap->arr[idx]), &(heap->arr[c_idx]));

    //
    idx = c_idx;
    c_idx = left_child_idx(idx);
  }
}

/*
- Pop largest (root) element from the heap by swapping it with the last element.
- Call fix down to move the new root to its correct position.
*/
int pop_max_heap(MaxHeap *heap)
{
  // Won't happen in this implementation.
  if (heap->size == 0)
    return -10001;

  int top = heap->arr[0];

  swap(&(heap->arr[0]), &(heap->arr[heap->size - 1]));
  (heap->size)--;
  fix_down(heap, 0);

  return top;
}

void free_heap(MaxHeap *heap)
{
  if (!heap)
    return;

  free(heap->arr);
  free(heap);
}

int findKthLargest(int *nums, int numsSize, int k)
{
  MaxHeap *heap = create_max_heap(numsSize);
  for (int i = 0; i < numsSize; i++)
    insert_max_heap(heap, nums[i]);

  int result;
  for (int i = 0; i < k; i++)
    result = pop_max_heap(heap);

  free_heap(heap);

  return result;
}
