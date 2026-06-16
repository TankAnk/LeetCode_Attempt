typedef struct ListNode Node;

Node* deleteDuplicates(struct ListNode* head)
{
  if (head == NULL || (*head).next == NULL)
    return head;

  Node *prev = head, *left = head, *right = (*head).next;
  while (left != NULL && right != NULL)
  {
    while (left != NULL && right != NULL && (*left).val != (*right).val)
    {
      left = (*left).next;
      right = (*right).next;
    }

    if (right != NULL)
    {
      while (right != NULL && (*left).val == (*right).val)
        right = (*right).next;

      if (right != NULL)
      {
        if (left == head)
        {
          (*head).next = right;
          head = right;
        }

        else
        {
          while ((*prev).next != left)
            prev = (*prev).next;

          (*prev).next = right;
        }

        left = right;
        right = (*right).next;
      }

      else
      {
        if (left == head)
          return NULL;

        while ((*prev).next != left)
            prev = (*prev).next;
        (*prev).next = right;
      }
    }
  }

  return head;
}
