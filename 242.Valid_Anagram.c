void merge(char *s, int left, int mid, int right)
{
  int left_size = mid - left + 1;
  int right_size = right - mid;
  char left_s[left_size];
  char right_s[right_size];

  for (int i = 0; i < left_size; i++)
    left_s[i] = s[left + i];

  for (int i = 0; i < right_size; i++)
    right_s[i] = s[mid + 1 + i];

  int i = 0, j = 0, k = left;
  while (i < left_size && j < right_size)
  {
    if (left_s[i] <= right_s[j])
      s[k++] = left_s[i++];

    else
      s[k++] = right_s[j++];
  }

  while (i < left_size)
    s[k++] = left_s[i++];
}

void merge_sort(char *s, int left, int right)
{
  if (left < right)
  {
    int mid = (right - left) / 2 + left;
    merge_sort(s, left, mid);
    merge_sort(s, mid + 1, right);
    merge(s, left, mid, right);
  }
}

bool isAnagram(char *s, char *t)
{
  int s_len = strlen(s);
  int t_len = strlen(t);

  if (s_len != t_len)
    return false;

  merge_sort(s, 0, s_len - 1);
  merge_sort(t, 0, t_len - 1);

  return (strcmp(s, t) == 0);
}
