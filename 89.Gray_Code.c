int solve(int n, int total, int *result, int idx, int curr, int *visited)
{
  if (idx == total)
    return 1;

  for (int i = 0; i < n; i++)
  {
    int next = curr ^ (1 << i); //Toggle LSB
    if (!visited[next])
    {
      visited[next] = 1;
      result[idx] = next;

      if (solve(n, total, result, idx + 1, next, visited))
        return 1;

      visited[next] = 0;
    }
  }

  return 0;
}

int* grayCode(int n, int* returnSize)
{
  *returnSize = 1 << n;
  int *result = malloc(*returnSize * sizeof(*result));
  result[0] = 0;

  int *visited = malloc(*returnSize * sizeof(*visited));
  memset(visited, 0, *returnSize * sizeof(*visited));
  visited[0] = 1;

  solve(n, *returnSize, result, 1, 0, visited);
  free(visited);
  return result;
}

/*n = 3
000
001
011
010
110
111
101
100
*/
