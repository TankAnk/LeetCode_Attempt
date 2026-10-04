typedef struct ListNode Node;
Node *reverseList(Node *head)
{
  Node dummy;
  dummy.next = NULL;

  while (head)
  {
    Node *next = head->next;
    head->next = dummy.next;
    dummy.next = head;
    head = next;
  }

  return dummy.next;
}
