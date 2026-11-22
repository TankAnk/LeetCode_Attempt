/*
- There are n houses in a row, and each house can be painted with one of the three colors: red, blue, or green. The cost of painting each house with a certain color is different.
- You have to paint all the houses such that no two adjacent houses have the same color.
- The cost of painting each house with a certain color is represented by an n x 3 matrix costs, where:
+ costs[i][0] is the cost of painting house i red.
+ costs[i][1] is the cost of painting house i blue.
+ costs[i][2] is the cost of painting house i green.
- Return the minimum cost to paint all houses.

Example 1:
Input: costs = [[17,2,17],[16,16,5],[14,3,19],[5,9,2]]
Output: 10
Explanation: Paint house 0 blue, house 1 green, house 2 blue and house 3 green. The total cost is 2 + 5 + 3 + 2 = 12.

Example 2:
Input: costs = [[1,2,3],[1,2,3]]
Output: 3

Example 3:
Input: costs = [[1,2,3]]
Output: 1

Constraints:
- costs.length == n
- 1 <= n <= 100
- costs[i].length == 3
- 1 <= costs[i][j] <= 20
*/

/*
- prev_color:
+ 0: The previous house was painted red.
+ 1: The previous house was painted blue.
+ 2: The previous house was painted green.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END_VALUE 5001

int solve(int **costs, int row_size, int house_idx, int prev_color, int **memo)
{
  if (house_idx >= row_size)
    return 0;

  if (memo[house_idx][prev_color] != -1)
    return memo[house_idx][prev_color];

  int val = END_VALUE;

  // Paint the house red.
  if (house_idx == 0 || prev_color != 0)
  {
    int red = costs[house_idx][0] + solve(costs, row_size, house_idx + 1, 0, memo);
    val = (val < red) ? val : red;
  }

  // Paint the house blue.
  if (house_idx == 0 || prev_color != 1)
  {
    int blue = costs[house_idx][1] + solve(costs, row_size, house_idx + 1, 1, memo);
    val = (val < blue) ? val : blue;
  }

  // Paint the house green.
  if (house_idx == 0 || prev_color != 2)
  {
    int green = costs[house_idx][2] + solve(costs, row_size, house_idx + 1, 2, memo);
    val = (val < green) ? val : green;
  }
  //printf("Idx: %d, Pre: %d, Val: %d\n", house_idx, prev_color, val);
  memo[house_idx][prev_color] = val;
  return memo[house_idx][prev_color];
}

int minCost(int **costs, int costsSize, int *costsColSize)
{
  // memo[current house index][color of previous house];
  int **memo = malloc(costsSize * sizeof(*memo));
  for (int i = 0; i < costsSize; i++)
  {
    memo[i] = malloc(costsColSize[0] * sizeof(**memo));
    for (int j = 0; j < costsColSize[0]; j++)
      memo[i][j] = -1;
  }

  int result = solve(costs, costsSize, 0, 0, memo);

  for (int i = 0; i < costsSize; i++)
    free(memo[i]);
  free (memo);

  return result;
}

void runTest(int data[][3], int rows, int expected, int testNo)
{
    int *costs[rows];
    int costsColSize[rows];

    for (int i = 0; i < rows; i++)
    {
        costs[i] = data[i];
        costsColSize[i] = 3;
    }

    int result = minCost(costs, rows, costsColSize);

    printf("Test %d: Expected = %d | Got = %d | %s\n",
           testNo, expected, result,
           result == expected ? "PASS" : "FAIL");
}

int main(void)
{
  int data1[][3] = {
    {1, 2, 3},
    {1, 2, 3}
  };

  int data2[][3] = {
    {17, 2, 17},
    {16, 16, 5},
    {14, 3, 19}
  };

  int data3[][3] = {
    {7, 3, 5}
  };

  int data4[][3] = {
    {5, 5, 5},
    {5, 5, 5},
    {5, 5, 5}
  };

  int data5[][3] = {
    {1, 10, 10},
    {10, 1, 10},
    {1, 10, 10},
    {10, 1, 10}
  };

  int data6[][3] = {
    {1, 2, 100},
    {1, 100, 100},
    {100, 1, 100}
  };

  int data7[][3] = {
    {7, 6, 2},
    {5, 8, 7},
    {3, 4, 6},
    {9, 2, 5},
    {6, 7, 3},
    {4, 5, 8}
  };

  int data8[][3] = {
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1},
    {1, 1, 1}
  };

  runTest(data1, 2, 3, 1);
  runTest(data2, 3, 10, 2);
  runTest(data3, 1, 3, 3);
  runTest(data4, 3, 15, 4);
  runTest(data5, 4, 4, 5);
  runTest(data6, 3, 4, 6);
  runTest(data7, 6, 22, 7);
  runTest(data8, 4, 4, 8);

  return 0;
}
