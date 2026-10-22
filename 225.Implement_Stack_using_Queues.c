#define MAX_SIZE 100

typedef struct
{
  int values[MAX_SIZE];
  int front;
  int rear;
  int size;
} Queue;

typedef struct
{
  Queue *primary;
  Queue *secondary;
} MyStack;

static void enqueue(Queue *q, int x)
{
  q->values[q->rear] = x;
  q->rear = (q->rear + 1) % MAX_SIZE;
  q->size++;
}

static int dequeue(Queue *q)
{
  int value = q->values[q->front];
  q->front = (q->front + 1) % MAX_SIZE;
  q->size--;

  return value;
}

static int peek(Queue *q)
{
  return q->values[q->front];
}

MyStack *myStackCreate(void)
{
  MyStack *stack = malloc(sizeof(*stack));

  if (stack == NULL)
    return NULL;

  stack->primary = calloc(1, sizeof(Queue));
  stack->secondary = calloc(1, sizeof(Queue));

  if (stack->primary == NULL || stack->secondary == NULL)
  {
    free(stack->primary);
    free(stack->secondary);
    free(stack);
    return NULL;
  }

  return stack;
}

bool myStackEmpty(MyStack *obj)
{
  return obj == NULL || obj->primary->size == 0;
}

void myStackPush(MyStack *obj, int x)
{
  if (obj == NULL || obj->primary->size >= MAX_SIZE)
    return;

  enqueue(obj->secondary, x);

  while (obj->primary->size > 0)
    enqueue(obj->secondary, dequeue(obj->primary));

  Queue *temp = obj->primary;
  obj->primary = obj->secondary;
  obj->secondary = temp;
}

int myStackPop(MyStack *obj)
{
  if (myStackEmpty(obj))
    return -1;

  return dequeue(obj->primary);
}

int myStackTop(MyStack *obj)
{
  if (myStackEmpty(obj))
    return -1;

  return peek(obj->primary);
}

void myStackFree(MyStack *obj)
{
  if (obj == NULL)
    return;

  free(obj->primary);
  free(obj->secondary);
  free(obj);
}
