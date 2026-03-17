#include <stdio.h>
#include <stdlib.h>
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define TABLE_SIZE 10007

typedef struct Node {
    int key;
    int index;
    struct Node* next;
} Node;

int hash(int key) {
    unsigned int x = (unsigned int)key;
    x = x * 2654435761u;
    return x % TABLE_SIZE;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    Node* table[TABLE_SIZE] = {0};

    for (int i = 0; i < numsSize; i++) {
        int complement = target - nums[i];
        int h = hash(complement);

        Node* curr = table[h];
        while (curr) {
            if (curr->key == complement) {
                int* result = malloc(2 * sizeof(int));
                result[0] = curr->index;
                result[1] = i;
                *returnSize = 2;
                return result;
            }
            curr = curr->next;
        }

        h = hash(nums[i]);
        Node* newNode = malloc(sizeof(Node));
        newNode->key = nums[i];
        newNode->index = i;
        newNode->next = table[h];
        table[h] = newNode;
    }

    *returnSize = 0;
    return NULL;
}

int main()
{
	int return_size;
	int nums[3] = {3, 2, 4};
	int *result = twoSum(nums, 3, 7, &return_size);
	for (int i = 0; i < 2; i++) printf("%d ", result[i]);
	
	return 0;
}


