#define MAX_SIZE 100;
typedef struct Stack
{
  int *vals;
  int top;
  int capacity;
} Stack;

typedef struct
{
  Stack *stk;
  Stack *reverse_stk;
  int front_val;
} MyQueue;

Stack *create_stack()
{
  Stack *stk = malloc(sizeof(*stk));
  stk->capacity = 100;
  stk->vals = malloc(stk->capacity * sizeof(*stk->vals));
  stk->top = -1;

  return stk;
}

bool is_empty(Stack *stk)
{
  if (!stk || stk->top == -1)
    return true;

  return false;
}

bool is_full(Stack *stk)
{
  if (stk && stk->top == stk->capacity - 1)
    return true;

  return false;
}

bool push_stack(Stack *stk, int val)
{
  if (is_full(stk))
    return false;

  stk->vals[++(stk->top)] = val;
  return true;
}

int pop_stack(Stack *stk)
{
  if (is_empty(stk))
    return -1;

  int val = stk->vals[(stk->top)--];
  return val;
}

int peek_stack(Stack *stk)
{
  if (is_empty(stk))
    return -1;

  return stk->vals[stk->top];
}

MyQueue *myQueueCreate()
{
  MyQueue *queue = malloc(sizeof(*queue));
  queue->stk = create_stack();
  queue->reverse_stk = create_stack();
  queue->front_val = -1;

  return queue;
}

bool myQueueEmpty(MyQueue *obj)
{
  return is_empty(obj->stk);
}

bool myQueueFull(MyQueue *obj)
{
  return is_full(obj->stk);
}

void myQueuePush(MyQueue *obj, int x)
{
  if (myQueueFull(obj))
    return;

  if (is_empty(obj->stk))
    obj->front_val = x;

  push_stack(obj->stk, x);
}

int myQueuePop(MyQueue *obj)
{
  if (myQueueEmpty(obj))
    return -1;

  while (!is_empty(obj->stk))
    push_stack(obj->reverse_stk, pop_stack(obj->stk));

  int val = pop_stack(obj->reverse_stk);
  obj->front_val = peek_stack(obj->reverse_stk);

  while (!is_empty(obj->reverse_stk))
    push_stack(obj->stk, pop_stack(obj->reverse_stk));

  return val;
}

int myQueuePeek(MyQueue *obj)
{
  return obj->front_val;
}

void myQueueFree(MyQueue *obj)
{
  if (!obj)
    return;

  free(obj->stk);
  free(obj->reverse_stk);
}
