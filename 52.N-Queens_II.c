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

void solve(int n, int* result, char **board, int row)
{  
  if (row >= n)
  {      
    (*result)++;
    return;
  }
  
  for (int col = 0; col < n; col++)
  {
    if (valid_move(board, n, row, col))
    {
      board[row][col] = 'Q';
      solve(n, result, board, row + 1);
      board[row][col] = '.';
    }
  }
}

int totalNQueens(int n)
{
  int result = 0;
  char **board = malloc(n * sizeof(*board));
  for (int i = 0; i < n; i++)
  {
    board[i] = malloc((n + 1) * sizeof(**board));

    for (int c = 0; c < n; c++)
      board[i][c] = '.';

    board[i][n] = '\0';
  }
      
  solve(n, &result, board, 0);
  for (int i = 0; i < n; i++)
    free(board[i]);
  free(board);
  return result;
}
