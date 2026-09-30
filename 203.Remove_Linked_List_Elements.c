typedef struct ListNode Node;

/*
void printList(Node *head)
{
  while (head)
  {
    printf("%d ", head->val);
    head = head->next;
  }

  printf("\n");
}
*/

Node *removeElements(Node *head, int val)
{
  Node dummy;
  dummy.next = head;
  Node *traverse = &dummy;

  //int run = 0;

  // traverse always points to the node immediately before the node
  // we're currently considering for deletion.
  while (traverse->next)
  {
    /*
    printf("Run %d\n", run);
    printf("  List before: ");
    printList(dummy.next);
    printf("  Current node: %d\n", traverse->val);
    */

    while (traverse->next && traverse->next->val != val)
      traverse = traverse->next;

    if (traverse->next)
    {
      Node *tmp = traverse->next;
      traverse->next = tmp->next;
      free(tmp);
    }

    /*
    printf("  List after: ");
    printList(dummy.next);
    printf("  Current node: %d\n", traverse->val);
    run++;
    */
  }

  return dummy.next;
}
