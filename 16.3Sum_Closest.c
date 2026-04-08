#include <stdio.h>
#include <stdlib.h>

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
        int m = (l + r) / 2;
        merge_sort(a, l, m);
        merge_sort(a, m + 1, r);
        merge(a, l, m, r);
    }
}

int threeSumClosest(int* nums, int numsSize, int target) {
    merge_sort(nums, 0, numsSize - 1);
    int left, right, cur_diff;
    int sum = nums[0] + nums[1] + nums[2];
    int diff = (sum - target > 0) ? sum - target : target - sum;
    int result = sum;
    
    printf("[ ");
    for (int z = 0; z < numsSize; z++)
        printf("%d ", z);
    printf("]\n");
    
    printf("[ ");
    for (int z = 0; z < numsSize; z++)
        printf("%d ", nums[z]);
    printf("]\n");
    
    for (int i = 0; i < numsSize - 2; i++)
    {
        left = i + 1;
        right = numsSize - 1;
        printf("i: %d\n", i);
        
        while (left < right)
        {
            sum = nums[i] + nums[left] + nums[right];
            cur_diff = (sum - target > 0) ? sum - target : target - sum;
            printf("    Before: left: %d, right: %d, sum: %d, diff: %d, target: %d, result = %d\n", left, right, sum, diff, target, result);
            
            if (cur_diff == 0)
                return target;
            
            else
            {
                if (cur_diff < diff)
                {
                    diff = cur_diff;
                    result = sum;
                }
                
                if (sum < target)
                    left++;
            
                else
                    right--;
            }
            
            printf("    After: left: %d, right: %d, sum: %d, diff: %d, target: %d, result = %d\n", left, right, sum, diff, target, result);
        }
    }
        
    return result;
}

int main()
{
    int a[] = {-1, 1, 0, 2, -4};
    printf("%d\n", threeSumClosest(a, sizeof(a)/sizeof(*a), 1));
    
    return 0;
}