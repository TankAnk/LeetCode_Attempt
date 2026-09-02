typedef struct ListNode Node;
Node *getIntersectionNode(Node *headA, Node *headB)
{
  if (!headA || !headB)
    return NULL;

  /*Concatenate A+B and B+A
    If there is an intersection: h1 = h2 = intersection
    If there is no intersection: h1 = h2 = NULL
  */
  Node *h1 = headA, *h2 = headB;
  while(h1 != h2)
  {
    h1 = (h1 != NULL) ? (*h1).next : headB;
    h2 = (h2 != NULL) ? (*h2).next : headA;
  }

  return h1;
}
