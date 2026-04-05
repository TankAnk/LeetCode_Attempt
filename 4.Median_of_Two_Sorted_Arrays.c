#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *merge_array(int *a1, int size1, int *a2, int size2)
{
	if (size1 == 0) return a2;
	if (size2 == 0) return a1;
	
	int *a = malloc((size1 + size2) * sizeof(*a));
	memcpy(a, a1, size1 * sizeof(*a));
	memcpy(a + size1, a2, size2 * sizeof(*a));
	
	return a; 
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
	
	//Atp either left or right is empty
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
		int m = (l + r - 1) / 2;
		merge_sort(a, l, m);
		merge_sort(a, m + 1, r);
		merge(a, l, m, r);
	}
}


double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size)
{
	int *result = merge_array(nums1, nums1Size, nums2, nums2Size);
	int size = nums1Size + nums2Size;
	merge_sort(result, 0, size - 1);
	
	if (size % 2 != 0) return (double) result[size / 2];
	else return ((result[size / 2] + result[size / 2 - 1]) / 2.0);   
}

int main()
{
	int nums1[] = {1, 2}, nums2[] = {3, 4};
	int s1 = sizeof(nums1)/sizeof(nums1[0]);
	int s2 = sizeof(nums2)/sizeof(nums2[0]);
	
	int *a = merge_array(nums1, s1, nums2, s2);
	merge_sort(a, 0, s1 + s2 - 1);
	
	printf("[ ");
	for (int i = 0; i < s1 + s1; i++)
		printf("%d ", a[i]);
	printf("]\n");
	
	printf("%f\n", findMedianSortedArrays(nums1, s1, nums2, s2));
	return 0;
}
