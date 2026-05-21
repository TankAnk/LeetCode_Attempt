int valid_move(char **board, int size, int row, int col)
{
  /*
    Queens are placed row-by-row downward --> no queens exist below current row
    Check:
    - same column upward
    - top-left diagonal
    - top-right diagonal
  */
  
  //Check columns upward
  for (int i = row - 1; i >= 0; i--)
    if (board[i][col] == 'Q')
      return 0;

  //Check top left diagonal
  for (int r = row - 1, c = col - 1; r >= 0 && c >= 0; r--, c--)
    if (board[r][c] == 'Q')
      return 0;

  //Check top right diagonal
  for (int r = row - 1, c = col + 1; r >= 0 && c < size; r--, c++)
    if (board[r][c] == 'Q')
      return 0;
  
  return 1;    
}

void solve(int n, int* returnSize, char **board, char ****result, int row, int *capacity, int** returnColumnSizes)
{
  if (*returnSize >= *capacity)
  {
    (*capacity) *= 2;
    *result = realloc(*result, *capacity * sizeof(**result));
    for (int i = *capacity / 2; i < *capacity; i++)
      (*result)[i] = malloc(n * sizeof(***result));    
    for (int i = *capacity / 2; i < *capacity; i++) 
      for (int j = 0; j < n; j++)
        (*result)[i][j] = malloc((n + 1) * sizeof(****result));
    
    *returnColumnSizes = realloc(*returnColumnSizes, *capacity * sizeof(**returnColumnSizes));
    for (int i = *capacity / 2; i < *capacity; i++)
      (*returnColumnSizes)[i] = n;
  }
  
  if (row >= n)
  {
    for (int i = 0; i < n; i++)
      memcpy((*result)[*returnSize][i], board[i], n + 1);
      
    (*returnSize)++;
    return;
  }
  
  for (int col = 0; col < n; col++)
  {
    if (valid_move(board, n, row, col))
    {
      board[row][col] = 'Q';
      solve(n, returnSize, board, result, row + 1, capacity, returnColumnSizes);
      board[row][col] = '.';
    }
  }
}

char*** solveNQueens(int n, int* returnSize, int** returnColumnSizes)
{
  *returnSize = 0;
  int capacity = 352;//Maximum number of combinations w/ n = 9 btw
  *returnColumnSizes = malloc(capacity * sizeof(**returnColumnSizes));
  for (int i = 0; i < capacity; i++)
    (*returnColumnSizes)[i] = n;
  
  char ***result = malloc(capacity * sizeof(*result));
  for (int i = 0; i < capacity; i++)
    result[i] = malloc(n * sizeof(**result));
  for (int i = 0; i < capacity; i++)
    for (int j = 0; j < n; j++)
      result[i][j] = malloc((n + 1) * sizeof(***result));

  char **board = malloc(n * sizeof(*board));
  for (int i = 0; i < n; i++)
  {
    board[i] = malloc((n + 1) * sizeof(**board));

    for (int c = 0; c < n; c++)
      board[i][c] = '.';

    board[i][n] = '\0';
  }
      
  solve(n, returnSize, board, &result, 0, &capacity, returnColumnSizes);
  for (int i = 0; i < n; i++)
    free(board[i]);
  free(board);
  return result;
}
