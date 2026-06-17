typedef struct ListNode Node;

Node* deleteDuplicates(Node* head)
{
  if (head == NULL || (*head).next == NULL)
    return head;

  Node *left = head, *right = (*head).next;
  while (right != NULL && left != NULL)
  {
    while (right != NULL && left != NULL && (*left).val != (*right).val)
    {
      left = (*left).next;
      right = (*right).next;
    }

    if (right != NULL)
    {
      while (right != NULL && (*left).val == (*right).val)
        right = (*right).next;

      (*left).next = right;
      if (right != NULL)
      {
        left = right;
        right = (*right).next;
      }
    }
  }

  return head;
}
/*
head->0-1-1-1-2-3-3-4-4-5-NULL
head->1-1-2-NULL
head->1-1-2-3-3-NULL
head->1-2-NULL
*/
