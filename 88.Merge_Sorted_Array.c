void merge(int* nums1, int nums1Size, int m, int* nums2, int nums2Size, int n)
{
  if (n == 0)
    return;

  if (m == 0)
  {
    memcpy(nums1, nums2, n * sizeof(*nums1));
    return;
  }

  int tmp[m];
  for (int i = 0; i < m; i++)
    tmp[i] = nums1[i];

  int i = 0, j = 0, k = 0;
  while (i < m && j < n)
  {
    if (tmp[i] <= nums2[j])
      nums1[k++] = tmp[i++];
    else
      nums1[k++] = nums2[j++];
  }

  while (i < m)
    nums1[k++] = tmp[i++];
  while (j < n)
    nums1[k++] = nums2[j++];
}
