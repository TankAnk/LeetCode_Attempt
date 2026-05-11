#include <stdio.h>
#include <stdlib.h>

int trap(int* height, int heightSize) {
  if (heightSize <= 2)
    return 0;
  //Sum of all positve value
  int area = 0, sum = 0;
  for (int i = 0 ; i < heightSize; i++)
    sum += height[i];

  //Find index of max value
  int left = 0, right = 0, max_idx = 0;
  for (int i = left + 1; i < heightSize; i++)
    if (height[i] > height[max_idx])
      max_idx = i; 

  //From left to max value
  while (left < max_idx && right < max_idx)
  {
    while (right < max_idx && height[left] >= height[right])
    {
      area += height[left];
      right++;
    }
    
    left = right;
  }

  //From right to max value
  right = heightSize - 1;
  left = right;
  while (left > max_idx && right > max_idx)
  {
    while (left > max_idx && height[right] >= height[left])
    {
      area += height[right];
      left--;
    }

    right = left;
  }
  
  return (height[max_idx] + area - sum);
}

int main()
{
  int height[] = {0,1,0,2,1,0,1,2,2,1,2,1};
  int heightSize = sizeof(height) / sizeof(*height);
  printf("%d\n", trap(height, heightSize));

  return 0;
}
