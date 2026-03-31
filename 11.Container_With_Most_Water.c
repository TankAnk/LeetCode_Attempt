#include <stdio.h>

//Height = height[i]
//width = last index - first index

int maxArea(int* height, int heightSize)
{
/*
    int i, j, h, w, max = 0;
    for (i = 0; i < heightSize - 1; i++)
    {
        for (j = i + 1; j < heightSize; j++)
        {
            h = (height[i] < height[j]) ? height[i] : height[j];
            w = j - i;
            if (h*w > max) max = h*w;
            //printf("i: %d j: %d h: %d w: %d max: %d\n", i, j, h, w, max);
        }
    }
*/
    int h, w, i = 0, j = heightSize - 1, max = 0;
    while (i < j)
    {
        h = (height[i] < height[j]) ? height[i] : height[j];
        w = j - i;
        if (h*w > max) max = h*w;
        if (height[i] < height[j]) i++;
        else j--;
    }
    return max;
}

int main()
{
    int height[] = {1,8,6,2,5,4,8,3,7};
    printf("%d\n", maxArea(height, sizeof(height)/sizeof(*height)));

    return 0;
}