#define TABLE_SIZE 200003

typedef struct Entry
{
  int val;
  int last_idx;
  bool occupied;
} Entry;

int hash(int key)
{
  int h = key % TABLE_SIZE;

  if (h < 0)
    h += TABLE_SIZE;

  return h;
}

bool containsNearbyDuplicate(int *nums, int numsSize, int k)
{
  // Set all fields to 0.
  Entry *table = calloc(TABLE_SIZE, sizeof(*table));

  for (int i = 0; i < numsSize; i++)
  {
    // Find nums[i] in the hash table.
    int idx = hash(nums[i]);

    /*
    - Skip collision and mismatched values.
    - This will stop when either:
      + Found an empty slot to insert.
      + Found matched key value.
    */
    while (table[idx].occupied && table[idx].val != nums[i])
      idx = (idx + 1) % TABLE_SIZE;

    // If this slot is occupied -> The value already exists
    if (table[idx].occupied)
    {
      // If i - table[idx].last_idx <= k, return true.
      if (i - table[idx].last_idx <= k)
        return true;

      // Otherwise, update last_idx to i.
      else
        table[idx].last_idx = i;
    }

    // If this slot is not occupied -> First time see this number
    else
    {
      // Insert this number into the current slot.
      table[idx].val = nums[i];
      table[idx].last_idx = i;
      table[idx].occupied = true;
    }
  }

  free(table);
  return false;
}
