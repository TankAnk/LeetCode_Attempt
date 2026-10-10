/**
 * Your WordDictionary struct will be instantiated and called as such:
 * WordDictionary* obj = wordDictionaryCreate();
 * wordDictionaryAddWord(obj, word);
 *
 * bool param_2 = wordDictionarySearch(obj, word);
 *
 * wordDictionaryFree(obj);
 */

#define MAX_CHAR 26

/*
 * Each TrieNode represents one position/prefix in the Trie.
 *
 * Example after adding "cat":
 *
 *      root
 *       |
 *       c
 *       |
 *       a
 *       |
 *       t
 *
 * EOW (End Of Word) tells us whether the current node represents the end of a complete word.
 *
 * For example, if only added "cat", the node for 'a' has EOW = false, while the node for 't' has EOW = true.
 */
typedef struct TrieNode
{
  bool EOW;

  /*
   * children[i] points to the next TrieNode for a particular letter.
   *
   * Index 0 -> 'a'
   * Index 1 -> 'b'
   * ...
   * Index 25 -> 'z'
   *
   * This is dynamically allocated instead of declaring:
   * TrieNode *children[26];
   *
   * Or:
   * TrieNode **children;
   */
  struct TrieNode **children;

} TrieNode;

/*
 * WordDictionary is basically the entire Trie.
 *
 * root is the starting point of the Trie. It does not represent a letter itself;
 * its children represent the first letters of words.
 */
typedef struct
{
  struct TrieNode *root;
} WordDictionary;

/*
 * Create and initialize one Trie node.
 *
 * Every node starts with:
 *   - 26 NULL child pointers
 *   - EOW = false
 *
 * The children are NULL because none path created
 * from this node yet.
 */
TrieNode *create_trie_node()
{
  TrieNode *node = malloc(sizeof(*node));
  if (!node)
    return NULL;

  /*
   * Allocate space for 26 child pointers.
   *
   * Store pointers to TrieNodes, not TrieNodes themselves.
   */
  node->children = malloc(MAX_CHAR * sizeof(*node->children));
  if (!node->children)
  {
    free(node);
    return NULL;
  }

  /* Initially, this node has no children. */
  for (int i = 0; i < MAX_CHAR; i++)
    node->children[i] = NULL;

  /* This node does not represent the end of a word yet. */
  node->EOW = false;

  return node;
}

/*
 * Create an empty WordDictionary.
 *
 * The dictionary starts with one root node.
 * The root itself does not represent a character.
 */
WordDictionary *wordDictionaryCreate()
{
  WordDictionary *wd = malloc(sizeof(*wd));
  if (!wd)
    return NULL;

  wd->root = create_trie_node();

  return wd;
}

/*
 * Add a word to the Trie.
 * Walk through the word one character at a time.
 * If the path for a character already exists, reuse it.
 * Otherwise, create a new TrieNode for that character.
 *
 * Example when adding "cat":
 * root -> c -> a -> t
 * Finally, the node representing 't' gets EOW = true,
 * telling us that "cat" is a complete stored word.
 */
void wordDictionaryAddWord(WordDictionary *obj, char *word)
{
  TrieNode *traverse = obj->root;

  for (int i = 0; word[i] != '\0'; i++)
  {
    /*
     * Convert the character into an array index.
     * 'a' - 'a' = 0
     * 'b' - 'a' = 1
     * ...
     * 'z' - 'a' = 25
     */
    char char_idx = word[i] - 'a';

    /*
     * If this character does not have a path yet,
     * create a new TrieNode for it.
     */
    if (!traverse->children[char_idx])
      traverse->children[char_idx] = create_trie_node();

    /*
     * Move to the node representing the current character.
     */
    traverse = traverse->children[char_idx];
  }

  /* Reached the end of the word. */
  traverse->EOW = true;
}

/*
 * Search the Trie starting from 'root'.
 * This function handles both:
 *   1. Normal letters:
 *      Follow the corresponding child.
 *   2. '.':
 *      '.' can represent ANY one letter, so must try
 *      every existing child.
 * The function receives a TrieNode rather than a WordDictionary
 * because recursion only needs to know:
 *      "Where am I in the Trie?"
 * It does not need to create another WordDictionary.
 */
bool search_trie(TrieNode *root, char *word)
{
  if (!root)
    return false;

  /*
   * Process the search word one character at a time.
   */
  for (int i = 0; word[i] != '\0'; i++)
  {
    /*
     * '.' can represent any ONE letter, so have to
     * try every possible child.
     */
    if (word[i] == '.')
    {
      for (int j = 0; j < MAX_CHAR; j++)
      {
        /*
         * There is no possible match through this letter
         * if this child does not exist.
         */
        if (!root->children[j])
          continue;

        /*
         * Continue searching from this child with the
         * remaining part of the search word.
         *
         * word + i + 1 points to the character immediately
         * after the current '.'.
         *
         * If ANY possible branch matches, the whole search
         * succeeds.
         */
        if (search_trie(root->children[j], word + i + 1))
          return true;
      }

      /*
       * Tried every possible child, but none matched.
       */
      return false;
    }

    else
    {
      /*
       * For a normal letter, there is only one possible path.
       *
       * Convert the letter to an index and follow that child.
       */
      int char_idx = word[i] - 'a';

      /*
       * If the required path does not exist,
       * no stored word can match this search.
       */
      if (!root->children[char_idx])
        return false;

      /*
       * Move to the next node in the Trie.
       */
      root = root->children[char_idx];
    }
  }

  /*
   * Already consumed the entire search word.
   *
   * The match is valid only if this node marks the end
   * of an actual stored word.
   *
   * This prevents a prefix from being considered a match.
   *
   * Example:
   *   Stored: "badminton"
   *   Search: "bad"
   *
   * The node for 'd' exists, but EOW at 'd' is false,
   * so "bad" is not considered a stored word.
   */
  return (root->EOW == true);
}

/*
 * Start the search from the root of the dictionary's Trie.
 *
 * The actual searching is handled by search_trie().
 */
bool wordDictionarySearch(WordDictionary *obj, char *word)
{
  return search_trie(obj->root, word);
}

/*
 * Recursively free the entire Trie.
 *
 * A Trie is a tree of dynamically allocated nodes, must
 * recursively visit and free every child before freeing the
 * current node.
 */
void free_trie(TrieNode *root)
{
  if (!root)
    return;

  /*
   * First free all subtrees.
   */
  for (int i = 0; i < MAX_CHAR; i++)
    free_trie(root->children[i]);

  /*
   * Then free this node's dynamically allocated child-pointer
   * array and finally the node itself.
   */
  free(root->children);
  free(root);
}

/*
 * Free the entire WordDictionary.
 *
 * First free the Trie, then free the WordDictionary itself.
 */
void wordDictionaryFree(WordDictionary *obj)
{
  if (!obj)
    return;

  free_trie(obj->root);
  free(obj);
}
