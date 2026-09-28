/*
  1 0 1 0 0 1 0 0
  1 0 1 0 0 1 0 1
  1 0 1 0 0 1 1 0
  1 0 1 0 0 1 1 1

  1 0 1 0 1 0 0 0
  1 0 1 0 1 0 0 1
  1 0 1 0 1 0 1 0
  1 0 1 0 1 0 1 1
  1 0 1 0 1 1 0 0
  1 0 1 0 1 1 0 1
  1 0 1 0 1 1 1 0
  1 0 1 0 1 1 1 1

  1 0 1 1 0 0 0 0
  1 0 1 1 0 0 0 1
  1 0 1 1 0 0 1 0
  1 0 1 1 0 0 1 1 //
  1 0 1 1 0 1 0 0
  1 0 1 1 0 1 0 1
  1 0 1 1 0 1 1 0
  1 0 1 1 0 1 1 1
  1 0 1 1 1 0 0 0 //
  1 0 1 1 1 0 0 1
  1 0 1 1 1 0 1 0
  1 0 1 1 1 0 1 1
  1 0 1 1 1 1 0 0
  1 0 1 1 1 1 0 1
  1 0 1 1 1 1 1 0
  1 0 1 1 1 1 1 1

  1 1 0 0 0 0 0 0

  Approach: For every bit from LBS to MSB, based 0:
  - If the current bit is 0, the corresponding bit of the result is 0
  - If the current bit is 1:
  + Check if the current bit will change in range [left, right]
  + If it changes, the corresponding bit of the result is 0
  + Else, the corresponding bit of the result is 1

  Observation: From LSB to MSB, based 0:
  - 0th bit: change every 2^0 time
  - 1th bit: change every 2^1 time - 2^0 time if 0th bit is setted
  - 2th bit: change every 2^2 time - 2^1 time if 1th bit is setted - 2^0 time if the 0th bit is setted
  - 3th bit: change every 2^3 time - 2^2 time if 2th bit is setted - 2^1 time of 1th bit is setted - 2^0 time if 0th bit is setted
  - nth bit: change every 2^n time - 2^(n - 1) time if (n-1)th bit is setted - 2^(n - 1) time if the (n - 2)th bit is setted - ... - 2^1 time if the 1th bit is setted - 2^0 time if the 0th bit is setted
*/

int rangeBitwiseAnd(int left, int right)
{
  // If the range contains only one number, its AND is the number itself
  if (left == right)
    return left;

  int result = 0;

  // Distance between the two ends of the range
  int diff = right - left;

  // Cumulative contribution of the lower bits to the current bit's position
  int deduct = 0;

  unsigned int pow = 1;

  // Mask used to set bit i in result
  unsigned int mask = 1;

  // Compute the actual total number of bits in an int (it's always 32 in LeetCode btw)
  int total_bits = sizeof(int) * CHAR_BIT;

  for (int i = 0; i < total_bits; i++)
  {
    // If the current bit is 0, the result bit must also be 0 -> no need to change
    if (left & 1)
    {
      /*
       * The current bit is 1 in left.
       *
       * pow represents the full cycle length of this bit.
       * deduct represents how much of that cycle has already been
       * consumed by the lower bits.
       *
       * If the range is shorter than the remaining distance before
       * this bit changes, the bit stays 1 throughout [left, right].
       * Therefore, this bit survives in the AND result.
       */
      if (diff < (pow - deduct))
        result |= mask;

      /*
       * Add the current bit's cycle length to the cumulative deduction.
       * This allows the next higher bit to account for the position
       * represented by all lower bits.
       */
      deduct += pow;
    }

    // Move to the next bit's cycle length: 1, 2, 4, 8, 16, ...
    pow *= 2;

    // Move the result mask to the next bit: 0001, 0010, 0100, ...
    mask <<= 1;

    // Move the current bit of the original left value into bit 0.
    // This allows (left & 1) to inspect the next bit on the next iteration.
    left >>= 1;
  }

  return result;
}
