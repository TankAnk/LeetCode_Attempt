#define MAX_SIZE 50021
#define INITIAL_CAPACITY 8

typedef struct Entry
{
  char *str;
  int *idx;
  unsigned size;
  unsigned capacity;
  bool occupied;
} Entry;

typedef struct WordDistance
{
  Entry *table;
} WordDistance;

unsigned long hash(unsigned char *str)
{
  unsigned long hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  return hash;
}

WordDistance *wordDistanceCreate(char **wordsDict, int wordsDictSize)
{
  WordDistance *wd = malloc(sizeof(*wd));
  wd->table = calloc(MAX_SIZE, sizeof(*wd->table));

  // Populate the hash table by traversing every string from input dict.
  for (int i = 0; i < wordsDictSize; i++)
  {
    int len = strlen(wordsDict[i]);
    int key = hash((unsigned char *)wordsDict[i]) % MAX_SIZE;

    // Stop if the next slot is empty OR found the same string.
    while (wd->table[key].occupied && strcmp(wd->table[key].str, wordsDict[i]) != 0)
      key = (key + 1) % MAX_SIZE;

    // If this slot is empty, initialize before insert new idx.
    if (!wd->table[key].occupied)
    {
      wd->table[key].str = malloc((len + 1) * sizeof(*wd->table[key].str));
      memcpy(wd->table[key].str, wordsDict[i], (len + 1) * sizeof(*wd->table[key].str));
      wd->table[key].occupied = true;

      wd->table[key].capacity = INITIAL_CAPACITY;
      wd->table[key].idx = malloc(wd->table[key].capacity * sizeof(*wd->table[key].idx));
    }

    // If this string is already in the table, check for full capacity before insert new idx.
    else if (wd->table[key].size == wd->table[key].capacity)
    {
      wd->table[key].capacity *= 2;
      wd->table[key].idx = realloc(wd->table[key].idx,
                                   wd->table[key].capacity * sizeof(*wd->table[key].idx));
    }

    // Insert new idx.
    wd->table[key].idx[wd->table[key].size] = i;
    (wd->table[key].size)++;
  }

  return wd;
}

/*
idx1 = 0  100
idx2 = 50 51 55 56
- 2 pointers.
- Increase the smaller one.
*/
int wordDistanceShortest(WordDistance *obj, char *word1, char *word2)
{
  // Guarantee word1 and word2 exist in the dict.
  int key1 = hash((unsigned char *)word1) % MAX_SIZE;
  while (obj->table[key1].occupied && strcmp(obj->table[key1].str, word1) != 0)
    key1 = (key1 + 1) % MAX_SIZE;

  int key2 = hash((unsigned char *)word2) % MAX_SIZE;
  while (obj->table[key2].occupied && strcmp(obj->table[key2].str, word2) != 0)
    key2 = (key2 + 1) % MAX_SIZE;

  int i = 0, j = 0;
  int result = MAX_SIZE;
  int size1 = obj->table[key1].size;
  int size2 = obj->table[key2].size;
  while (i < size1 && j < size2)
  {
    int dist = abs(obj->table[key1].idx[i] - obj->table[key2].idx[j]);
    result = (result < dist) ? result : dist;

    if (obj->table[key1].idx[i] < obj->table[key2].idx[j])
      i++;

    else
      j++;
  }

  return result;
}

void wordDistanceFree(WordDistance *obj)
{
  if (!obj)
    return;

  for (int i = 0; i < MAX_SIZE; i++)
  {
    if (obj->table[i].occupied)
    {
      free(obj->table[i].str);
      free(obj->table[i].idx);
    }
  }
  free(obj->table);
  free(obj);
}
