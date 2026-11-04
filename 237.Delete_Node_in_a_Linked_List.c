typedef struct ListNode Node;

void deleteNode(Node *node)
{
  Node *nxt = node->next;
  node->val = nxt->val;
  node->next = nxt->next;
  free(nxt);
}
