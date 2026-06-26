typedef struct ListNode Node;
Node *reverseBetween(Node *head, int left, int right)
{
  if (left == right || !head || !((*head).next))
    return head;

  Node dummy;
  dummy.next = head;
  Node *prev = &dummy;
  for (int i = 1; i < left; i++)
    prev = (*prev).next;
  Node *curr = (*prev).next;

  for (int i = 0; i < right - left; i++)
  {
    Node *after = (*curr).next;
    (*curr).next = (*after).next;
    (*after).next = (*prev).next;
    (*prev).next = after;
  }

  return dummy.next;
}
/*left = 2, right = 6
head-1-2-3-4-5-6-7-8-NULL
head-1-5-4-3-2-6-7-8-NULL
*/
