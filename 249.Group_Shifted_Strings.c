/**
 * Return an array of arrays of strings.
 * The sizes of the arrays are returned via returnSize and * returnColumnSizes.
 * Note: Both returned arrays must be malloced.
 */

/*
  a b c d e f g h i j k l m n o p q r s t u v w x y z

  Input: strings = ["abc","bcd","acef","xyz","az","ba","a","z"]
  Output: [["acef"],["a","z"],["abc","bcd","xyz"],["az","ba"]]
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

char ***groupStrings(char **strings, int stringsSize, int *returnSize, int **returnColumnSizes)
{
  *returnSize = 0;
  char ***result = malloc(stringsSize * sizeof(*result));
  *returnColumnSizes = malloc(stringsSize * sizeof(**returnColumnSizes));
  bool used[stringsSize];
  memset(used, 0, stringsSize * sizeof(*used));
  int lens[stringsSize];
  for (int i = 0; i < stringsSize; i++)
    lens[i] = strlen(strings[i]);

  for (int i = 0; i < stringsSize; i++)
  {
    if (used[i])
      continue;

    int matched_cnt = 1;
    bool matched_idx[stringsSize];
    memset(matched_idx, 0, stringsSize * sizeof(*matched_idx));
    matched_idx[i] = true;

    for (int j = 0; j < stringsSize; j++)
    {
      if (used[j] || i == j || lens[i] != lens[j])
        continue;

      bool matched = true;
      int diff = (strings[i][0] - strings[j][0] + 26) % 26;
      for (int k = 1; k < lens[i] && matched; k++)
        if ((strings[i][k] - strings[j][k] + 26) % 26 != diff)
          matched = false;

      if (matched)
      {
        matched_idx[j] = true;
        matched_cnt++;
      }
    }

    (*returnColumnSizes)[*returnSize] = matched_cnt;
    result[*returnSize] = malloc(matched_cnt * sizeof(**result));
    for (int k = 0; k < stringsSize && matched_cnt > 0; k++)
    {
      if (!matched_idx[k])
        continue;

      used[k] = true;
      result[*returnSize][matched_cnt - 1] = malloc((lens[k] + 1) * sizeof(***result));
      memcpy(result[*returnSize][matched_cnt - 1], strings[k], (lens[k] + 1) * sizeof(***result));
      matched_cnt--;
    }

    (*returnSize)++;
  }

  return result;
}

int main(void) {

  /*
    char* strings[] = {
    "abc", "bcd", "acef", "xyz", "az",
    "ba", "a", "z", "aa", "bb", "acs"
    };
  */

  /*
    char* strings[] = {
    "abc", "bcd", "cde",
    "nop", "opq",
    "az", "ba", "yx",
    "a", "z", "m",
    "aa", "bb", "cc",
    "ace", "bdf",
    "abcd", "bcde",
    "hello", "world"
    };
  */

  char* strings[] = {
    "abc", "bcd", "xyz", "yza",
    "az", "by", "cx",
    "za", "ab", "bc",
    "a", "b", "c", "z",
    "aaa", "bbb", "ccc",
    "ace", "bdf", "ceg",
    "abcd", "bcde", "cdef",
    "mnop", "qrst",
    "leetcode", "geeksforgeeks"
  };

  int stringsSize = sizeof(strings) / sizeof(strings[0]);

  int returnSize = 0;
  int* returnColumnSizes = NULL;

  char*** result = groupStrings(
    strings,
    stringsSize,
    &returnSize,
    &returnColumnSizes
    );

  // Print the grouped strings
  printf("Number of groups: %d\n\n", returnSize);

  for (int i = 0; i < returnSize; i++) {
    printf("Group %d: [", i + 1);

    for (int j = 0; j < returnColumnSizes[i]; j++) {
      printf("\"%s\"", result[i][j]);

      if (j < returnColumnSizes[i] - 1) {
        printf(", ");
      }
    }

    printf("]\n");
  }

  // Free allocated memory
  for (int i = 0; i < returnSize; i++) {
    for (int j = 0; j < returnColumnSizes[i]; j++) {
      free(result[i][j]);
    }
    free(result[i]);
  }

  free(result);
  free(returnColumnSizes);

  return 0;
}
