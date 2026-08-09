/*
Number that appears 3 times contributes its bits 3 times
[2,2,2,5]
0 1 0
0 1 0
0 1 0
1 0 1
-----
1 3 1 % 3 = 1 0 1 = 5
*/

int singleNumber(int *nums, int numsSize)
{
  int result = 0;
  for (int bit = 0; bit < 32; bit++)
  {
    int cnt = 0;

    for (int i = 0; i < numsSize; i++)
    {
      //Extract nth bit by right shift n times, then AND 1
      int curr_bit = ((unsigned int)nums[i] >> bit) & 1;
      if (curr_bit)
        cnt++;
    }

    //Add bit directly into result
    //Set nth bit to 1 by left shift bitmask 1 n times, then OR
    if (cnt % 3 != 0)
      result |= (1u << bit);
  }

  return result;
}
