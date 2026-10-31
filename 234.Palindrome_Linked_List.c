typedef struct ListNode Node;

/*
- Find the first node of the second half.
- Reverse the 2nd half.
- Compare

Ex: head->1->2->3->3->2->1->NULL
- First node of the second half: 3 (the second 3).
- Reverse: head->1->2->3->3<-2<-1.
- Compare.

Ex: head->1->2->3->4->5->NULL
- First node of the second half: 3.
- Reverse: head->1->2->3<-4<-5.
- Compare.
*/

Node *reverse_linked_list(Node *head)
{
  Node *prev = NULL;
  Node *curr = head;

  while (curr)
  {
    Node *next = curr->next;
    curr->next = prev;

    prev = curr;
    curr = next;
  }

  return prev;
}

bool isPalindrome(Node *head)
{
  if (!head->next)
    return true;

  Node *fast = head;
  Node *slow = head;

  // Find the first node of the second half of the linked list.
  while (fast && fast->next)
  {
    slow = slow->next;
    fast = fast->next->next;
  }

  // printf("Slow: %d, Tail: %d\n", slow->val, tail->val);

  // Reverse the 2nd half.
  Node *second_half = reverse_linked_list(slow);

  while (head != slow && second_half)
  {
    if (head->val != second_half->val)
      return false;

    head = head->next;
    second_half = second_half->next;
  }

  return true;
}
