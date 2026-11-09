/*
O(n) time & O(1) space (result array does not count in the space complexity)
No division operator
1 2 3 4 5 -> 120 60 40 30 24

First idea (Incorrect):
nums[i] = nums[i] * nums[i - 1] -> 1 2 6 12 20
nums[i] = nums[i] * nums[i + 1] -> 2 6 12 20 5
nums[i] = nums[i - 1] * nums[i + 1] -> 2 3 8 15 4
nums[i] = nums[i] * nums[i - 1] * nums[i + 1] -> 2 6 24 60 20
nums[i] = cumulative * nums[i + 1] -> 2 6 24 120 120

0 1 2 3 4
1 2 3 4 5
i = 0
  Left Product: 1
  Right Product: 120
  answer[i] = 120

i = 1
  Left Product: 1
  Right Product: 60
  answer[i] = 60

i = 2
  Left Product: 2
  Right Product: 20
  answer[i] = 40

Left Product use * -> Okay
Right Product use / -> Reject -> use result filled w/ pre-calculated Right Product?
nums =   1   2  3  4 5
result = 120 60 20 5 1
*/

int *productExceptSelf(int *nums, int numsSize, int *returnSize)
{
  *returnSize = numsSize;
  int *result = malloc(numsSize * sizeof(*result));

  /*
  - Calculate product of all elements to the right of the current element and put into result array.
  - result[i] = nums[i + 1] * nums[i + 2] *...* nums[numsSize - 1].
  */
  for (int i = numsSize - 1; i >= 0; i--)
    result[i] = (i == numsSize - 1) ? 1 : nums[i + 1] * result[i + 1];

  // result[0] is the product of all elemnts from 1 to numsSize - 1.
  if (result[0] == 1 && nums[0] == 1)
    return result;

  /*
  - left_product keep track of the product of all elements to the left of the current element.
  - left_product at index i = nums[0] * nums[1] *...* nums[i - 1].
  */
  int left_product = 1;
  for (int i = 0; i < numsSize; i++)
  {
    left_product = (i == 0) ? 1 : left_product * nums[i - 1];
    result[i] = result[i] * left_product;
  }

  return result;
}
