bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
  for (int row = 0; row < boardSize; row++)
  {
    for (int col = 0; col < boardColSize[row]; col++)
    {
      char cell = board[row][col];

      if (cell != '.')
      {
	
	//Check on the same column
	for (int i = row + 1; i < boardSize; i++)
	  if (cell == board[i][col])
	    return false;

	//Check on the same row
	for (int j = col + 1; j < boardColSize[row]; j++)
	  if (cell == board[row][j])
	    return false;

	//Check forward 3x3 sub-box
	int start_row = (row / 3) * 3, start_col = (col / 3) * 3;
	int curr_pos = (row - start_row) * 3 + (col - start_col);
	for (int pos = curr_pos + 1; pos < 9; pos++)
	  if (cell == board[start_row + (pos / 3)][start_col + (pos % 3)])
	    return false;
      }
    }
  }

  return true;
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
