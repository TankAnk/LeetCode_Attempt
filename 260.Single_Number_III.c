/*
- Ex: [1 1 2 2 3 10] -> x = 3, y = 10
- After XOR the arr, we get 1001 = x XOR y
- From 1001 (based 0, from right to left or LSB to MSB):
  + bit 0 = 1 -> x and y have different value of bit 0
  + bit 1 = 0 -> x and y have the equal value of bit 1
  //And so on

- Choose bit 0 (with value 1) to separate arr into 2 groups:
  + Numbers with bit 0 = 1: 1 1 3
  + Numbers with bit 0 = 0: 2 2 10
  + XOR 1st group -> 3 left
  + XOR 2nd group -> 10 left
*/

int *singleNumber(int *nums, int numsSize, int *returnSize)
{
  *returnSize = 2;
  int *result = malloc(*returnSize * sizeof(*result));

  unsigned int arr_xor = 0;
  for (int i = 0; i < numsSize; i++)
    arr_xor ^= (unsigned int)nums[i];

  //Extract bit from LSB to MSB to find first bit with value 1
  int bit = -1;
  for (unsigned int i = 0, mask = 1u; i < sizeof(unsigned int) * CHAR_BIT && bit == -1; i++, mask <<= 1)
  {
    if (arr_xor & mask)
      bit = (int)i;
  }

  //XOR array in 2 groups
  //x for bit group 0, y for bit group 1
  int x = 0, y = 0;
  unsigned int mask = 1u << (unsigned int)bit;

  for (int i = 0; i < numsSize; i++)
  {
    if (!(nums[i] & mask))
      x ^= nums[i];

    else
      y ^= nums[i];
  }

  result[0] = x;
  result[1] = y;

  return result;
}
