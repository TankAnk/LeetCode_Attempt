int* plusOne(int* digits, int digitsSize, int* returnSize)
{
  int carry = 1;
  *returnSize = digitsSize;
  for (int i = digitsSize - 1; i >= 0; i--)
  {
    digits[i] += carry;
    carry = digits[i] / 10;
    digits[i] %= 10;
  }

  if (carry == 0)
    return digits;

  (*returnSize)++;
  int *result = malloc(*returnSize * sizeof(*result));
  memcpy(result + 1, digits, digitsSize * sizeof(*result));
  result[0] = carry;

  return result;
}
