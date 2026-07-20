typedef struct Node Node;

Node *connect(Node *root)
{
  if (!root)
    return NULL;

  /*
  Maximum depth = log2 of 4096 = 12
  Each level k (from 0 - 11) has 2^k nodes
  --> Maximum node at level 11 = 2^11 = 2048
  1 extra slot
  */

  int front = 0, rear = 0, capacity = 2049;
  Node *queue[capacity];
  queue[rear++] = root;
  while (front != rear)
  {
    int size = (rear - front + capacity) % capacity;
    for (int i = 0; i < size; i++)
    {
      //Dequeue
      Node *curr = queue[front];
      front = (front + 1) % capacity;

      (*curr).next = (i < size - 1) ? queue[front] : NULL;

      //Enqueue
      if ((*curr).left)
      {
        queue[rear] = (*curr).left;
        rear = (rear + 1) % capacity;
      }

      if ((*curr).right)
      {
        queue[rear] = (*curr).right;
        rear = (rear + 1) % capacity;
      }
    }
  }

  return root;
}
