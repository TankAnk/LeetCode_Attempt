typedef struct ListNode Node;
Node *detectCycle(Node *head)
{
  Node *left = head;
  Node *right = head;

  while (right && (*right).next)
  {
    right = (*(*right).next).next;
    left = (*left).next;

    if (left == right)
    {
      Node *new_left = head;
      Node *meeting = left;

      while (new_left != meeting)
      {
        new_left = (*new_left).next;
        meeting = (*meeting).next;
      }

      return new_left;
    }
  }

  return NULL;
}
