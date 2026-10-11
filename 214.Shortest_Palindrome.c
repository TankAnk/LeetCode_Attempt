/*
1. Find the longest prefix that is already a palindrome
2. Reverse the remaining suffix and add to the start of the string

Ex: abcd
-> Longest prefix that is already a palindrome: a
-> Reverse "bcd" and add to the start: dcb|a|bcd

Ex: aacecaaa
-> Longest prefix that is already a palindrome: aacecaa
-> Reverse "a" and add to the start: aaacecaaa

Ex: antartica
-> Longest prefix that is already a palindrome: a
-> Reverse "ntartica" and add to the start: acitratn|a|ntartica

Ex: racecar
-> It's already a palindrome

3. But how to find the lognest palindrome prefix?
The longest palindrome prefix of s = The longest prefix of s, which is also a suffix of the reversed of s
Ex:
s:          a b a c
reversed s: c a b a

s prefixes:
a
ab
aba

reversed s suffixes:
a
ba
aba
-> aba is the longest prefix that is also a suffix

4. But how to determine the longest prefix of s which is also a suffix of reversed s?
- Use KMP algorithm, with lps[i] = length of the longest proper prefix of x[0..i] that is also a suffix of x[0..i]
- Because lsp help to detect prefix and suffix WITHIN THE SAME STRING, NOT 2 SEPARATED ONES, we have to combine: s + "#"(seperator as a boundary) + reversed s
- The last LPS value gives the length of the longest palindromic prefix of s
*/

int *build_lsp(char *str, int str_len)
{
  /*
  lps[i]: the length of the longest proper prefix of s[0..i] that is also a suffix of s[0..i]
  */

  /*
    idx: the index of the character whose LPS value need to be calculated. Start at 1 because the substring containing only s[0] cannot have a non-empty proper prefix
    len: length of the prefix that currently matches a suffix of the substring processed so far.
  */
  int idx = 1, len = 0;
  int *lsp = malloc(str_len * sizeof(*lsp));
  lsp[0] = 0;

  while (idx < str_len)
  {
    /*
      If the current character matches the character immediately after the matching prefix, extend the match by one
    */
    if (str[idx] == str[len])
    {
      len++;
      lsp[idx++] = len;
    }

    /*
      If the characters do not match and no prefix to fall back to, there is no non-empty proper prefix that is also a suffix.
    */
    else if (len == 0)
      lsp[idx++] = 0;

    /*
      If the characters do not match but len > 0, try a shorter prefix
      lps[len - 1] = the length of the next shorter prefix that could still match a suffix
      This avoids restarting the search from the beginning
    */
    else
      len = lsp[len - 1];

    /*
      Do NOT increment idx
      We still need to compare s[idx] with the character at the new prefix position, because a shorter match might still work.
    */
  }

  return lsp;
}

char *shortestPalindrome(char *s)
{
  int s_len = strlen(s);

  // Combine s + "#" + reversed s
  char *combined = malloc((2*s_len + 2) * sizeof(*combined));
  memcpy(combined, s, s_len * sizeof(*combined));
  combined[s_len] = '#';
  for (int i = 0; i < s_len; i++)
    combined[s_len + 1 + i] = s[s_len - 1 - i];
  combined[2*s_len + 1] = '\0';

  // Find the longest palindrome prefix
  int *lsp = build_lsp(combined, 2*s_len + 1);

  // Caculate the no of char to append
  int add = s_len - lsp[2*s_len];
  free(lsp);

  // Return s if it's aleady palindrome
  if (add == 0)
    return s;

  // Reallocate to store result
  combined = realloc(combined, (add + s_len + 1) * sizeof(*combined));

  // Copy from the end of s to be beginning
  for (int i = 0; i < add; i++)
    combined[i] = s[s_len - 1 - i];

  // Copy the oroginal string to the rest of the result
  memcpy(combined + add, s, (s_len + 1) * sizeof(*combined));

  return combined;
}
