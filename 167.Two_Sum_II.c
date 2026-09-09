/*1. Hash table - TLE lol
#define TABLE_SIZE 3011

typedef struct Entry
{
  bool occupied;
  int val;
  unsigned int idx;
} Entry;

int *twoSum(int *numbers, int numbersSize, int target, int *returnSize)
{
  *returnSize = 2; //there is exactly 1 solution
  int *result = malloc(*returnSize * sizeof(*result));

  Entry memo[TABLE_SIZE] = {0};

  for (int i = 0; i < numbersSize; i++)
  {
    int complement = target - numbers[i];
    //Probe to find complement
    int com_key = complement % TABLE_SIZE;
    if (com_key < 0)
      com_key += TABLE_SIZE;

    while (memo[com_key].occupied)
    {
      if (memo[com_key].val == complement)
      {
        result[0] = memo[com_key].idx + 1;
        result[1] = i + 1;

        return result;
      }

      com_key = (com_key + 1) % TABLE_SIZE;
    }

    //Probe to find empty slot to insert current entry
    int curr_key = numbers[i] % TABLE_SIZE;
    if (curr_key < 0)
      curr_key += TABLE_SIZE;
    //Skip occupied slots
    while (memo[curr_key].occupied)
      curr_key = (curr_key + 1) % TABLE_SIZE;
    memo[curr_key].occupied = true;
    memo[curr_key].val = numbers[i];
    memo[curr_key].idx = i;
  }

  return result;
}
*/

//Optimized solution with sorted input array
int *twoSum(int *numbers, int numbersSize, int target, int *returnSize)
{
  int left = 0, right = numbersSize - 1;
  int *result;
  *returnSize = 0;

  while (left < right && *returnSize == 0)
  {
    if (target < numbers[left] + numbers[right])
      right--;

    else if (target > numbers[left] + numbers[right])
      left++;

    else
    {
      *returnSize = 2;
      result = malloc(*returnSize * sizeof(*result));
      result[0] = left + 1;
      result[1] = right + 1;
    }
  }

  return result;
}
