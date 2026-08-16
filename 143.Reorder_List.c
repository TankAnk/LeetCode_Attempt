typedef struct ListNode Node;

Node *reverse_linked_list(Node *head)
{
  if (!head)
    return NULL;

  Node *curr = head, *prev = NULL, *next;
  while (curr)
  {
    next = (*curr).next;
    (*curr).next = prev;
    prev = curr;
    curr = next;
  }

  return prev;
}

void reorderList(Node *head)
{
  //Find the middle of the list
  Node *left = head, *right = head;
  while (right && (*right).next)
  {
    right = (*(*right).next).next;
    left = (*left).next;
  }

  //Split list in half
  Node *second = (*left).next;
  (*left).next = NULL;

  //Reverse the second half
  second = reverse_linked_list(second);

  /*Now we have
    1->2->3->NULL
    5->4->NULL
    Concatenate 2 list
  */
  Node *first = head, *next_first, *next_second;
  while (first && second)
  {
    next_first = (*first).next;
    next_second = (*second).next;

    (*first).next = second;
    (*second).next = next_first;

    first = next_first;
    second = next_second;
  }
}
