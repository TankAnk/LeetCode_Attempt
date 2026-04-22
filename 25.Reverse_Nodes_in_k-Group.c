typedef struct ListNode node;

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
  if (!head || !(*head).next)
    return head;

  int size = 0;
  node *tmp = head;
  while (tmp)
  {
    size++;
    tmp = (*tmp).next;
  }
  
  if (size < k)
    return head;

  node *prev = NULL;
  node *curr = head;
  node *nxt = NULL;

  for (int i = 0; i < k; i++)
  {
    nxt = (*curr).next;
    (*curr).next = prev;
    prev = curr;
    curr = nxt;
  }
  
  (*head).next = reverseKGroup(curr, k);

  return prev;
}
