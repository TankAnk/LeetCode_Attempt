bool isOneEditDistance(char *s, char *t)
{
  int s_len = strlen(s), t_len = strlen(t);
  //Make sure s is always the longer string -> Only have to handle delete
  if (s_len < t_len)
    return isOneEditDistance(t, s);

  if (s_len - t_len > 1)
    return false;

  int diff_idx = 0;
  while (diff_idx < t_len && s[diff_idx] == t[diff_idx])
    diff_idx++;

  //No difference -> true if s has 1 char left to delete
  if (diff_idx == t_len)
    return (s_len == t_len + 1);

  int remain = t_len - diff_idx;
  //Equal length -> Replace -> true if the rest is match
  if (s_len == t_len)
    return (memcmp(s + diff_idx + 1, t + diff_idx + 1, remain * sizeof(*s)) == 0);

  //Diff by 1 -> Delete -> Skip 1 char from s, compare the rest
  return (memcmp(s + diff_idx + 1, t + diff_idx, remain * sizeof(*s)) == 0);
}
