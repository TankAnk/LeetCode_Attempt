#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str_merge(char *str, int left, int mid, int right)
{
  int s1 = mid - left + 1, s2 = right - mid;
  char s_left[s1], s_right[s2]; 
  for (int i = 0; i < s1; i++)
    s_left[i] = str[left + i];
  for (int j = 0; j < s2; j++)
    s_right[j] = str[mid + 1 + j];

  int i = 0, j = 0, k = left;
  while (i < s1 && j < s2)
  {
    if (s_left[i] <= s_right[j])
      str[k++] = s_left[i++];
    else
      str[k++] = s_right[j++];
  }

  while (i < s1)
    str[k++] = s_left[i++];
  while (j < s2)
    str[k++] = s_right[j++];
}

void str_merge_sort(char *str, int left, int right)
{
  if (left < right)
  {
    int mid = left + (right - left) / 2;
    str_merge_sort(str, left, mid);
    str_merge_sort(str, mid + 1, right);
    str_merge(str, left, mid, right);
  }
}

void solve(char **strs, int strsSize, int *returnSize, int **returnColumnSizes, char **sorted, char ****result, int *capacity, int *result_idx)
{
  int *used = calloc(strsSize, sizeof(*used));
  for (int i = 0; i < strsSize; i++)
  {
    if (*result_idx >= *capacity)
    {
      (*capacity) *= 2;
      *result = realloc(*result, *capacity * sizeof(**result));
      *returnColumnSizes = realloc(*returnColumnSizes, *capacity * sizeof(**returnColumnSizes));
    }

    int count = 0, curr_len = strlen(strs[i]);
    int *is_anagram = calloc(strsSize - i, sizeof(*is_anagram));
    
    for (int j = i; j < strsSize; j++)
    {
      if (!used[j] && strcmp(sorted[i], sorted[j]) == 0)
      {
        count++;
        is_anagram[j - i] = 1;
        used[j] = 1;
      }
    }

    if (count > 0)
    {
      (*result)[*result_idx] = malloc(count * sizeof(***result));
      for (int k = 0, m = 0; k < strsSize - i && m < count; k++)
      {
        if (is_anagram[k])
        {
          (*result)[*result_idx][m] = malloc((curr_len + 1) * sizeof(****result));
          memcpy((*result)[*result_idx][m++], strs[k + i], curr_len + 1);
        }
      }    

      (*result_idx)++;
      (*returnColumnSizes)[*returnSize] = count;
      (*returnSize)++;
    }
    
    free(is_anagram);
  }
}

/*
0 {"bat", "tab"}
1 {"tea", "eat", "ate"}
2 {"nat", "tan"}
*/
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
  *returnSize = 0;
  int capacity = 150;
  char ***result = malloc(capacity * sizeof(**result));  
  *returnColumnSizes = malloc(capacity * sizeof(**returnColumnSizes));
  char **sorted = malloc(strsSize * sizeof(*sorted));
  for (int i = 0; i < strsSize; i++)
  {
    int curr_len = strlen(strs[i]);
    sorted[i] = malloc((curr_len + 1) * sizeof(**sorted));
    memcpy(sorted[i], strs[i], curr_len + 1);
    str_merge_sort(sorted[i], 0, curr_len - 1);
  }
  int result_idx = 0;
  solve(strs, strsSize, returnSize, returnColumnSizes, sorted, &result, &capacity, &result_idx);
  for (int i = 0; i < strsSize; i++)
    free(sorted[i]);
  free(sorted);
  return result;
}

int main()
{
  char str[] = "cgead";
  str_merge_sort(str, 0, strlen(str) - 1);
  printf("%s\n", str);
  return 0;
}
