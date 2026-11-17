/*
Design an iterator to flatten a 2D vector.

Implement the Vector2D class:
- Vector2D(int** vec, int vecSize, int* vecColSize): Initializes the object with the 2D vector vec.
- int next(): Returns the next element from the 2D vector and moves the pointer one position forward.
- bool hasNext(): Returns true if there are still elements in the vector, otherwise returns false.

Constraints:
- 0 <= vec.length <= 200
- 0 <= vec[i].length <= 500
- -500 <= vec[i][j] <= 500
- At most 10^5 calls will be made to next and hasNext.
- There will be at least one element in the 2D vector when next is called.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROWS 200
#define COLS 500
#define NON_EMPTY_ROWS 100

typedef struct Vector2D
{
  int **vec_ptr;
  int row_size;
  int *col_size;
  int row_ptr;
  int col_ptr;

} Vector2D;

Vector2D *vector2DCreate(int **vec, int vecSize, int *vecColSize)
{
  Vector2D *v = malloc(sizeof(*v));

  v->vec_ptr = vec;
  v->row_size = vecSize;
  v->col_size = vecColSize;
  v->row_ptr = 0;
  v->col_ptr = 0;

  return v;
}

bool vector2DHasNext(Vector2D *obj)
{
  if (!obj)
    return false;

  while (obj->row_ptr < obj-> row_size && obj->col_size[obj->row_ptr] == 0)
    (obj->row_ptr)++;

  return (obj->row_ptr < obj->row_size);
}

int vector2DNext(Vector2D *obj)
{
  if (!vector2DHasNext(obj))
    return -4004;

  int result = (obj->vec_ptr)[obj->row_ptr][obj->col_ptr];
  (obj->col_ptr)++;

  if (obj->col_ptr == (obj->col_size)[obj->row_ptr])
  {
    (obj->row_ptr)++;
    obj->col_ptr = 0;
  }

  return result;
}

void vector2DFree(Vector2D *obj)
{
  if (!obj)
    return;

  free(obj);
}

int main(void) {
  /*
  int data[ROWS][COLS];
  int* vec[ROWS];
  int vecColSize[ROWS];

  // Initialize maximum-size 2D vector.
  for (int i = 0; i < ROWS; i++) {
    vec[i] = data[i];
    vecColSize[i] = COLS;

    for (int j = 0; j < COLS; j++) {
      data[i][j] = i * COLS + j;
    }
  }

  // Create iterator.
  Vector2D* iterator = vector2DCreate(vec, ROWS, vecColSize);

  int count = 0;
  bool passed = true;

  // Traverse and validate all 100,000 elements.
  while (vector2DHasNext(iterator)) {

    // hasNext() must not advance the iterator.
    if (!vector2DHasNext(iterator)) {
      passed = false;
      break;
    }

    int actual = vector2DNext(iterator);
    int expected = count;

    if (actual != expected) {
      printf("ERROR at index %d: expected %d, got %d\n",
             count, expected, actual);
      passed = false;
      break;
    }

    count++;
  }

  // Final validation.
  if (count != ROWS * COLS) {
    passed = false;
  }

  if (vector2DHasNext(iterator)) {
    passed = false;
  }

  printf("========== EXTREME TEST ==========\n");
  printf("Rows: %d\n", ROWS);
  printf("Columns per row: %d\n", COLS);
  printf("Expected elements: %d\n", ROWS * COLS);
  printf("Processed elements: %d\n", count);
  printf("Result: %s\n", passed ? "PASSED" : "FAILED");
  printf("==================================\n");

  vector2DFree(iterator);

  return 0;
  */

  int *vec[ROWS];
  int vecColSize[ROWS];

  // Allocate data for only 100 non-empty rows.
  int data[NON_EMPTY_ROWS][COLS];

  int dataIndex = 0;
  int expectedTotal = NON_EMPTY_ROWS * COLS;

  for (int i = 0; i < ROWS; i++)
  {
    // 100 rows is non-empty.
    if (i % 2 == 1)
    {
      vec[i] = data[dataIndex];
      vecColSize[i] = COLS;

      for (int j = 0; j < COLS; j++)
        data[dataIndex][j] = dataIndex * COLS + j;

      dataIndex++;
    }
    else
    {
      vec[i] = NULL;
      vecColSize[i] = 0;
    }
  }

  Vector2D *iterator = vector2DCreate(vec, ROWS, vecColSize);

  int count = 0;
  bool passed = true;

  while (vector2DHasNext(iterator))
  {
    int actual = vector2DNext(iterator);
    int expected = count;

    if (actual != expected)
    {
      printf("ERROR at index %d: expected %d, got %d\n",
             count, expected, actual);
      passed = false;
      break;
    }

    count++;
  }

  if (count != expectedTotal)
    passed = false;

  if (vector2DHasNext(iterator))
    passed = false;

  printf("========== EMPTY-ROW EXTREME TEST ==========\n");
  printf("Total rows:       %d\n", ROWS);
  printf("Non-empty rows:   %d\n", NON_EMPTY_ROWS);
  printf("Empty rows:       %d\n", ROWS - NON_EMPTY_ROWS);
  printf("Elements per row: %d\n", COLS);
  printf("Expected elements: %d\n", expectedTotal);
  printf("Processed elements: %d\n", count);
  printf("Result: %s\n", passed ? "PASSED" : "FAILED");
  printf("============================================\n");

  vector2DFree(iterator);

  return 0;
}
