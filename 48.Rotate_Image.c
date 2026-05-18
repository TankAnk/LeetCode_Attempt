#include <stdio.h>
#include <stdlib.h>

/*
  90 = transpose + reverse row
  180 = reverse row + reverse column
  270 = transpose + reverse col
*/

void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void rotate(int** matrix, int matrixSize, int* matrixColSize) {
  matrixColSize = malloc(matrixSize * sizeof(*matrixColSize));
  for (int i = 0; i < matrixSize; i++)
    matrixColSize[i] = matrixSize;
  
  //Transpose
  for (int row = 0; row < matrixSize - 1; row++)
    for (int col = row + 1; col < matrixSize; col++)
      swap(&matrix[row][col], &matrix[col][row]);

  //Reverse
  for (int row = 0; row < matrixSize; row++)
    for (int col = 0; col < matrixSize / 2; col++)
      swap(&matrix[row][col], &matrix[row][matrixSize - col - 1]);
}

int main()
{
  int matrixSize = 4;
  int *matrixColSize = NULL;

  int **matrix = malloc(matrixSize * sizeof(*matrix));

  for (int i = 0; i < matrixSize; i++)
      matrix[i] = malloc(matrixSize * sizeof(**matrix));

  int values[4][4] = {
    {5,1,9,11},
    {2,4,8,10},
    {13,3,6,7},
    {15,14,12,16}
    };

  for (int i = 0; i < matrixSize; i++)
  {
      for (int j = 0; j < matrixSize; j++)
      {
          matrix[i][j] = values[i][j];
      }
  }

  rotate(matrix, matrixSize, matrixColSize);

  for (int i = 0; i < matrixSize; i++)
  {
      for (int j = 0; j < matrixSize; j++)
      {
          printf("%d ", matrix[i][j]);
      }
      printf("\n");
  }

  for (int i = 0; i < matrixSize; i++)
    free(matrix[i]);

  free(matrix);

    return 0;
}
