void setZeroes(int** matrix, int matrixSize, int* matrixColSize)
{
  int **set = malloc(matrixSize * sizeof(*set));
  for (int i = 0; i < matrixSize; i++)
    set[i] = calloc(matrixColSize[0], sizeof(**set));

  for (int row = 0; row < matrixSize; row++)
    for (int col = 0; col < matrixColSize[0]; col++)
      if (matrix[row][col] == 0)
        set[row][col] = 1;

  for (int row = 0; row < matrixSize; row++)
  {
    for (int col = 0; col < matrixColSize[0]; col++)
    {
      if (set[row][col] == 1)
      {
        //Row traverse
        for (int r = 0; r < matrixSize; r++)
          matrix[r][col] = 0;

        //Col traverse
        for (int c = 0; c < matrixColSize[0]; c++)
          matrix[row][c] = 0;
      }
    }
  }

  for (int i = 0; i < matrixSize; i++)
    free(set[i]);
  free(set);
}
