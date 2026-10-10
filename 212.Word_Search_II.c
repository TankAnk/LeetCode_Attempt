#define MAX_CHAR 26

typedef struct TrieNode
{
  bool EOW;

  // struct TrieNode *children[26];
  struct TrieNode **children;
} TrieNode;

TrieNode *create_trie_node()
{
  TrieNode *root = malloc(sizeof(*root));
  root->EOW = false;
  root->children = malloc(MAX_CHAR * sizeof(*root->children));
  for (int i = 0; i < MAX_CHAR; i++)
    root->children[i] = NULL;

  return root;
}

void insert_trie(TrieNode *obj, char *word)
{
  for (int i = 0; word[i] != '\0'; i++)
  {
    int child_idx = word[i] - 'a';

    if (obj->children[child_idx] == NULL)
      obj->children[child_idx] = create_trie_node();

    obj = obj->children[child_idx];
  }

  obj->EOW = true;
}

bool search_trie(TrieNode *obj, char *word)
{
  for (int i = 0; word[i] != '\0'; i++)
  {
    int child_idx = word[i] - 'a';

    if (obj->children[child_idx] == NULL)
      return false;

    obj = obj->children[child_idx];
  }

  return obj->EOW;
}

/*
bool start_with(TrieNode *obj, char *prefix)
{
  for (int i = 0; prefix[i] != '\0'; i++)
  {
    int child_idx = prefix[i] - 'a';

    if (obj->children[child_idx] == NULL)
      return false;

    obj = obj->children[child_idx];
  }

  return true;
}
*/

void free_trie(TrieNode *obj)
{
  if (!obj)
    return;

  for (int i = 0; i < MAX_CHAR; i++)
    free_trie(obj->children[i]);

  free(obj->children);
  free(obj);
}

/*
 * Searches the board for dictionary words using DFS and backtracking.
 * The Trie allows us to explore only paths that match prefixes of words
 * in the dictionary.
 *
 * board      - Character board to search.
 * row_size   - Number of rows in the board.
 * col_size   - Number of columns in the board.
 * row, col   - Coordinates of the current cell.
 * result     - Dynamic array storing the words found.
 * returnSize - Number of words found so far.
 * capacity   - Current allocated capacity of result.
 * tmp_buf    - Characters along the current search path.
 * buf_size   - Number of characters currently in tmp_buf.
 * visited    - Tracks cells already used in the current path.
 * curr       - Trie node representing the prefix before this cell.
 */
void solve(char **board, int row_size, int col_size, int row, int col, char ***result, int *returnSize, int *capacity, char *tmp_buf, int buf_size, bool **visited, TrieNode *curr)
{
  // Stop if the coordinates are outside the board or this cell has already
  // been used in the current path. A cell cannot be reused within one word.
  if (row < 0 || row >= row_size || col < 0 || col >= col_size || visited[row][col])
    return;

  // Follow the Trie edge corresponding to this cell's character.
  // If the edge does not exist, this path cannot form a dictionary word.
  int idx = board[row][col] - 'a';
  if (!curr->children[idx])
    return;

  // Include this cell in the current path and advance to the matching
  // Trie node. buf_size is passed by value to each recursive call.
  visited[row][col] = true;
  tmp_buf[buf_size++] = board[row][col];
  curr = curr->children[idx];

  // If this node marks the end of a word, save the current path as a result.
  if (curr->EOW)
  {
    // Double the result array's capacity when it becomes full.
    if (*returnSize == *capacity)
    {
      *capacity *= 2;
      *result = realloc(*result, *capacity * sizeof(**result));
    }

    // Allocate memory for the word and its null terminator, then copy it.
    (*result)[*returnSize] = malloc((buf_size + 1) * sizeof(***result));
    memcpy((*result)[*returnSize], tmp_buf, buf_size * sizeof(***result));
    (*result)[*returnSize][buf_size] = '\0';
    (*returnSize)++;

    // The input words are unique, so mark this word as found to prevent
    // duplicate results. Keep the node because longer words may share
    // this word as a prefix.
    curr->EOW = false;
  }

  // Continue exploring even after finding a word, because it may be a
  // prefix of a longer word. Explore all four valid directions.
  // Go up
  solve(board, row_size, col_size, row - 1, col, result, returnSize, capacity, tmp_buf, buf_size, visited, curr);

  // Go left
  solve(board, row_size, col_size, row, col - 1, result, returnSize, capacity, tmp_buf, buf_size, visited, curr);

  // Go down
  solve(board, row_size, col_size, row + 1, col, result, returnSize, capacity, tmp_buf, buf_size, visited, curr);

  // Go right
  solve(board, row_size, col_size, row, col + 1, result, returnSize, capacity, tmp_buf, buf_size, visited, curr);

  // Backtrack: make this cell available for other search paths.
  visited[row][col] = false;
}

/*
 * The function builds a Trie by inserting all words, then starts a DFS from
 * every board cell.
 *
 * board        - Character board to search.
 * boardSize    - Number of rows in the board.
 * boardColSize - Array containing the column count for each row.
 * words        - Array of dictionary words to search for.
 * wordsSize    - Number of words in the dictionary.
 * returnSize   - Output parameter receiving the number of words found.
 *
 * Returns a dynamically allocated array of the words found. The caller
 * is responsible for freeing the returned strings and the result array.
 */
char **findWords(char **board, int boardSize, int *boardColSize, char **words, int wordsSize, int *returnSize)
{
  // Insert all words to trie.
  TrieNode *root = create_trie_node();
  for (int i = 0; i < wordsSize; i++)
    insert_trie(root, words[i]);

  *returnSize = 0;
  int capacity = 128;
  char **result = malloc(capacity * sizeof(*result));

  // Store the characters along the current search path.
  // The maximum word length is 10, so 10 bytes are sufficient.
  char tmp_buf[10];

  // Allocate a visited matrix initialized to false. It prevents a search
  // path from reusing a cell. solve() restores cells through backtracking.
  bool **visited = malloc(boardSize * sizeof(*visited));
  for (int i = 0; i < boardSize; i++)
    visited[i] = calloc(boardColSize[0], sizeof(**visited));

  // Start a DFS from every cell. The Trie root represents the empty prefix
  // before the first character is processed.
  for (int row = 0; row < boardSize; row++)
  {
    for (int col = 0; col < boardColSize[0]; col++)
    {
      solve(board, boardSize, boardColSize[0], row, col, &result, returnSize, &capacity, tmp_buf, 0, visited, root);
    }
  }

  for (int i = 0; i < boardSize; i++)
    free(visited[i]);
  free(visited);
  free_trie(root);

  return result;
}
