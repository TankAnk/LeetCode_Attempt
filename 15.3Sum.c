#include <stdio.h>
#include <stdlib.h>

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
 
 /*
Approach:
    1. Sort the array
    2. Fix one number nums[i]
    3. Use two pointers left and right
    4. Move them based on the sum
 */
 
 void merge(int *a, int l, int m, int r)
 {
    int s1 = m - l + 1, s2 = r - m;
	int i = 0, j = 0, k = l;
	
	int *left = malloc(s1 * sizeof(*left));
	for (int z = 0; z < s1; z++)
		left[z] = a[l + z];
		
	int *right = malloc(s2 * sizeof(*right));
	for (int z = 0; z < s2; z++)
		right[z] = a[m + 1 + z];
        
    while (i < s1 && j < s2)
    {
        if (left[i] < right[j])
        {
            a[k] = left[i];
            i++;
        }
        
        else
        {
            a[k] = right[j];
            j++;
        }
        
        k++;
    }
    
    while (i < s1)
    {
        a[k] = left[i];
        i++;
        k++;
    }
    
    while (j < s2)
    {
        a[k] = right[j];
        j++;
        k++;
    }
    
 }
 
 void merge_sort(int *a, int l, int r)
 {
    if (l < r)
    {
        int m = (r + l - 1) / 2;
        merge_sort(a, l, m);
        merge_sort(a, m + 1, r);
        
        merge(a, l, m, r);
    }
 }
 
void merge(int *a, int l, int m, int r)
 {
    int s1 = m - l + 1, s2 = r - m;
	int i = 0, j = 0, k = l;
	
	int *left = malloc(s1 * sizeof(*left));
	for (int z = 0; z < s1; z++)
		left[z] = a[l + z];
		
	int *right = malloc(s2 * sizeof(*right));
	for (int z = 0; z < s2; z++)
		right[z] = a[m + 1 + z];
        
    while (i < s1 && j < s2)
    {
        if (left[i] < right[j])
        {
            a[k] = left[i];
            i++;
        }
        
        else
        {
            a[k] = right[j];
            j++;
        }
        
        k++;
    }
    
    while (i < s1)
    {
        a[k] = left[i];
        i++;
        k++;
    }
    
    while (j < s2)
    {
        a[k] = right[j];
        j++;
        k++;
    }

    free(left);
    free(right);
    
 }
 
void merge_sort(int *a, int l, int r)
 {
    if (l < r)
    {
        int m = (r + l) / 2;
        merge_sort(a, l, m);
        merge_sort(a, m + 1, r);
        
        merge(a, l, m, r);
    }
 }
 
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes)
{
    *returnSize = 0;
    *returnColumnSizes = NULL;

    if (numsSize < 3)
        return NULL;

    merge_sort(nums, 0, numsSize - 1);

    /* dynamic capacity */
    int capacity = 64;
    int **result = malloc(capacity * sizeof(int *));
    int row = 0;

    for (int i = 0; i < numsSize - 2; i++)
    {
        /* skip duplicate anchor */
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int left = i + 1;
        int right = numsSize - 1;

        while (left < right)
        {
            int sum = nums[i] + nums[left] + nums[right];

            if (sum == 0)
            {
                /* grow capacity if needed */
                if (row == capacity)
                {
                    capacity *= 2;
                    result = realloc(result, capacity * sizeof(int *));
                }

                result[row] = malloc(3 * sizeof(int));
                result[row][0] = nums[i];
                result[row][1] = nums[left];
                result[row][2] = nums[right];
                row++;

                left++;
                right--;

                /* skip duplicate left */
                while (left < right && nums[left] == nums[left - 1])
                    left++;

                /* skip duplicate right */
                while (left < right && nums[right] == nums[right + 1])
                    right--;
            }
            else if (sum < 0)
            {
                left++;
            }
            else
            {
                right--;
            }
        }
    }

    /* no result */
    if (row == 0)
    {
        free(result);
        return NULL;
    }

    *returnSize = row;

    *returnColumnSizes = malloc(row * sizeof(int));
    for (int i = 0; i < row; i++)
        (*returnColumnSizes)[i] = 3;

    return result;
}

int main()
{
    int returnSize;
    int nums[] = {0, 0, 0};
    int *returnColumnSizes;
    int **result = threeSum(nums, sizeof(nums)/sizeof(nums[0]), &returnSize, &returnColumnSizes);
    printf("returnSize = %d\n", returnSize);

    for (int i = 0; i < returnSize; i++)
    {
        printf("[");
        for (int j = 0; j < returnColumnSizes[i]; j++)
        {
            printf("%d", result[i][j]);
            if (j < returnColumnSizes[i] - 1)
                printf(", ");
        }
        printf("]\n");
    }
    
    return 0;
}