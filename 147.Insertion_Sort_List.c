/*
for i = 1 to the end
  j = i - 1;
  key = arr[i];
  while (j >= 0 && arr[j] > key)
    arr[j + 1] = a[j];
    j--;

  arr[j + 1] = key;
*/
typedef struct ListNode Node;

void print_list(Node *head)
{
  while (head)
  {
    printf("%d ", (*head).val);
    head = (*head).next;
  }

  printf("\n");
}

Node *insertionSortList(Node *head)
{
  if (!head || !(*head).next)
    return head;

  Node dummy;
  dummy.next = head;
  Node *curr = (*head).next;
  Node *prev = head;

  while (curr)
  {
    //curr is in wrong position
    if ((*prev).val > (*curr).val)
    {
      int key = (*curr).val;
      Node *traverse = &dummy;
      //Find position to insert curr
      while ((*traverse).next != prev && (*(*traverse).next).val <= key)
        traverse = (*traverse).next;

      //Insert AFTER traverse
      Node *nxt = (*curr).next;
      (*prev).next = nxt;
      (*curr).next = (*traverse).next;
      (*traverse).next = curr;

      //curr moves, prev stays. The next curr remains immediately after prev.
      curr = nxt;
    }

    //Nothing wrong, keep going
    else
    {
      curr = (*curr).next;
      prev = (*prev).next;
    }

    //print_list((*dummy).next);
    //printf("prev: %d, curr: %d\n", (*prev).val, (*curr).val);
  }

  return dummy.next;
}
