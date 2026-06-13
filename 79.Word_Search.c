/*ABCD
AB
CD
*/

bool solve(char **board, int row_size, int col_size, int row, int col, char* word, int word_len, int word_idx, int **used)
{
  if (row >= row_size || col >= col_size || col < 0 || row < 0 || used[row][col])
    return false;

  if (word_idx == word_len - 1)
    return board[row][col] == word[word_idx];

  bool result = false;
  if (board[row][col] == word[word_idx])
  {
    used[row][col] = 1;
    //Go up
    bool c1 = solve(board, row_size, col_size, row - 1, col, word, word_len, word_idx + 1, used);

    //Go left
    bool c2 = solve(board, row_size, col_size, row, col - 1, word, word_len, word_idx + 1, used);

    //Go right
    bool c3 = solve(board, row_size, col_size, row, col + 1, word, word_len, word_idx + 1, used);

    //Go down
    bool c4 = solve(board, row_size, col_size, row + 1, col, word, word_len, word_idx + 1, used);

    result = c1 || c2 || c3 || c4;
  }

  used[row][col] = 0;
  return result;
}

bool exist(char** board, int boardSize, int* boardColSize, char* word)
{
  int word_len = strlen(word);
  int **used = malloc(boardSize * sizeof(*used));
  for (int i = 0; i < boardSize; i++)
    used[i] = calloc(boardColSize[0], sizeof(**used));

  for (int row = 0; row < boardSize; row++)
    for (int col = 0; col < boardColSize[0]; col++)
      if (solve(board, boardSize, boardColSize[0], row, col, word, word_len, 0, used))
        return true;
  for (int i = 0; i < boardSize; i++)
    free(used[i]);
  free(used);
  return false;
}
