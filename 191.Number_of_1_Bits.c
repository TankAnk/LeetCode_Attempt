/* Attempt 1: Check LSB, shift right
int hammingWeight(int n)
{
  //unsigned int total_bits = sizeof(n) * CHAR_BIT;
  int result = 0;
  while (n > 0)
  {
    result += (1 & n);
    n >>= 1;
  }

  return result;
}
*/

/* Attempt 2: Count the no of bit 1 cleared
n:       1 0 1 1 0 1 0
n - 1:   1 0 1 1 0 0 1
n&(n-1): 1 0 1 1 0 0 0
*/

int hammingWeight(int n)
{
  int result = 0;
  while (n > 0)
  {
    result++;

    // Clear the right most 1 bit
    n &= (n - 1);
  }

  return result;
}
