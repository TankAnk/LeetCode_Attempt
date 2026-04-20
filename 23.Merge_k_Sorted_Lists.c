void split(struct ListNode *source, struct ListNode **left, struct ListNode **right)
{
  if (!source || !(*source).next)
  {
    *left = source;
    *right = NULL;
    return;
  }

  struct ListNode *slow = source;
  struct ListNode *fast = (*source).next;

  while(fast)
  {
    fast = (*fast).next;
    if (fast)
    {
      slow = (*slow).next;
      fast = (*fast).next;
    }
  }

  *left = source;
  *right = (*slow).next;
  (*slow).next = NULL;
}

struct ListNode* merge(struct ListNode *left, struct ListNode *right)
{
  struct ListNode dummy;
  struct ListNode *traverse = &dummy;
  dummy.next = NULL;

  while (left && right)
  {
      if ((*left).val <= (*right).val)
      {
        (*traverse).next = left;
        left = (*left).next;
      }

      else
      {
        (*traverse).next = right;
        right = (*right).next;
      }
      
      traverse = (*traverse).next;
  }

  (*traverse).next = (left) ? left : right;

  return dummy.next;
}

void merge_sort(struct ListNode **head)
{
  if (!(*head) || !(**head).next)
    return;
  
  struct ListNode *a;
  struct ListNode *b;

  split(*head, &a, &b);

  merge_sort(&a);
  merge_sort(&b);
  *head = merge(a, b);
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
  if (listsSize <= 1)
    return (listsSize == 0) ? NULL : *lists;

  struct ListNode dummy;
  dummy.next = NULL;
  struct ListNode *traverse = &dummy;

  for (int i = 0; i < listsSize; i++)
  {
    while(lists[i])
    {
      (*traverse).next = lists[i];
      traverse = (*traverse).next;
      lists[i] = (*lists[i]).next;
    }
  }

  struct ListNode *result = dummy.next;

  merge_sort(&result);

  return result;
}
