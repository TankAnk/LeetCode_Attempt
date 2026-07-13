typedef struct TreeNode T_Node;
typedef struct ListNode L_Node

T_Node *solve(L_Node **head, int size)
{
  if (size == 0)
    return NULL;

  T_Node *root = malloc(sizeof(*root));
  int left_size = size / 2;
  (*root).left = solve(head, left_size);
  (*root).val = (*(*head)).val;
  *head = (*(*head)).next;
  (*root).right = solve(head, size - left_size - 1);

  return root;
}

T_Node *sortedListToBST(L_Node *head)
{
  if (!head)
    return NULL;

  int node_count = 0;
  L_Node *tmp = head;
  while (tmp)
  {
    node_count++;
    tmp = (*tmp).next;
  }

  return solve(&head, node_count);
}
