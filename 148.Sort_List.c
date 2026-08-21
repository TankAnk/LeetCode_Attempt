typedef struct ListNode Node;

Node *sortList(Node *head)
{
  if (!head || !(*head).next)
    return head;

  Node dummy;
  dummy.next = head;
  int len = 1;
  Node *traverse = head;
  while ((*traverse).next)
  {
    len++;
    traverse = (*traverse).next;
  }

  int run_size = 1;
  while (run_size < len)
  {
    //Start at dummy.next as head changes during merge
    Node *curr = dummy.next;
    Node *tail = &dummy;

    while (curr)
    {
      Node *left = curr;
      Node *right = curr;
      //Find the start of the 2nd run
      for (int i = 0; i < run_size && right; i++)
        right = (*right).next;

      int left_remain = run_size, right_remain = run_size;
      while (left_remain > 0 && right_remain > 0 && right)
      {
        if ((*left).val <= (*right).val)
        {
          (*tail).next = left;
          left = (*left).next;
          left_remain--;
        }

        else
        {
          (*tail).next = right;
          right = (*right).next;
          right_remain--;
        }
      }

      while (left_remain > 0 && left)
      {
        (*tail).next = left;
        left = (*left).next;
        left_remain--;
        tail = (*tail).next;
      }

      while (right_remain > 0 && right)
      {
        (*tail).next = right;
        right = (*right).next;
        right_remain--;
        tail = (*tail).next;
      }

      curr = right;
    }

    (*tail).next = NULL;
    run_size *= 2;
  }

  reuturn dummy.next;
}
