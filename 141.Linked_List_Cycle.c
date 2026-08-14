typedef struct ListNode Node;
bool hasCycle(Node *head)
{
  if (!head)
    return false;

  Node *left = head;
  Node *right = head;
  while (right && (*right).next)
  {
    left = (*left).next;
    right = (*(*right).next).next;

    if (left == right)
      return true;
  }

  return false;
}

/*
1 -> 2 -> 3 -> 4
^              |
|              |
|______________|
*/
