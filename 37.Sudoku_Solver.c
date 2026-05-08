int is_valid(char **board, int row, int col, char cell)
{
  for (int i = 0; i < 9; i++)
    if ((i != row && cell == board[i][col]) || (i != col && cell == board[row][i]))
      return 0;
  
  int row_start = (row /3 ) * 3;
  int col_start = (col / 3) * 3;
  int curr_pos = (row - row_start) * 3 + (col - col_start);
  for (int pos = 0; pos < 9; pos++)
  {
    if (pos != curr_pos)
    {
      int r = row_start + (pos / 3);
      int c = col_start + (pos % 3);
      if (cell == board[r][c])
	return 0;
    }
  }

  return 1;
}
/*
    0   1   2     3   4   5     6   7   8
0 [".",".","5" | ".",".","." | ".",".","."]
1 [".",".","." | "8",".","." | ".","3","."]
2 [".","5","." | ".","2","." | ".",".","."]
-----------------------------------------
3 [".",".","." | ".",".","." | ".",".","."]
4 [".",".","." | ".",".","." | ".",".","9"]
5 [".",".","." | ".",".","." | "4",".","."]
-----------------------------------------
6 [".",".","." | ".",".","." | ".",".","7"]
7 [".","1","." | ".","3","." | ".",".","."]
8 ["2","4","." | ".",".","." | "9",".","."]
*/
int solve(char **board, int boardSize, int *boardColSize)
{
  for (int row = 0; row < boardSize; row++)
  {
    for (int col = 0; col < boardColSize[row]; col++)
    {
      char cell = board[row][col];
      if (cell == '.')
      {
	for (int i = 0; i < 9; i++)
	{
	  char tmp = '1' + i;
	  if (is_valid(board, row, col, tmp))
	  {
	    board[row][col] = tmp;

	    if (solve(board, boardSize, boardColSize))
	      return 1;

	    board[row][col] = '.';
	  }
	}

	return 0;
      }
    }
  }

  return 1;
}

void solveSudoku(char** board, int boardSize, int* boardColSize) {
  solve(board, boardSize, boardColSize);
}
