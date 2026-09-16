int calculateMinimumHP(int **dungeon, int dungeonSize, int *dungeonColSize)
{
  int r_size = dungeonSize, c_size = dungeonColSize[0];

  // memo[i][j] = Minimum HP to ENTER this cell
  int memo[r_size][c_size];

  // Base case: To enter last cell
  if (dungeon[r_size - 1][c_size - 1] >= 0)
    memo[r_size - 1][c_size - 1] = 1;
  else
    memo[r_size - 1][c_size - 1] = -dungeon[r_size - 1][c_size - 1] + 1;

  for (int r_idx = r_size - 1; r_idx >= 0; r_idx--)
  {
    for (int c_idx = c_size - 1; c_idx >= 0; c_idx--)
    {
      // Skip last cell
      if (r_idx == r_size - 1 && c_idx == c_size - 1)
        continue;

      int next_move, require;

      // Can only move right at last row
      if (r_idx == r_size - 1)
        next_move = memo[r_idx][c_idx + 1];

      // Can only move down at last column
      else if (c_idx == c_size - 1)
        next_move = memo[r_idx + 1][c_idx];

      // For normal cell, choose move that require least HP
      else
        next_move = (memo[r_idx + 1][c_idx] < memo[r_idx][c_idx + 1]) ? memo[r_idx + 1][c_idx] : memo[r_idx][c_idx + 1];

      // Calculate the required HP for THIS CURRENT cell based on next move
      require = next_move - dungeon[r_idx][c_idx];

      // Save to memo
      memo[r_idx][c_idx] = require <= 0 ? 1 : require;
    }
  }

  return memo[0][0];
}
