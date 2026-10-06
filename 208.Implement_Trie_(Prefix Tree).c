/**
 * Your Trie struct will be instantiated and called as such:
 * Trie* obj = trieCreate();
 * trieInsert(obj, word);

 * bool param_2 = trieSearch(obj, word);

 * bool param_3 = trieStartsWith(obj, prefix);

 * trieFree(obj);
*/
#define MAX_CHAR 26

typedef struct Trie
{
  bool EOW;

  // struct Trie *children[26];
  struct Trie **children;
} Trie;

Trie *trieCreate()
{
  Trie *root = malloc(sizeof(*root));
  root->EOW = false;
  root->children = malloc(MAX_CHAR * sizeof(*root->children));
  for (int i = 0; i < MAX_CHAR; i++)
    root->children[i] = NULL;

  return root;
}

void trieInsert(Trie *obj, char *word)
{
  for (int i = 0; word[i] != '\0'; i++)
  {
    int child_idx = word[i] - 'a';

    if (obj->children[child_idx] == NULL)
      obj->children[child_idx] = trieCreate();

    obj = obj->children[child_idx];
  }

  obj->EOW = true;
}

/* search vs startWith
- Search: Does this path end a word?
- startWith: Does this path exist?
Ex: Insert "doggo"
search("dog") -> false because "g" is not EOW
startWith("dog") -> true
*/

bool trieSearch(Trie *obj, char *word)
{
  for (int i = 0; word[i] != '\0'; i++)
  {
    int child_idx = word[i] - 'a';

    if (obj->children[child_idx] == NULL)
      return false;

    obj = obj->children[child_idx];
  }

  return obj->EOW;
}

bool trieStartsWith(Trie *obj, char *prefix)
{
  for (int i = 0; prefix[i] != '\0'; i++)
  {
    int child_idx = prefix[i] - 'a';

    if (obj->children[child_idx] == NULL)
      return false;

    obj = obj->children[child_idx];
  }

  return true;
}

void trieFree(Trie *obj)
{
  if (!obj)
    return;

  for (int i = 0; i < MAX_CHAR; i++)
    trieFree(obj->children[i]);

  free(obj->children);
  free(obj);
}
