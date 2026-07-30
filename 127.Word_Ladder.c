/*
int solve(char *curr, char *end, int wrd_len, char **list, int ls_size, int count, int *visited)
{
  if (strcmp(curr, end) == 0)
    return count;

  int result = ls_size + 2;

  for (int i = 0; i < ls_size; i++)
  {
    if (diff_by_one(curr, list[i], wrd_len) && !visited[i])
    {
      visited[i] = 1;
      int move = solve(list[i], end, wrd_len, list, ls_size, count + 1, visited);
      visited[i] = 0;

      if (move > 0 && move < result)
        result = move;
    }
  }

  return (result == ls_size + 2 ? 0 : result);
}

int ladderLength(char *beginWord, char *endWord, char **wordList, int wordListSize)
{
  int *visited = calloc (wordListSize, sizeof(*visited));
  int result = solve(beginWord, endWord, strlen(endWord), wordList, wordListSize, 1, visited);
  free(visited);
  return result;
}
*/

typedef struct
{
  char *word;
  int dist;
} Node;

#define CAP 5001

bool diff_by_one(char *s1, char *s2, int len)
{
  int cnt = 0;
  for (int i = 0; i < len && cnt < 2; i++)
    if (s1[i] != s2[i])
      cnt++;

  return (cnt == 1);
}

int ladderLength(char *beginWord, char *endWord, char **wordList, int wordListSize)
{
  int len = strlen(endWord);
  int visited[wordListSize];
  memset(visited, 0, wordListSize * sizeof(*visited));

  Node queue[CAP];
  int front = 0, rear = 0;
  queue[rear++] = (Node){beginWord, 1};

  while (front != rear)
  {
    Node curr = queue[front++];

    if (strcmp(curr.word, endWord) == 0)
      return curr.dist;

    for (int i = 0; i < wordListSize; i++)
    {
      if (diff_by_one(wordList[i], curr.word, len) && !visited[i])
      {
        visited[i] = 1;
        queue[rear++] = (Node){wordList[i], curr.dist + 1};
      }
    }
  }

  return 0;
}
