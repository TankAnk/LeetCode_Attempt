typedef struct TreeNode Node;

/*
Find tree height.
*/
int find_height(Node *root)
{
  if (!root)
    return 0;

  return 1 + find_height(root->left);
}

/*
Find node at target index in tree (as the tree is flaten into an array with base 0 index).
*/
bool search_binary_tree(Node *root, int idx, int height)
{
  if (!root)
    return false;

  if (idx == 0)
    return true;

  // Construct the full path from root to target node (excluding the root at index 0).
  bool path[height - 1];

  /*
  - Extract the LSB of the idx.
  - We only need to know LSB to decide to go left or right:
    + If the index is even, go right.
    + If the index is odd, go left.
  */
  for (int i = height - 2; i >= 0; i--)
  {
    path[i] = 1 & idx;

    // Find parent node index.
    idx = (idx - 1) / 2;
  }

  // Traverse the tree to find target node.
  Node *traverse = root;
  for (int i = 0; i < height - 1; i++)
  {
    if (!traverse)
      return false;

    // Go left if the child index is even (true), go right otherwise.
    traverse = path[i] ? traverse->left : traverse->right;
  }

  // Does this node exist?
  return traverse != NULL;
}

int countNodes(Node *root)
{
  if (!root)
    return 0;

  int height = find_height(root);
  if (height == 1)
    return 1;

  // Calculate the total nodes in all levels excluding the last level.
  int result = 0;
  int exp = 1;
  for (int i = 0; i < height - 1; i++, exp *= 2)
    result += exp;

  /*
  - Binary search for all nodes in the last level excluding first node.
  - If node nth exists, [left, nth] exist -> search right half for potential existing nodes.
  - If node nth does not exist, [nth, right] does not exist -> search left half.
  - After the loop, left is now the index (based 0) of the non-exist node
  -> Total nodes = Total nodes from levels above + Left (Because [0, left - 1] hae left nodes).
  */
  int left = 1, right = exp - 1;
  while (left <= right)
  {
    int mid = (right - left) / 2 + left;

    /*
    - Calculate the index of this node in the whole tree flaten out.
    - For example: Index in the tree of the 4th node in the level 3
    = total nodes from all level above + index of the current node in its level
    = 7 + 4 = 11.
    */
    int mid_idx = result + mid;

    if (search_binary_tree(root, mid_idx, height))
      left = mid + 1;

    else
      right = mid - 1;
  }

  return result += left;
}
