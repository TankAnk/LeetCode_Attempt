#include <stdio.h>
#include <stdlib.h>

void merge(int *a, int l, int m, int r)
{
    int i = 0, j = 0, k = l;
    int s1 = m - l + 1, s2 = r - m;
    
    int *left = malloc(s1 * sizeof(*left));
    for (int z = 0; z < s1; z++)
        left[z] = a[z + l];
        
    int *right = malloc(s2 * sizeof(*right));
    for (int z = 0; z < s2; z++)
        right[z] = a[z + m + 1];
        
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
        int m = (l + r) / 2;
        merge_sort(a, l, m);
        merge_sort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    if (numsSize <= 3)
        return NULL;
    
    merge_sort(nums, 0, numsSize - 1);
    int **result = NULL;
    
    for (int i = 0; i < numsSize - 3; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
            continue;
            
        for (int j = i + 1; j < numsSize - 2; j++)
        {
            if (j > i + 1 && nums[j] == nums[j - 1])
                continue;
                
            int left = j + 1, right = numsSize - 1;
            while (left < right && right < numsSize && left < numsSize && i != left && j != left && i != right && j != right)
            {
                long long sum = (long long) nums[i] + nums[j] + nums[left] + nums[right];
                if (sum == target)
                {
                    (*returnSize)++;
                    result = realloc(result, ((*returnSize) * sizeof(*result)));
                    result[*returnSize - 1] = malloc(4 * sizeof(**result));
                    result[*returnSize - 1][0] = nums[i];
                    result[*returnSize - 1][1] = nums[j];
                    result[*returnSize - 1][2] = nums[left];
                    result[*returnSize - 1][3] = nums[right];
                    
                    while (left < right && nums[left] == nums[left + 1])
                        left++;
                    
                    while (left < right && nums[right] == nums[right - 1])
                        right--;

                    left++;
                    right--;
                }
                
                else if (sum < target)
                    left++;
                    
                else
                    right--;
            }           
        }
    }
    
    if (*returnSize == 0)
        return NULL;
    
    *returnColumnSizes = malloc((*returnSize) * sizeof(**returnColumnSizes));
    for (int i = 0; i < *returnSize; i++)
        (*returnColumnSizes)[i] = 4;
        
    return result;
}

int main()
{
    int nums[] = {2,2,2,2,2};
    int numsSize = sizeof(nums) / sizeof(*nums);
    int target = 8;
    int returnSize, *returnColumnSizes;
    int **result = fourSum(nums, numsSize, target, &returnSize, &returnColumnSizes);
    
    for (int i = 0; i < returnSize; i++)
    {
        for (int j = 0; j < returnColumnSizes[i]; j++)
        {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
