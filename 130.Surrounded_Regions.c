/*
 - A cell can only connected to other cell vertically or horizontally (not diagonally)
 - A region is one or more connected cells
 - Find a region:
  + If ANY of the region's cell is on the edge, skip
  + If NONE of the region's cell is on the edge, replace the region w/ X
 */
#define MAX_SIZE 40000

typedef struct Cell
{
  int row;
  int col;
} Cell;

void solve(char **board, int boardSize, int *boardColSize)
{
  bool visited[boardSize][boardColSize[0]];
  for (int i = 0; i < boardSize; i++)
    memset(visited[i], 0, boardColSize[0] * sizeof(**visited));

  for (int r = 1; r < boardSize - 1; r++)
  {
    for (int c = 1; c < boardColSize[0] - 1; c++)
    {
      if (board[r][c] == 'X' || visited[r][c])
        continue;

      int front = 0, rear = 0;
      Cell queue[MAX_SIZE];
      queue[rear++] = (Cell){r, c};
      int top = -1;
      Cell stack[MAX_SIZE];
      bool replace = true;

      while (front != rear)
      {
        Cell curr = queue[front++];
        if (curr.row == 0 || curr.row == boardSize - 1 || curr.col == 0 || curr.col == boardColSize[0] - 1)
        {
          replace = false;
          continue;
        }

        stack[++top] = curr;
        if (curr.row > 0 && !visited[curr.row - 1][curr.col] && board[curr.row - 1][curr.col] == 'O')
        {
          visited[curr.row - 1][curr.col] = 1;
          queue[rear++] = (Cell){curr.row - 1, curr.col};
        }

        if (curr.col > 0 && !visited[curr.row][curr.col - 1] && board[curr.row][curr.col - 1] == 'O')
        {
          visited[curr.row][curr.col - 1] = true;
          queue[rear++] = (Cell){curr.row, curr.col - 1};
        }

        if (curr.col < boardColSize[0] - 1 && !visited[curr.row][curr.col + 1] && board[curr.row][curr.col + 1] == 'O')
        {
          visited[curr.row][curr.col + 1] = true;
          queue[rear++] = (Cell){curr.row, curr.col + 1};
        }

        if (curr.row < boardSize - 1 && !visited[curr.row + 1][curr.col] && board[curr.row + 1][curr.col] == 'O')
        {
          visited[curr.row + 1][curr.col] = true;
          queue[rear++] = (Cell){curr.row + 1, curr.col};
        }
      }

      for (top; top >= 0 && replace; top--)
        board[stack[top].row][stack[top].col] = 'X';
    }
  }
}
