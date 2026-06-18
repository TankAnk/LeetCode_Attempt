int largestRectangleArea(int* heights, int heightsSize)
{
  if (heightsSize == 1)
    return heights[0];

  int result = 0, stack_idx = -1, i = 0, width, area, top;
  int stack[heightsSize];

  while (i < heightsSize)
  {
    if (stack_idx < 0 || heights[i] >= heights[stack[stack_idx]])
      stack[++stack_idx] = i++;

    else
    {
      top = stack[stack_idx--];
      width = (stack_idx < 0) ? i : i - stack[stack_idx] - 1;
      area = width * heights[top];
      if (result < area)
        result = area;
    }
  }

  while (stack_idx >= 0)
  {
    top = stack[stack_idx--];
    width = (stack_idx < 0) ? i : i - stack[stack_idx] - 1;
    area = width * heights[top];
    if (result < area)
      result = area;
  }

  return result;
}
