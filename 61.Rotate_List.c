typedef struct ListNode ListNode;

size_t get_size(ListNode *head)
{
  size_t size = 0;
  while(head != NULL)
  {
    size++;
    head = (*head).next;
  }
  return size;
}

struct ListNode* rotateRight(ListNode* head, int k)
{
  if (head == NULL || (*head).next == NULL)
    return head;
  int size = get_size(head);
  k %= size;
  if (k == 0)
    return head;

  ListNode *prev = head;
  for (int i = 0; i < size - 1 - k; i++)
    prev = (*prev).next;
  ListNode *start = (*prev).next;
  ListNode *end = start;
  while ((*end).next != NULL)
    end = (*end).next;

  (*prev).next = (*end).next; //= in NULL in this case btw
  (*end).next = head;
  head = start;

  return head;
}
