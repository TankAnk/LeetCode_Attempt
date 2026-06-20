/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
typedef struct ListNode Node;
Node* partition(Node* head, int x)
{
  Node small_dummy = {0, NULL}, large_dummy = {0, NULL};
  Node *small = &small_dummy;
  Node *large = &large_dummy;
  Node *traverse = head;

  while (traverse)
  {
    if ((*traverse).val < x)
    {
      (*small).next = traverse;
      small = (*small).next;
    }

    else
    {
      (*large).next = traverse;
      large = (*large).next;
    }

    traverse = (*traverse).next;
  }

  (*small).next = large_dummy.next;
  (*large).next = NULL;

  return small_dummy.next;
}
