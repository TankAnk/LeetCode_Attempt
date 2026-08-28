#define MAX_SIZE 30000

typedef struct MinStack
{
  int stack_top;
  int mins_top;
  int *vals;
  int *mins;
} MinStack;

MinStack *minStackCreate(void);
void minStackPush(MinStack *obj, int value);
void minStackPop(MinStack *obj);
int minStackTop(MinStack *obj);
int minStackGetMin(MinStack *obj);
void minStackFree(MinStack *obj);

MinStack *minStackCreate()
{
  MinStack *stack = malloc(sizeof(*stack));
  if (!stack)
    return NULL;
  (*stack).stack_top = -1;
  (*stack).mins_top = -1;
  (*stack).vals = malloc(MAX_SIZE * sizeof(int));
  if (!(*stack).vals)
    return NULL;
  (*stack).mins = malloc(MAX_SIZE * sizeof(int));
  if (!(*stack).mins)
    return NULL;

  return stack;
}

void minStackPush(MinStack *obj, int value)
{
  if (!obj || (*obj).stack_top == MAX_SIZE - 1)
    return;

  (*obj).stack_top++;
  (*obj).vals[(*obj).stack_top] = value;
  if ((*obj).stack_top == 0 || minStackGetMin(obj) >= value)
  {
    (*obj).mins_top++;
    (*obj).mins[(*obj).mins_top] = value;
  }
}

void minStackPop(MinStack *obj)
{
  if (!obj || (*obj).stack_top == -1)
    return;

  if (minStackTop(obj) == minStackGetMin(obj))
    (*obj).mins_top--;

  (*obj).stack_top--;
}

int minStackTop(MinStack *obj)
{
  assert(obj != NULL);
  assert((*obj).stack_top != -1);

  return (*obj).vals[(*obj).stack_top];
}

int minStackGetMin(MinStack *obj)
{
  assert(obj != NULL);
  assert((*obj).stack_top != -1);
  assert((*obj).mins != NULL);

  return (*obj).mins[(*obj).mins_top];
}

/*
void minsStackPrint(MinStack *stack)
{
  if (!stack || (*stack).stack_top == -1)
    return;

  for (int i = 0; i <= (*stack).stack_top; i++)
    printf("%d ", (*stack).vals[i]);

  printf("\n");
  printf("stack_top position: %d, stack_top Value: %d, Min value: %d\n", (*stack).stack_top, minsStackstack_top(stack), minsStackGetMin(stack));
}
*/

void minStackFree(MinStack *obj)
{
  if (!obj)
    return;

  free((*obj).vals); //free(NULL) is safe
  free((*obj).mins);
  free(obj);
}
