#include <stdio.h>
/* Constraints:
nums1.length == m
nums2.length == n
0 <= m <= 1000
0 <= n <= 1000
1 <= m + n <= 2000
-10^6 <= nums1[i], nums2[i] <= 10^6

Algorithm: Check if
	- Total elements on the left side = total elements on the right side
	- Every element on left <= every element on right
*/

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    double median;
}

int main()
{
	int nums1[2] = {0, 2, 3, 7, 8, 16, 17};
	int nums2[1] = {0, 1, 3, 8, 14};
	// 0 1 2 3 7 8 14 16 17
	int s1 = sizeof(nums1)/sizeof(nums1[0]);
	int s2 = sizeof(nums2)/sizeof(nums2[0]);
	double result = findMedianSortedArrays(nums1, s1, nums2, s2);
	printf("%.5lf\n", result);

	return 0;
}
